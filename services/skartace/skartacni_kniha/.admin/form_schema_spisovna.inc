<?php

/*
  $USER_INFO = $GLOBALS["POSTA_SECURITY"]->GetUserInfo(); 
    $FORM_CONFIG["schema"][] = array( "elements"=>array(
                       array( "type"=>"text", "name"=>"LISTU"),
                       ),
                       "label"=>"Počet listů:");
    $FORM_CONFIG["schema"][] = array( "elements"=>array(
                       array( "type"=>"textarea", "name"=>"PRILOHY"),
                       ),
                       "label"=>"Počet příloh:");
    $FORM_CONFIG["schema"][] = array( "elements"=>array(
                       array( "type"=>"text", "name"=>"DIGITALNI"),
                       ),
                       "label"=>"Počet digitálních:");

*/


if ($GLOBALS['REGISTRATURA'] == '-1' && !$is_multiedit) include_once('.admin/form_schema.inc');
else
        $FORM_CONFIG["schema"][] = array( "elements"=>array(
                  array( "type"=>"textarea", "name"=>"POZNAMKA","cols"=>50, "rows"=>5 ),
                  array( "type"=>"hidden", "name"=>"DOKUMENT_ID" ),
                   ),
                  "visible"=>!$is_multiedit,
                  "label"=>"Poznámka pro uložení:"); 

if ($is_multiedit) UNSET($GLOBALS['LOKACE_ID']);
  include_once(FileUp2(".admin/form_schema_lokace.inc"));
                    