<?php
require("tmapy_config.inc");
header("Cache-Control: public, must-revalidate");
header("Pragma: hack");
require(FileUp2(".admin/upload_.inc"));
include_once(FileUp2("interface/.admin/upload_funkce.inc"));


if ($GLOBALS['HTTP_POST_FILES']['UPLOAD_FILE']) {
  $tmp_file = $GLOBALS['HTTP_POST_FILES']['UPLOAD_FILE']['tmp_name'];
  if (!is_array($tmp_file)) {
    $tmp = $tmp_file;
    $tmp_file = array();
    $tmp_file[] = $tmp
    ;
  }
  foreach($tmp_file as $file) {
    if (strpos($file, '.pdf')) {
      $fp = fopen($file, 'r');
      $data = fread($fp, filesize($file));
      if (JePodepsanyDokument($data, 0)) {
        $GLOBALS['DESCRIPTION'] = 'el. podepsano';
      }
    }
  }
}
if ($GLOBALS['RECORD_ID']>0) {
  //kontrola, abych nevidel cizi dokumenty
  $idOLD = $GLOBALS['ID'];
  $GLOBALS['ID'] = $GLOBALS['RECORD_ID'];
	EedTools::MaPristupKCteniDokumentu($idOLD, 'zobrazeni uploadu');
  $GLOBALS['ID'] = $idOLD;
}


$q=new DB_POSTA;
$PROPERTIES['UPLOAD_CONFIG']['USE_ANONYM_ACCESS'] = false;

$GLOBALS['use_private_access'] = false;
$GLOBALS['MUZE_DUVERNE'] = false;
$co=StrTok($GLOBALS["QUERY_STRING"], '&');


if ($GLOBALS['RECORD_ID'] && $GLOBALS['FILE_ID'] !=-1) {

  require(FileUp2("html_header_full.inc"));
  $cj_obj = LoadClass('EedCj',$GLOBALS['RECORD_ID']);
  $caption = $cj_obj->cislo_jednaci;
  echo '<h1 align="center">'.$caption.'</h1>';
  require(FileUp2("html_footer.inc"));

}

if (HasRole("cist-dokument-do-vlastnich-rukou")) $GLOBALS['MUZE_DUVERNE'] = true; 

if ($GLOBALS['RECORD_ID'] && !$GLOBALS['EDIT_ID']) { //jde o insert souboru

  $spis_znaky_duverne = explode(',', $GLOBALS['CONFIG_POSTA']['HLAVNI']['SPISOVE_ZNAKY_DUVERNE']);
  
  $spisovna = LoadClass('EedSpisovna', $GLOBALS['RECORD_ID']);

  if (in_array($spisovna->spisZnakKod, $spis_znaky_duverne)) {
    $GLOBALS['MUZE_DUVERNE'] = true;
//    $GLOBALS['PRIVATE'] = 'y';
  }
}

if (!$GLOBALS['FILE_ID'] && !HasRole("cist-dokument-do-vlastnich-rukou")) {
  $USER_INFO = $GLOBALS["POSTA_SECURITY"]->GetUserInfo(); 
  $REFERENT = $USER_INFO["ID"];

  if ($GLOBALS['EDIT_ID'] && !$GLOBALS['RECORD_ID']) {
    $sql = 'select * from files where id='.$GLOBALS['EDIT_ID'];
    $q->query($sql); $q->Next_Record(); $GLOBALS['RECORD_ID']=$q->Record['RECORD_ID'];
    if ($q->Record['PRIVATE'] == 'y') {
      $GLOBALS['MUZE_DUVERNE'] = true;
    }
  }

  if ($GLOBALS['RECORD_ID']) {
    $sql = 'select referent,private,superodbor from posta where id='.$GLOBALS['RECORD_ID'];
    $q->query($sql); $q->Next_Record(); $data=$q->Record;

    //nacteme vedouci pracovniky
//     $userObj = LoadClass('EedUser', $REFERENT);
//     $vedouci_array = $userObj->VratNadrizeneVedouci($data['REFERENT']);
//
//     //jestli jsem nadrizeny vedouci referenta, pak pravo na soubor mam
//     if (in_array($REFERENT, $vedouci_array) && $data['SUPERODBOR'] == VratSuperOdbor()) $GLOBALS['MUZE_DUVERNE'] = true;
    

    if ($data['PRIVATE']==1 && !HasRole('spravce')) {
      if ($data['REFERENT']<>$REFERENT) {
         EedLog::writeLog('Nepovolený přístup k souborům', array('ID'=>$GLOBALS['RECORD_ID'], 'chyba'=>true));
         $USER_INFO = $GLOBALS["POSTA_SECURITY"]->GetUserInfo();
         $user_id = $USER_INFO['ID'];
         $EedUser = LoadClass('EedUser', $USER_INFO['ID']);
         $text = 'Uživatel <b>' . $EedUser->cele_jmeno . '</b> (' . $EedUser->id_user. ') se snažil číst soubory u dokumentu <b>' . $GLOBALS['RECORD_ID'] . '</b>, na které nemá oprávnění.';
         EedTransakce::ZapisLog(0, $text, 'SYS', $user_id);
          
         require(FileUp2("html_header_full.inc"));
         echo '<h1>Nemáte právo na tyto soubory!</h1>';
         echo '<p>Tento záznam je označen příznakem Do vlastních rukou - tyto soubory může číst pouze ten, kdo je uveden jako zpracovatel dokumentu.';
         echo '</p>';
         echo '<input type="button" name="Zavřít" value="   Zavřít okno   " onclick="window.close();" class="btn"> ';
         require(FileUp2("html_footer.inc"));
         Die();
    
      }
    }
   
    //nastavime, ze privatni videt nemame (ostatni lidi)
    $PROPERTIES['UPLOAD_CONFIG']['USE_PRIVATE_ACCESS'] = false;
    
    if ($GLOBALS['MUZE_DUVERNE']) $PROPERTIES['UPLOAD_CONFIG']['USE_PRIVATE_ACCESS'] = false;

  }
}

if ($GLOBALS['RECORD_ID']) @EedLog::writeLog('Zobrazení seznamu souborů', array('ID'=>$GLOBALS['RECORD_ID']));
if ($GLOBALS['FILE_ID']) @EedLog::writeLog('Zobrazení obsahu souboru id='.$GLOBALS['FILE_ID'], array('ID'=>$GLOBALS['RECORD_ID']));

if ($GLOBALS['DELETE_ID']>0) {
  $sql = 'select * from ' .$SERVER_CONFIG['UPLOAD_CONFIG']['MODULES']['table']['TABLE'] . ' where id='.$GLOBALS['DELETE_ID'];
  $q->query($sql);
  $q->Next_Record();
  if ($q->Record['PRIVATE'] == 'y') {
    include_once(FileUp2('.admin/upload/table_func_posta.inc'));
    $muze_duverne = false;
    $muze_duverne = MuzeDuverne($q->Record['RECORD_ID'], $q->Record['OWNER_ID']);
    if (!$muze_duverne) Die('<br/><br/><h3>Nemáte právo pro editaci tohoto záznamu.</h3>');
  }
}

if ($GLOBALS['DELETE_ID'] && $GLOBALS['show_typ'] == 2) {
  if ($GLOBALS['DELETE_ID']>0) {
    $sql = 'select * from ' .$SERVER_CONFIG['UPLOAD_CONFIG']['MODULES']['table']['TABLE'] . ' where id='.$GLOBALS['DELETE_ID'];
    $q->query($sql);
    $q->Next_Record();
    $text = 'U dokumentu (<b>'.$q->Record['RECORD_ID'].'</b>) byl smazán soubor <b>' . $q->Record['NAME'] . '</b>, velikost: '.$q->Record['FILESIZE'].' bytes';
    EedTransakce::ZapisLog($q->Record['RECORD_ID'], $text, 'DOC');
  }
}

$md5 = array();
$vlozene_soubory = array();
if ($_FILES) {
  $file_temp = $_FILES['UPLOAD_FILE']['tmp_name'];
  if (!is_array($file_temp) && $file_temp<>'') {
    $temp = $file_temp;
    $file_temp = array();
    $file_temp[] = $temp;
  }
  if (!is_array($file_temp) && $file_temp=='') $file_temp = array();
  foreach($file_temp as $key => $file) {
    $fp = fopen($file ,'r');
    $data = @fread($fp, $_FILES['UPLOAD_FILE']['size'][$key]);
    fclose($fp);
    $vlozene_soubory[$key]['NAME'] = $_FILES['UPLOAD_FILE']['name'][$key];
    $vlozene_soubory[$key]['SIZE'] = $_FILES['UPLOAD_FILE']['size'][$key];
    $vlozene_soubory[$key]['MD5'] = md5($data);
    $vlozene_soubory[$key]['PRIVATE'] = $GLOBALS['PRIVATE'];
  }
}

if ($show_typ ==4 && $HISTORY_ID) {
  $caption = "Předchozí verze souboru";

//$sql = 'select id,null,record_id,name,directory,filesize,typefile,description,anonym,private,last_user_id,owner_id,last_date,last_time,version from ' .$SERVER_CONFIG['UPLOAD_CONFIG']['MODULES']['table']['TABLE'] . ' where id=' . $HISTORY_ID.'
//UNION select id,id_h,record_id,name,directory,filesize,typefile,description,anonym,private,last_user_id,owner_id,last_date,last_time,version from ' .$SERVER_CONFIG['UPLOAD_CONFIG']['MODULES']['table']['TABLE'] . '_h where id=' . $HISTORY_ID.'';
$sql = 'select id,id_h,record_id,name,directory,filesize,typefile,description,anonym,private,last_user_id,owner_id,last_date,last_time from ' .$SERVER_CONFIG['UPLOAD_CONFIG']['MODULES']['table']['TABLE'] . '_h where id=' . $HISTORY_ID.'';

require(FileUp2('html_header_full.inc'));
$count = Table(array(
  'tablename' => 'denik',
  'setvars' => true,
  'caption' => $caption,
  'showupload' => false,
  'showhistory' => false,
  'showinfo' => true,
  'showedit' => false,
  'showdelete' => false,
  'sql' => $sql,
  'schema_file' => '.admin/upload/table_schema.inc',
  'page_size' => '100',
));

require(FileUp2('html_footer.inc'));

Die();

}
else {
  Upload(array());
  
}

if ($GLOBALS['show_typ'] == 2 && $GLOBALS['RECORD_ID']>0 && count($vlozene_soubory)>0) {
  foreach($vlozene_soubory as $soubor) {
    if ($soubor['PRIVATE']) $add = ' v režimu <b>vyhrazené</b>';
    $text = 'K dokumentu (<b>'.$GLOBALS['RECORD_ID'].'</b>) byl vložen soubor <b>' . $soubor['NAME'] . '</b>, velikost: '.$soubor['SIZE'].' bytes, MD5 ' . $soubor['MD5']. $add;
    EedTransakce::ZapisLog($GLOBALS['RECORD_ID'], $text, 'DOC');
  }
}

if ($GLOBALS['RECORD_ID'] && $co<>'insert') {
  $uplobj=Upload(array('create_only_objects'=>true,'agenda'=>'POSTA','noshowheader'=>true));
  $upload_records = $uplobj['table']->GetRecordsUploadForAgenda($GLOBALS['RECORD_ID']);
  $pocet=count($upload_records);
  if ($pocet==0) $img='folder_empty'; else $img='folder_full';
  $size = 0; $vysl = '0B';
  foreach($upload_records as $soubor) $size=$size+$soubor['FILESIZE'];
  if ($size>1024) {$size = round($size/1024); $vysl = $size . ' KB';}
  if ($size>1024) {
    $size = round($size/1024, 1); 
    $vysl = $size . ' MB';
    IF ($size>10) $img = 'unhappy'; 
  }
  
  reset ($GLOBALS["CONFIG_POSTA"]["PLUGINS"]);
  foreach($GLOBALS["CONFIG_POSTA"]["PLUGINS"] as $plug_name => $plug) {
    if ($plug['enabled']){
      $file = FileUp2('plugins/'.$plug['dir'].'/ug_file_end.php');
      if (File_Exists($file)) include($file);
    }
  }
  
  echo '<table height=150><tr><td valign=top>';
  echo '<span class="caption">Celková velikost souborů je ' . $vysl . '</span>'; 
  echo '</td></tr></table>';
}

echo '<p>&nbsp;</p>';


