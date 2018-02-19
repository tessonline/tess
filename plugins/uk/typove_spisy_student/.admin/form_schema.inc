<?php


    $FORM_CONFIG["schema"][] = array("elements"=>array(
              array( "type"=>"hidden", "name"=>"TYP_STUDIA","value"=>$_GET['omez_typ']),
              array( "type"=>"select_vsechny_spisuzly", "name"=>"ODBOR","add"=>"id=\"ODBOR\" onChange=\"UkazPracovnika(this,'REFERENT');\""),
              array( "type"=>"select_referent", "name"=>"REFERENT","insertnull"=>true,"required"=>true,"label"=>"Zpracovatel", add=>  "onChange=\"REFERENT_ON(this)\""),
              ),
              "label"=>'' . $GLOBALS["CONFIG"]["NAZEV_ODBOR"] . ':');

  $FORM_CONFIG["schema"][] = array(
    "elements"=>array(array(
      "type"=>"select_typovy_spis",
      "name"=>"TYPOVY_SPIS",
      "required"=>true,
       add=>  "onChange=\"TYPSPIS_ON(this)\"",
      "insertnull" => true,
    )),
    "label" => "Vyberte šablonu typového spisu"
  );


