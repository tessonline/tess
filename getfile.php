<?php
require("tmapy_config.inc");

require_once(FileUp2(".admin/upload_.inc"));

$uplobj=Upload(array('create_only_objects'=>true,'agenda'=>'POSTA','noshowheader'=>true));
$upload_records = $uplobj['table']->GetRecordsUploadForAgenda($_GET['POSTA_ID']);

$SOUBOR_ID = $_GET['FILE_ID'];
while (list($key,$val)=each($upload_records))
  if ($val[ID]==$SOUBOR_ID)
{
      $data=$uplobj['table']->GetUploadFiles($val);
      $name = $val['FILE_NAME'];
}
echo $data;