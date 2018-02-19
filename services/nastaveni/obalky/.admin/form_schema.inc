<?php


if ($_GET['create_objects']) {
  $GLOBALS['NAZEV'] = "KOPIE: ".$GLOBALS['NAZEV'];
}

$FORM_CONFIG["schema"][] = array( "elements"=>array(
                   array( "type"=>"text_number", "name"=>"PORADI")),
                   "label"=>"Pořadí v seznamu:");

$FORM_CONFIG["schema"][] = array( "elements"=>array(
                   array( "type"=>"text", "name"=>"NAZEV")),
                   "label"=>"Název:");

$FORM_CONFIG["schema"][] = array( "elements"=>array(
                   array( "type"=>"select_velikost", "name"=>"VELIKOST")),
                   "label"=>"Velikost papíru:");

$FORM_CONFIG["schema"][] = array( "elements"=>array(
                   array( "type"=>"select_otoceni", "name"=>"OTOCENI")),
                   "label"=>"Orientace:");

$FORM_CONFIG["schema"][] = array( "elements"=>array(
                   array( "type"=>"select_ano_ne", "name"=>"AKTIVNI")),
                   "label"=>"Aktivní:");

$FORM_CONFIG["schema"][] = array( "elements"=>array(
                   array( "type"=>"hidden", "name"=>"create_objects")),
                   );

$FORM_CONFIG["schema"][] = array( "elements"=>array(
  array( "type"=>"hidden", "name"=>"envelope_id")),
);

if (!HasRole('access_all')) $GLOBALS['ID_SUPERODBOR'] = EedTools::VratSuperOdbor();

$FORM_CONFIG["schema"][] = array("elements"=>array(
  array(
    "type"=>"select_superodbor",
    "name"=>"ID_SUPERODBOR",
    "insertnull"=>true,
    "frozen" => !HasRole('access_all')
  ),
),
  "visible" => ($GLOBALS['CONFIG']['USE_SUPERODBOR'] ? true : false),
  "label"=>$GLOBALS["CONFIG"]["NAZEV_SUPERODBOR"].":");


?>
