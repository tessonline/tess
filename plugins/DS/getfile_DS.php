<?php
require("tmapy_config.inc");
require(FileUp2(".admin/brow_.inc"));
require(FileUp2(".admin/nastaveni.inc"));
require(FileUp2(".admin/funkce.inc"));
require(FileUp2("interface/.admin/soap_funkce.inc"));

header("Cache-Control: public, must-revalidate");
header("Pragma: hack");
$typ_file = end(explode(".",$name));
switch (StrToLower($typ_file)) {
   case "jpg" : $content_type = "image/jpeg"; break;
   case "gif" : $content_type = "image/gif"; break;
   case "png" : $content_type = "image/png"; break;
   case "bmp" : $content_type = "image/bmp"; break;
   case "tif" : $content_type = "image/tiff"; break;
   case "pdf" : $content_type = "application/pdf"; break;
   case "rtf" : $content_type = "application/rtf"; break;
   case "doc" : $content_type = "application/msword"; break;
   case "xls" : $content_type = "application/msexcel"; break;
   case "ppt" : $content_type = "application/vnd.ms-powerpoint"; $content_disposition = "attachment"; break;
   case "txt" : $content_type = "text/plain"; break;
   case "mpg" : $content_type = "video/mpg"; break;
   case "avi" : $content_type = "video/msvideo"; break;
   case "wav" : $content_type = "audio/wav"; break;
   case "mp3" : $content_type = "audio/mpeg"; break;
   default    : $content_type = $q->Record['TYPEFILE']?$q->Record['TYPEFILE']:false;
}


$cesta=$GLOBALS[CONFIG_POSTA][HLAVNI][tmp_adresar].$val[dmID].'/';
$odkaz_soubor=$cesta.'/'.$dmID.'/'.TxtEncoding4Soap($fileDZ);

header("Content-type: $content_type");
header("Content-disposition:  attachment; filename=\"".basename($name)."\"");
header("Content-length: ".(string)(filesize($odkaz_soubor))."\"");
$fp = fopen($odkaz_soubor,'r');
fpassthru($fp);
fclose($fp);
//echo $odkaz_soubor;
//  $fp = fopen($cesta.$valz[filename], "w");
