<?php 

$FORM_CONFIG["schema"][] = "Kopie agendy";



$FORM_CONFIG["schema"][] = array("elements"=>array(
  array(
    "type"=>"text",
    "name"=>"NAZEV",
    ),
  ),
  "label"=>"Agenda:");

$FORM_CONFIG["schema"][] = array("elements"=>array(
  array(
    "type"=>"select_superodbor",
    "name"=>"ID_SUPERODBOR",
    "insertnull"=>true,
    "frozen" => !HasRole('spravce'),
    
  ),
),
  "visible" => ($GLOBALS['CONFIG']['USE_SUPERODBOR'] ? true : false),
  "label"=>$GLOBALS["CONFIG"]["NAZEV_SUPERODBOR"].":");


$FORM_CONFIG["schema"][] = array( "elements"=>array(
  array( "type"=>"checkbox", "name"=>"NEAKTIVNI")),
  "label"=>"Neaktivní:");

$FORM_CONFIG['schema'][] = array("elements"=>array(
  array("type"=>"hidden","name"=>"ID_AGENDY", "value"=>$GLOBALS['id']),
  array("type"=>"hidden","name"=>"KOPIE_AGENDY", "value"=>1)
  
));