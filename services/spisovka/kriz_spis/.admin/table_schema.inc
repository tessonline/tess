<?php


if ($GLOBALS['SMER_KRIZ']==1)
{
  $TABLE_CONFIG = array(
    "schema" => array( 
   array( field=>"tableFormatCJednaci(PUVODNI_SPIS,'1','2')", "label"=>"Předcházející čísla jednací"),
//   array( field=>"PUVODNI_SPIS", "číslo jednací"),
  ));
}
else
{  
  $TABLE_CONFIG = array(
    "schema" => array( 
   array( field=>"tableFormatCJednaci(NOVY_SPIS,'1','2')", "label"=>"Následující čísla jednací"),
   //array( field=>"NOVY_SPIS", "číslo jednací"),
  ));
} 
?>
