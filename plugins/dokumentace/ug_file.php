<?php
require("tmapy_config.inc");
require(FileUp2(".admin/upload_.inc"));
// Header("Pragma: cache");
// Header("Cache-Control: public"); 
if (isset($GLOBALS['DOWNLOAD'])) {
  $upload = Upload(array('create_only_objects' => true, 'agenda' => $PROPERTIES['AGENDA_IDENT'], 'noshowheader' => true));
  $upload_records = $upload['table']->GetRecordsUploadForAgenda($GLOBALS['ID']);
  $download = array();
  foreach ($upload_records as $record) {
    if ($record['ID'] == $GLOBALS['DOWNLOAD']) {
      $download = $record;
      break;
    }
  }
  $file = $upload['table']->GetUploadFiles($download);
  if(empty($file)) {
    echo "Soubor nenalezen";
    die();
  }
  if ($file) {
    header('Content-type: '.$download['TYPEFILE']);
    header('Content-Disposition: inline; filename="'.$download['NAME'].'"');
    header('Content-length: '.$download['FILESIZE']);
    echo $file;
    exit;
  }
  else {
    echo "Nepodařilo se přečíst soubor";
    die();
  }
}
else {

  Upload(array());
  echo '<p><span class="caption">Zde se zobrazují všechny uložené dokumentace. V přehledové tabulce se zobrazují pouze přílohy označené pro Anonymní přístup.</span></p>';
}