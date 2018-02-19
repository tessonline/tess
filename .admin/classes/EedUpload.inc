<?php
include_once(FileUp2('interface/.admin/soap_funkce.inc'));
include_once(FileUp2('.admin/classes/dokument/Temp.php'));
include_once($GLOBALS['TMAPY_LIB'].'/upload/functions/SOAP_602_print2pdf.php');

class EedUpload {
  
  private $uplobj;
  public $uplobj_records;
  private $agenda_ident = 'POSTA';
  private $record_id;
  public $services602;
  public $files = array();

//  public function __construct($record_id) {
  public function EedUpload($record_id) {
    global $CONFIG;
    include_once(FileUp2('.admin/upload_.inc'));

    $this->record_id = $record_id;  
    $this->uplobj = Upload(array(
              'create_only_objects' => true,
              'agenda' => $this->agenda_ident,
              'noshowheader'=>true)
            );

    $this->uplobj_records = $this->uplobj['table']->GetRecordsUploadForAgenda($this->record_id);
    if (count($this->uplobj_records)>0) {
      return $this->uplobj_records;
    }
    else
      return false;
  }
  
  public function refreshUploadRecords() {
    $this->uplobj_records = $this->uplobj['table']->GetRecordsUploadForAgenda($this->record_id);
  }
  
  public function getFile($file) {
    if (count($this->uplobj_records)>0) {

      foreach($this->uplobj_records as $key => $val) {
        if ($file == $val['NAME']) {
          return $val;
        }
      }
    }
  }

  function set602_services() {
    if ($GLOBALS['SERVER_CONFIG']["UPLOAD_CONFIG"]["MODULES"]["table"]["STORAGE"]["Print2PDF_SERVICE"]) {
      $this->services602 = new SOAP_602_print2pdf($GLOBALS['SERVER_CONFIG']["UPLOAD_CONFIG"]["MODULES"]["table"]["STORAGE"]["Print2PDF_SERVICE"]);
    }
    else
      return false;
  }
  public function getContent($val) {
    $data = $this->uplobj['table']->GetUploadFiles($val);
    return $data;
  }

  public function ConvertFile($file) {
    $val = $this->getFile($file);
    if ($val['NAME']) {
      if (!$this->services602) $this->set602_services();

      try {

        if ($GLOBALS['CONFIG']['USE_CUL_ONLINE_EDIT']) {
          $ret = $this->uplobj['table']->stg_obj->getInfoPDF($val);
          $name = $val['NAME'] . '.pdf';

          if (!$ret['pdf']) return false;
          $ret2 = $this->uplobj['table']->stg_obj->getInfoPDF(array('DIRECTORY' => $ret['pdf']));
          $properties = $this->uplobj['table']->config['AGENDA_PROPERTIES'];
          $properties['DB_NAME'] = $this->uplobj['table']->config['DB_NAME']?$this->uplobj['table']->config['DB_NAME']:'DB_DEFAULT';
          $properties['AGENDA_ID'] = 'ID';
          $properties['AGENDA_TABLE'] = $this->uplobj['table']->config['TABLE'];
          $properties['NO_TABLE'] = true; //preskoceni access
          $vals = $val;
          $vals['TYPEFILE'] = $ret2['mimeType'];
          $vals['FILESIZE'] = $ret2['size'];
          $vals['NAME'] = $name;
          $vals['DIRECTORY']  = $ret['pdf'];
          $vals['LAST_DATE'] = Date('Y-m-d');
          $vals['OWNER_ID'] = $val[LAST_USER_ID];
          $vals['CONVERTED'] = 1;
          $vals['EDIT_ID'] = $val['ID'];
          foreach($properties as $name => $value) $GLOBALS['PROPERTIES'][$name] = $value;
          foreach($vals as $name => $value) $GLOBALS[$name] = $value;
          //unset($GLOBALS['ID']);
          $GLOBALS['NEW_ID_UPLOAD'] = Run_(array('outputtype'=>1, 'no_unsetvars'=>true,"to_history" =>true));
          return true;
        }
        else {
          $res = $this->services602->ConvertUploadFile($val['NAME'], $val["DIRECTORY"]);
  //      $tmp_soubor_x = TxtEncoding4Soap($GLOBALS[CONFIG_POSTA][HLAVNI][tmp_adresar].$res[0]);
          $tmp_soubor_x = $GLOBALS[CONFIG_POSTA][HLAVNI][tmp_adresar].$res[0];
          $tmp_soubor = $GLOBALS[CONFIG_POSTA][HLAVNI][tmp_adresar].$res[0];
          $data_save = $res[1];
          if (is_file($tmp_soubor_x)) unlink($tmp_soubor_x);
          if (strlen($data_save)<1) return 'Není k dispozici obsah souboru ';
          if (!$fp = fopen($tmp_soubor_x, 'w')) return 'Chyba pri ulozeni tmp souboru ' . $tmp_soubor;
          fwrite($fp, $data_save);
          fclose($fp);
          chmod($tmp_soubor_x, 0777);

          $old_edit_id = $GLOBALS['EDIT_ID'];
          $old_private = $GLOBALS['PRIVATE'];

          $GLOBALS['ID'] = $val[ID];
          $GLOBALS['FILE_ID'] = $val[ID];
          $GLOBALS['COSTIM'] = 'archiv_a'; //archivuj puvodni
          $GLOBALS['show_typ']=2;
          $GLOBALS['EDIT_ID'] = $val[ID];
          $GLOBALS['UPL_FILE'] = $res[0];
          $GLOBALS['LAST_DATE'] = Date('Y-m-d');
          $GLOBALS['OWNER_ID'] = $val[LAST_USER_ID];
          $GLOBALS['CONVERTED'] = 1;

          $ret = $this->uplobj['table']->SaveFileToAgendaRecord($tmp_soubor, $this->record_id);
          if ($ret['err_msg']<>'') return $ret['err_msg'];
          $md5 = md5($data_save);
          $text = 'Provedena konverze souboru <b>' . $val['NAME'] . '</b> do formátu PDF. K dokumentu (<b>'.$this->record_id.'</b>) byl vložen soubor <b>' . basename($tmp_soubor_x) . '</b>, velikost: '.filesize($tmp_soubor_x).' bytes, MD5 ' . $md5;;
          EedTransakce::ZapisLog($this->record_id, $text, 'KONVERZE', $user_id);

          $GLOBALS['EDIT_ID'] = $old_edit_id;
          $GLOBALS['PRIVATE'] = $old_private;

          /*      if ($unset_edit_id)
           unset($GLOBALS['EDIT_ID']);
           if ($unset_edit_id)
           unset($GLOBALS['PRIVATE']);*/
        }
        return true;
      }
      catch (Exception $e) {
//           echo '<span style="color: red; font-weight: bold;">';
//           echo $e;
//           echo '</span><br />';
          return false;
      }
    }

    return 'soubor nenalezen';
  }
  
  public function saveFile($name,$content,$uid) {
    try {      
      $temp = new Temp($GLOBALS['CONFIG_POSTA']['HLAVNI']['tmp_adresar']);
      $tmp_file =  $temp->getTempDir().'/'.$name;     
      file_put_contents($tmp_file,$content);
      //chmod($tmp_file, 0777);
      include(FileUp2(".admin/run2_.inc"));
      $res = $this->uplobj['table']->SaveFileToAgendaRecord($tmp_file,$this->record_id);
      $temp->delTempDir();
      return $res;
    }
    catch (Exception $e) {
      return false;
    }
  }

/*  public function rtfToDoc($source_path) {
    phpinfo();
    $dir = dirname($source_path);
    $dest_path = $dir."/".basename($source_path,".rtf").".doc";
    $dest_path = $dir."/".basename($source_path,".rtf").".doc";
    /*require_once(FileUp2('lib/PhpWord/PhpWord.php'));
    $phpWord = new PhpWord();
    require_once(FileUp2('lib/PhpOffice/PhpWord/IOFactory.php'));
    $d = copy("./lib");
    chdir($d);
    $phpWord =  \PhpOffice\PhpWord\IOFactory::load($source_path,"RTF");
    $x = 1;
    
    
  }*/



}
