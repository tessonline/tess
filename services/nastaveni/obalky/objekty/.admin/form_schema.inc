<?php

$FORM_CONFIG["schema"][] = array( "elements"=>array(
                   array( "type"=>"hidden", "name"=>"OBALKA_ID")),
                   "label"=>"");


$FORM_CONFIG["schema"][] = array( "elements"=>array(
                   array( "type"=>"select_objekt", "name"=>"OBJEKT")),
                   "label"=>"Objekt:");

$FORM_CONFIG["schema"][] = array( "elements"=>array(
                   array( "type"=>"text_number", "name"=>"SOURX"),
                   array( "type"=>"text_number", "name"=>"SOURY")),
                   "format"=>"SOURX...'&nbsp;&nbsp;&nbsp;Y:&nbsp;'...SOURY",
                   "label"=>"Souřadnice X:");

$FORM_CONFIG["schema"][] = array( "elements"=>array(
                   array( "type"=>"text_number", "name"=>"VELIKOST")),
                   "label"=>"Délka okna:");

$FORM_CONFIG["schema"][] = array( "elements"=>array(
                   array( "type"=>"text_number", "name"=>"VELIKOST_FONTU")),
                   "label"=>"Velikost písma:");

$FORM_CONFIG["schema"][] = array( "elements"=>array(
                   array( "type"=>"select_tucne", "name"=>"FONT")),
                   "label"=>"Styl písma:");

$FORM_CONFIG["schema"][] = array( "elements"=>array(
                   array( "type"=>"text_number", "name"=>"RADKOVANI")),
                   "label"=>"Řádkování:");
$FORM_CONFIG["schema"][] = array( "elements"=>array(
                   array( "type"=>"text", "name"=>"TEXT","size"=>80)),
                   "format"=>"TEXT...'<br/>Použito jen pokud je vybrán objekt Vlastní text.<br/><br/><b>Všechny míry jsou v mm.</b>'",
                   "label"=>"Vlastní text:");



?>
