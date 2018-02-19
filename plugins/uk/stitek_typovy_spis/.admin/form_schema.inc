<?php

  $FORM_CONFIG["schema"][] = array("elements"=>array(
            array( "type"=>"select_stitek", "name"=>"STITEK","typovy_spis"=>1),
            array( "type"=>"hidden", "name"=>"ID","value"=>$GLOBALS["ID"]),
 
            ),
            "label"=>"Štítek:");							
            
  $FORM_CONFIG["schema"][] = array("elements"=>array(
            array( "type"=>"text_number", "name"=>"POZICE","size"=>4),
            ),
            "label"=>"Pozice:");							

  $FORM_CONFIG["schema"][] = array("elements"=>array(
              array( 
                "type"=>"hidden", 
                "name"=>"IDS[]",
                "value"=>$GLOBALS['EDIT_ID'],
              )
            ));						
            

/* $FORM_CONFIG["schema"][] = array("elements"=>array(
            array( "type"=>"checkbox", "name"=>"CELE","size"=>8,"values"=>1,"add"=>($GLOBALS['CONFIG']['STAMP_CELE']?"CHECKED":""))),
            "visible"=>($GLOBALS["ODESLANA"]=='f' || !$GLOBALS["ID"]),
            "label"=>"Celé razítko?:");		

$FORM_CONFIG["schema"][] = array("elements"=>array(
            array( "type"=>"checkbox", "name"=>"PRAC_KOPIE","size"=>8,"values"=>1)),
            "visible"=>($GLOBALS["ODESLANA"]=='f' || !$GLOBALS["ID"]),
            "label"=>"Pracovní kopie");*/