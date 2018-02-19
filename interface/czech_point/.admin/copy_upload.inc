<?php
include(FileUp2('.admin/upload_fce_.inc'));
@include(FileUp2('.admin/db/db_upload.inc'));
include(FileUp2('.config/settings/agenda_path.inc'));
require_once(FileUp2('.admin/upload_.inc'));
//tak a ulozime soubor
$filename=$dokument['prilohy']['priloha'];
//$dir_arr=GetUploadDir('POSTA',$dokument_id);
$file = $dir_arr[0].$dir_arr[1].$filename['nazev'];
$uplobj=Upload(array('create_only_objects'=>true,'agenda'=>'POSTA','noshowheader'=>true,'skip_access'=>true)); 
$cesta=$GLOBALS[CONFIG_POSTA][HLAVNI][tmp_adresar];


//$upload_records = $uplobj['table']->GetRecordsUploadForAgenda($q->Record["ID"]);
//echo 'jsetum ';

$tmp_soubor = $cesta.substr(uniqid('a'),0,2).'-'.$filename['nazev'];
$data=base64_decode($filename['obsah']['!']);
if (strlen($data)<1) return VratChybu($session_id,'send_files','Není k dispozici obsah souboru '.$val["FILE_NAME"]);
$text='(COPY_UPLOAD) - ukladam dokument '.$dokument_id.' soubor '.$tmp_soubor;
WriteLog($software_id,$text,$session_id);

if (file_exists($tmp_soubor)) unlink($tmp_soubor);
if (!$fp=fopen($tmp_soubor,'w')) return VratChybu($session_id,'send_files','Chyba pri ulozeni tmp souboru '.$val["FILE_NAME"]);
fwrite($fp,$data);
fclose($fp);
$text='(COPY_UPLOAD) - soubor ulozen:'.$tmp_soubor;
WriteLog($software_id,$text,$session_id);

$GLOBALS['DESCRIPTION'] = 'application/octet-stream';
$GLOBALS['LAST_USER_ID'] = $GLOBALS["KONEKTOR"][$software_id]["LAST_USER_ID"];
$ret = $uplobj['table']->SaveFileToAgendaRecord($tmp_soubor, $dokument_id);
//print_r($ret);
if ($ret[err_msg]) {
  $text = "Nepovedlo se ulozit soubor " . $filename['nazev'];
  EedTransakce::ZapisLog($dokument_id, $text, 'DOC');

  return VratChybu($session_id,'send_files','Chyba pri ulozeni souboru '.$val["FILE_NAME"].': '.$ret[err_msg]);
}

  $text = "Vložen soubor " . $filename['nazev'];
  EedTransakce::ZapisLog($dokument_id, $text, 'DOC');


