<?php
$file_temp = $_GET['file'];
require("tmapy_config.inc");
include(FileUp2(".admin/brow_.inc"));
include(FileUp2(".admin/config.inc"));
include_once(FileUp2(".admin/security_name.inc"));
include(FileUp2(".admin/oth_funkce.inc"));
include(FileUp2('.admin/upload_fce_.inc'));
$dir = $GLOBALS[CONFIG_POSTA][HLAVNI][tmp_adresar];

$file = $dir.$file_temp;

if (is_file($file)) {
  $content_type = "application/pdf";  
  header("Content-type: $content_type");
  header("filename=\"".basename($file)."\"");
  header("Content-length: ".(string)(filesize($file))."");
  $fp=fopen($file,'r');
  fpassthru($fp);
  fclose($fp);

}
else
Die('Soubor nenalezen');

?>
