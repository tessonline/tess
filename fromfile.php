<?php

require("tmapy_config.inc");
include_once(FileUp2('.admin/brow_.inc'));
include_once($GLOBALS['TMAPY_LIB'] . '/oohforms.inc');
require(FileUp2("html_header_full.inc"));



$h = 1130;
if ($GLOBALS['load_content']==true) {
  $unit = ($GLOBALS['width']-110) /10;
  if ($unit>152) $unit = 152; 
  $w1 = 6*$unit;
  $w2 = 4*$unit;
}
else {
  $w1 =$w2 = ($GLOBALS['width']-110);
 // if ($w1>760) $w1 = 760;
  if ($w1>780) $w1 = 780;
}
  
$url = "/".GetAgendaPath('POSTA')."/";
echo "
<iframe src=\"".$url."edit.php?insert&cacheid=&path_content=".urlencode($GLOBALS['path_content'])."&type_content=".$GLOBALS['type_content']."\" onload=\"this.width=".$w1.";this.height=".$h.";\">
</iframe>";
if ($GLOBALS['load_content']==true)
echo "
<div style=\"float:right\">
<iframe src=\"".$url."services/spisovka/vnitrni_ze_souboru/loadfile.php?load_content=".$GLOBALS['load_content']."&path_content=".urlencode($GLOBALS['path_content'])."\" onload=\"this.width=".$w2.";this.height=".$h.";\">
</iframe>
</div>
    
";


require(FileUp2("html_footer.inc"));


?>
