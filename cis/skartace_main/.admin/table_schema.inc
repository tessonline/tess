<?php
Function ChangeClassBarva($t)
// staci pustit to zaremovany a barvi se cely radek....
{
  If (!$GLOBALS["AKTIVNI"]==1) $t->classname="gray_line";
  else 
  {
   static $i=1;
    if ($i):
      $t->classname = "brow".$color;
      $i = 0;
    else:
      $t->classname = "browdark".$color;
      $i = 1;
    endif;
  
  }
      
  
}
$TABLE_CONFIG["callback"]="ChangeClassBarva";

$TABLE_CONFIG["schema"][] =  array( "field"=>"JIDPlan(ID)", "label"=>"JID plánu");
$TABLE_CONFIG["schema"][] =  array( "field"=>"NAZEV", "label"=>"Název");
$TABLE_CONFIG["schema"][] =  array( "field"=>"PLATNOST_OD", "label"=>"Platnost od");
$TABLE_CONFIG["schema"][] =  array( "field"=>"PLATNOST_DO", "label"=>"Platnost do");
$TABLE_CONFIG["schema"][] =  array( "field"=>"ShowStrom(ID)", "label"=>"","class"=>"image");
$TABLE_CONFIG["schema"][] =  array( "field"=>"ExportXML(ID)", "label"=>"","class"=>"image");
$TABLE_CONFIG["schema"][] =  array( "field"=>"ImportXML(ID)", "label"=>"","class"=>"image");

?>
