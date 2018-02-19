<?php
include(FileUp2(".admin/config.inc"));

$doc_id = $_GET['SPIS_ID'];
$spis_id = $doc_id;
$cj_obj = LoadClass('EedCj',$doc_id);

$GLOBALS['ODBOR'] = VratOdbor();

  $FORM_CONFIG["schema"][] = array("elements"=>array(
            array( "type"=>"hidden", "name"=>"CISLO_SPISU1","value"=>$GLOBALS["spis1"],"frozen"=>true),
            ),
            "label"=>$GLOBALS["CONFIG"]["CISLO_SPISU"].":");							



  $FORM_CONFIG["schema"][] = array("elements"=>array(
            array( "type"=>"select_vsechny_spisuzly", "name"=>"ODBOR","add"=>"id=\"ODBOR\" onChange=\"UkazPracovnika(this,'REFERENT');\" onLoad=\"UkazPracovnika(this,'REFERENT');\""),
            array( "type"=>"hidden", "name"=>"ODBOR_PUV","value"=>$GLOBALS['ODBOR']),
//              array( "type"=>"select_odbor", "name"=>"ODBOR","extrahtml"=>"onchange=\"window.reload()\""),
            ),
            "label"=>"Nový spisový uzel:");
  $FORM_CONFIG["schema"][] = array("elements"=>array(
            array( "type"=>"select_referent", "name"=>"REFERENT"),
            ),
             "format"=>"'<span id=\"REF_span\">'...REFERENT...'</span>'",
            "label"=>"Nový zpracovatel:");

 $FORM_CONFIG["schema"][] = array("elements"=>array(
            array( "type"=>"date_db", "name"=>"DATUM","insertdatebutton"=>true,"required"=>true),),   
            "label"=>"Dne:");		

 $FORM_CONFIG["schema"][] = array("elements"=>array(
              array( "type"=>"text", "name"=>"POZNAMKA"),
              array( "type"=>"hidden", "name"=>"SPIS_ID"),
              array( "type"=>"hidden", "name"=>"OLD_SO"),
            ),   
            "label"=>"Poznámka:");		

//include(FileUp2(".admin/el/urednik_id_zmena_dat_cas.inc"));

