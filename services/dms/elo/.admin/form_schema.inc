<?php

  $FORM_CONFIG["schema"][] = array("elements"=>array(
            array( "type"=>"select_odbor", "name"=>"ODBOR","insertnull"=>true),
            ),
            "label"=>"Odbor:");							
            
 $FORM_CONFIG["schema"][] = array("elements"=>array(
            array( "type"=>"date_db", "name"=>"DATUM_OD","insertdatebutton"=>true,"required"=>true),   
            array( "type"=>"date_db", "name"=>"DATUM_DO","insertdatebutton"=>true,"required"=>true)),   
            "format"=>"DATUM_OD...'&nbsp;do&nbsp;'...DATUM_DO",
            "label"=>"Datum od:");		

// If ($GLOBALS[smer]=='prichozi')
 $FORM_CONFIG["schema"][] = array("elements"=>array(
            array( "type"=>"text_number", "name"=>"EV_CISLO_OD","size"=>8),   
            array( "type"=>"text_number", "name"=>"EV_CISLO_DO","size"=>8)),   
            "format"=>"EV_CISLO_OD...'&nbsp;do&nbsp;'...EV_CISLO_DO",
            "label"=>"podací číslo od:");		

 $FORM_CONFIG["schema"][] = array("elements"=>array(
            array( "type"=>"text_number", "name"=>"CISLO_JEDNACI1_OD","size"=>8),   
            array( "type"=>"text_number", "name"=>"CISLO_JEDNACI1_DO","size"=>8)),   
            "format"=>"CISLO_JEDNACI1_OD...'&nbsp;do&nbsp;'...CISLO_JEDNACI1_DO",
            "label"=>"Číslo jednací od:");		

 $FORM_CONFIG["schema"][] = array("elements"=>array(
            array( "type"=>"hidden", "name"=>"SMER","value"=>$GLOBALS["smer"]),   
            array( "type"=>"hidden", "name"=>"PODATELNA_ID","value"=>$GLOBALS["podatelna_id"])),   
            "label"=>"");		


?>
