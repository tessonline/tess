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
//$q=new DB_POSTA;
$TABLE_CONFIG["callback"]="ChangeClassBarva"; 
$TABLE_CONFIG["schema"][] = array("field"=>"ID", "label"=>"id",  "width"=>"1%","add"=>"align=center");
$TABLE_CONFIG["schema"][] = array("field"=>"UkazUsera(OSOBA)", "label"=>"člověk",  "width"=>"60%","add"=>"align=center");
//$TABLE_CONFIG["schema"][] = array("field"=>"SESSION_ID", "label"=>"session",  "width"=>"10%","add"=>"align=center");
$TABLE_CONFIG["schema"][] = array("field"=>"PRICHOZI", "label"=>"příchozí",  "width"=>"20%","add"=>"align=center");
$TABLE_CONFIG["schema"][] = array("field"=>"ODCHOZI", "label"=>"odchozí",  "width"=>"20%","add"=>"align=left");
$TABLE_CONFIG["schema"][] = array("field"=>"PLATNOST_OD...'&nbsp;-&nbsp;'...PLATNOST_DO...'&nbsp;'", "label"=>"Platnost",  "width"=>"20%","add"=>"align=left");

