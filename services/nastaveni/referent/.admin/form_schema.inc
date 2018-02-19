<?php
include(FileUp2(".admin/config.inc"));
$is_filter = In_Array($form_params["formtype"], array($f_filter, $f_filter_all));

  $FORM_CONFIG["schema"][] = array("elements"=>array(
            array( "type"=>"select_referent", "name"=>"ZPRACOVATEL","insertnull"=>$is_filter),
//            array( "type"=>"select_referent", "name"=>"PUV_REFERENT"),
            ),
            "label"=>"Osoba, která bude konat zástup:");							

  $FORM_CONFIG["schema"][] = array("elements"=>array(
            array( "type"=>"select_referent", "name"=>"ZASTOUPENA","insertnull"=>$is_filter),
            ),
            "label"=>"Osoba, která bude zastupována:");							
 $FORM_CONFIG["schema"][] = array("elements"=>array(
            array( "type"=>"date_db", "name"=>"DATUM","insertdatebutton"=>true,"required"=>true),
            ),   
            "label"=>"Dne:");		

 $FORM_CONFIG["schema"][] = array("elements"=>array(
            array( "type"=>"text", "name"=>"POZNAMKA","size"=>"80"),),   
            "label"=>"Poznámka:");		

