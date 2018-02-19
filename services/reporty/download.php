<?php
require("tmapy_config.inc");
include(FileUp2(".admin/brow_.inc"));
include(FileUp2(".admin/config.inc"));
include_once(FileUp2(".admin/security_name.inc"));
include(FileUp2(".admin/oth_funkce.inc"));
include(FileUp2('.admin/upload_fce_.inc'));
$dir_arr=@GetUploadDir('POSTA',1);
$dir_arr[0]=$GLOBALS["TMAPY_DIR"].'/'.$GLOBALS["SERVER_CONFIG"]["UPLOAD_CONFIG"]["MODULES"]["table"]["STORAGE"]["UPLOAD_DIR"]."/POSTA/";
$file = $dir_arr[0].$dir_arr[1].$file;

if (is_file($file))
{
  $content_type = "application/csv";
  Header("Content-Type: application/csv");
  Header("Content-Disposition: attachment;filename=".basename($file)."");
  Header("Pragma: cache");
  Header("Cache-Control: public");
  $fp=fopen($file,'r');
  fpassthru($fp);
  fclose($fp);

}
else
Die('Soubor nenalezen');

?>
