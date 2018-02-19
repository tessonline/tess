<?php
require("tmapy_config.inc");
require(FileUp2(".admin/edit_.inc"));
require(FileUp2("html_header_title.inc"));

if ($GLOBALS['ID']) {
  $cj_obj = LoadClass('EedCj',$GLOBALS['ID']);
  $cj_info = $cj_obj->GetCjInfo($GLOBALS['ID']);
  $caption = $cj_info['CELE_CISLO'];
  echo '<h1 align="center">'.$caption.'</h1>';
}

Form_();
require(FileUp2("html_footer.inc"));
?>
