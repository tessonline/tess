<?php
include_once(FileUp2(".admin/config.inc"));
include_once(FileUp2(".admin/javascript.inc"));

$is_filter = In_Array($form_params["formtype"], array($f_filter, $f_filter_all));
$is_filter_all = In_Array($form_params["formtype"], array($f_filter_all));
$is_filter_simple = In_Array($form_params["formtype"], array($f_filter));
$is_insert = In_Array($form_params["formtype"], array($f_insert));
$is_update = In_Array($form_params["formtype"], array($f_insert, $f_edit));
$is_edit = In_Array($form_params["formtype"], array($f_edit));
$is_info = In_Array($form_params["formtype"], array($f_info));
$is_history = In_Array($form_params["formtype"], array($f_history));
$is_new = In_Array($form_params["formtype"], array($f_insertfrom)); 


//die(print_r($GLOBALS));
/*
echo "
  <br />
  cislo_spisu1 = ".$GLOBALS["cislo_spisu1"]."<br />
  cislo_spisu2 = ".$GLOBALS["cislo_spisu2"]."<br />
";
*/
if ($GLOBALS["ODES_TYP"]=='A' || $GLOBALS["ODES_TYP"]=='V' || $GLOBALS["ODES_TYP"]=='Z') $GLOBALS["ODESL_PRIJMENI_NAZEV"]=$GLOBALS["ODESL_PRIJMENI"];
if ($GLOBALS["ODES_TYP"]=='P' || $GLOBALS["ODES_TYP"]=='U') $GLOBALS["ODESL_PRIJMENI_FIRMA"]=$GLOBALS["ODESL_PRIJMENI"];


if ($is_insert) {
  $USER_INFO = $GLOBALS["POSTA_SECURITY"]->GetUserInfo(); 
  if ($GLOBALS["cislo_spisu1"]) $CISLO_SPISU1 = $GLOBALS["cislo_spisu1"];
  if ($GLOBALS["cislo_spisu2"]) $CISLO_SPISU2 = $GLOBALS["cislo_spisu2"];
  if ($GLOBALS["nazev_spisu"]) $NAZEV_SPISU = $GLOBALS["nazev_spisu"];
  if (!$GLOBALS["ODBOR"]) $GLOBALS["ODBOR"] = VratOdbor();
  if (!$GLOBALS["REFERENT"]) $GLOBALS["REFERENT"]=$USER_INFO["ID"];
  If($GLOBALS[CONFIG][NASTAVIT_ODESILATEL]) $GLOBALS["ODES_TYP"]=$GLOBALS[CONFIG][NASTAVIT_ODESILATEL];
}



$FORM_CONFIG["schema"][] = array(
  "elements"=>array(array( "type"=>"hidden", "name"=>"NAZEV_SPISU")),
  "visible"=>false,
);

$FORM_CONFIG["schema"][] = array( "elements"=>array(
  array("type"=>"hidden", "name"=>"CISLO_SPISU1", "value"=>$GLOBALS["cislo_spisu1"], "frozen"=>true),
  array("type"=>"hidden", "name"=>"CISLO_SPISU2", "value"=>$GLOBALS["cislo_spisu2"], "frozen"=>true),
   ),
  "visible"=>$is_insert,
  "label"=>$GLOBALS["CONFIG"]["CISLO_SPISU"].":"
  //"label"=>"Číslo spisu: "
);

    $FORM_CONFIG["schema"][] = array("elements"=>array(
              array( "type"=>"select_vsechny_spisuzly", "name"=>"ODBOR","disabled_onoff"=>true,"add"=>"id=\"ODBOR\" onChange=\"UkazPracovnika(this,'REFERENT');\""),
              ),
              "visible"=>$is_multiedit && (HasRole('podatelna') || HasRole('spravce') || HasRole('zmena_spisového uzlu')),
              "label"=>'' . $GLOBALS["CONFIG"]["NAZEV_ODBOR"] . ':');


  $frozen_ref=true;
  If (HasRole('spravce')||HasRole('vedouci-odbor')||HasRole('podatelna')) {$frozen_ref=false;}

  If (!HasRole('podatelna-odbor') && !HasRole('vedouci-odbor') && !HasRole('spravce') && !HasRole('podatelna') &&!HasRole('zmena-odboru'))
  {
    $odbor=VratOdbor();

     $REFERENT = $USER_INFO["ID"];
    //pokud zapisuji dokumenty na podatelne odboru, pak musime automaticky dopsat datum predani (ze to bylo predano pres CK)
    $FORM_CONFIG["schema"][] = array("elements"=>array(
              array( "type"=>"hidden", "name"=>"ODBOR","value"=>$odbor),
              array( "type"=>"hidden", "name"=>"DATUM_PREDANI","value"=>($is_insert?Date('d.m.Y H:m:s'):$GLOBALS[DATUM_PREDANI])),
              array( "type"=>"hidden", "name"=>"PODATELNA_ID","value"=>($is_insert?$REFERENT:$GLOBALS[PODATELNA_ID])),
              ),
              "visible"=>$is_edit or $is_info or $is_insert ,
              "label"=>"");

  }
  else
  {
    $FORM_CONFIG["schema"][] = array("elements"=>array(
              array( "type"=>"select_vsechny_spisuzly", "name"=>"ODBOR","frozen"=>!(HasRole('spravce')||HasRole('podatelna')||HasRole('zmena_spisového uzlu')),"add"=>"id=\"ODBOR\" onChange=\"UkazPracovnika(this,'REFERENT');\"","insertnull"=>!HasRole('zmena_spisového uzlu')),
              array( "type"=>"select_referent", "name"=>"REFERENT","disabled_onoff"=>$is_multiedit,"fullselect"=>$is_multiedit,"insertnull"=>true,"label"=>"Zpracovatel","frozen"=>$frozen_ref, add=>  "onChange=\"REFERENT_ON()\""),
              array( "type"=>"hidden", "name"=>"PODATELNA_ID","value"=>($is_insert?$REFERENT:$GLOBALS[PODATELNA_ID])),
              ),
              "visible"=>$is_edit or $is_info or $is_insert ,
              "label"=>'' . $GLOBALS["CONFIG"]["NAZEV_ODBOR"] . ':');
  }
$FORM_CONFIG["schema"][] = array("elements"=>array(
  array("type"=>"text", "name"=>"VEC", "size"=>80),
  ),
  "visible"=>true ,										 
  "label"=>"Věc:"
);										 
/*
$FORM_CONFIG["schema"][] = array("elements"=>array(
  array("type"=>"text", "name"=>"DATUM_PODATELNA_PRIJETI", "size"=>20),
  ),
  "visible"=>true ,										 
  "label"=>"Datum zaloľení:"
);										 
*/


if (!$GLOBALS['ODES_TYP']) $GLOBALS['ODES_TYP'] == 'O';
include_once(FileUp2('.admin/form_schema_adresat.inc'));

$FORM_CONFIG["schema"][] = array("elements"=>array(
  array( "type"=>"hidden", "name"=>"DATUM_VYRIZENI"),
  array( "type"=>"hidden", "name"=>"VLASTNICH_RUKOU","value"=>1),
  array( "type"=>"hidden", "name"=>"DATUM_REFERENT_PRIJETI"),
  array( "type"=>"hidden", "name"=>"SKARTACE"),
  array( "type"=>"hidden", "name"=>"VYRIZENO"),
  ),
  "visible"=>true,
  "label"=>""
);


$FORM_CONFIG["schema"][] = array("elements"=>array(
  array( "type"=>"datetime_db", "name"=>"DATUM_PODATELNA_PRIJETI","insertdatebutton"=>true,"required"=>true,"label"=>"Datum přijetí"),   
  ),
  "visible"=>$is_edit or $is_info or $is_insert,										 
  "label"=>"Datum přijetí:"
);		

    $FORM_CONFIG["schema"][] = array("elements"=>array(
              array( "type"=>"text_number", "name"=>"POCET_LISTU","required"=>true,"label"=>"Počet listů"),
              array( "type"=>"text", "name"=>"DRUH_PRILOH","size"=>20,"required"=>true,"label"=>"Druh příloh"),
              array( "type"=>"text_number", "name"=>"POCET_PRILOH","required"=>true,"label"=>"Počet příloh")),
            "format"=>"POCET_LISTU...'&nbsp;&nbsp;&nbsp;Druh příloh:&nbsp;'...DRUH_PRILOH...'&nbsp;&nbsp;&nbsp;Počet(velikost) příloh:&nbsp;'...POCET_PRILOH...'(ks/kB)'",
            "visible"=>!$is_filter && !$is_multiedit,
            "label"=>"Počet listů:",
              // zruseni format pro tema square
            'theme_config' => array(
              'square' => array(
                'format' => '',
              )
            )
      );

if ($GLOBALS["ODES_TYP"])
  echo "<script>DruhAdresata('".$GLOBALS[ODES_TYP]."')</script>";
