<?php


  $FORM_CONFIG["schema"][] = array("elements"=>array(
            array( "type"=>"select_odbor", "name"=>"ODBOR"),
            ),
            "label"=>"Odbor:");							
            
 $FORM_CONFIG["schema"][] = array("elements"=>array(
            array( "type"=>"datetime_db", "name"=>"DATUM_OD","insertdatebutton"=>true,"required"=>true),   
            array( "type"=>"datetime_db", "name"=>"DATUM_DO","insertdatebutton"=>true,"required"=>true)),   
            "format"=>"DATUM_OD...'&nbsp;do&nbsp;'...DATUM_DO",
            "label"=>"Datum od:");		


?>
