<?php
/*if ($form_params["formtype"] == $f_edit || $form_params["formtype"] == $f_insert || $form_params["formtype"] == $f_info || $form_params["formtype"] == $f_filterall)             
   $visible=true; else $visible=false;
*/   
    $FORM_CONFIG["schema"][] = array( "elements"=>array(
                  array( "type"=>"hidden", "name"=>"SPIS_ID"),
                   ),
                  );
/*
    $FORM_CONFIG["schema"][] = array( "elements"=>array(
                  array( "type"=>"select_typ_ukladaciznacka", "name"=>"ZNACKA_TYP"),
                   ),
                  "label"=>"Druh značky - nepoužívat:");
*/
 // $FORM_CONFIG["schema"][] = array( "elements"=>array(
                  // array( "type"=>"select_text_ukladaciznacka", "name"=>"ZNACKA_ID"),
                   // ),
                  // "label"=>"text značky:");

    $FORM_CONFIG["schema"][] = array( "elements"=>array(
                array('type' => 'valid_fce', 'name_fce' => 'if(f.ZNACKA_ID.value == 0) { alert(\'Vyberte správnou hodnotu!\'); f.ZNACKA_ID_AUTOCOMPLETE.focus(); return false;}'),
                array( "type"=>"text", "name"=>"ZNACKA_ID_AUTOCOMPLETE", 'size'=>50, 'add'=>'id="txtAuto"'),
                array( "type"=>"hidden", "name"=>"ZNACKA_ID", 'add'=>'id="znackaId"')
                ),
                "format"=>"ZNACKA_ID_AUTOCOMPLETE...' <small>(nutno zadat min. 3 písmena a zobrazí max. 1000 záznamů)</small>'",
                "label"=>"Text značky:"
                );


//    $FORM_CONFIG["schema"][] = array( "elements"=>array(
//                array( "type"=>"hidden", "name"=>"ZNACKA_ID", 'add'=>'id="znackaId"')
//                ),
//                "label"=>""
//                );


//f ($form_params["formtype"] == $f_edit  include(FileUp2(".admin/el/owner_user_date_form_add.inc"));

