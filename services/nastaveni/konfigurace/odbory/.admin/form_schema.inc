<?php
include(FileUp2(".admin/config.inc"));
include(FileUp2(".admin/javascript.inc"));
$is_filter = In_Array($form_params["formtype"], array($f_filter, $f_filter_all));
$is_edit = In_Array($form_params["formtype"], array($f_edit));


$GLOBALS['HODNOTA'] = str_replace('\\', '', $GLOBALS['HODNOTA']);
$GLOBALS['POPIS'] = str_replace('\\', '', $GLOBALS['POPIS']);


  $FORM_CONFIG["schema"][] = array("elements"=>array(
            array( "type"=>"select_nastaveni_kategorie", "name"=>"KATEGORIE","insertnull"=>true,"required"=>true,'frozen' => $is_edit,
                   "add"=>"onChange=\"UkazKonfiguraceHodnota(this);\""),

            ),
            "label"=>"Kategorie:");


  $FORM_CONFIG["schema"][] = array("elements"=>array(
            array( "type"=>"select_nastaveni_kategorie_parametr", "name"=>"PARAMETR",'frozen' => $is_edit),
            array( "type"=>"hidden", "name"=>"SUPERODBOR"),
            ),
            "visible"=>!$is_filter,
            "label"=>"Parametr:");							

      $FORM_CONFIG["schema"][] = array("elements"=>array(
        array( "type"=>"select_vsechny_spisuzly", "name"=>"ODBOR", 'superodbor' => $GLOBALS['SUPERODBOR']),
      ),
        "visible"=>!$is_filter,
        "label"=>'' . $GLOBALS["CONFIG"]["NAZEV_ODBOR"] . ':');


 $FORM_CONFIG["schema"][] = array("elements"=>array(
            array( "type"=>"textarea", "name"=>"HODNOTA","cols"=>50,"rows"=>10),
            ),   
            "visible"=>!$is_filter,
            "label"=>"Popis:");		
