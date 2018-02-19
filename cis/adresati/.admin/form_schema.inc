<?php



$FORM_CONFIG["schema"][] = array( "elements"=>array(
                   array( "type"=>"text", "name"=>"NAZEV"),
                   array( "type"=>"hidden", "name"=>"ODBOR","value"=>0)),
                   "label"=>"Název:");

$FORM_CONFIG["schema"][] = array( "elements"=>array(
                   array( "type"=>"checkbox", "name"=>"AKTIVNI","value"=>"1")),
                   "label"=>"Aktivní:");
