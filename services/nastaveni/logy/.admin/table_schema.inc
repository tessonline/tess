<?php
Function ChangeClassBarva($t)
{
  $color='';
  if ($GLOBALS["CHYBA"]>0) $color='_red2';
  static $i=1;
  if ($i):
    $t->classname = "posta_brow".$color;
    $i = 0;
  else:
    $t->classname = "posta_browdark".$color;
    $i = 1;
  endif;
}
$TABLE_CONFIG["callback"]="ChangeClassBarva"; 
$TABLE_CONFIG["schema"][] = array("field"=>"ID", "label"=>"id",  "width"=>"10%","add"=>"align=center");
$TABLE_CONFIG["schema"][] = array("field"=>"DATUM", "label"=>"datum",  "width"=>"20%","add"=>"align=center");
//$TABLE_CONFIG["schema"][] = array("field"=>"SESSION_ID", "label"=>"session",  "width"=>"10%","add"=>"align=center");
$TABLE_CONFIG["schema"][] = array("field"=>"SW", "label"=>"software",  "width"=>"10%","add"=>"align=center");
$TABLE_CONFIG["schema"][] = array("field"=>"POPIS", "label"=>"akce",  "width"=>"60%","add"=>"align=left");
?>
