<?php
include_once(FileUp2('.admin/classes/dokument/Temp.php'));
echo '<table width="99%" align="center"><tr><td align="center">';
echo '<p><span class="caption">'.$GLOBALS['RSTR_IMPORT']['import_hotovo2'].'</span></p>';
echo '<img src="images/Check.png" title="' . $GLOBALS['RSTR_IMPORT']['import_importer_dobhel_ok'] . '">';
echo '</td></tr>';

$uplobj = Upload(array(
  'create_only_objects' => true,
  'agenda' => $GLOBALS['PROPERTIES']['AGENDA_IDENT'],
  'noshowheader' => true,
));


$importFiles = array();
$upload_records = $uplobj['table']->GetRecordsUploadForAgenda($id);
while (list($key, $val) = each($upload_records)) {
  if (strpos($val['NAME'], 'import_log') === false) {
    $importFiles[] = $val;
  }
}

if (sizeof($importFiles)<2) {
  $GLOBALS['csv_only']=1;
}

if (strlen($GLOBALS['FNAME'])>1) 
{
  try {
    $temp = new Temp($GLOBALS['DNAME'], true);
    $temp->delTempDir();
    //echo                     $GLOBALS['DNAME'];
    }
    catch (Exception $e) { }
}


$log = $GLOBALS['RSTR_IMPORT']['import_importer_dobhel_ok'];
ZapisLog($log);


echo '<tr><td align="center">';
if ($GLOBALS['csv_only']!=1)
echo '<input type="button" class="button btn" onclick="window.location.href=\'import2.php?id='.$id.'&restart=4\'" value="' . $GLOBALS['RSTR_IMPORT']['import_zpet_na'] . '"> ';
echo '<input type="button" class="button btn" onclick="window.location.href=\'import2.php?id=' . $id . '&restart=1\'" value="' . $GLOBALS['RSTR_IMPORT']['import_pregenerovat'] . '">&nbsp;&nbsp;&nbsp;';
echo '</td></tr>';
echo '</table>';

