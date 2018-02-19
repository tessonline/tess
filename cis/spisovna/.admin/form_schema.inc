<?php
include_once(FileUp2('.admin/config.inc'));

$FORM_CONFIG["schema"][] = array( "elements"=>array(
                   array( "type"=>"text", "name"=>"SPISOVNA")),
                   "label"=>"Spisovna:");


 if (!HasRole('access_all')) $GLOBALS['SUPERODBOR'] = EedTools::VratSuperOdbor();

  $FORM_CONFIG["schema"][] = array("elements"=>array(
    array(
      "type"=>"select_superodbor",
      "name"=>"SUPERODBOR",
      "insertnull"=>true,
      "frozen" => !HasRole('access_all')&&!HasRole('spravce'),
      "add"=>"onChange=\"SuperodborChange('ODBOR')\"",
   ),
  ),
    "visible" => ($GLOBALS['CONFIG']['USE_SUPERODBOR'] ? true : false),
    "label"=>$GLOBALS["CONFIG"]["NAZEV_SUPERODBOR"].":");

$FORM_CONFIG["schema"][] = array( "elements"=>array(
  array( "type"=>"select_vsechny_spisuzly", "superodbor" => $GLOBALS['SUPERODBOR'],"name"=>"ODBOR","insertnull"=>true)),
                   "label"=>"Spisový uzel:");


