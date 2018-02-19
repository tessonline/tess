<?php

 $FORM_CONFIG["schema"][] = array("elements"=>array(
            array( "type"=>"datetime_db", "name"=>"DATUM_OD","insertdatebutton"=>true,"required"=>true,"label"=>"Datum od"),
            array( "type"=>"datetime_db", "name"=>"DATUM_DO","insertdatebutton"=>true,"required"=>true,"label"=>"Datum do"),
            array( "type"=>"hidden", "name"=>"smer","value"=>$GLOBALS["smer"]),
            ),
            "label"=>"Datum od:");

 $FORM_CONFIG["schema"][] = array("elements"=>array(
            array( "type"=>"select_odbor", "name"=>"ODBOR","insertnull"=>true),
            ),
            "visible"=>!$GLOBALS["smer"]=='odchozi',
            "label"=>"Spisový uzel:");

$FORM_CONFIG["schema"][] = array(
  "elements"=>array(array(
    "type" => "checkbox",
    "name" => "HAS_DATA_BOX_ID"
  )),
  "label" => "Zprávy bez ID datové schránky?:"
);							

