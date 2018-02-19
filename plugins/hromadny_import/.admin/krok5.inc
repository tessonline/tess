<?php
include_once(FileUp2('.admin/classes/dokument/Zip.php'));
include_once(FileUp2('.admin/classes/dokument/PDF.php'));
include_once(FileUp2('.admin/classes/dokument/Temp.php'));
include_once(FileUp2('.admin/classes/EedImport.inc'));
//echo '<p><span class="caption">'.$GLOBALS['RSTR_IMPORT']['import_download'].'</span></p>';
$is_pdf = $GLOBALS['PDF'];
$log = ($is_pdf)? 'PDF download' : 'ZIP download';
ZapisLog($log);

$table = $GLOBALS['PROPERTIES']['AGENDA_TABLE'];
$tid = $id;

$sql = 'SELECT id_posta FROM ' . $table .'_POSTA WHERE id_import=' . intval($id);
$log = 'SQL: ' . $sql;
ZapisLog($log);
$q->query($sql);

$id_array = array();
while ($q->Next_Record()) {
  $id_array[] =  $q->Record['ID_POSTA'];
}

$uplobj = Upload(array(
  'create_only_objects' => true,
  'agenda' => 'POSTA',
  'noshowheader'=>true)
    );

$temp = new Temp($GLOBALS['CONFIG_POSTA']['HLAVNI']['tmp_adresar']);
$temp2 = new Temp($GLOBALS['CONFIG_POSTA']['HLAVNI']['tmp_adresar']);

$template_names = EedImport::getTemplateNames($tid);


$File = ($is_pdf) ? "PDF" : "Zip";
$i=0;
//if ($is_pdf) {
  $file = array();
  foreach ($template_names as $template_name) {
    $path_parts = pathinfo($template_name);
    $template_name = $path_parts['filename'];
    $file_name = $temp->getTempDir($template_name.($is_pdf ? '.pdf' : '.zip'));
    $file[$i] = new $File($file_name);
    foreach ($id_array as $id) {
      if ($is_pdf) {
        $item = EedImport::getImportedFileId($template_name,$id);
        $file[$i]->add($item);
      } else {
        $item = EedImport::getImportedDocData($template_name,$id);
        file_put_contents($temp2->getTempDir($item['NAME']), $item['DATA']);
        $file[$i]->add($item['NAME'],$item['DATA']);
      }
    }
    if (!$file[$i]->create()) {
      $sql = 'update ' . $table .' set stav=4,last_date=\''.$LAST_DATE.'\',last_time=\''.$LAST_TIME.'\',last_user_id='.$LAST_USER_ID.' where tid=' . intval($tid);
      $log = 'SQL: ' . $sql;
      ZapisLog($log);
      $q->query($sql);
      echo '<br />';
      echo 'Požadavek na generování PDF se ukládá do fronty, která je postupně zpracovávána. Z toho důvodu může být výsledné PDF k dispozici až za několik minut.<br />';
      echo 'Prosím pokuste se jej znovu stáhnout později.';
      echo '<br />';
      echo '<br />';
      
      echo '<input type="button" class="button btn" onclick="window.location.href=\'import2.php?id='.$tid.'&restart=5&PDF=1\'" value="' . $GLOBALS['RSTR_IMPORT']['download_pdf'] . '">';
      die();
    }
    $redirect = ($i+1 < sizeof($template_names)) ? "&redirect_false" : "";
    $file[$i]->download($tid,$redirect);
    $i++;
  }
  
/*} else {


  $i = 0;
  $zip = array();
  foreach ($template_names as $template_name) {
    $path_parts = pathinfo($template_name);
    $template_name = $path_parts['filename'];
    $zip_name = $temp->getTempDir($template_name.'.zip');
    $zip[$i] = new Zip($zip_name);
    foreach ($id_array as $id) {
      $item = EedImport::getImportedDocData($template_name,$id);
      file_put_contents($temp2->getTempDir($item['NAME']), $item['DATA']);
      $zip[$i]->add($item['NAME'],$item['DATA']);
    }
    $zip[$i]->create();
    $redirect = ($i+1 < sizeof($template_names)) ? "&redirect_false" : "";
    $zip[$i]->download($tid,$redirect);
    $i++;
  }
}*/

//$zip[$i-1]->downloadAll($tid);

/*foreach ($id_array as $id) {
  $upload_item =  $uplobj['table']->GetRecordsUploadForAgenda($id);
  foreach ($upload_item as $item) {
    $data = $uplobj['table']->GetUploadFiles($item);
    file_put_contents($temp2->getTempDir($item['NAME']), $data);
    $zip->add($item['NAME'],$data);
  }
}*/
$sql = 'update ' . $table .' set stav=5,last_date=\''.$LAST_DATE.'\',last_time=\''.$LAST_TIME.'\',last_user_id='.$LAST_USER_ID.' where tid=' . intval($id);
$log = 'SQL: ' . $sql;
ZapisLog($log);
$q->query($sql);

echo '<br />';
echo '<tr><td align="center">';
echo '<input type="button" class="button btn" onclick="window.location.href=\'import2.php?id='.$tid.'&dalsi_krok=1&DNAME='.dirname($file[$i-1]->getFileName()).'\'" value="' . $GLOBALS['RSTR_IMPORT']['import_dokoncit'] . '"> ';
echo '</td></tr>';
echo '</table>';

