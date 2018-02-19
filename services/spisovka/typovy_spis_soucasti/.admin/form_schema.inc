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

if ($is_insert || $is_edit) {

  $GLOBALS['DALSI_SPIS_ID'] = 0;
  $GLOBALS['PUVODNI_SPIS'] = $GLOBALS["spis1"]."/".$GLOBALS["spis2"];
  $GLOBALS['NOVY_SPIS'] = $GLOBALS["spis1"]."/".$GLOBALS["spis2"];

  $FORM_CONFIG["schema"][] = array(
    "elements"=>array(array(
      "type"=>"hidden",
      "name"=>"PUVODNI_SPIS",
    ))
  );

  $FORM_CONFIG["schema"][] = array(
    "elements"=>array(array(
      "type"=>"hidden",
      "name"=>"NOVY_SPIS",
    ))
  );

  $FORM_CONFIG["schema"][] = array(
    "elements"=>array(
    		array(
      "type"=>"hidden",
      "name"=>"SPIS_ID",
      "value"=>$GLOBALS['spis_id'],
    ))
  );

  $FORM_CONFIG["schema"][] = array(
    "elements"=>array(array(
      "type"=>"hidden",
      "name"=>"DALSI_SPIS_ID",
      "value"=>0,
    ))
  );

  $FORM_CONFIG["schema"][] = array(
    "elements"=>array(array(
      "type"=>"select_typovy_spis",
      "name"=>"TYPOVY_SPIS",
    )),
    "label" => "Vyberte typový spis"
  );

  $FORM_CONFIG["schema"][] = array(
    "elements"=>array(array(
      "type"=>"text",
      "name"=>"NAZEV_SPISU",
      "size" => 80,
    )),
    "label" => "Zadejte název typového spisu"
  );



}
if ($is_new) {
  $GLOBALS['SOUCAST'] = $GLOBALS['SOUCAST']+1;
	$GLOBALS['NAZEV_SPISU'] = '';
			$FORM_CONFIG["schema"][] = array(
					"elements"=>array(array(
							"type"=>"text",
							"name"=>"NAZEV_SPISU",
							"size" => 80,
					)),
					"label" => "Zadejte název součásti"
			);
  $FORM_CONFIG["schema"][] = array(
    "elements"=>array(
   		array("type"=>"hidden", "name"=>"SOUCAST"),
  		array("type"=>"hidden", "name"=>"DIL", "value"=>1),
   		array("type"=>"hidden", "name"=>"TYPOVY_SPIS", "value"=>1),
   		array("type"=>"hidden", "name"=>"TYPOVY_SPIS_ID"),
   		array("type"=>"hidden", "name"=>"SPIS_ID", "value"=>$GLOBALS['TYPOVY_SPIS_ID']),
    	array("type"=>"hidden", "name"=>"PUVODNI_SPIS"),
    	array("type"=>"hidden", "name"=>"DATUM_OTEVRENI", 'value'=>Date('Y-m-d')),
   		array("type"=>"hidden", "name"=>"NOVY_SPIS"),
    	array("type"=>"hidden", "name"=>"DALSI_SPIS_ID",'value' => -1),
    		
    )
  );
}
