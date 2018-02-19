<?php
$isEdit = In_Array($form_params['formtype'], array($f_edit));
$isInfo = In_Array($form_params['formtype'], array($f_info));
$isInsert = In_Array($form_params['formtype'], array($f_insert));



if (isset($GLOBALS['doc'])) {
 
  $FORM_CONFIG['schema'][] = array('elements'=>array(
    array(
      'type' => 'select_typ_posty',
      'name' => 'ID_DOKUMENTU',
    )),
    'label'=> 'Druh dokumentu:'
  );
  
  $FORM_CONFIG['schema'][] = array('elements'=>array(
    array(
      'type' => 'hidden',
      'name' => 'ID_AGENDY',
      'value' => $GLOBALS['doc'],
    )),
  );

} else {

  $FORM_CONFIG["schema"][] = array( "elements"=>array(
    array( "type"=>"text", "name"=>"NAZEV")),
    "label"=>"Agenda:");
   
  
 if (!HasRole('access_all')) $GLOBALS['ID_SUPERODBOR'] = EedTools::VratSuperOdbor();

  $FORM_CONFIG["schema"][] = array("elements"=>array(
    array(
      "type"=>"select_superodbor",
      "name"=>"ID_SUPERODBOR",
      "insertnull"=>true,
      "frozen" => !HasRole('access_all')
   ),
  ),
    "visible" => ($GLOBALS['CONFIG']['USE_SUPERODBOR'] ? true : false),
    "label"=>$GLOBALS["CONFIG"]["NAZEV_SUPERODBOR"].":");

  $FORM_CONFIG["schema"][] = array( "elements"=>array(
    array( "type"=>"text", "name"=>"EXTERNAL_ID")),
    "label"=>"Externí ID pro konektor:");

    
  $FORM_CONFIG["schema"][] = array( "elements"=>array(
    array( "type"=>"checkbox", "name"=>"NEAKTIVNI")),
    "label"=>"Neaktivní:");
    
  
}
                          
?>
