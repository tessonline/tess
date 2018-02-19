<?php


$FORM_CONFIG["schema"][] = array( "elements"=>array(
                   array( "type"=>"select_referent", "name"=>"OSOBA","insertnull"=>true)),
                   "label"=>"Osoba:");

$FORM_CONFIG["schema"][] = array( "elements"=>array(
                   array( "type"=>"date_db", "name"=>"PLATNOST_OD","frozen"=>true),
                   array( "type"=>"date_db", "name"=>"PLATNOST_DO","frozen"=>true),
                   ),
                   "format"=>"PLATNOST_OD...'&nbsp;&nbsp;&nbsp;do:&nbsp;'...PLATNOST_DO",
                   "label"=>"Platnost:");

$FORM_CONFIG["schema"][] = array( "elements"=>array(
                   array( "type"=>"select_ano_ne", "name"=>"PRICHOZI")),
                   "label"=>"Používat pro doručenky příchozích emailů:");

$FORM_CONFIG["schema"][] = array( "elements"=>array(
                   array( "type"=>"select_ano_ne", "name"=>"ODCHOZI")),
                   "label"=>"Používat pro napojení na DS:");

$FORM_CONFIG["schema"][] = array( "elements"=>array(
                   array( "type"=>"date_db", "name"=>"ZNEPLATNENI_DATUM")),
                   "label"=>"Datum zneplatnění:");

$FORM_CONFIG["schema"][] = array( "elements"=>array(
                   array( "type"=>"text", "name"=>"ZNEPLATNENI_DUVOD","size"=>60)),
                   "label"=>"Důvod zneplatnění:");

