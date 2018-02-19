<?php
$is_filter = In_Array($form_params["formtype"], array($f_filter, $f_filter_all));
$is_filter_all = In_Array($form_params["formtype"], array($f_filter_all));
$is_filter_simple = In_Array($form_params["formtype"], array($f_filter));
$is_insert = In_Array($form_params["formtype"], array($f_insert));
$is_update = In_Array($form_params["formtype"], array($f_insert, $f_edit));
$is_edit = In_Array($form_params["formtype"], array($f_edit));
$is_info = In_Array($form_params["formtype"], array($f_info));
$is_history = In_Array($form_params["formtype"], array($f_history));
$is_new = In_Array($form_params["formtype"], array($f_insertfrom));
$is_multiedit = In_Array($form_params["formtype"], array($f_editall));

      $FORM_CONFIG["schema"][] = array("elements"=>array(
        array( "type"=>"select_superodbor", "name"=>"SUPERODBOR","disabled_onoff"=>false),
      ),
        "visible"=>$GLOBALS['CONFIG']['USE_SUPERODBOR'],
        "label"=>$GLOBALS["CONFIG"]["NAZEV_SUPERODBOR"].":");

$FORM_CONFIG["schema"][] = array( "elements"=>array(
                   array( "type"=>"text", "name"=>"NAZEV")),
                   "label"=>"Název:");
$FORM_CONFIG["schema"][] = array( "elements"=>array(
                   array( "type"=>"date_db", "name"=>"PLATNOST_OD","insertdatebutton"=>true)),
                   "label"=>"Platnost od:");
$FORM_CONFIG["schema"][] = array( "elements"=>array(
                   array( "type"=>"date_db", "name"=>"PLATNOST_DO","insertdatebutton"=>true)),
                   "label"=>"Platnost do:");
$FORM_CONFIG["schema"][] = array( "elements"=>array(
                   array( "type"=>"checkbox", "name"=>"AKTIVNI","value"=>"1")),
                   "label"=>"Aktivní:");

if ($is_filter) {
 $FORM_CONFIG["schema"][] = array(
   "label"=>"Spisové znaky:");
                   
                   
  $FORM_CONFIG["schema"][] = array( "elements"=>array(
    array( "type"=>"text", "name"=>"SKARTACE_NAZEV")),
    "label"=>"Název znaku:");
                   
  $FORM_CONFIG["schema"][] = array( "elements"=>array(
    array( "type"=>"select_skartace_kod", "name"=>"SKARTACE_SKUPINA","insertnull"=>true)),
    "label"=>"Skupina znaku:");
                   
   $FORM_CONFIG["schema"][] = array( "elements"=>array(
     array( "type"=>"checkbox", "name"=>"SKARTACE_AKTIVNI")),
     "label"=>"Jen aktivní:");

   $FORM_CONFIG["schema"][] = array( "elements"=>array(
     array( "type"=>"checkbox", "name"=>"SKARTACE_NEAKTIVNI")),
     "label"=>"Jen neaktivní:");

   $FORM_CONFIG["schema"][] = array( "elements"=>array(
     array( "type"=>"select_skartacni_pismeno", "name"=>"SKARTACE_ZNAK","insertnull"=>true)),
     "label"=>"Skar. znak:");

   $FORM_CONFIG["schema"][] = array( "elements"=>array(
     array( "type"=>"text_number", "name"=>"SKARTACE_LHUTA")),
     "label"=>"Lhůta:");
                   
                   
}