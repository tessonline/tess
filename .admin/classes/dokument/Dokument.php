<?php
include_once('Temp.php');

class Dokument {


  //pole nazvu promennych ktere budou nahrazeny
  public $var_array = array();
  
  
  //cesta k souboru dokumentu
  protected $doc_path;
  protected $encoding = "WINDOWS-1250";
  
  protected $convert_array_db = array();
  
  public $is_odesl_prijmeni_firma = false;

  /*
   * Contructor
   * @author luma
   */
  function __construct() {
   }

  /*
   * Nastavi pole promennych ke cteni z dokumentu souboru
   * @param array $var_array pole promennych ke cteni z eml souboru
   */
  public function setVarArray($var_array = array ("Subject","Body")) {
    $this->var_array = $var_array;
  }
  
  /*
   * Nastavi cestu k dokumentu
   * @param string $doc_path cesta k souboru dokumentu
   */
  public function setDocumentPath($doc_path) {
    $this->doc_path = $doc_path;
  }
  
  public function addVars($v_array) {
    foreach ($v_array as $var) {
      $this->var_array[] = $var;
    }
  }
  
  public function toEnc($text) {
    $text = html_entity_decode($text,null,'UTF-8');
    return iconv('UTF-8', $this->encoding, $text);
  }

  public function setGlobals($data_item) {
    $size = sizeof($data_item);
    $var_array = array_slice($this->var_array, 0, $size, "" );
    $data_item = array_reverse($data_item);
    $i=0;
    foreach (array_reverse($var_array) as $var) {
      $glob_var = $var;
      if (isset($this->convert_array_db[$var])) {
        $glob_var = $this->convert_array_db[$var];
        if (($var == "ODESL_PRIJMENI_FIRMA")&&(strlen($data_item[$i])>0)) 
          $this->is_odesl_prijmeni_firma = true;
      }
      $GLOBALS[$glob_var] = $data_item[$i];
      $i++;
    }
  }
  
  public function setEncoding($enc) {
    $this->encoding = $enc;
  }
  
  public function upload($id,$filename = null,$agenda = 'POSTA') {
     if ($filename==null)
       $filename = $this->doc_path;
     include_once(FileUp2('.admin/upload_.inc'));
     $u=Upload(array('create_only_objects'=>true,'agenda'=>$agenda,'noshowheader'=>true));
     $ret = $u['table']->SaveFileToAgendaRecord($filename, $id);
     return $ret;
  }
  
  public function delTempDir() {
    $dir = dirname($this->doc_path);
    $temp = new Temp($dir,true);
    $temp->delTempDir();
  }

  public function getStringBetween($string, $start, $end){
    $string = ' ' . $string;
    $ini = strpos($string, $start);
    if ($ini == 0) return '';
    $ini += strlen($start);
    $len = strpos($string, $end, $ini) - $ini;
    return substr($string, $ini, $len);
  }
  
  public function getStringAfter($string,$find) {
    $arr = explode($find, $string);
    if (is_array($arr)&&sizeof($arr)>1)
      return $arr[1];
    else 
      return ""; 
  }
  
  public function detectEncoding ($string, $enc=null, $ret=null) {
    
    static $enclist = array(
      'Windows-1250','UTF-8','ISO-8859-1','ASCII',
      'Windows-1251', 'Windows-1252', 'Windows-1254','ISO-8859-1', 'ISO-8859-2', 'ISO-8859-3', 'ISO-8859-4', 'ISO-8859-5',
      'ISO-8859-6', 'ISO-8859-7', 'ISO-8859-8', 'ISO-8859-9', 'ISO-8859-10',
      'ISO-8859-13', 'ISO-8859-14', 'ISO-8859-15', 'ISO-8859-16',
    );
    
    $result = false;
    
    foreach ($enclist as $item) {
      $sample = iconv($item, $item, $string);
      if (md5($sample) == md5($string)) {
        if ($ret === NULL) { $result = $item; } else { $result = true; }
        break;
      }
    }
    
    return $result;
  }
  
  
}