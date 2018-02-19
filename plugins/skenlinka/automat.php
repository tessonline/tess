<?php
require("tmapy_config.inc");
include(FileUp2(".admin/run2_.inc"));
require_once(FileUp2(".admin/config.inc"));
require_once(FileUp2(".admin/db/db_posta.inc"));
require_once(FileUp2(".admin/oth_funkce.inc"));
require_once(FileUp2(".admin/form_func.inc"));
require_once(FileUp2("html_header_full.inc"));
require(FileUp2("interface/.admin/soap_funkce.inc"));
require_once(FileUp2(".admin/security_obj.inc"));
include_once(FileUp2(".admin/status.inc")); 
require_once(FileUp2('.admin/upload_.inc')); 

set_time_limit(0);
$q=new DB_POSTA;
$id_user=468;

$cesta=$GLOBALS[CONFIG_POSTA][SCANNER][scanner_cesta];
$chybne  = array();
$oddelovac='-';
$USER_INFO = $GLOBALS["TMAPY_SECURITY"]->GetUserInfo($id);
//print_r($USER_INFO); Die();
$software_id='SCANNER';

if (!@$d = dir($cesta)) {
  $text='(AUTOMAT) - Neexistuje cesta ' . $val;
  WriteLog($software_id,$text,$session_id,1);
  die;
}

while($entry=$d->read())  {
  if ($entry<>'.' && $entry<>'..')
  {
    list($ev_cislo,$pripona)=explode('.',$entry);
    $id=PrevedCPnaID($ev_cislo);
    if (!$id) $id = 0;
    $sql='select id from posta where id='.$id;
    $q->query($sql);
    $pocet=$q->Num_Rows();
    if (!$id || $id<0 || $pocet==0)
      $chybne[]=$entry; 
    else
      $file_scan[$id]=$entry;
  }
}

//print_r($file_scan);

$uplobj=Upload(array('create_only_objects'=>true,'agenda'=>'POSTA','noshowheader'=>true));

if (count($file_scan)>0) {
  while (list($key,$val)=each($file_scan)) {
  //echo "Nactiam $key";
    $files=$uplobj['table']->getRecordsUploadForAgenda($key);
    $copy = true;

    UNSET($GLOBALS["ID"]);
    UNSET($GLOBALS["FILE_ID"]);

    $file = array(); $edit = false;
    while (list($key1,$val1)=each($files)) if ($val1[NAME]==$val) {$copy=true; $file = $val1; $edit = true;}

    $tmp_soubor=$cesta.'/'.$val;

    if ($copy) {
      if ($edit) {
        $GLOBALS['COSTIM']='archiv_a'; //archivuj puvodni
        $GLOBALS['show_typ']=2;
        $GLOBALS['archiv_file_system']=true;
        $GLOBALS['EDIT_ID']=$file[ID];
//        $GLOBALS['ID']=$file[ID];
        //$GLOBALS['EDIT_ID']=$file[FILE_ID];
      }
      else {
        unset($GLOBALS['COSTIM']);
        unset($GLOBALS['show_typ']);
        unset($GLOBALS['archiv_file_system']);
        unset($GLOBALS['EDIT_ID']);
      }
      $GLOBALS['DESCRIPTION'] = 'scan dokumentu';
      $GLOBALS['LAST_USER_ID'] = $id_user;
      $GLOBALS['CONVERT'] = false;
      $uplobj=Upload(array('create_only_objects'=>true,'agenda'=>'POSTA','noshowheader'=>true));
      $ret = $uplobj['table']->SaveFileToAgendaRecord($tmp_soubor, $key);
      if ($ret[err_msg]<>'') {
        $text ='Chyba pri uložení souboru '.basename($tmp_soubor).': '.$ret[err_msg]."";
        $text='(AUTOMAT) - '.$text;
        WriteLog($software_id,$text,$session_id, 1);
      } 
      else {

        $fp = fopen($tmp_soubor ,'r');
        $data = fread($fp, filesize($tmp_soubor));
        fclose($fp);
        $md5 = md5($data);

        $text = 'K dokumentu (<b>'.$key.'</b>) byl vložen soubor <b>' . basename($tmp_soubor) . '</b>, velikost: '.filesize($tmp_soubor).' bytes, MD5 ' . $md5;
        EedTransakce::ZapisLog($key, $text, 'DOC');

        $text='(AUTOMAT) - '.strip_tags($text);
        WriteLog($software_id,$text,$session_id);
        @unlink($tmp_soubor);
      }
    }
    else {
      @unlink($tmp_soubor);
    }

  }
}

foreach($chybne as $file) {
  $text = 'Tento soubor nebyl načten: ' . $file;
        $text='(AUTOMAT) - '.strip_tags($text);
        WriteLog($software_id,$text,$session_id,1);
}

echo 'Hotovo';
require_once(FileUp2("html_footer.inc"));
