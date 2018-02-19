<?php


  $FORM_CONFIG["schema"][] = array("elements"=>array(
            array( "type"=>"select_vsechny_spisuzly", "name"=>"ODBOR"),
            ),
            "label"=>"Odbor:");							
/*
  $FORM_CONFIG["schema"][] = array("elements"=>array(
            array( "type"=>"radio_typ_odeslani", "name"=>"DOPORUCENE"),
            ),
            "label"=>"Druh pošty:");							
*/
  $FORM_CONFIG["schema"][] = array("elements"=>array(
            array( "type"=>"hidden", "name"=>"VSTUP","value"=>true),
            ),
            "label"=>"");							
            
 $FORM_CONFIG["schema"][] = array("elements"=>array(
            array( "type"=>"datetime_db", "name"=>"DATUM_OD","insertdatebutton"=>true,"required"=>true,'label'=>'Datum od'),
            array( "type"=>"datetime_db", "name"=>"DATUM_DO","insertdatebutton"=>true,"required"=>true,'label'=>'Datum od')),
            "format"=>"DATUM_OD...'&nbsp;do&nbsp;'...DATUM_DO",
            "label"=>"Datum od:",
              // zruseni format pro tema square
            'theme_config' => array(
              'square' => array(
                'format' => '',
              )
            )
      );


?>
