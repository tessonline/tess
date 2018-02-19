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

  $GLOBALS['DALSI_SPIS_ID'] = ($_GET['DALSI_SPIS_ID'] ? $_GET['DALSI_SPIS_ID'] : 0);
  if ($is_insert) $GLOBALS['DALSI_SPIS_ID'] = 0;
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
    "elements"=>array(array(
      "type"=>"hidden",
      "name"=>"SPIS_ID",
      "value"=>$GLOBALS['spis_id'],
    ))
  );
  $FORM_CONFIG["schema"][] = array(
    "elements"=>array(array(
      "type"=>"hidden",
      "name"=>"DALSI_SPIS_ID",
      "value"=>$GLOBALS['DALSI_SPIS_ID'],
    ))
  );

  $FORM_CONFIG["schema"][] = array(
    "elements"=>array(array(
      "type"=>"text",
      "name"=>"NAZEV_SPISU",
      "size" => 80,
    )),
    "label" => "Zadejte název"
  );


  if ($_GET['typovy_spis']) {
    $FORM_CONFIG["schema"][] = array( "elements"=>array(
                  array(
                    "type"=>"select_skartace",
                    "name"=>"SKARTACE_ID",
                    "insertnull" => true,
                    "add"=>'onChange="UkazSkartacniRezim(this);"',
                  ),
                  array( "type"=>"hidden", "name"=>"SKARTACE_ID_PUV"),
                   ),
                  "visible"=>$is_edit || $is_insert,
                  "label"=>$GLOBALS["CONFIG"]["NAZEV_SKARTACE"].":");

    $FORM_CONFIG["schema"][] = array( "elements"=>array(
                    array(
                      "type"=>"select_skartacni_rezim",
                      "name"=>"REZIM_ID",
                      "tooltip" => "Vyberte odpovídající skartační režim. Pokud není skartační režim vybrán, bude skartační režim převzat z spisového znaku",
                      "insertnull"=>true),
                   ),
                  "visible"=>$is_edit || $is_insert,
                  "label"=>"Skartační režim:");
  }


}
