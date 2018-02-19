<?php
$is_filter = In_Array($form_params["formtype"], array($f_filter, $f_filter_all));
$is_insert = In_Array($form_params["formtype"], array($f_insert));
$is_multiedit = In_Array($form_params["formtype"], array($f_editall));


     include_once(FileUp2("$path_posta/.admin/javascript.inc"));

if ($is_filter) {
  include_once(FileUp2(".admin/form_schema_filter.inc"));
}
else {

  if ($is_multiedit) {include_once('.admin/form_schema_spisovna.inc');}
  else {


    $FORM_CONFIG["schema"][] = array( "label"=>"Základní údaje");

if ($is_insert) {
  $USER_INFO = $GLOBALS["POSTA_SECURITY"]->GetUserInfo();
  $GLOBALS['PREVZAL_ID'] = $USER_INFO['ID'];
  $GLOBALS['SPISOVNA_ID'] = 1;
  $GLOBALS['DOKUMENT_ID'] = -1;
}
else {
  $GLOBALS['VYHLEDAVANI'] = 1;
}
    $FORM_CONFIG["schema"][] = array("elements"=>array(
                   array( "type"=>"select_spisovna", "name"=>"SPISOVNA_ID","insertnull"=>true,'label'=>'Spisovna','required'=>true),
                   array( "type"=>"hidden", "name"=>"REGISTRATURA","value"=>-1),
                   array( "type"=>"hidden", "name"=>"DIGITALNI","value"=>0),
                   array( "type"=>"hidden", "name"=>"DOKUMENT_ID"),
                ),
      );

    $FORM_CONFIG["schema"][] = array("elements"=>array(
              array( "type"=>"select_vsechny_spisuzly", "name"=>"ODBOR","insertnull"=>true,"add"=>"id=\"ODBOR\" onChange=\"UkazPracovnika(this,'PREDAL_ID');\""),
              ),
              "label"=>'<b>' . $GLOBALS["CONFIG"]["NAZEV_ODBOR"] . ':</b>');

      $FORM_CONFIG["schema"][] = array( "elements"=>array(
                  array( "type"=>"text", "name"=>"CISLO_SPISU1",'label'=>'Pořadové číslo','required'=>false),
                  array( "type"=>"text", "name"=>"CISLO_SPISU2","size"=>8,'label'=>'Rok','required'=>false),
                  array( "type"=>"text", "name"=>"TEXT_CJ","size"=>30,"maxlength"=>29,'label'=>'Celé čj./spis','required'=>false),
                   ),
                  "label"=>$GLOBALS["CONFIG"]["CISLO_SPISU"].":",
              // zruseni format pro tema square
            'theme_config' => array(
              'square' => array(
                'format' => '',
              )
            )
      );



      $FORM_CONFIG["schema"][] = array("elements"=>array(
              array( "type"=>"text", "name"=>"VEC", "size"=>80),
              ),
              "label"=>"Věc:");

      $FORM_CONFIG["schema"][] = array("elements"=>array(
                array( "type"=>"text_number", "name"=>"LISTU",'label'=>'Listů','required'=>true),
                array( "type"=>"text", "name"=>"PRILOHY", "size"=>65,'label'=>'Přílohy'),
              ),
              "label"=>"Počet listů:");

   $FORM_CONFIG["schema"][] = array("elements"=>array(
                array( "type"=>"select_skartace", "name"=>"SKARTACE_ID","size"=>"1", "insertnull"=>true),
              ),
              "label"=>$GLOBALS["CONFIG"]["NAZEV_SKARTACE"].":");


    $FORM_CONFIG["schema"][] = array("elements"=>array(
                   array( "type"=>"select_skartacni_pismeno", "name"=>"SKAR_ZNAK","insertnull"=>true,'label'=>'Písmeno','required'=>true),
                   array( "type"=>"text_number", "name"=>"LHUTA","insertnull"=>true,"size"=>"2",'label'=>'Lhůta','required'=>true),
                ),
      );

    $FORM_CONFIG["schema"][] = array("elements"=>array(
                   array( "type"=>"text_year", "name"=>"ROK_PREDANI","size"=>"4",'label'=>'Rok uzavření spisu','required'=>true,"add"=>"onChange=\"PrepocitejDobu();\""),
                   array( "type"=>"text_year", "name"=>"ROK_SKARTACE","size"=>"4",'label'=>'Rok skartace','required'=>true),
                ),
      );

    $FORM_CONFIG["schema"][] = array( "elements"=>array(
                  array( "type"=>"select_typ_spisu", "name"=>"ULOZENI","value"=>'A','frozen'=>true),
                  array( "type"=>"date_db", "name"=>"DATUM_PREDANI", "insertcalendar"=>true, "insertdatebutton"=>true,'label'=>'Uložení do spisovny','required'=>true),
                   ),
                  "label"=>"Uložení ve spisovně:");

      $FORM_CONFIG["schema"][] = array("elements"=>array(
                array( "type"=>"select_referent", "name"=>"PREDAL_ID", "fullselect"=>true,'label'=>'Předal','required'=>true),
                array( "type"=>"select_referent", "name"=>"PREVZAL_ID", "fullselect"=>true,'label'=>'Převzal','required'=>true),
              ),
      );

        $FORM_CONFIG["schema"][] = array( "elements"=>array(
                  array( "type"=>"textarea", "name"=>"POZNAMKA","cols"=>90, "rows"=>5 ),
                   ),
                  "label"=>"Poznámka pro uložení:");


  include_once(FileUp2(".admin/form_schema_lokace.inc"));
}
}