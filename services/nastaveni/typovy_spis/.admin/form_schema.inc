<?php
    $FORM_CONFIG["schema"][] = array( "elements"=>array(
                  array( "type"=>"text", "name"=>"NAZEV","required"=>true, size=>60),
                   ),
                  "label"=>"Název typového spisu:");

if (HasRole('lokalni-spravce')) $GLOBALS['ID_SUPERODBOR'] = EedTools::VratSuperOdbor();

$FORM_CONFIG["schema"][] = array("elements"=>array(
          array(
            "type"=>"select_superodbor",
            "name"=>"ID_SUPERODBOR",
            "insertnull"=>true,
            "frozen" => !HasRole('spravce')),
          ),
          "visible" => ($GLOBALS['CONFIG']['USE_SUPERODBOR'] ? true : false),
          "label"=>$GLOBALS["CONFIG"]["NAZEV_SUPERODBOR"].":");


    $FORM_CONFIG["schema"][] = array("elements"=>array(
              array( "type"=>"select_vsechny_spisuzly", "name"=>"ODBOR","insertnull"=>true,"selectfull"=>false),
              ),
              "label"=>$GLOBALS["CONFIG"]["NAZEV_ODBOR"]);
