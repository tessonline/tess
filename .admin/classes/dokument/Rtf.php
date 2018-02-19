<?php

include_once('Dokument.php');

class Rtf extends Dokument{

  
  //zdrojovy text souboru rtf
  protected $source;
    
  //pole obsahujici vsechny zpracovane soubory a id zaznamu
  public $files = array();
  
  private $zip_name;
  
  private $db;
  
  //id prave zpracovavaneho dokumentu
  private $id;
  
  
  
  private $convert_array_rtf = array (
    "prijmjmeno" => "příjmení jméno",    
    "Kobor" => "studijní program",
    "Kstprog" => "studijní obor",
    "datnarozen" => "dat. narození",
    "ulicecis" => "Ulice",
    "mesto" => "Město",
    "psc" => "PSČ",
    //"Kzemx" => "",
    //"kulicecis" => "",
    //"kmesto" => "",
    //"kpsc" => "",
    //"Kkzemx" => "",
    "Stip1" => "výše stipendia",
    "bankucetba" => "číslo účtu ze SIS",
    //"poradi" => ""
  );

     
  /*
   * Contructor
   * @author luma
   */
  function __construct($source = null,$var_array = null) {
    $this->convert_array_db = array(
      "JMENO" => "ODESL_JMENO",
      "PRIJMENI" => "ODESL_PRIJMENI",
      "prijmjmeno" => "ODESL_PRIJMENI",
      "ulicecis" => "ODESL_ULICE",
      "CP" => "ODESL_CP",
      "mesto" => "ODESL_POSTA",
      "psc" => "ODESL_PSC",
      "datnarozen" => "ODESL_DATNAR",
      "ODESL_PRIJMENI_FIRMA" => "ODESL_PRIJMENI",
      "ODESL_DATSCHR" => "ODESL_DATSCHRANKA"
    );
    $this->source = $source;
    $this->var_array = $var_array;
  }

  /*
   * Ze zdrojoveho rtf souboru vytvori novy soubor ve kterem nahradi promenne a zaroven nastavi promenne do GLOBALS
   * @param $destination cesta k cilovemu rtf souboru 
   * @param $id id zaznamu - nepovinne
   * @param $to_file - vystup ukladat do souboru
   */
  public function process($destination,$data_item,$id=0,$to_file = true) {
    $this->id = $id;
    $this->files[] = array('ID' => $id,'FILENAME' => $destination);
    
    //$str=file_get_contents($this->source);
    $str = $this->source;
    
    foreach(array_keys($data_item) as $key){
      $data_item[$key] = iconv('UTF-8',$this->encoding, $data_item[$key]);
    }
    
    $i=0;
    foreach ($this->var_array as $var) {
    //  $rtf_var = $var;
    //  if (isset($this->convert_array_rtf[$var])) $rtf_var = $this->convert_array_rtf[$var];
    //  $str=str_ireplace("%".$rtf_var."%", $data_item[$i],$str);
      
      if (isset($this->convert_array_rtf[$var])) 
        $rtf_var[] = "%".$this->convert_array_rtf[$var]."%"; 
        else
        $rtf_var[] = "%".$var."%";
      $i++;
    }
    $this->defaultValuesRtf($rtf_var,$data_item);
    if (isset($this->db)) $this->oldRtfValues($rtf_var,$data_item);
   // $str=str_ireplace(array_reverse($rtf_var), array_reverse($data_item), $str);
    $str=str_ireplace($rtf_var, $data_item, $str);
    if ($to_file===true)
      file_put_contents($destination, $str);
    else 
      return $str;
  }
  
  
  private function defaultValuesRtf(&$rtf_var,&$data_item) {
      $rtf_var[] = '%DATUM_PODATELNA_PRIJETI%';
      $data_item[] = date('d.m.Y H:i:s');      
  }
  
  /*private function rep($key,$values) {
    if (array_key_exists($key,$values)) 
      return $values[$key];
    else 
      return "";
  }*/
  
  private function oldRtfValues(&$rtf_var,&$data_item) {
    
    $q = $this->db;
    
    
    //"%ROZDELOVNIK%"

    
    $values = array_combine ( $rtf_var,$data_item );
    $rtf_var[] = '%DATUM_PRIJETI%';
    $data_item[] = date('d.m.Y H:i:s');

    $doc = LoadClass('EedDokument', $this->id);
    $rtf_var[] = '%CISLO_JEDNACI%'; 
    $data_item[] = $doc->cislo_jednaci;
       
    $rtf_var[] = '%CAROVY_KOD%';
    $data_item[] = $doc->barcode;

    $cjObject = LoadClass('EedCj', $this->id);
    $cj = $cjObject->GetCjInfo($this->id);
    $rtf_var[] = '%CISLO_SPISU%'; 
    $data_item[] = $cj['CELE_CISLO'];
    
    $rtf_var[] = '%VEC_DOPISU%';
    $data_item[] = $this->toEnc($doc->vec);
    
    $rtf_var[] = '%ODBOR_REFERENTA%';
    $data_item[] = $this->toEnc(UkazOdbor($cj['ODBOR'],false,true));

    if ($cj['ODESL_CP']) $cislo = $cj['ODESL_CP'];
    if ($cj['ODESL_COR']) $cislo = $cj['ODESL_COR'];
    if (($cj['ODESL_COR']) && ($cj['ODESL_CP'])) $cislo = $cj['ODESL_CP']."/".$cj['ODESL_COR'];
    
    $psc_bez_mezer = str_replace(' ', '', $cj['ODESL_PSC']);
    $psc = substr($psc_bez_mezer,0,3)." ".substr($psc_bez_mezer,3,2);
    
    $rtf_var[] = '%ADRESA_ODESILATELE%';
    $data_item[] = $this->toEnc($cj['ODESL_TITUL']." ".$cj['ODESL_JMENO']." ".$cj['ODESL_PRIJMENI'].
                    " \\par ".$cj['ODESL_ULICE']." ".$cislo." \\par ".$psc." ".$cj['ODESL_POSTA']);
    
    if (isset($cj['ODESL_OSLOVENI']))
    {
      $q->query('select nazev from posta_cis_osloveni where id = '.$cj['ODESL_OSLOVENI']); 
      $q->Next_Record();
      $rtf_var[] = '%ADRESA_OSLOVENI%';
      $data_item[] = $this->toEnc($q->Record["NAZEV"]);
    }    
    
    $rtf_var[] = '%ADRESA_JMENO%'; 
    $data_item[] = $this->toEnc($cj['ODESL_TITUL']." ".$cj['ODESL_JMENO']." ".$cj['ODESL_PRIJMENI']);
    
    $rtf_var[] = '%ADRESA_ULICE%';
    $data_item[] = $this->toEnc($cj['ODESL_ULICE']." ".$cislo);
        
    $rtf_var[] = '%ADRESA_MESTO%';
    $data_item[] = $this->toEnc($psc."  ".strtoupper($cj['ODESL_POSTA']));
    
    $rtf_var[] = '%ADRESA_ODD%';
    $data_item[] = $this->toEnc($cj['ODESL_ODD']);
    
    $rtf_var[] = '%ADRESA_KONTOSOBA%';
    $data_item[] = $this->toEnc($cj['ODESL_OSOBA']);
    
    $USER_INFO = $GLOBALS["POSTA_SECURITY"]->GetUserInfo();
    if ($GLOBALS[CONFIG][OTOCIT_JMENO_ZPRACOVATELE])
      $REFERENT_JMENO = $USER_INFO["FNAME"]." ".$USER_INFO["LNAME"];
      else
        $REFERENT_JMENO = $USER_INFO["LNAME"]." ".$USER_INFO["FNAME"];
        if ($USER_INFO["TITLE_1"]) $REFERENT_JMENO = $USER_INFO["TITLE_1"]." ".$REFERENT_JMENO;
        if ($USER_INFO["TITLE_2"]) $REFERENT_JMENO = $REFERENT_JMENO.", ".$USER_INFO["TITLE_2"];
    
    $rtf_var[] = '%UREDNIK_JMENO%';
    $data_item[] = $this->toEnc($REFERENT_JMENO);    
    
    $rtf_var[] = '%UREDNIK_JEN_PRIJMENI%';
    $data_item[] = $this->toEnc($USER_INFO["LNAME"]);
    
    $rtf_var[] = '%UREDNIK_TELEFON%';
    $data_item[] = $this->toEnc($USER_INFO["PHONE"]);
    
    $rtf_var[] = '%UREDNIK_EMAIL%';
    $data_item[] = $this->toEnc($USER_INFO["EMAIL"]);
    
    $rtf_var[] = '%UREDNIK_FAX%';
    $data_item[] = $this->toEnc($USER_INFO["FAX"]);
      
   /*    if ($GLOBALS[CONFIG][OTOCIT_JMENO_ZPRACOVATELE])
         $REFERENT_JMENO = $cjObject->jmeno." ".$cjObject->prijmeni;
         else
           $REFERENT_JMENO = $cjObject->prijmeni." ".$cjObject->jmeno;
        //   if ($USER_INFO["TITLE1"]) $REFERENT_JMENO = $USER_INFO["TITLE1"]." ".$REFERENT_JMENO;
        //   if ($USER_INFO["TITLE2"]) $REFERENT_JMENO = $REFERENT_JMENO." ".$USER_INFO["TITLE2"];
      
           $rtf_var[] = '%UREDNIK_JMENO%';
           $data_item[] = $this->toEnc($REFERENT_JMENO);
      
           $rtf_var[] = '%UREDNIK_JEN_PRIJMENI%';
           $data_item[] = $this->toEnc($cjObject->prijmeni);
            
           $rtf_var[] = '%UREDNIK_EMAIL%';
           $data_item[] = $this->toEnc($cjObject->email);
      */
      
      
    
    $rtf_var[] = '%JEJICH_CJ%';
    $data_item[] = $doc->jejich_cj;
    $rtf_var[] = '%JEJICH_CJ_DNE%';
    $data_item[] = $this->toEnc($doc->jejich_cj_dne);
    
    if ($cj['SKARTACE'])
    {
      $q->query('select text from cis_posta_skartace where id = '.$cj['SKARTACE']);
      $q->Next_Record();
      $rtf_var[] = '%SPIS_ZNAK%';
      $data_item[] = $this->toEnc($q->Record["TEXT"]);
    }
    
    
    /*$rtf_var[] = '%ROZDELOVNIK%';
    $data_item[] =*/

    $rtf_var[] = '%DATUM_NAROZENI%';
    $data_item[] = $doc->datum_narozeni;
    
    $su = LoadClass('EedSpisUzelKontakt', $doc->odbor);

    $rtf_var[] = '%SU_ADRESA%';
    $data_item[] = $su->adresa;
    
    $rtf_var[] = '%SU_TELEFON%';
    $data_item[] = $su->telefon;
    
    $rtf_var[] = '%SU_MOBIL%';
    $data_item[] = $su->mobil;
    
    $rtf_var[] = '%SU_EMAIL%';
    $data_item[] = $su->email;

    $rtf_var[] = '%SU_WEB%';
    $data_item[] = $su->web;
    
    $rtf_var[] = '%DNESNI_DATUM%';
    $data_item[] = date('d.m.Y');
  }
  
  /*
   * Vrati pole id vsech zaznamu
   */
  public function getIdArray() {
    $this->id_array();
  }
  
  /*
   * Nastavi promenne do GLOBALS
   * @param array $data_item pole hodnot promennych
   */
  public function setGlobals($data_item) {
    parent::setGlobals($data_item);
    $this->checkDefaultValues();
  }
  
  private function checkDefaultValues() {
    
    if (!isset($GLOBALS['ROK'])) $GLOBALS['ROK'] = date("Y");
    
    if (!isset($GLOBALS['ODES_TYP'])) {
      if ((isset($GLOBALS['ODESL_JMENO']))||(isset($GLOBALS['ODESL_PRIJMENI']))) 
        $GLOBALS['ODES_TYP'] = 'O'; 
        else
          $GLOBALS['ODES_TYP'] = 'P';
    }
    
    if ($this->is_odesl_prijmeni_firma) 
      $GLOBALS['ODES_TYP'] = 'P';
    
    if (!isset($GLOBALS['DATUM_PODATELNA_PRIJETI'])) $GLOBALS['DATUM_PODATELNA_PRIJETI'] = date('Y-m-d H:i:s'); 
    if (isset($GLOBALS['ODESL_DATSCHRANKA'])&&$GLOBALS['ODESL_DATSCHRANKA']!="") {
//    if (isset($GLOBALS['DAT_SCHR']) || isset($GLOBALS['DATOVA_SCHRANKA'])|| isset($GLOBALS['DS']) || isset($GLOBALS['ODESL_DATSCHRANKA'])) {   
  /*    if (!isset($GLOBALS['ODESL_DATSCHRANKA']))
        $GLOBALS['ODESL_DATSCHRANKA'] = isset($GLOBALS['DAT_SCHR']) ? $GLOBALS['DAT_SCHR'] : (isset($GLOBALS['DATOVA_SCHRANKA']) ? $GLOBALS['DATOVA_SCHRANKA'] : $GLOBALS['DS']);*/
      $GLOBALS['VLASTNICH_RUKOU'] = 9;
      $GLOBALS['TYP_DOKUMENTU'] = 'D';
      $GLOBALS['DOPORUCENE'] = 5;
    }
    
  }
  
  
  
  public function createZip($zip_name) {
    $this->zip_name = $zip_name;
    $zip = new ZipArchive;
    $zip->open($this->zip_name, ZipArchive::CREATE);
    foreach ($this->files as $file) {
      $zip->addFile($file['FILENAME']);
    }
    $zip->close();
  }
   
  public function downloadZip() {   
    ?>  
    <script>
    	window.location.href = "download.php?file=<?php echo $this->zip_name; ?>";
    </script>;
    <?php 
  }
  
  public function getTableData() {
    foreach ($this->files as &$file) {
       $file['FILENAME'] = basename($file['FILENAME']);
    }
    return $this->files;
  }
  
  public function getTableConfig() {
    $TABLE_CONFIG['schema'][] = array ('field'=>"ID",'label'=>"ID dokumentu");
    $TABLE_CONFIG['schema'][] = array ('field'=>"FILENAME",'label'=>"Příloha");
    return $TABLE_CONFIG;
  }
  
 
  public function setDb($db) {
    $this->db = $db;
  }
  
}

