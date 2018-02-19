<?php


$FORM_CONFIG["schema"][] = array( "elements"=>array(
                   array( "type"=>"text", "name"=>"DATUM")),
                   "label"=>"Datum:");

$FORM_CONFIG["schema"][] = array( "elements"=>array(
                   array( "type"=>"select_log_sw", "name"=>"SW","insertnull"=>true)),
                   "label"=>"Software:");

$FORM_CONFIG["schema"][] = array( "elements"=>array(
                   array( "type"=>"text", "name"=>"SESSION_ID")),
                   "label"=>"SessionID:");

$FORM_CONFIG["schema"][] = array( "elements"=>array(
                   array( "type"=>"text", "name"=>"POPIS")),
                   "label"=>"Popis:");

$FORM_CONFIG["schema"][] = array( "elements"=>array(
                   array( "type"=>"checkbox", "name"=>"CHYBA")),
                   "label"=>"Pouze chyby:");


?>
