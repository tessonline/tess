<?php
//include(FileUp2(".admin/el/urednik_id_zmena_dat_cas.inc"));
//include(FileUp2(".admin/el/owner_user_date_form_add.inc"));

$GLOBALS["POCET_PRILOH"]=$GLOBALS["POCET_PRILOH"]?$GLOBALS["POCET_PRILOH"]:0;
$GLOBALS["POCET_PRILOH_2"]=$GLOBALS["POCET_PRILOH_2"]?$GLOBALS["POCET_PRILOH_2"]:0;
$GLOBALS["DRUH_PRILOH"]=$GLOBALS["DRUH_PRILOH"]?$GLOBALS["DRUH_PRILOH"]:'písemné';
$GLOBALS["ODESL_ADRKOD"]=$GLOBALS["ODESL_ADRKOD"]?$GLOBALS["ODESL_ADRKOD"]:0;

$GLOBALS["PRILOHY_ZAPOCITAT"]=$GLOBALS["PRILOHY_ZAPOCITAT"]?$GLOBALS["PRILOHY_ZAPOCITAT"]:1;
$GLOBALS["PRILOHY_ZAPOCITAT_2"]=$GLOBALS["PRILOHY_ZAPOCITAT_2"]?$GLOBALS["PRILOHY_ZAPOCITAT_2"]:1;
if (strpos($GLOBALS['DRUH_PRILOH'], '/')) {
  list($GLOBALS["POCET_PRILOH"], $GLOBALS["POCET_PRILOH_2"]) = explode('/', $GLOBALS['DRUH_PRILOH']);
  $GLOBALS["DRUH_PRILOH"] = 'písemné';
  $GLOBALS["DRUH_PRILOH_2"] = 'elektronické';
}

if ($GLOBALS['PRILOHY_ZAPOCITAT']>9) {
   $GLOBALS['PRILOHY_ZAPOCITAT_2'] = substr($GLOBALS['PRILOHY_ZAPOCITAT'], 0,1);
   $GLOBALS['PRILOHY_ZAPOCITAT'] = substr($GLOBALS['PRILOHY_ZAPOCITAT'], 1,1);
}

if ($GLOBALS["DRUH_PRILOH"]== 'elektronické') {
  $GLOBALS["DRUH_PRILOH"] = 'písemné';
  $GLOBALS["DRUH_PRILOH_2"] = 'elektronické';
}

$temp = array();
foreach($FORM_CONFIG["schema"] as $key => $val) {

  if ($FORM_CONFIG["schema"][$key]['elements'][0]['name'] == 'POCET_LISTU') {

    $temp[] = array("elements"=>array(
              array( "type"=>"text_number", "name"=>"POCET_LISTU","required"=>false,"label"=>"Počet listů","size"=>5),
          ),
            "visible"=>!$is_filter && !$is_multiedit,
            "label"=>"Počet listů:");

    $temp[] = array("elements"=>array(
              array( "type"=>"select_druh_priloh", "name"=>"DRUH_PRILOH","value"=>"písemné","add"=>"DISABLED", "required"=>false,'label'=>'Druh příloh'),
              array( "type"=>"text_number", "name"=>"POCET_PRILOH","required"=>false,"label"=>"Počet příloh","size"=>5),
              array( "type"=>"checkbox", "name"=>"PRILOHY_ZAPOCITAT","label"=>"Zůstává u spisu")),
            "visible"=>!$is_filter && !$is_multiedit,
            "label"=>"Druh příloh:");

    $temp[] = array("elements"=>array(
              array( "type"=>"select_druh_priloh", "name"=>"DRUH_PRILOH_2","value"=>"elektronické","add"=>"DISABLED","required"=>false,'label'=>'Druh příloh'),
              array( "type"=>"text_number", "name"=>"POCET_PRILOH_2","required"=>false,"label"=>"Počet příloh","size"=>5),
              array( "type"=>"checkbox", "name"=>"PRILOHY_ZAPOCITAT_2","label"=>"Zůstává u spisu")),
            "visible"=>!$is_filter && !$is_multiedit,
            "label"=>"");


  }

  else
    $temp[] = $val;

}
$FORM_CONFIG['schema'] = $temp;

$temp = array();
foreach($FORM_CONFIG["schema"] as $key => $val) {
//echo $FORM_CONFIG["schema"][$key]['elements'][0]['name'].'<br/>';
  if ($FORM_CONFIG["schema"][$key]['elements'][0]['name'] == 'AGENDA_DOKUMENTU') {
    $temp[] = array("elements"=>array(
                array(
                  "type"=>"select_typ_posty",
                  "name"=>"TYP_POSTY",
                  "insertnull"=>true,
                  "label"=>"Věcná klasifikace",
                  "add"=>'onChange="ZmenaTypuDokumentu(this);"',
  //                "lhuta"=>getLhutaDleKlasifikace()
                )
              ),
              "visible"=>($is_edit or $is_info or $is_insert ) ,
              );

    $temp[] = array("elements"=>array(
                  array( "type"=>"select_jine", "name"=>"JINE","insertnull"=>true,"disabled_onoff"=>$is_multiedit),
             ),
//             "visible"=>$is_edit or $is_info or $is_insert or $is_multiedit or $is_new,
            "label"=>"Věcná fáze:");


  }

  else
    $temp[] = $val;

}
$FORM_CONFIG['schema'] = $temp;



$fce_decin_znak = "
if (document.forms[0].DATUM_VYRIZENI.value && (!document.forms[0].SKARTACE.value || !document.forms[0].VYRIZENO.value)) {
  alert('Při zadání datumu vyřízení je nutné vyplnit spisový znak a způsob vyřízení!');
  return(false);
}
";


$FORM_CONFIG["schema"][] = array("elements"=>array(
   array("type"=>"valid_fce","name_fce"=>$fce_decin_znak)),
      "visible"=>$is_edit && ($GLOBALS['ODESLANA_POSTA']=='f'),
   );

