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

$GLOBALS['CONFIG']['VYHLEDAVANI_NAPRIC_DB'] = true;
$FORM_CONFIG["schema"][] = array( "elements"=>array(
                   array( "type"=>"select_referent", "name"=>"USER_ID", "fullselect"=>true),
                   ),
                   "label"=>"Uživatel:");

$FORM_CONFIG["schema"][] = array( "elements"=>array(
                   array( "type"=>"text", "name"=>"LOGIN"),
                   ),
                   "label"=>"Login:");

$FORM_CONFIG["schema"][] = array( "elements"=>array(
                   array( "type"=>"text", "name"=>"PASSWD"),
                   ),
                   "label"=>"Heslo:");

