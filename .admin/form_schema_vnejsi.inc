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

$input_zakony="<input class=\"button\" type=\"button\" value=\"?\" onclick=\"Zakony()\">";
$puvodni = isset($GLOBALS['ID_PUVODNI']);

$smer=($GLOBALS['ODESLANA_POSTA']=="t" || $GLOBALS['odeslana']=="t") ? "O" : (($GLOBALS['ODES_TYP']!="Z") ? "P" : "");

if ($GLOBALS['CONFIG']['VYHLEDAVANI_NAPRIC_DB'] && $is_filter && !$GLOBALS['SUPERODBOR']) $GLOBALS['SUPERODBOR']=VratSuperOdbor();
if ($is_info) $input_zakony="";

If ($GLOBALS["odeslana"]=="t"){$GLOBALS["ODESLANA_POSTA"]="t";}
If ($is_new) $GLOBALS["ODESLANA_POSTA"]="t";

if ($GLOBALS['CONFIG']['POUZIVAT_SBERNE_ARCHY']) {
  If ($is_new) {
    $GLOBALS['ID_PUVODNI'] = $GLOBALS['EDIT_ID'];  // rychla odpoved
    $GLOBALS['PRIRAD_PODCISLO'] = 1; //pridame dokument do sberneho archu
  }
  If ($is_insert) {
    $GLOBALS["ID_PUVODNI"] = ''; // zalozeni nove odchozi
  }
}
if ($GLOBALS['add_adresat']) {
  $GLOBALS['EXEMPLAR'] = -1; //dalsi vypraveni pridava exemplar
  $GLOBALS['PRIRAD_PODCISLO'] = 0; //nebudeme pridavat lomeni sberneho archu
}

if ($is_new && $GLOBALS['ODES_TYP']=='X') {
  $GLOBALS['ODES_TYP']=$GLOBALS[CONFIG][NASTAVIT_ODESILATEL]?$GLOBALS[CONFIG][NASTAVIT_ODESILATEL]:'0';
  UNSET($GLOBALS['ODESL_PRIJMENI']); UNSET($GLOBALS['ODESL_JMENO']);
}

If ($is_insert && !$GLOBALS["LHUTA"]) $GLOBALS["LHUTA"]='30';

if ($GLOBALS['omez_stav'] == 202) $is_multiedit_odchozi = true; else  $is_multiedit_prichozi = true;


if ($is_filter && !$is_multiedit) $GLOBALS['VYHLEDAVANI']=true; //do of_select se spatne prehnaselo, kvuli referentum

if (isset($GLOBALS['type_content'])) {
  $USER_INFO = $GLOBALS["POSTA_SECURITY"]->GetUserInfo();
  $GLOBALS['DRUH_PRILOH'] = "elektronické";
  $GLOBALS['ODES_TYP'] = "M";
  $GLOBALS['ODBOR'] = VratOdbor();
  $GLOBALS['REFERENT'] = $USER_INFO["ID"];
  $GLOBALS['TYP_DOKUMENTU'] = "D";
}

If ($is_insert && !$GLOBALS["CONFIG"]["ODDELENI"] && (!(HasRole('spravce')||HasRole('podatelna')) || ($GLOBALS["ODESLANA_POSTA"]=='t')))  {
  $GLOBALS["ODBOR"]=VratOdbor();
}

//zrusime DALSI_PRIJEMCI
If (strpos($GLOBALS["DALSI_PRIJEMCI"],':')) $GLOBALS["DALSI_PRIJEMCI"]='';

if ($is_insert && $GLOBALS['odeslana'] == 't') $GLOBALS['MAIN_DOC'] = 1;
if ($GLOBALS['ODESLANA_POSTA']<>'t')
{
  //kvuli multiedit
  if ($is_multiedit && HasRole('podatelna')) $GLOBALS['ODBOR']=VratSuperOdbor();
  if ($is_multiedit && HasRole('editace_uzel') && !$GLOBALS['ODBOR']) $GLOBALS['ODBOR']=VratOdbor();
}
If ($GLOBALS["CONFIG"]["KONTROLA_UIR"])
$KONTROLNI_PANEL="<input type='button' class='button btn' onclick=\"javascript:UirAdr(3714)\" value='UIRADR-okres'>&nbsp;&nbsp;&nbsp;<input type='button'   class='button btn' onclick=\"javascript:UirAdr(0)\" value='UIRADR-ČR'>";
If ($GLOBALS["CONFIG"]["KONTROLA_ROB"])
$KONTROLNI_PANEL_ROB="<input type='button' class='button btn' onclick=\"javascript:Rob()\" value='R'>";

If ($GLOBALS["CONFIG"]["SHOW_C_JEDNACI"])
$VYTVOR_SPIS="<input class=\"button\" type=\"button\" value=\"Vytvoř spis\" onclick=\"".
"window.open('guide.php?G_NAME=posta_vytvorspis&ID=".$GLOBALS["ID"]."&CISLO_JEDNACI1=".$GLOBALS["CISLO_JEDNACI1"]."&CISLO_JEDNACI2=".$GLOBALS["CISLO_JEDNACI2"]."&ODBOR=".$GLOBALS["ODBOR"]."',   'guide', 'height=600px,width=600px,scrollbars,resizable');\">";
else
  $VYTVOR_SPIS="<span id=NastavCJ><input type=\"button\"  class=button onclick=\"NastavCJ(0)\" value=\"Vytvořit číslo jednací\"></span>";
  
  
  if (HasRole('editace_uzel') || HasRole('vedouci-odd') || HasRole('zpracovatel'))
  {
    $GLOBALS["WHERE_ID_ODBOR"] = "WHERE group_id = ".$USER_INFO["GROUP_ID"];
    //  $GLOBALS["ODBOR"] = $USER_INFO["GRPOUP_ID"];
  }
  else
  {
    $GLOBALS["WHERE_ID_ODBOR"] = "";
  }
  
  //$prava_podatelna
  
  //  If ((!$is_filter) and (!$GLOBALS["HISTORY_ID"]) and !$is_multiedit)
  If ((!$GLOBALS["HISTORY_ID"])) {
    //nacteme JS pro praci s ruznejma promennejma
    include_once(FileUp2("$path_posta/.admin/javascript.inc"));
  }
  
  
  if ($GLOBALS["ODESLANA_POSTA"]=="t" && $is_insert) {
    $GLOBALS['REFERENT'] = $USER_INFO["ID"];
    $FORM_CONFIG["schema"][] = array("elements"=>array(
      array( 'type'=>'hidden', 'name'=>'REFERENT','value'=>$USER_INFO["ID"]),
    ),
    );
  }
  
  $FORM_CONFIG["schema"][] = array(
    "visible"=>$is_multiedit,
    "label"=>'Upozornění: pro změnu údajů musíte zaškrtnout checkbox');
  
  
  //nacteme panel s obalkama
  If ($is_edit && $GLOBALS["ODESLANA_POSTA"]=='t')  include_once(FileUp2('.admin/form_schema_obalky.inc'));
  //ukazeme ho i u prichozi, u vlastniho zaznamu
  //  if (!$is_info && !$is_filter)
    //    If (($GLOBALS["ODES_TYP"]=='Z' && $GLOBALS["ODESLANA_POSTA"]=='f')||$GLOBALS[CONFIG][SABLONY_V_PRICHOZICH])  include_once(FileUp2('.admin/form_schema_obalky.inc'));
  
  // příchozí dokument
  //!$is_filter)
  
  //  $cislo_jednaci=FormatCJednaci(1,0);
  //******************************************
  // PRICHOZI DOKUMENT!!!!
  //******************************************
  
  If (($GLOBALS["ODESLANA_POSTA"]<>"t"))
  {
    $FORM_CONFIG["schema"][] = array("elements"=>array(
      array( "type"=>"select_status", "name"=>"STATUS"),
      array( "type"=>"text", "name"=>"DATUM_PREDANI"),
    ),
      "format"=>"'Status:&nbsp;'...STATUS...'&nbsp;Předání:&nbsp;'...DATUM_PREDANI",
      "visible"=>$is_info && HasRole('spravce'),
      "label"=>"Info:");
    
    $rok=date('20y');
    
    // pokud je to první spis, tak není možno měnit č. jednací!!!
    // kdyz je to edit, tak zkontrolovat, jestli na to uz neni odpoved....
    If ($is_edit)
    {
      $podtext='';
      If ($GLOBALS["CISLO_JEDNACI1"]==$GLOBALS["CISLO_SPISU1"] && $GLOBALS["CISLO_JEDNACI2"]==$GLOBALS["CISLO_SPISU2"])
      {
        $Frozen=true; $podtext='(prvotní dokument ve spisu, nelze ho přeřadit jinam)'; //prvotni pisemnost ke spisu!
      }
    }
    //
    If (($UzJeNaToOdpoved)) {$Frozen=true;} else
    { $Frozen=!(HasRole('spravce')||HasRole('zpracovatel')||HasRole('editace_uzel')||HasRole('vedouci-odd')); }
    If (($GLOBALS["CISLO_SPISU1"]==""))
    {$Frozen=!(HasRole('spravce')||HasRole('zpracovatel')||HasRole('editace_uzel')||HasRole('vedouci-odd')); }
    
    If ($GLOBALS["CISLO_SPISU1"]<>"" &&$GLOBALS["CISLO_SPISU1"]<>0)  {
      if ($GLOBALS['MAIN_DOC'] == 2)
        $text="Přeřadit dokument do jiného archu"; //uz je v nejakem archu
        else
          $text="Přeřadit dokument do sběrného archu"; //uz je v nejakem archu
          
          $cislo_spisu=$GLOBALS["cislo_spisu"];
          $novy_spis="";
    }
    else {
      /*
       $text="Přiřadit dokument do sběrného archu";
       $novy_spis=$VYTVOR_SPIS;
       $FORM_CONFIG['schema'][] = array('elements'=>array(
       array( 'type' => 'button', 'name' => 'NastavCjButton', 'value' => 'Přidělit jednací číslo', 'onclick' => 'NastavCJ(0)', 'label' => 'Přidělit jednací číslo', 'tooltip' => 'test'),
       ),
       "visible"=>!$Frozen and !$is_info and !$is_filter and !$is_insert and !$is_multiedit && $GLOBALS['CONFIG']['POUZIVAT_SBERNE_ARCHY'],
       "label"=>$GLOBALS["CONFIG"]["CISLO_SPISU"].":"
       
       );
       */
    }
    include_once(FileUp2('.admin/el/of_spandiv.inc'));
    
    if ($GLOBALS['SHOW_MESSAGE']) {
      $message = "Vkládáte MSG soubor. Prosím zkontrolujte správnost vyplněných údajů, především pole \"Věc\".";
      $FORM_CONFIG['schema'][] = array('elements'=>array(
        array( 'type' => 'span', 'name' => 'SHOW_MESSAGE', 'value' => $message, 'addStyle'=> 'color:red; font-weight:bold;', 'margin_left' => '0px'),
      ),
  
      );
    }
    
    $FORM_CONFIG['schema'][] = array('elements'=>array(
      array( 'type' => 'button', 'name' => 'SbernyArch', 'value' => $text, 'onclick' => "DoSbernehoArchu(".$GLOBALS["ID"].")", 'label' => $text, 'tooltip' => 'test'),
      array( 'type' => 'button', 'name' => 'SbernyArchVyjmuti', 'value' => 'Založit pod nové čj.', 'onclick' => "ZSbernehoArchu(0)", 'label' => 'Vyjmout ze sběrného archu', 'tooltip' => 'test'),
    ),
      "visible"=>!$is_info && $GLOBALS['CONFIG']['POUZIVAT_SBERNE_ARCHY'] && $GLOBALS['CISLO_SPISU1']>0 && $GLOBALS['PODCISLO_SPISU']<>$GLOBALS['CONFIG']['PRVOTNI_PODLOMENI'] ,
      "label"=>$GLOBALS["CONFIG"]["CISLO_SPISU"].":"
    );
    
    
    $FORM_CONFIG['schema'][] = array('elements'=>array(
      array( 'type' => 'button', 'name' => 'SpisButton', 'value' => 'Přiřadit do spisu', 'onclick' => "DoSpisu(".$GLOBALS["ID"].")", 'label' => $text, 'tooltip' => 'test'),
      array( 'type' => 'button', 'name' => 'SpisCreateButton', 'value' => 'Založit spis', 'onclick' => "ZalozitSpis(".$GLOBALS["ID"].")", 'label' => $text, 'tooltip' => 'test'),
    ),
      "visible"=>($is_new || $is_insert) && $GLOBALS['CONFIG']['SPIS_V_EDITACI'],
      "label"=>$GLOBALS["CONFIG"]["CISLO_SPISU"].":"
      
    );
    
    $FORM_CONFIG['schema'][] = array('elements'=>array(
      array( 'type' => 'button', 'name' => 'SpisButton', 'value' => 'Přiřadit do spisu', 'onclick' => "DoSpisu(".$GLOBALS["ID"].")", 'label' => $text, 'tooltip' => 'test'),
      array( 'type' => 'button', 'name' => 'SpisCreateButton', 'value' => 'Založit spis', 'onclick' => "ZalozitSpis(".$GLOBALS["ID"].")", 'label' => $text, 'tooltip' => 'test'),
    ),
      "visible"=>$is_edit && !EedTools::JeDocVeSpisu($GLOBALS['EDIT_ID']) && $GLOBALS['CONFIG']['SPIS_V_EDITACI'],
      "label"=>$GLOBALS["CONFIG"]["CISLO_SPISU"].":"
      
    );
    
    
    $objkod=$GLOBALS['OBJEKT_KOD'];
    $okreskod=$GLOBALS['OKRES_KOD'];
    $FORM_CONFIG['schema'][] = array('elements'=>array(
      array( 'type'=>'hidden', 'name'=>'DOSPISU','value'=>0),
      array( 'type'=>'hidden', 'name'=>'SOUCASTSPISU','value'=>0),
      array( 'type'=>'hidden', 'name'=>'EXEMPLAR','value'=>$GLOBALS['EXEMPLAR']),
      array( 'type'=>'hidden', 'name'=>'CISLO_SPISU1','value'=>$GLOBALS['CISLO_SPISU1']),
      array( 'type'=>'hidden', 'name'=>'CISLO_SPISU2','value'=>$GLOBALS['CISLO_SPISU2']),
      //array( 'type'=>'hidden', 'name'=>'NAZEV_SPISU','value'=>$GLOBALS['NAZEV_SPISU']),
      array( 'type'=>'hidden', 'name'=>'DOPORUCENE','value'=>$GLOBALS['DOPORUCENE']),
      array( 'type'=>'hidden', 'name'=>'DOSBERNEHOARCHU','value'=>''),
      array( 'type'=>'hidden', 'name'=>'ID_PUVODNI','value'=>$GLOBALS['ID_PUVODNI']),
      array( 'type'=>'hidden', 'name'=>'ODESL_ADRKOD','value'=>$adrkod),
      array( 'type'=>'hidden', 'name'=>'OBJEKT_KOD','value'=>$objkod),
      array( 'type'=>'hidden', 'name'=>'OKRES_KOD','value'=>$okreskod),
      array( 'type'=>'hidden', 'name'=>'OBYVATEL_KOD','value'=>''),
      array( 'type'=>'hidden', 'name'=>'ODESL_RC','value'=>''),
      array( 'type'=>'hidden', 'name'=>'ODBOR_SPISU','value'=>$GLOBALS['ODBOR_SPISU']),
      array( 'type'=>'hidden', 'name'=>'FROZEN','value'=>$GLOBALS['FROZEN']),
      array( 'type'=>'hidden', 'name'=>'VLASTNICH_RUKOU','value'=>''),
      array( 'type'=>'hidden', 'name'=>'CISLO_JEDNACI1','value'=>''),
      array( 'type'=>'hidden', 'name'=>'CISLO_JEDNACI2','value'=>''),
      array( 'type'=>'hidden', 'name'=>'DATUM_VYPRAVENI','value'=>''),
      array( 'type'=>'hidden', 'name'=>'DATUM_REFERENT_PRIJETI2','value'=>'')),
      'visible'=>!$is_filter && !$is_multiedit,
    );
    
    $FORM_CONFIG['schema'][] = array('elements'=>array(
                array( 'type'=>'hidden', 'name'=>'ODESLANA_POSTA','value'=>'t')),
                'visible'=>$is_multiedit_odchozi,
                );


    If ($is_insert && $GLOBALS['CONFIG_POSTA']['PLUGINS']['deniky']['enabled'] && $GLOBALS['MAIN_DOC']>1) {
      $FORM_CONFIG['schema'][] = array('elements'=>array(
        array( 'type'=>'hidden', 'name'=>'CISLO_JEDNACI1','value'=>'1'),
        array( 'type'=>'hidden', 'name'=>'MAIN_DOC','value'=>$GLOBALS['MAIN_DOC'])),
      );
    }
    
    
    $FORM_CONFIG['schema'][] = array('elements'=>array(
      array( 'type'=>'hidden', 'name'=>'OLD_CISLO_SPISU1','value'=>$GLOBALS['CISLO_SPISU1']),
      array( 'type'=>'hidden', 'name'=>'OLD_CISLO_SPISU2','value'=>$GLOBALS['CISLO_SPISU2']),
      array( 'type'=>'hidden', 'name'=>'PODCISLO_SPISU','value'=>$GLOBALS['PODCISLO_SPISU']),
      array( 'type'=>'hidden', 'name'=>'PRIRAD_PODCISLO','value'=>0),
      array( 'type'=>'hidden', 'name'=>'EV_CISLO')),
      'visible'=>!$is_filter && !$is_multiedit,              );
      
      
      //    $FORM_CONFIG["schema"][] = array("elements"=>array(
      //                 //array( "type"=>"hidden", "name"=>"TEST"),
      //                 ),
      //                 "format"=>"'<span id=NastavCJ><a class=\"btn btn-loading\" href=\"%\" onclick=\"NastavCJ(1)\">Nepřiřazovat číslo jednací</a></span>'",
      //                 "visible"=>$is_insert,
      //                 "label"=>"&nbsp;");
      //
      //     $FORM_CONFIG["schema"][] = array("elements"=>array(
      //               array( "type"=>"select_superodbor", "name"=>"SUPERODBOR","disabled_onoff"=>true),
      //               ),
      //               "visible"=>$is_multiedit && HasRole('zmena-superodboru'),
      //               "label"=>$GLOBALS["CONFIG"]["NAZEV_SUPERODBOR"].":");
      //
      //     $FORM_CONFIG["schema"][] = array("elements"=>array(
      //               array( "type"=>"select_superodbor", "name"=>"SUPERODBOR","add"=>"onChange=\"VymazOdbor(this);\""),
      //               array( "type"=>"hidden", "name"=>"SUPERODBOR_PUVODNI","value"=>$GLOBALS['SUPERODBOR']),
      //               array( "type"=>"hidden", "name"=>"ODBOR_PUVODNI","value"=>$GLOBALS['ODBOR']),
      //               ),
      //               "visible"=>$is_edit && HasRole('zmena-superodboru'),
      //               "label"=>$GLOBALS["CONFIG"]["NAZEV_SUPERODBOR"].":");
      //
      
      $FORM_CONFIG["schema"][] = array("elements"=>array(
        array( "type"=>"select_superodbor", "name"=>"SUPERODBOR","disabled_onoff"=>true),
      ),
        "visible"=>$is_multiedit && HasRole('zmena-pracoviste') && $GLOBALS['CONFIG']['USE_SUPERODBOR'],
        "label"=>$GLOBALS["CONFIG"]["NAZEV_SUPERODBOR"].":");
      
      $FORM_CONFIG["schema"][] = array("elements"=>array(
        array( "type"=>"select_superodbor", "name"=>"SUPERODBOR","add"=>"onChange=\"VymazOdbor(this);\""),
        array( "type"=>"hidden", "name"=>"SUPERODBOR_PUVODNI","value"=>$GLOBALS['SUPERODBOR']),
        array( "type"=>"hidden", "name"=>"ODBOR_PUVODNI","value"=>$GLOBALS['ODBOR']),
      ),
        "visible"=>$is_edit && HasRole('zmena-pracoviste') && $GLOBALS['CONFIG']['USE_SUPERODBOR'],
        "label"=>$GLOBALS["CONFIG"]["NAZEV_SUPERODBOR"].":");
      
      $FORM_CONFIG["schema"][] = array("elements"=>array(
        array( "type"=>"select_vsechny_spisuzly", "name"=>"ODBOR","disabled_onoff"=>true,"add"=>"id=\"ODBOR\" onChange=\"UkazPracovnika(this,'REFERENT');\""),
      ),
        "visible"=>$is_multiedit && $is_multiedit_prichozi && (HasRole('podatelna') || HasRole('spravce') || HasRole('zmena-spisoveho-uzlu')),
        "label"=>'' . $GLOBALS["CONFIG"]["NAZEV_ODBOR"] . ':');
      
      //zobrazeni poli definovanych ve workflow nactecnych v edit_start.php
      include_once(FileUp2('.admin/form_schema_workflow.inc'));
      $frozen_ref=true;
      If (HasRole('spravce')||HasRole('editace_uzel')||HasRole('podatelna')) {$frozen_ref=false;}
      
      If (!HasRole('podatelna-odbor') && !HasRole('editace_uzel') && !HasRole('spravce') && !HasRole('podatelna') &&!HasRole('zmena-spisoveho-uzlu'))
      {
        $odbor=VratOdbor();
        $REFERENT = $USER_INFO["ID"];
        //pokud zapisuji dokumenty na podatelne odboru, pak musime automaticky dopsat datum predani (ze to bylo predano pres CK)
        $FORM_CONFIG["schema"][] = array("elements"=>array(
          array( "type"=>"hidden", "name"=>"ODBOR","value"=>$odbor),
          array( "type"=>"hidden", "name"=>"REFERENT","value"=>$REFERENT),
          array( "type"=>"hidden", "name"=>"DATUM_PREDANI","value"=>($is_insert?Date('Y-m-d H:i:s'):$GLOBALS[DATUM_PREDANI])),
          array( "type"=>"hidden", "name"=>"PODATELNA_ID","value"=>($is_insert?$REFERENT:$GLOBALS[PODATELNA_ID])),
        ),
          "visible"=>$is_edit or $is_info or $is_insert ,
          "label"=>"");
        
      }
      else
      {
        $FORM_CONFIG["schema"][] = array("elements"=>array(
          array( "type"=>"select_vsechny_spisuzly", "name"=>"ODBOR","frozen"=>!(HasRole('spravce')||HasRole('podatelna')||HasRole('zmena-spisoveho-uzlu')),"add"=>"id=\"ODBOR\" onChange=\"UkazPracovnika(this,'REFERENT','undefined',1);\"","insertnull"=>HasRole('zmena-spisoveho-uzlu')),
          array( "type"=>"select_referent", "name"=>"REFERENT","disabled_onoff"=>$is_multiedit,"fullselect"=>$is_multiedit,"insertnull"=>true,"label"=>"Zpracovatel", add=>  "onChange=\"REFERENT_ON()\""),
          array( "type"=>"hidden", "name"=>"PODATELNA_ID","value"=>($is_insert?$REFERENT:$GLOBALS[PODATELNA_ID])),
        ),
          "visible"=>$is_edit or $is_info or $is_insert ,
          "label"=>'' . $GLOBALS["CONFIG"]["NAZEV_ODBOR"] . ':');
        
        $FORM_CONFIG["schema"][] = array("elements"=>array(
          array( "type"=>"hidden", "name"=>"DATUM_PREDANI","value"=>($is_insert?Date('d.m.Y H:m:s'):$GLOBALS[DATUM_PREDANI])),
        ),
          "visible"=>($is_edit or $is_info or $is_insert) && (HasRole('podatelna-odbor') || HasRole('editace_uzel')) ,
          "label"=>"");
        
      }
      
      
      $FORM_CONFIG["schema"][] = array("elements"=>array(
        array( "type"=>"text", "name"=>"VEC", "size"=>90,"required"=>"true"),
        array( "type"=>"hidden", "name"=>"ROK","value"=>$rok),
      ),
        "visible"=>$is_edit or $is_info or $is_insert ,
        "label"=>"Věc:");
      
      $FORM_CONFIG["schema"][] = array("elements"=>array(
        array( "type"=>"hidden", "name"=>"ODESLANA_POSTA", "value"=>"f")),
        "visible"=>$is_edit or $is_info or $is_insert  or ($is_multiedit && $is_multiedit_prichozi) ,
      );
      
      $FORM_CONFIG["schema"][] = array("elements"=>array(
        array( "type"=>"select_vita", "name"=>"STAV","disabled_onoff"=>$is_multiedit,"fullselect"=>$is_info)
      ),
        "visible"=>$is_edit or $is_info or ($is_multiedit && $is_multiedit_prichozi),
        "label"=>"Kde se vyřizuje:");
      
     
      $FORM_CONFIG["schema"][] = array("elements"=>array(
        array(
          "type"=>"select_agenda_dokumentu",
          //"filter"=>$agenda_filter,
          "filter"=>true,
          "addagenda"=> (isset($GLOBALS['edit'])&&($puvodni==true)) ? VratAgenduDokumentu($GLOBALS['TYP_POSTY']): 0,
          
          "name"=>"AGENDA_DOKUMENTU",
          "insertnull"=>false,
          "multiple"=>$multiple,
          "puvodni"=>isset($GLOBALS['ID_PUVODNI']),
          "add"=>"onChange=\"UkazTypPosty(this,'TYP_POSTY','','',0,'".$GLOBALS['TYP_POSTY']."','','".$smer."');\"","label"=>"Agenda"
        ),
        array(
          "type"=>"select_typ_posty",
          "name"=>"TYP_POSTY",
          "default_agenda" => !isset($GLOBALS['ID_PUVODNI']),
          "insertnull"=>false,
          "filter"=>true,
          "label"=>"Druh dokumentu",
          "required" => true,
          "add"=>" onchange=\"ZmenaTypuDokumentu(this); AgendaDocOnChange(this,'AGENDA_DOKUMENTU','".$GLOBALS['odeslana']."','".$GLOBALS['EDIT_ID']."');\" ",
          //                "lhuta"=>getLhutaDleKlasifikace()
        ),
        array( 'type' => 'button', 'name' => 'TYP_POSTY_NAPOVEDA', 'value' => '?', 'onclick' => 'TypPosty()', 'label' => 'TPN'),
        
      ),
        "visible"=>($is_edit or $is_info or $is_insert),
      );
      
      
      $FORM_CONFIG["schema"][] = array("elements"=>array(
        array( "type"=>"select_typ_dokumentu", "name"=>"TYP_DOKUMENTU","insertnull"=>true,"disabled_onoff"=>$is_multiedit,"label"=>"Typ dokumentu"),
      ),
        "visible"=>($is_edit or $is_info or $is_insert ) ,
        //              "format"=>"TYP_POSTY...'&nbsp;&nbsp;&nbsp;Typ dokumentu:&nbsp;'...TYP_DOKUMENTU",
        
        // zruseni format pro tema square
        'theme_config' => array(
          'square' => array(
            'format' => '',
          )
        )
      );
      
      //     $FORM_CONFIG["schema"][] = array("elements"=>array(
      //               array( "type"=>"select_typ_dokumentu", "name"=>"TYP_DOKUMENTU","insertnull"=>true,"disabled_onoff"=>$is_multiedit,"label"=>"Typ dokumentu"),
      //               ),
      //               "visible"=>($is_edit or $is_info or $is_insert or $is_multiedit) && ($GLOBALS['MAIN_DOC']==0),
      //               "label"=>"Typ dokumentu:");
      //
      
      //nacteme adresaty
      include_once(FileUp2('.admin/form_schema_adresat.inc'));
      
      $FORM_CONFIG["schema"][] = array("elements"=>array(
        array( "type"=>"text", "name"=>"JEJICH_CJ","label"=>"Číslo jednací firmy","add"=>' id="JEJICH_CJ"',"size"=>60),
        array( "type"=>"date_db", "name"=>"JEJICH_CJ_DNE","label"=>"Ze dne","insertdatebutton"=>true),
      ),
        "format"=>"JEJICH_CJ...'&nbsp;&nbsp;&nbsp;ze&nbsp;dne:&nbsp;'...JEJICH_CJ_DNE",
        "visible"=>$is_edit or $is_info or $is_insert or $is_filter_all,
        "label"=>"Vaše čj.:",
        // zruseni format pro tema square
        'theme_config' => array(
          'square' => array(
            'format' => '',
          )
        )
      );
      
      $FORM_CONFIG["schema"][] = array("elements"=>array(
        array( "type"=>"datetime_db", "name"=>"DATUM_PODATELNA_PRIJETI","insertdatebutton"=>true,"required"=>true,"frozen"=>!(HasRole('spravce')||HasRole('podatelna') || HasRole('edit-datum-prijeti')),"label"=>"Datum přijetí","add"=>"datetime=\"true\""),
        array( "type"=>"select_druh_prijeti", "name"=>"ZPUSOB_PODANI","required"=>true,"label"=>"Způsob přijetí"),
        array( "type"=>"checkbox", "name"=>"PRIVATE","required"=>false,"label"=>"Do vlastních rukou"),
      ),
        "format"=>"DATUM_PODATELNA_PRIJETI...'&nbsp;&nbsp;&nbsp;Způsob podání:&nbsp;'...ZPUSOB_PODANI...'&nbsp;&nbsp;&nbsp;Do vlastních rukou: '...PRIVATE",
        "visible"=>$is_edit or $is_info or $is_insert,
        "label"=>"Datum přijetí:",
        'theme_config' => array(
          'square' => array(
            'format' => '',
          )
        )
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
      $FORM_CONFIG["schema"][] = array("elements"=>array(
        array( "type"=>"text_number", "name"=>"ZMOCNENI_ZAKON","label"=>"Zmocnění: zákon"),
        array( "type"=>"text_number", "name"=>"ZMOCNENI_ROK","label"=>"rok"),
        array( "type"=>"text_number", "name"=>"ZMOCNENI_PAR","label"=>"paragraf"),
        array( "type"=>"text_number", "name"=>"ZMOCNENI_ODST","label"=>"ostavec"),
        array( "type"=>"text", "name"=>"ZMOCNENI_PISMENO","label"=>"písmeno"),
      ),
        "format"=>"'Zákon:&nbsp;'...ZMOCNENI_ZAKON...'&nbsp;/&nbsp;'...ZMOCNENI_ROK...'&nbsp;$input_zakony&nbsp;§&nbsp;'...ZMOCNENI_PAR...'&nbsp;&nbsp;&nbsp;odstavec:&nbsp;'...ZMOCNENI_ODST...'&nbsp;&nbsp;&nbsp;písmeno:&nbsp;'...ZMOCNENI_PISMENO",
        "visible"=>$is_edit or $is_info or $is_insert or $is_new,
        "label"=>"Zmocnění:",
        // zruseni format pro tema square
        'theme_config' => array(
          'square' => array(
            'format' => '',
          )
        )
      );
      
      // pokud jde o refenta, musime ukayat frouznuty okno...
      $frozen_ref=!(HasRole('spravce')||HasRole('editace_uzel')||HasRole('vedouci-odd'));
      If ($frozen_ref)
      {
        If ($GLOBALS["REFERENT"]=="" && !HasRole('podatelna'))
        {
          $GLOBALS["REFERENT"]=$REFERENT;
          $jmeno_referenta=UkazUsera($GLOBALS["REFERENT"]);
        }
        $FORM_CONFIG["schema"][] = array("elements"=>array(
          //            array( "type"=>"hidden", "name"=>"REFERENT","label"=>"Zpracovatel"),
          //           array( "type"=>"select_referent", "name"=>"REFERENT","insertnull"=>true,"label"=>"Zpracovatel","frozen"=>true),
          array( "type"=>"datetime_db", "name"=>"DATUM_REFERENT_PRIJETI","label"=>"Zpracovatel přečetl","insertdatebutton"=>true,"add"=>"datetime=\"true\"")
        ),
        //              "format"=>"REFERENTACEK...'&nbsp;&nbsp;&nbsp;Zpracovatel přečetl&nbsp;'...DATUM_REFERENT_PRIJETI",
          "visible"=>$is_edit or $is_info or $is_insert,
          "label"=>'' . $GLOBALS["CONFIG"]["NAZEV_REFERENT"] . ':',
          // zruseni format pro tema square
          'theme_config' => array(
            'square' => array(
              'format' => '',
            )
          )
        );
      }
      else
      {
        $odbor=VratOdbor();
        
        If ($odbor<>$GLOBALS["ODBOR"]) {$frozen_ref=true;}
        If (HasRole('spravce')||HasRole('editace_uzel')||HasRole('editace_admin')||HasRole('editace_zpracovatel')||HasRole('podatelna')) {$frozen_ref=false;}
        $frozen_ref = false;
        $FORM_CONFIG["schema"][] = array("elements"=>array(
        //                array( "type"=>"select_referent", "name"=>"REFERENT","disabled_onoff"=>$is_multiedit,"fullselect"=>$is_multiedit,"insertnull"=>true,"label"=>"Zpracovatel","frozen"=>$frozen_ref, add=>  "onChange=\"REFERENT_ON()\""),
          array( "type"=>"datetime_db", "name"=>"DATUM_REFERENT_PRIJETI","label"=>"Zpracovatel přečetl","insertdatebutton"=>true,"frozen"=>($frozen_ref),"add"=>"datetime=\"true\""),
        ),
          //               "format"=>"'<span id=REFERENT>'...REFERENT...'</span>&nbsp;&nbsp;&nbsp;Zpracovatel přečetl&nbsp;'...DATUM_REFERENT_PRIJETI",
          "visible"=>$is_edit or $is_info or $is_insert,
          "label"=>'' . $GLOBALS["CONFIG"]["NAZEV_REFERENT"] . ':',
          // zruseni format pro tema square
          'theme_config' => array(
            'square' => array(
              'format' => '',
            )
          )
        );
        
        //                array( "type"=>"select_referent", "name"=>"REFERENT","fullselect"=>($is_multiedit && HasRole('podatelnaX')),"disabled_onoff"=>$is_multiedit,"insertnull"=>true,"label"=>"Zpracovatel","frozen"=>$frozen_ref, add=>  "onChange=\"REFERENT_ON()\""),
        
        $FORM_CONFIG["schema"][] = array("elements"=>array(
          array( "type"=>"select_referent", "name"=>"REFERENT","fullselect"=>false,"disabled_onoff"=>$is_multiedit,"insertnull"=>true,"label"=>"Zpracovatel","frozen"=>$frozen_ref, add=>  "onChange=\"REFERENT_ON()\""),
          array( "type"=>"hidden", "name"=>"MULTIEDIT","value"=>1),
        ),
          "visible"=>$is_multiedit&& $is_multiedit_prichozi ,
          "label"=>'' . $GLOBALS["CONFIG"]["NAZEV_REFERENT"] . ':');
        
      }
      
      
      $FORM_CONFIG["schema"][] = array("elements"=>array(
        array( "type"=>"text_number", "name"=>"LHUTA","size"=>"5","frozen"=>!(HasRole('spravce')||HasRole('editace_uzel')||HasRole('editace_admin')||HasRole('editace_vse_pracoviste')),"label"=>"Lhůta"),
        array( "type"=>"date_db", "name"=>"LHUTA_VYRIZENI","size"=>"5","insertdatebutton"=>true,"frozen"=>!(HasRole('spravce')||HasRole('editace_uzel')||HasRole('editace_vse_pracoviste')||HasRole('editace_admin')),"label"=>"Vyřídit do"),
        array( "type"=>"datetime_db", "name"=>"DATUM_VYRIZENI","label"=>"Datum vyřízení","insertdatebutton"=>true,"frozen"=>!(HasRole('spravce')||HasRole('editace_vse_pracoviste')||HasRole('editace_zpracovatel')||HasRole('editace_admin')||HasRole('editace_uzel')||HasRole('vedouci-odd')||HasRole('zpracovatel')),"add"=>"datetime=\"true\""),
      ),
        "format"=>"LHUTA...'&nbsp;&nbsp;&nbsp;Do&nbsp;dne:'...LHUTA_VYRIZENI...'&nbsp;&nbsp;&nbsp;&nbsp;Datum vyřízení&nbsp;'...DATUM_VYRIZENI",
        "visible"=>$is_edit or $is_info or $is_insert,
        "label"=>"Lhůta k vyřízení:",
        // zruseni format pro tema square
        'theme_config' => array(
          'square' => array(
            'format' => '',
          )
        )
      );
      
      $FORM_CONFIG["schema"][] = array("elements"=>array(
        array( "type"=>"datetime_db", "name"=>"DATUM_VYRIZENI","insertdatebutton"=>true,"label"=>"Datum vyřízení","disabled_onoff"=>$is_multiedit,"add"=>"datetime=\"true\""),
      ),
        "visible" => $is_multiedit && $is_multiedit_prichozi, //lhuty budeme resit i u odchozich
         "label"=>"Lhůta k vyřízení:",
      );
      
      
      //    $FORM_CONFIG["schema"][] = array("elements"=>array(
      //               array( "type"=>"date_db", "name"=>"DATUM_VYRIZENI","label"=>"Datum vyřízení","insertdatebutton"=>true,"disabled_onoff"=>$is_multiedit),
      //               ),
      //               "visible"=>$is_multiedit,
      //               "label"=>"Datum vyřízení:");
      
      $FORM_CONFIG["schema"][] = array(
        "elements"=>array(array(
          "type"=>"select_vyrizeno",
          "name"=>"VYRIZENO",
          "insertnull"=>true,
          //       "frozen"=>!(HasRole('spravce')||HasRole('editace_uzel')||HasRole('vedouci-odd')||HasRole('zpracovatel')),
          "disabled_onoff"=>$is_multiedit && $is_multiedit_prichozi ,
          'size' => 20,
          //       'maxlength' => 100
        )),
        "visible"=>$is_edit or $is_info or $is_insert or ($is_multiedit && $is_multiedit_prichozi),
        "label"=>"Způsob vyřízení:"
      );
      
      If ($GLOBALS["CONFIG"]["UKAZ_ULOZENO"])
      $FORM_CONFIG["schema"][] = array("elements"=>array(
        array( "type"=>"select_ulozeno", "name"=>"ULOZENO","insertnull"=>true,"frozen"=>!(HasRole('spravce')||HasRole('editace_uzel')||HasRole('vedouci-odd')||HasRole('zpracovatel'))),
      ),
        "label"=>"Uloženo:");


        $FORM_CONFIG["schema"][] = array("elements"=>array(
          array( "type"=>"text_number", "name"=>"POCET_LISTU","disabled_onoff"=>$is_multiedit,"label"=>"Počet listů"),
          array( "type"=>"text", "name"=>"DRUH_PRILOH","size"=>20,"disabled_onoff"=>$is_multiedit,"label"=>"Druh příloh"),
          array( "type"=>"text_number", "name"=>"POCET_PRILOH","disabled_onoff"=>$is_multiedit,"label"=>"Počet příloh")),
            "visible"=>$is_multiedit && $is_multiedit_odchozi,
        );

            $FORM_CONFIG["schema"][] = array("elements"=>array(
              array( "type"=>"select_typ_odeslani", "name"=>"DOPORUCENE", "width"=>10,"disabled_onoff"=>$is_multiedit,'label'=>'Obálka'),
              array( "type"=>"select_druh_odeslani", "name"=>"VLASTNICH_RUKOU","disabled_onoff"=>$is_multiedit,'label'=>'Vypravení')),
              "visible"=>$is_multiedit && $is_multiedit_odchozi,
            );

          $FORM_CONFIG["schema"][] = array("elements"=>array(
              array( "type"=>"datetime_db", "name"=>"DATUM_PODATELNA_PRIJETI","disabled_onoff"=>$is_multiedit,"insertdatebutton"=>true, "add"=>"datetime=\"true\"",'label'=>$GLOBALS['CONFIG']['NAZEV_DATUM_ODESLANI']),
            ),
            "visible"=>$is_multiedit && $is_multiedit_odchozi,
          );

          $FORM_CONFIG["schema"][] = array("elements"=>array(
              array( "type"=>"datetime_db", "name"=>"DATUM_VYPRAVENI","disabled_onoff"=>$is_multiedit,"insertdatebutton"=>true,"label"=>"Datum vypravení","add"=>"datetime=\"true\""),
            ),
            "visible"=>$is_multiedit && $is_multiedit_odchozi,
          );

          $FORM_CONFIG["schema"][] = array("elements"=>array(
            array( "type"=>"datetime_db", "name"=>"DATUM_DORUCENI","disabled_onoff"=>$is_multiedit,"insertdatebutton"=>true,"label"=>"Datum doručení","add"=>"onChange=\"Vypnout_PM()\" datetime=\"true\""),
            ),
            "visible"=>$is_multiedit && $is_multiedit_odchozi,
          );

          $FORM_CONFIG["schema"][] = array("elements"=>array(
            array( "type"=>"datetime_db", "name"=>"DATUM_PM","disabled_onoff"=>$is_multiedit,"insertdatebutton"=>true,"label"=>"Datum právní moci","add"=>"datetime=\"true\""),
            ),
            "visible"=>$is_multiedit && $is_multiedit_odchozi,
          );




      
      $FORM_CONFIG["schema"][] = array("elements"=>array(
      //              array( "type"=>"text", "name"=>"POZNAMKA","size"=>"80","maxlength"=>250),
        array( "type"=>"textarea", "name"=>"POZNAMKA","cols"=>"80","rows"=>3,"disabled_onoff"=>$is_multiedit),
      ),
        "visible"=>$is_edit or $is_info or $is_insert or $is_multiedit,
        "label"=>"Poznámka:");
      
      $FORM_CONFIG["schema"][] = array("elements"=>array(
        array( "type"=>"select_skartace_kod", "name"=>"SKARTACEKOD","size"=>"1","disabled_onoff"=>$is_multiedit, "insertnull"=>true,'label'=>'Kód','add'=> "onChange=\"ZmenSkartace(this);\" style=\"width: 630px;\""),
        array( "type"=>"select_skartace", "name"=>"SKARTACE","size"=>"1","disabled_onoff"=>$is_multiedit, "insertnull"=>true,"ukazjenaktivni"=>$is_insert, "width"=>"15"),
      ),
        "visible"=>$is_edit or $is_info or $is_insert,
        "label"=>$GLOBALS["CONFIG"]["NAZEV_SKARTACE"].":");
      
      $FORM_CONFIG["schema"][] = array("elements"=>array(
        array( "type"=>"select_skartace", "name"=>"SKARTACE","size"=>"1","disabled_onoff"=>$is_multiedit, "insertnull"=>true,"ukazjenaktivni"=>$is_insert, "width"=>"15"),
      ),
        "visible"=>$is_multiedit,
        "label"=>$GLOBALS["CONFIG"]["NAZEV_SKARTACE"].":");
      
      
      //   If ($GLOBALS["DALSI_PRIJEMCI"]==",") {$GLOBALS["DALSI_PRIJEMCI"]="";}
      //   If ($is_info)
      //   {$prijemci=UkazOdesilatele($GLOBALS[DALSI_PRIJEMCI],'n');}
      //   else
        //   {$prijemci=UkazOdesilatele($GLOBALS[DALSI_PRIJEMCI],'a');}
      //$prijemci=$GLOBALS[DALSI_PRIJEMCI];
      
      //echo $prijemci;
      $FORM_CONFIG["schema"][] = array("elements"=>array(
        array( "type"=>"hidden", "name"=>"DALSI_PRIJEMCI"),
      ),
        "visible"=>$is_edit or $is_insert,
        "label"=>"</tr><tr><td>Další odesílatelé:</td><td><span id=\"PRIJEMCI_SPAN\" style=\"font-weight:bold;\">".$prijemci."</span><br/><input   type='button' class='button btn' value='Přidat další odesílatele dokumentu' onclick=\"Prijemci('posta_prijemci');\"></td></tr>");
      
      
      $FORM_CONFIG["schema"][] = array("elements"=>array(
        array( "type"=>"hidden", "name"=>"DALSI_PRIJEMCI"),
      ),
        "visible"=>$is_info,
        "label"=>"</tr><tr><td>Další odesílatelé:</td><td><span id=\"PRIJEMCI_SPAN\" style=\"font-weight:bold;\">".$prijemci."</span></td></tr>");
      
      
  }
  
  
  //******************************************
  // Odpoved na dopis!!!!
  //******************************************
  
  
  if ($is_new || $is_insert) $GLOBALS["ROK"]=Date('Y');
  
  if ($is_new && $GLOBALS["ODES_TYP"]=='M') {
    //nastavime u emailu odeslani primo elektronicky
    $GLOBALS["DOPORUCENE"]='E';
    $GLOBALS["VLASTNICH_RUKOU"]=5;
    $GLOBALS["ODESL_SUBJ"]="Re: ".$GLOBALS["ODESL_SUBJ"];
  }
  if ($is_insert && $GLOBALS['ODESLANA_POSTA']=='t') {
    $pole=OdborPrac($USER_INFO["ID"]);
    $GLOBALS['ODBOR']=$pole['odbor'];
  }
  if ($is_edit) {
    //pokud uz je pridelen kod pro ceskou postu
    if ($cisloPostaCK = EedCeskaPosta::VratCK($GLOBALS['EDIT_ID'])) $disabled_vypraveni = 'DISABLED';
    else $disabled_vypraveni = '';
    
    //onma, po dohode s zaloudkem
    $disabled_vypraveni = '';
  }
  
  if (($GLOBALS["ODESLANA_POSTA"]=="t") or ($is_filter_all)) {


    $FORM_CONFIG['schema'][] = array('elements'=>array(
       array("type"=>"radio", "name"=>"ZALOZIT_ARCH", "value"=>"1",
              "options"=>array("nový exemplář vypravení (CISLO/ROK-X-Y) "=>"1","nový dokument SA (CISLO/ROK-X ) "=>"2")
      ),
    ),
      "visible"=>$is_new && $GLOBALS['CONFIG']['POUZIVAT_SBERNE_ARCHY']  && $GLOBALS['add_adresat']==1 ,
      "label"=>"Založit jako:"
    );

    
    $FORM_CONFIG["schema"][] = array("elements"=>array(
      array( "type"=>"select_status", "name"=>"STATUS"),
      array( "type"=>"text", "name"=>"DATUM_PREDANI_VEN"),
    ),
      "format"=>"'Status:&nbsp;'...STATUS...'&nbsp;Předání:&nbsp;'...DATUM_PREDANI_VEN",
      "visible"=>$is_info && HasRole('spravce'),
      "label"=>"Info:");
    
    //        $FORM_CONFIG["schema"][] = array("elements"=>array(
    //                     //array( "type"=>"hidden", "name"=>"TEST"),
    //                     ),
    //                     "format"=>"'<span id=NastavCJ><input type=\"button\"  class=button onclick=\"NastavCJ(1)\" value=\"Nepřiřazovat číslo jednací\"></span>'",
    //                     "visible"=>$is_insert,
    //                     "label"=>"&nbsp;");
    //
    $text="Přeřadit dokument do sběrného archu";
    
    $FORM_CONFIG['schema'][] = array('elements'=>array(
      array( 'type' => 'button', 'name' => 'SbernyArch', 'value' => $text, 'onclick' => "DoSbernehoArchu(".$GLOBALS["ID"].")", 'label' => $text, 'tooltip' => 'test'),
      array( 'type' => 'button', 'name' => 'SbernyArchVyjmuti', 'value' => 'Založit pod nové čj.', 'onclick' => "ZSbernehoArchu(0)", 'label' => 'Vyjmout ze sběrného archu', 'tooltip' => 'test'),
    ),
      //          		"visible"=>!$is_info && $GLOBALS['CONFIG']['POUZIVAT_SBERNE_ARCHY'] && $GLOBALS['CISLO_SPISU1']>0,
      "visible"=>$is_edit && $GLOBALS['CONFIG']['POUZIVAT_SBERNE_ARCHY'] && $GLOBALS['CISLO_SPISU1']>0 && $GLOBALS['PODCISLO_SPISU']<>$GLOBALS['CONFIG']['PRVOTNI_PODLOMENI'] ,
      "label"=>$GLOBALS["CONFIG"]["CISLO_SPISU"].":"
    );
    $FORM_CONFIG['schema'][] = array('elements'=>array(
      array( 'type' => 'button', 'name' => 'SpisButton', 'value' => 'Přiřadit do spisu', 'onclick' => "DoSpisu(".$GLOBALS["ID"].")", 'label' => $text, 'tooltip' => 'test'),
      array( 'type' => 'button', 'name' => 'SpisCreateButton', 'value' => 'Založit spis', 'onclick' => "ZalozitSpis(".$GLOBALS["ID"].")", 'label' => $text, 'tooltip' => 'test'),
    ),
      "visible"=>$is_insert && $GLOBALS['CONFIG']['SPIS_V_EDITACI'],
      "label"=>$GLOBALS["CONFIG"]["CISLO_SPISU"].":"
      
    );
    
    $FORM_CONFIG['schema'][] = array('elements'=>array(
      array( 'type' => 'button', 'name' => 'SpisButton', 'value' => 'Přiřadit do spisu', 'onclick' => "DoSpisu(".$GLOBALS["ID"].")", 'label' => $text, 'tooltip' => 'test'),
      array( 'type' => 'button', 'name' => 'SpisCreateButton', 'value' => 'Založit spis', 'onclick' => "ZalozitSpis(".$GLOBALS["ID"].")", 'label' => $text, 'tooltip' => 'test'),
    ),
      "visible"=>$is_edit && !EedTools::JeDocVeSpisu($GLOBALS['EDIT_ID']) && $GLOBALS['CONFIG']['SPIS_V_EDITACI'],
      "label"=>$GLOBALS["CONFIG"]["CISLO_SPISU"].":"
      
    );
    
    
    // $FORM_CONFIG["schema"][] = array("visible"=>$filter_all,"label"=>"Detaily odchozí pošty");
    $objkod=$GLOBALS["OBJEKT_KOD"];
    $okreskod=$GLOBALS["OKRES_KOD"];
    
    $FORM_CONFIG["schema"][] = array("elements"=>array(
      array( 'type'=>'hidden', 'name'=>'DOSPISU','value'=>0),
      array( 'type'=>'hidden', 'name'=>'SOUCASTSPISU','value'=>0),
      array( "type"=>"hidden", "name"=>"TEXT_CJ","value"=>$GLOBALS["TEXT_CJ"]),
      array( "type"=>"hidden", "name"=>"CISLO_SPISU1","value"=>$GLOBALS["CISLO_SPISU1"]),
      array( "type"=>"hidden", "name"=>"CISLO_SPISU2","value"=>$GLOBALS["CISLO_SPISU2"]),
      //array( "type"=>"hidden", "name"=>"NAZEV_SPISU","value"=>$GLOBALS["NAZEV_SPISU"]),
      array( "type"=>"hidden", "name"=>"PODCISLO_SPISU","value"=>$GLOBALS["PODCISLO_SPISU"]),
      array( "type"=>"hidden", "name"=>"ID_PUVODNI","value"=>$GLOBALS["ID_PUVODNI"]),
      array( "type"=>"hidden", "name"=>"ODESL_ADRKOD","value"=>$GLOBALS["ODESL_ADRKOD"]),
      array( "type"=>"hidden", "name"=>"OBJEKT_KOD","value"=>"$objkod"),
      array( "type"=>"hidden", "name"=>"OKRES_KOD","value"=>"$okreskod"),
      array( "type"=>"hidden", "name"=>"OBYVATEL_KOD","value"=>""),
      array( "type"=>"hidden", "name"=>"ODESL_RC","value"=>""),
      array( 'type'=>'hidden', 'name'=>'DOSBERNEHOARCHU','value'=>''),
      array( "type"=>"hidden", "name"=>"CISLO_JEDNACI1","value"=>$GLOBALS["CISLO_JEDNACI1"]),
      array( "type"=>"hidden", "name"=>"FROZEN","value"=>$GLOBALS["FROZEN"]),
      array( "type"=>"hidden", "name"=>"DALSI_ID_AGENDA","value"=>$GLOBALS["DALSI_ID_AGENDA"]),
      array( "type"=>"hidden", "name"=>"CISLO_JEDNACI2","value"=>$GLOBALS["CISLO_JEDNACI2"]),
      array( "type"=>"hidden", "name"=>"PRIRAD_PODCISLO","value"=>$podcislo),
      array( "type"=>"hidden", "name"=>"ODBOR_SPISU","value"=>$GLOBALS["ODBOR_SPISU"]),
    ),
      "visible"=>!$is_filter,
    );
    
    $FORM_CONFIG["schema"][] = array( "elements"=>array(
      array( "type"=>"hidden", "name"=>"OLD_CISLO_SPISU1","value"=>$GLOBALS["CISLO_SPISU1"]),
      array( "type"=>"hidden", "name"=>"OLD_CISLO_SPISU2","value"=>$GLOBALS["CISLO_SPISU2"]),
    ),
      "label"=>"");
    
    
    
    //  If (!HasRole('spravce'))
    {
      $FORM_CONFIG["schema"][] = array("elements"=>array(
        array( "type"=>"hidden", "name"=>"ODBOR","value"=>$GLOBALS["ODBOR"]),
        array( "type"=>"hidden", "name"=>"ODDELENI","value"=>$GLOBALS["ODDELENI"]),
      ),
        "visible"=>$is_edit or $is_info or $is_insert or $is_new,
        "label"=>"");
    }
    /*
     else
     {
     $FORM_CONFIG["schema"][] = array("elements"=>array(
     array( "type"=>"select_odbor", "name"=>"ODBOR"),
     ),
     "visible"=>$is_edit or $is_info or $is_insert  or $is_new,
     "label"=>'<b>' . $GLOBALS["CONFIG"]["NAZEV_ODBOR"] . ':</b>');
     $FORM_CONFIG["schema"][] = array("elements"=>array(
     array( "type"=>"select_oddeleni", "name"=>"ODDELENI","insertnull"=>true),
     ),
     "visible"=>($is_edit or $is_info or $is_insert  or $is_new) && $GLOBALS[CONFIG][ODDELENI],
     "label"=>"Oddělení:");
     }
     */
    $FORM_CONFIG["schema"][] = array("elements"=>array(
      array( "type"=>"hidden", "name"=>"EV_CISLO"),
      array( "type"=>"hidden", "name"=>"ODESLANA_POSTA","value"=>'t'),
      //              array( "type"=>"hidden", "name"=>"REFERENT","value"=>$GLOBALS["REFERENT"]),
      array( "type"=>"hidden", "name"=>"EDITOVANE_ID","value"=>$GLOBALS["EDITOVANE_ID"]),
      array( "type"=>"hidden", "name"=>"ID_PUVODNI","value"=>$GLOBALS["ID_PUVODNI"]),
      array( "type"=>"hidden", "name"=>"EXEMPLAR","value"=>$GLOBALS["EXEMPLAR"]),
      array( "type"=>"hidden", "name"=>"ROK", "value"=>$rok),
    ),
      "visible"=>$is_edit or $is_info or $is_insert or $is_new,
      "label"=>"");
    
    include_once(FileUp2('.admin/form_schema_workflow.inc'));
    
    
    $FORM_CONFIG["schema"][] = array("elements"=>array(
      array( "type"=>"text", "name"=>"VEC", "size"=>90,"required"=>"true")),
      "visible"=>$is_edit or $is_info or $is_insert or $is_new,
      "label"=>"Věc:");
      
      $FORM_CONFIG["schema"][] = array(
        "elements"=>array(
          array( "type"=>"text", "name"=>"ZNACKA"),
        ),
        
        "visible"=>!$is_multiedit,
        "label"=>"Značka ČJ:"
      );
      
      if (($GLOBALS['add_adresat']==1))
      //if (($GLOBALS['add_adresat']==1)||($GLOBALS['co']=="insertfrom"))
        $FORM_CONFIG["schema"][] = array("elements"=>array(
          array(
            "type"=>"hidden",
            "name"=>"TYP_POSTY1",
            "value" => $GLOBALS['TYP_POSTY'],
          ),
        ),
        );
        
        $agenda_count = sizeof(getSelectDataEed(new of_select_agenda_dokumentu(array())));
        
           $odchozi_posta = $GLOBALS['odeslana'];
           $odchozi_posta = $GLOBALS['ODESLANA_POSTA'];
        if (isset($GLOBALS['ID_PUVODNI'])) $odchozi_posta = "t";
        
        
        $FORM_CONFIG["schema"][] = array("elements"=>array(
          array(
            "type"=>"select_agenda_dokumentu",
            "filter"=>true,
            "name"=>"AGENDA_DOKUMENTU",
            "insertnull"=>false,
            "addagenda"=> (isset($GLOBALS['insertfrom'])&&($puvodni==true)) ? VratAgenduDokumentu($GLOBALS['TYP_POSTY']): 0,
            //"frozen" => $puvodni,
            "add"=>"onChange=\"UkazTypPosty(this,'TYP_POSTY','','',0,'".$GLOBALS['TYP_POSTY']."','','".$smer."');\"","label"=>"Agenda"),
          array(
            "type"=>"select_typ_posty",
            "name"=>"TYP_POSTY",
            "insertnull"=>false,
            "agendacount"=>$agenda_count,
            "width"=>10,
            "required" => true,
            //"frozen"=>!($insert||$GLOBALS['MAIN_DOC']==1) or $puvodni,
            "add"=>"onChange=\"ZmenaTypuDokumentu(this); AgendaDocOnChange(this,'AGENDA_DOKUMENTU','".$odchozi_posta."','".$GLOBALS['EDIT_ID']."');\" onfocus=\"this.selectedIndex = -1;\"",
            "label"=>"Druh dokumentu"
          ),
          array( 'type' => 'button', 'name' => 'TYP_POSTY_NAPOVEDA', 'value' => '?', 'onclick' => 'TypPosty()', 'label' => 'TPN'),
          
        ),
          "visible"=>  ($is_edit or $is_info or $is_insert or $is_new),
          
          'theme_config' => array(
            'square' => array(
              'format' => '',
            )
          )
        );
        
        $FORM_CONFIG["schema"][] = array("elements"=>array(
          array( "type"=>"select_typ_dokumentu", "name"=>"TYP_DOKUMENTU","insertnull"=>false,"label"=>"Typ dokumentu"),
        ),
          "visible"=>($is_edit or $is_info or $is_insert or $is_new) && $GLOBALS['MAIN_DOC']==1,
          "label"=>"Typ dokumentu:",
          'theme_config' => array(
            'square' => array(
              'format' => '',
            )
          )
        );
        
        
        $FORM_CONFIG["schema"][] = array("elements"=>array(
          array( "type"=>"select_typ_dokumentu", "name"=>"TYP_DOKUMENTU","insertnull"=>true,"disabled_onoff"=>$is_multiedit),
        ),
          "visible"=>($is_edit or $is_info or $is_insert or $is_multiedit) && ($GLOBALS['MAIN_DOC']==0),
          "label"=>"Typ dokumentu:");
        
        
        
        
        /*
         $FORM_CONFIG["schema"][] = array("elements"=>array(
         array( "type"=>"select_odes_typ", "name"=>"ODES_TYP", "width"=>10,"required"=>"true",add=>"onChange=\"ON_OFF_rozh()\"")),
         "visible"=>$is_insert or $is_new,
         "label"=>"Adresát:");
         */
        //nacteme adresaty
        include_once(FileUp2('.admin/form_schema_adresat.inc'));

        $FORM_CONFIG["schema"][] = array("elements"=>array(
          array( "type"=>"text", "name"=>"JEJICH_CJ","label"=>"Číslo jednací firmy","size"=>60),
          array( "type"=>"date_db", "name"=>"JEJICH_CJ_DNE","label"=>"Ze dne","insertdatebutton"=>true),
        ),
          "format"=>"JEJICH_CJ...'&nbsp;&nbsp;&nbsp;ze&nbsp;dne:&nbsp;'...JEJICH_CJ_DNE",
          "visible"=>!$is_filter && !$is_multiedit,
          "label"=>"Vaše čj.:",
          'theme_config' => array(
            'square' => array(
              'format' => '',
            )
          )
        );
/*

      $FORM_CONFIG["schema"][] = array("elements"=>array(
        array( "type"=>"text_number", "name"=>"LHUTA","size"=>"5","frozen"=>!(HasRole('spravce')||HasRole('editace_uzel')||HasRole('editace_admin')||HasRole('editace_vse_pracoviste')),"label"=>"Lhůta"),
        array( "type"=>"date_db", "name"=>"LHUTA_VYRIZENI","size"=>"5","insertdatebutton"=>true,"frozen"=>!(HasRole('spravce')||HasRole('editace_uzel')||HasRole('editace_vse_pracoviste')||HasRole('editace_admin')),"label"=>"Vyřídit do"),
        array( "type"=>"datetime_db", "name"=>"DATUM_VYRIZENI","label"=>"Datum vyřízení","insertdatebutton"=>true,"frozen"=>!(HasRole('spravce')||HasRole('editace_vse_pracoviste')||HasRole('editace_zpracovatel')||HasRole('editace_admin')||HasRole('editace_uzel')||HasRole('vedouci-odd')||HasRole('zpracovatel')),"add"=>"datetime=\"true\""),
      ),
        "format"=>"LHUTA...'&nbsp;&nbsp;&nbsp;Do&nbsp;dne:'...LHUTA_VYRIZENI...'&nbsp;&nbsp;&nbsp;&nbsp;Datum vyřízení&nbsp;'...DATUM_VYRIZENI",
        "visible"=>$is_edit or $is_info or $is_insert,
        "label"=>"Lhůta k vyřízení:",
        // zruseni format pro tema square
        'theme_config' => array(
          'square' => array(
            'format' => '',
          )
        )
      );
*/
        //ukazeme informaci, ze jde o postu z vlastniho podnetu (bylo Vlož odchozí)
        If ($GLOBALS["ID_PUVODNI"]=="")
        $FORM_CONFIG["schema"][] = array("elements"=>array(),
          "format"=>"'<b>DOKUMENT Z VLASTNÍHO PODNĚTU</b>'",
          "visible"=>$is_info,
          "label"=>"Pozn:");
        
        $FORM_CONFIG["schema"][] = array("elements"=>array(
          array( "type"=>"text_number", "name"=>"ZMOCNENI_ZAKON","label"=>"Zmocnění: zákon"),
          array( "type"=>"text_number", "name"=>"ZMOCNENI_ROK","label"=>"rok"),
          array( "type"=>"text_number", "name"=>"ZMOCNENI_PAR","label"=>"paragraf"),
          array( "type"=>"text_number", "name"=>"ZMOCNENI_ODST","label"=>"ostavec"),
          array( "type"=>"text", "name"=>"ZMOCNENI_PISMENO","label"=>"písmeno"),
        ),
          "format"=>"'Zákon:&nbsp;'...ZMOCNENI_ZAKON...'&nbsp;/&nbsp;'...ZMOCNENI_ROK...'&nbsp;$input_zakony&nbsp;§&nbsp;'...ZMOCNENI_PAR...'&nbsp;&nbsp;&nbsp;odstavec:&nbsp;'...ZMOCNENI_ODST...'&nbsp;&nbsp;&nbsp;písmeno:&nbsp;'...ZMOCNENI_PISMENO",
          "visible"=>$is_edit or $is_info or $is_insert or $is_new,
          "label"=>"Zmocnění:",
          'theme_config' => array(
            'square' => array(
              'format' => '',
            )
          )
        );
        
        
        
        /*
         $FORM_CONFIG["schema"][] = array("elements"=>array(
         array( "type"=>"select_typ_odeslani", "name"=>"DOPORUCENE", "width"=>10,"required"=>"true"),
         array( "type"=>"select_druh_odeslani", "name"=>"VLASTNICH_RUKOU", "width"=>10,"required"=>"true","add"=>"onChange=\"Predani()\"")),
         "format"=>"DOPORUCENE...'&nbsp;&nbsp;&nbsp;Doručení:&nbsp;'...VLASTNICH_RUKOU",
         "visible"=>$is_edit or $is_info or $is_insert or $is_new,
         "label"=>"Odeslat:");
         */
        
        reset($GLOBALS["CONFIG"]["TYP_ODESLANI"]);
        
        $GLOBALS['datum_podatelna_prichozi']=$GLOBALS["DATUM_PODATELNA_PRIJETI"];
        If (($is_insert) or ($is_new) && !$GLOBALS['add_adresat']) Unset($GLOBALS["DATUM_PODATELNA_PRIJETI"]);
        
        if ($GLOBALS['add_adresat']) { //pridani dalsiho adresata
          UNSET($GLOBALS['DATUM_VYPRAVENI']); UNSET($GLOBALS['DATUM_DORUCENI']);
          UNSET($GLOBALS['DATUM_PM']); UNSET($GLOBALS['ODESL_PRIJMENI']);
          UNSET($GLOBALS['ODESL_PRIJMENI_FIRMA']); UNSET($GLOBALS['ODESL_PRIJMENI_NAZEV']);
          UNSET($GLOBALS['ODESL_OSLOVENI']); UNSET($GLOBALS['ODESL_JMENO']);
          UNSET($GLOBALS['ODESL_DATNAR']); UNSET($GLOBALS['ODESL_TITUL']);
          UNSET($GLOBALS['ODESL_ICO']); UNSET($GLOBALS['ODESL_ULICE']);
          UNSET($GLOBALS['ODESL_CP']); UNSET($GLOBALS['ODESL_COR']);
          UNSET($GLOBALS['ODESL_POSTA']); UNSET($GLOBALS['ODESL_PSC']);
          UNSET($GLOBALS['ODESL_OSOBA']); UNSET($GLOBALS['ODESL_EMAIL']);
          UNSET($GLOBALS['ODESL_SUBJ']); UNSET($GLOBALS['ODESL_REKOMANDO']);
          UNSET($GLOBALS['ODESL_POSTAODESL']); UNSET($GLOBALS['ODESL_DATSCHRANKA']);
        }
        
        //dalsi dokumenty do obalky
        $add="nic není zařazeno.";
        $img="<img src='".FileUp2('images/people_address.gif')."' border=0>";
        
        if ($is_edit || $is_info)
        {
          include_once(FileUp2('.admin/oth_funkce.inc'));
          $sql='select * from posta_hromadnaobalka where obalka_id='.$GLOBALS["EDIT_ID"];
          $q->query($sql);
          $adresat=array();
          while ($q->Next_Record())
          {
            $adresat[]=strip_tags(FormatCJednaci($q->Record["DOKUMENT_ID"]))." - ".UkazAdresu($q->Record["DOKUMENT_ID"],', ');
          }
          if (count($adresat)>0) $add=implode('<br/>',$adresat);
          if ($is_edit)
            $dalsi_obalky='<a href="#" onclick="window.open(\'services/spisovka/dalsi_obalky/edit.php?edit&EDIT_ID='.$GLOBALS["EDIT_ID"].'&REFERENT='.$REFERENT.'\');" title="'.$add.'">'.$img.'</a>';
            else
            {
              //dodelame info okno pekne do divu...
              $dalsi_obalky="<a onclick='if (document.getElementById(\"dalsi_adresati\").style.display==\"block\") document.getElementById(\"dalsi_adresati\").style.display=\"none\"; else document.getElementById(\"dalsi_adresati\").style.display=\"block\";'>$img</a>";
              if (count($adresat)==0)
              {
                $sql='select * from posta_hromadnaobalka where dokument_id='.$GLOBALS["EDIT_ID"];
                $q->query($sql);
                $adresat=array();
                while ($q->Next_Record())
                {
                  $adresat[]="<a href='edit.php?info&EDIT_ID=".$q->Record["OBALKA_ID"]."'>".strip_tags(FormatCJednaci($q->Record["OBALKA_ID"]))."</a> - ".UkazAdresu($q->Record["OBALKA_ID"],', ');
                }
                if (count($adresat)>0) $add=implode('<br/>',$adresat);
                $dalsi_obalky.="<div id='dalsi_adresati' style='display:none'><br/><b>Dokument je zařazen v této obálce:</b><br/>".$add."</div><br/>";
              }
              else
                $dalsi_obalky.="<div id='dalsi_adresati' style='display:none'><br/><b>Další dokumenty v této obálce:</b><br/>".$add."</div><br/>";
            }
        }
        //konec dalsich dokumentu do obalky
        
        $FORM_CONFIG["schema"][] = array("elements"=>array(
          array( "type"=>"text_number", "name"=>"POCET_LISTU","required"=>true,"label"=>"Počet listů"),
          array( "type"=>"text", "name"=>"DRUH_PRILOH","size"=>20,"required"=>true,"label"=>"Druh příloh"),
          array( "type"=>"text_number", "name"=>"POCET_PRILOH","required"=>true,"label"=>"Počet příloh")),
          "format"=>"POCET_LISTU...'&nbsp;&nbsp;&nbsp;Druh příloh:&nbsp;'...DRUH_PRILOH...'&nbsp;&nbsp;&nbsp;Počet(velikost) příloh:&nbsp;'...POCET_PRILOH...'(ks/kB)'",
          "visible"=>!$is_filter && !$is_multiedit,
          "label"=>"Počet listů:",
          'theme_config' => array(
            'square' => array(
              'format' => '',
            )
          )
        );
        
        
        if (HasRole("zmena-referenta"))
        {
          $FORM_CONFIG["schema"][] = array("elements"=>array(
            array( "type"=>"select_referent", "name"=>"REFERENT","value"=>$GLOBALS["REFERENT"]),
            array( "type"=>"hidden", "name"=>"OLD_REFERENT","value"=>$GLOBALS["REFERENT"]),
          ),
            "visible"=>$is_edit or $is_info or $is_insert or $is_new,
            "label"=>"Referent:");
        }
        else
          $FORM_CONFIG["schema"][] = array("elements"=>array(
            array( "type"=>"hidden", "name"=>"REFERENT","value"=>$GLOBALS["REFERENT"]),
          ),
            "visible"=>$is_edit or $is_info or $is_insert or $is_new,
            "label"=>"");
          
          
          
          if (HasRole('spravce')||HasRole('lokalni-spravce')||HasRole('podatelna')||HasRole('podatelna-odbor')||HasRole('edit-datum-vypraveni'))
          {
            
            $FORM_CONFIG["schema"][] = array("elements"=>array(
              array( "type"=>"select_typ_odeslani", "name"=>"DOPORUCENE", "width"=>10,"required"=>"true", "add"=>"onChange=\"DatumVypraveni(this);\" $disabled_vypraveni ","label"=>"Obálka"),
              array( "type"=>"select_druh_odeslani", "name"=>"VLASTNICH_RUKOU", "omez_prava"=>true ,"width"=>10,"required"=>"true","add"=>"onChange=\"TypObalky(this,'1');\" $disabled_vypraveni ","label"=>"Způsob vypravení")),
              "format"=>"DOPORUCENE...'&nbsp;&nbsp;&nbsp;Doručení:&nbsp;'...VLASTNICH_RUKOU...'&nbsp;$dalsi_obalky'",
              "visible"=>$is_edit or $is_info or $is_insert or $is_new,
              "label"=>"Způsob vypravení:",
              'theme_config' => array(
                'square' => array(
                  'format' => '',
                )
              )
            );
            
            $FORM_CONFIG["schema"][] = array("elements"=>array(
              array( 'type' => 'text', 'name' => 'KOD_CP', 'value' => $cisloPostaCK, 'label' => 'Kód zásilky pro Českou poštu', 'frozen'=>true),
            ),
              "visible"=>($disabled_vypraveni<>''?true:false),
              'theme_config' => array(
                'square' => array(
                  'format' => '',
                )
              )
            );
            
            
            $FORM_CONFIG["schema"][] = array("elements"=>array(
              array( 'type' => 'button', 'name' => 'HromObalka', 'value' => 'Hromadná obálka', 'onclick' => 'NewWindowGuide(\'services/spisovka/dalsi_obalky/edit.php?edit&EDIT_ID='.$GLOBALS["EDIT_ID"].'&REFERENT='.$REFERENT.'\');' , 'label' => 'Hromadná obálka'),
            ),
              "visible"=>$is_edit or $is_info,
              'theme_config' => array(
                'square' => array(
                  'format' => '',
                )
              )
            );
            
            
            $FORM_CONFIG["schema"][] = array("elements"=>array(
              array( "type"=>"checkbox", "name"=>"OBALKA_NEVRACET","label"=>"nevracet"),
              array( "type"=>"checkbox", "name"=>"OBALKA_10DNI","label"=>"Jen 10 dní"),
            ),
              "format"=>"OBALKA_NEVRACET...'Nevracet, vložit do schránky&nbsp;&nbsp;&nbsp;'...OBALKA_10DNI...'Jen 10 dní&nbsp;'",
              "visible"=>$is_edit or $is_info or $is_insert or $is_new,
              "label"=>"Na obálku:",
              'theme_config' => array(
                'square' => array(
                  'format' => '',
                )
              )
            );
            
            
            $FORM_CONFIG["schema"][] = array("elements"=>array(
              array( "type"=>"datetime_db", "name"=>"DATUM_PODATELNA_PRIJETI","required"=>true,"insertdatebutton"=>true, "add"=>"datetime=\"true\""),
              array( "type"=>"datetime_db", "name"=>"DATUM_VYPRAVENI","insertdatebutton"=>true,"label"=>"Datum vypravení","add"=>"datetime=\"true\"")),
              "format"=>"DATUM_PODATELNA_PRIJETI...'&nbsp;&nbsp;&nbsp;Datum vypravení:&nbsp;'...DATUM_VYPRAVENI",
              "visible"=>$is_edit or $is_info or $is_insert or $is_new,
              "label"=>$GLOBALS['CONFIG']['NAZEV_DATUM_ODESLANI'],
              'theme_config' => array(
                'square' => array(
                  'format' => '',
                )
              )
            );
          }
          else
          {
            $FORM_CONFIG["schema"][] = array("elements"=>array(
              array( "type"=>"select_typ_odeslani", "name"=>"DOPORUCENE", "width"=>10,"required"=>"true", "add"=>"onChange=\"DatumVypraveni(this);\" $disabled_vypraveni ","label"=>"Obálka"),
              array( "type"=>"select_druh_odeslani", "name"=>"VLASTNICH_RUKOU", "omez_prava"=>true, "width"=>10,"required"=>"true","add"=>"onChange=\"Predani(); TypObalky(this,'1');\" $disabled_vypraveni","label"=>"Způsob vypravení")),
              "format"=>"DOPORUCENE...'&nbsp;&nbsp;&nbsp;Doručení:&nbsp;'...VLASTNICH_RUKOU...'&nbsp;$dalsi_obalky'",
              "visible"=>$is_edit or $is_info or $is_insert or $is_new,
              "label"=>"Odeslat:",
              'theme_config' => array(
                'square' => array(
                  'format' => '',
                )
              )
            );
            
            $FORM_CONFIG["schema"][] = array("elements"=>array(
              array( 'type' => 'button', 'name' => 'HromObalka', 'value' => 'Hromadná obálka', 'onclick' => 'NewWindowGuide(\'services/spisovka/dalsi_obalky/edit.php?edit&EDIT_ID='.$GLOBALS["EDIT_ID"].'&REFERENT='.$REFERENT.'\');' , 'label' => 'Hromadná obálka'),
            ),
              "visible"=>$is_edit or $is_info,
              'theme_config' => array(
                'square' => array(
                  'format' => '',
                )
              )
            );
            
            
            
            $FORM_CONFIG["schema"][] = array("elements"=>array(
              array( "type"=>"checkbox", "name"=>"OBALKA_NEVRACET","label"=>"nevracet"),
              array( "type"=>"checkbox", "name"=>"OBALKA_10DNI","label"=>"Jen 10 dní"),
            ),
              "format"=>"OBALKA_NEVRACET...'Nevracet, vložit do schránky&nbsp;&nbsp;&nbsp;'...OBALKA_10DNI...'Jen 10 dní&nbsp;'",
              "visible"=>$is_edit or $is_info or $is_insert or $is_new,
              "label"=>"Na obálku:",
              'theme_config' => array(
                'square' => array(
                  'format' => '',
                )
              )
            );
            
            $FORM_CONFIG["schema"][] = array("elements"=>array(
              array( "type"=>"datetime_db", "name"=>"DATUM_PODATELNA_PRIJETI","required"=>true,"insertdatebutton"=>true,"add"=>"datetime=\"true\""),
              array( "type"=>"datetime_db", "name"=>"DATUM_VYPRAVENI","insertdatebutton"=>true,"label"=>"Datum vypravení","add"=>"datetime=\"true\"")),
              "format"=>"DATUM_PODATELNA_PRIJETI...'&nbsp;&nbsp;&nbsp;Datum vypravení:&nbsp;'...DATUM_VYPRAVENI",
              "visible"=>$is_edit or $is_info or $is_insert or $is_new,
              "label"=>$GLOBALS['CONFIG']['NAZEV_DATUM_ODESLANI'],
              'theme_config' => array(
                'square' => array(
                  'format' => '',
                )
              )
            );
          }
          
          
          $FORM_CONFIG["schema"][] = array("elements"=>array(
            array( "type"=>"datetime_db", "name"=>"DATUM_DORUCENI","insertdatebutton"=>true,"label"=>"Datum doručení","add"=>"onChange=\"Vypnout_PM()\" datetime=\"true\""),
            array( "type"=>"datetime_db", "name"=>"DATUM_PM","insertdatebutton"=>true,"label"=>"Datum právní moci","add"=>"datetime=\"true\"")),
            "format"=>"DATUM_DORUCENI...'&nbsp;&nbsp;&nbsp;Datum&nbsp;právní&nbsp;moci:&nbsp;'...DATUM_PM",
            "visible"=>$is_edit or $is_info or $is_insert or $is_new,
            "label"=>"Datum doručení:",
            'theme_config' => array(
              'square' => array(
                'format' => '',
              )
            )
          );
          
          If ($GLOBALS["CONFIG"]["UKAZ_ULOZENO"])
          $FORM_CONFIG["schema"][] = array("elements"=>array(
            array( "type"=>"select_ulozeno", "name"=>"ULOZENO","insertnull"=>true,"frozen"=>!(HasRole('spravce')||HasRole('editace_uzel')||HasRole('vedouci-odd')||HasRole('zpracovatel'))),
          ),
            "visible"=>!$is_filter,
            "label"=>"Uloženo:");
          
          $FORM_CONFIG["schema"][] = array("elements"=>array(
            //              array( "type"=>"text", "name"=>"POZNAMKA","size"=>"80","maxlength"=>250),
            array( "type"=>"textarea", "name"=>"POZNAMKA","cols"=>"80","rows"=>3),
          ),
            "visible"=>!$is_filter,
            "label"=>"Poznámka:");
          
          $FORM_CONFIG["schema"][] = array("elements"=>array(
            array( "type"=>"text", "name"=>"POZNAMKA","size"=>"80","maxlength"=>250),
          ),
            "visible"=>$is_filter,
            "label"=>"Poznámka:");
          
          //       if ($is_edit && HasRole('podatelna') && $REFERENT<>$GLOBALS[REFERENT] && $GLOBALS[REFERENT]<>0)
            //       {
            //        $FORM_CONFIG["schema"][] = array("elements"=>array(
            //                   array( "type"=>"hidden", "name"=>"SKARTACE"),
            //                  ),
            //                   "visible"=>$is_new or $is_insert or $is_info or $is_edit,
            //                   "label"=>"");
            //       }
          //
          //       else
          $FORM_CONFIG["schema"][] = array("elements"=>array(
            array( "type"=>"select_skartace_kod", "name"=>"SKARTACEKOD","size"=>"1","disabled_onoff"=>$is_multiedit, "insertnull"=>true,'label'=>'Kód','add'=> "onChange=\"ZmenSkartace(this);\" style=\"width: 630px;\""),
            array( "type"=>"select_skartace", "name"=>"SKARTACE", "insertnull"=>true,"size"=>"1","ukazjenaktivni"=>($is_insert||$is_new)?true:false, "width"=>"15","required"=>($GLOBALS['CONFIG']['ODCHOZI_DOC_POVINNY_SPISZNAK'])),
          ),
            "visible"=>$is_new or $is_insert or $is_info or $is_edit,
            "label"=>$GLOBALS["CONFIG"]["NAZEV_SKARTACE"].":");
          
          
  $FORM_CONFIG['schema'][] = array('elements'=>array(
                      array( "type"=>"checkbox", "name"=>"KOPIE_SOUBORU_ANO","label"=>"Přidat přílohy z příchozího dokumentu do odpovědi"),
                      array( "type"=>"hidden", "name"=>"KOPIE_SOUBORU_HODNOTA","value"=>$GLOBALS['EDIT_ID']),
              ),
        "visible"=>$is_new && !$GLOBALS['add_adresat'],
        "label"=>"Přidat přílohy z příchozího dokumentu do odpovědi");


  if ($is_new && $GLOBALS['EDIT_ID']>0) {
    $sql = 'select status from posta where id=' . $GLOBALS['EDIT_ID'];
    $q->query($sql); $q->Next_Record();

    $FORM_CONFIG['schema'][] = array('elements'=>array(
                        array( "type"=>"checkbox", "name"=>"PRICHOZI_VYRIZEN","label"=>"Označit příchozí dokument jako vyřízený"),
                ),
          "visible"=>$is_new && !$GLOBALS['add_adresat'] && $q->Record['STATUS']>1 && $q->Record['STATUS']<>9,
          "label"=>"Označit příchozí dokument jako vyřízený");
  }


            //       If ($is_info)
            //       {$prijemci=UkazAdresaty($GLOBALS[DALSI_PRIJEMCI],'n');}
            //       else
              //       {$prijemci=UkazAdresaty($GLOBALS[DALSI_PRIJEMCI],'a');}
            
            //$prijemci=$GLOBALS[DALSI_PRIJEMCI];
            
            
            /*
             IF (($GLOBALS["ID_PUVODNI"]<>$GLOBALS["EDIT_ID"]) and ($is_info) and ($GLOBALS["ID_PUVODNI"]<>""))
             {
             
             
             $FORM_CONFIG["schema"][] = array("elements"=>array(
             array( "type"=>"text", "name"=>"BLABLA","value"=>UkazPrvotnihoAdresata($GLOBALS[ID_PUVODNI]))),
             "visible"=>$is_info,
             "label"=>"Prvotní adresát:");
             }
             */
            //  If ($GLOBALS["ID_PUVODNI"]) {$puvodni_prij="<input type='button' class='button btn' value='Prvotní adresáti'   onclick=\"window.open('./services/spisovka/adresy/adresati.php?ID=".$GLOBALS["ID_PUVODNI"]."', 'adresati', 'height=1px,width=1px,left=0,top=0,scrollbars')\"'>";}
            
            $FORM_CONFIG["schema"][] = array("elements"=>array(
              array( "type"=>"hidden", "name"=>"DALSI_PRIJEMCI"),
            ),
              "visible"=>$is_insert or $is_new,
              "label"=>"</tr><tr><td>Další adresáti:</td><td><span id=\"PRIJEMCI_SPAN\" style=\"font-weight:bold;\">".$prijemci."</span><br/><input   type='button' class='button btn' value='Přidat další adresáty dokumentu' onclick=\"Prijemci('posta_adresati');\">&nbsp;&nbsp;&nbsp;$puvodni_prij</td></tr>");
            
            
            $FORM_CONFIG["schema"][] = array("elements"=>array(
              array( "type"=>"hidden", "name"=>"DALSI_PRIJEMCI"),
            ),
              "visible"=>$is_info,
              "label"=>"</tr><tr><td>Další adresáti:</td><td><span id=\"PRIJEMCI_SPAN\" style=\"font-weight:bold;\">".$prijemci."</span></td></tr>");
            
            
            //konec odchozi posty
  }
  
  
  
  
  
  If ($is_info && $GLOBALS["ODESLANA_POSTA"]=='t' && $GLOBALS["CONFIG"]["XERTEC"])  include(FileUp2("plugins/xertec/.admin/form_schema_xertec.inc"));
  //   If ($is_edit && $GLOBALS["ODESLANA_POSTA"]=='t' && (HasRole('spravce')||HasRole('podatelna')) && $GLOBALS["CONFIG"]["XERTEC"])
  //      include(FileUp2("plugins/xertec/.admin/form_schema_xertec.inc"));
  
  
  $FORM_CONFIG["schema"][] = array("elements"=>array(
    array( "type"=>"hidden","name"=>"KOPIE_SOUBORU","value"=>$GLOBALS['EDIT_ID'])),
    "visible"=>($GLOBALS['EDIT_ID'] && $GLOBALS['add_adresat']==1),
    "label"=>""
  );
  
  
  //include(FileUp2(".admin/el/urednik_id_zmena_dat_cas.inc"));
  //include(FileUp2(".admin/el/owner_user_date_form_add.inc"));
  
  
  If ($is_info && !$GLOBALS["VCETNE_HISTORIE"])
  {   $ev_cis=$GLOBALS["EV_CISLO"];
  $where=$_SESSION["WHERE_PODMINKA"];
  If ($where<>"") {$sql='SELECT id FROM posta p WHERE ev_cislo > ('.$ev_cis.') '.$where.' order by id ASC';}
  else {  $ev_cis=$GLOBALS["EV_CISLO"]+1;$sql='SELECT  id FROM posta WHERE ev_cislo > ('.$ev_cis.') order by id ASC';}
  //    echo $sql;
  $q=new DB_POSTA;
  $q->query($sql);
  $dalsizaznam=$q->Num_Rows();
  If ($dalsizaXznam>0)
  {
    $q->Next_Record();
    $ID=$q->Record["ID"];
    $FORM_CONFIG["schema"][] = array("elements"=>array(
      array( "type"=>"hidden", "name"=>"EV_CISLO"),
    ),
      "label"=>"</table><table width=100% border=0><td width=100% align=right><input type='button' class='button btn'   onclick='document.location.href=\"edit.php?info&EDIT_ID=".$ID."\"' value='  Další  '>&nbsp;<input type='button' class='button btn' onclick='window.close()'   value='  Zavřít  '></td>");
  }
  else
  {
    $FORM_CONFIG["schema"][] = array("elements"=>array(
      array( "type"=>"hidden", "name"=>"EV_CISLO"),
    ),
      "label"=>"</table><table width=100% border=0><td width=100% align=right><input type='button' class='button btn' onclick='window.close()'   value='  Zavřít  '></td>");
    
  }
  
  }
  
  $fce = "
  if (!document.forms[0].ODESL_ADRKOD.value) {
   if (!confirm('POZOR: Pozor, adresa nebyla ověřena přes UIRADR!!\\n\\nPokračovat?')){return(false)};
   }
  ";
  $fce2="
  if (document.forms[0].DATUM_VYRIZENI.value && !document.forms[0].CISLO_SPISU1.value) {
    alert('Není zadán spis!');
    return(false);
  }
  ";
  $fce3="
  if (!document.forms[0].CISLO_SPISU1.value) {
    alert('Není zadán spis!');
    return(false);
  }
  ";
  
  $fce4="
  if (document.forms[0].CISLO_SPISU1.value && document.forms[0].REFERENT.value && !document.forms[0].SKARTACE.value) {
    if (document.forms[0].REFERENT.value == " . ($USER_INFO["ID"]?$USER_INFO["ID"]:0) . ") {
      alert('Není vyplněn spisový znak!');
      return(false);
    }
  }
  ";
  
  $fce5="
  if(document.forms[0].VLASTNICH_RUKOU.value==9)
    if(!document.forms[0].ODESL_DATSCHRANKA.value){
      alert('Není vyplněno číslo dat. schránky!');
      return false;
    }
  ";
  
  $fce6="
  if (document.forms[0].ODES_TYP.value=='U' && !document.forms[0].JEJICH_CJ.value) {
    alert('Není vyplněno číslo jednací dané instituce!');
    return(false);
  }
  ";
  
  $fce7="
  if (document.forms[0].DATUM_VYPRAVENI.value) {
    alert('Dokument je ve schvalovacím procesu, nelze označit datum vypravení!');
   document.forms[0].DATUM_VYPRAVENI.value='';
    return(false);
  }
  ";
  
  $fce_rejst_cislo="
  if (document.forms[0].PAMATKA_REJSTRC_TEXT.value) {
      
    var reg = new RegExp(\"^([0-9]{5,6})?$\");
    if (!reg.test(f.PAMATKA_REJSTRC_TEXT.value)) {
      alert('Rejstříkové číslo musí být vetší než 10000!');
      return(false);
    }
  }
  ";
  
  $fce_vyrizeno="
  if (document.forms[0].DATUM_VYRIZENI.value && !document.forms[0].VYRIZENO.value) {
      alert('Pole Způsob vyřízení musí být vyplněno !');
      return(false);
  }
  if (!document.forms[0].DATUM_VYRIZENI.value && document.forms[0].VYRIZENO.value) {
      alert('Datum vyřízení musí být vyplněno!');
      return(false);
  }
      
  if (document.forms[0].DATUM_VYRIZENI.value && document.forms[0].VYRIZENO.value && !document.forms[0].REFERENT.value) {
      alert('Pole Zpracovatel musí být vyplněno!');
      return(false);
  }
  ";
  
  $fce_potvrd_zmenu_superodboru="
    var selectedIndex = document.forms[0].SUPERODBOR.selectedIndex;
    if (document.forms[0].SUPERODBOR.options[selectedIndex].defaultSelected != true) {
      return confirm('Provedli jste změnu vyřizujícího pracoviště NPÚ. Dokument bude předán na toto pracoviště! Pokračovat?');
    }
  ";
  
  $fce_poznamka_zmena_odboru="
    var selectedIndex = document.forms[0].ODBOR.selectedIndex;
    if (document.forms[0].ODBOR.options[selectedIndex].defaultSelected != true) {
      if (document.forms[0].POZNAMKA.defaultValue==document.forms[0].POZNAMKA.value) {
        alert('Při změně odboru musíte vyplnit do poznámky, proč dochází k předání!');
        return(false);
      }
    }
  ";
  
  $datumy_prichozi = "
    if (document.forms[0].TYP_DOKUMENTU.value == 'A' && document.forms[0].ZPUSOB_PODANI.value == '3') {
      alert('Analogový dokument nemůže mít způsob přijetí elektronicky!');
      return(false);
    }
      
    if (document.forms[0].TYP_DOKUMENTU.value == 'D' && document.forms[0].ZPUSOB_PODANI.value == '1') {
      alert('Digitální dokument nemůže mít způsob přijetí písemně!');
      return(false);
    }
      
    if (ConvertDate(document.forms[0].DATUM_VYRIZENI.value)<ConvertDate(document.forms[0].DATUM_PODATELNA_PRIJETI.value)) {
      alert('Datum vyřízení nemůže být dříve než datum přijetí!');
      return(false);
    }
    if (ConvertDate(document.forms[0].DATUM_REFERENT_PRIJETI.value)<ConvertDate(document.forms[0].DATUM_PODATELNA_PRIJETI.value)) {
      alert('Datum přečtení zpracovatelem nemůže být dříve než datum přijetí!');
      return(false);
    }
    if (ConvertDate(document.forms[0].LHUTA_VYRIZENI.value)<ConvertDate(document.forms[0].DATUM_PODATELNA_PRIJETI.value)) {
      alert('Datum Vyřídit do nemůže být dříve než datum přijetí!');
      return(false);
    }
      
    if (ConvertDate(document.forms[0].DATUM_VYRIZENI.value)<ConvertDate(document.forms[0].DATUM_REFERENT_PRIJETI.value)) {
      alert('Datum vyřízení nemůže být dříve než datum přečtení zpracovatelem!');
      return(false);
    }
  ";
  
  $datumy_odchozi = "
    if (ConvertDate(document.forms[0].DATUM_VYPRAVENI.value)<ConvertDate(document.forms[0].DATUM_PODATELNA_PRIJETI.value)) {
      alert('Datum vypravení nemůže být dříve než datum odeslání!');
      return(false);
    }
    if (ConvertDate(document.forms[0].DATUM_DORUCENI.value)<ConvertDate(document.forms[0].DATUM_PODATELNA_PRIJETI.value)) {
      alert('Datum doručení nemůže být dříve než datum odeslání!');
      return(false);
    }
    if (ConvertDate(document.forms[0].DATUM_PM.value)<ConvertDate(document.forms[0].DATUM_PODATELNA_PRIJETI.value)) {
      alert('Datum právní moci nemůže být dříve než datum odeslání!');
      return(false);
    }
      
    if (ConvertDate(document.forms[0].DATUM_DORUCENI.value)<ConvertDate(document.forms[0].DATUM_VYPRAVENI.value)) {
      alert('Datum doručení nemůže být dříve než datum vypravení!');
      return(false);
    }
    if (ConvertDate(document.forms[0].DATUM_PM.value)<ConvertDate(document.forms[0].DATUM_VYPRAVENI.value)) {
      alert('Datum právní moci nemůže být dříve než datum vypravení!');
      return(false);
    }
      
    if (ConvertDate(document.forms[0].DATUM_PM.value)<ConvertDate(document.forms[0].DATUM_DORUCENI.value)) {
      alert('Datum právní moci nemůže být dříve než datum doručení!');
      return(false);
    }
  ";
  
  if ($GLOBALS['EDIT_ID']>0 && !$is_multiedit) {
    $doc = LoadClass('EedCj', $GLOBALS['EDIT_ID']);
    $udaje = $doc->GetDocInfo($GLOBALS['EDIT_ID']);
    $datum_prijeti = $udaje['DATUM_PODATELNA_PRIJETI'];
  }
  
  $datumy_odpoved = "
  if (ConvertDate(document.forms[0].DATUM_PODATELNA_PRIJETI.value)<ConvertDate('$datum_prijeti')) {
  alert('Datum odeslání nemůže být dříve než datum přijetí vstupního dokumentu!');
  return(false);
}
if (ConvertDate(document.forms[0].DATUM_VYPRAVENI.value)<ConvertDate('$datum_prijeti')) {
alert('Datum vypravení nemůže být dříve než datum přijetí vstupního dokumentu!');
return(false);
}
if (ConvertDate(document.forms[0].DATUM_DORUCENI.value)<ConvertDate('$datum_prijeti')) {
alert('Datum doručení nemůže být dříve než datum přijetí vstupního dokumentuí!');
return(false);
}
if (ConvertDate(document.forms[0].DATUM_PM.value)<ConvertDate('$datum_prijeti')) {
alert('Datum právní moci nemůže být dříve než datum přijetí vstupního dokumentu!');
return(false);
}

if (ConvertDate(document.forms[0].DATUM_DORUCENI.value)<ConvertDate('$datum_prijeti')) {
alert('Datum doručení nemůže být dříve než datum přijetí vstupního dokumentu!');
return(false);
}
";
  
  //jestlize je zapnuta kontrola na UIR-ADR, tak vypiseme varovani, pokud adresa nebyla overena
  $FORM_CONFIG["schema"][] = array("elements"=>array(
    array("type"=>"valid_fce","name_fce"=>$fce)),
    "visible"=>($is_insert or $is_new or $is_edit)&&$GLOBALS["CONFIG"]["KONTROLA_UIR"],
  );
  
  //pokud je zapnuta volba pro nutnost spisu, tak udelame alert okno, pokud chce u prichozi uzivatel zadat datum vyrizeni
  $FORM_CONFIG["schema"][] = array("elements"=>array(
    array("type"=>"valid_fce","name_fce"=>$fce2)),
    "visible"=>$is_edit&&$GLOBALS["CONFIG"]["ODPOVED_SPIS"]&&($GLOBALS["ODESLANA_POSTA"]=='f'),
  );
  
  //pokud je zapnuta volba pro nutnost spisu, tak udelame alert okno u kazdeho odchoziho dokumentu
  $FORM_CONFIG["schema"][] = array("elements"=>array(
    array("type"=>"valid_fce","name_fce"=>$fce3)),
    "visible"=>$GLOBALS["CONFIG"]["ODPOVED_SPIS"]&&($GLOBALS["ODESLANA_POSTA"]=='t')&&!$is_insert,
  );
  
  //pokud je zapnuta volba pro nutnost spisu, tak udelame alert okno u dokumentu, ktery je dan do spisu a pokud nema skartacni znak
  $FORM_CONFIG["schema"][] = array("elements"=>array(
    array("type"=>"valid_fce","name_fce"=>$fce4)),
    "visible"=>$GLOBALS["CONFIG"]["ODPOVED_SPIS"]&&!$is_insert&&!$is_filter && !HasRole('podatelna'),
  );
  
  //aby pri zpusobu doruceni datovou schrankou muselo byt vyplnene pole dat.schranka
  $FORM_CONFIG["schema"][] = array("elements"=>array(
    array("type"=>"valid_fce","name_fce"=>$fce5)),
    "visible"=>$is_insert || $is_new || $is_edit,
    //"visible"=>$is_edit,
  );
  
  //aby pri vyplneni datumu vypraveni zakricelo, ze je ve schvalovacim procesu
  $FORM_CONFIG["schema"][] = array("elements"=>array(
    array("type"=>"valid_fce","name_fce"=>$fce7)),
    "visible"=>$is_edit && $GLOBALS['ODESLANA_POSTA']=='t' && !$GLOBALS['DATUM_VYPRAVENI'] && $GLOBALS['STATUS']==11,
    //"visible"=>$is_edit,
  );
  
  //aby u prichoziho dokumentu bylo u organizace statni sprava povinne pole Jejich CJ
  $FORM_CONFIG["schema"][] = array("elements"=>array(
    array("type"=>"valid_fce","name_fce"=>$fce6)),
    "visible"=>($is_insert || $is_new || $is_edit)&&($GLOBALS["ODESLANA_POSTA"]<>'t')&&$GLOBALS["CONFIG"]["KONTROLA_VYPLNENI_CJ"],
    //"visible"=>$is_edit,
  );
  
  //varovani pri zmene superodboru
  //   $FORM_CONFIG["schema"][] = array("elements"=>array(
  //      array("type"=>"valid_fce","name_fce"=>$fce_potvrd_zmenu_superodboru)),
  //            "visible"=>$is_edit && $GLOBALS["ODESLANA_POSTA"] <> 't',
  //      );
  //
  
  //varovani pri zmene superodboru
  $FORM_CONFIG["schema"][] = array("elements"=>array(
    array("type"=>"valid_fce","name_fce"=>  $fce_vyrizeno)),
    "visible"=>($is_edit || $is_multiedit) && $GLOBALS["ODESLANA_POSTA"] <> 't',
  );
  
  //varovani pri zmene odboru
  $FORM_CONFIG["schema"][] = array("elements"=>array(
    array("type"=>"valid_fce","name_fce"=>  $fce_poznamka_zmena_odboru)),
    "visible"=>($is_edit) && $GLOBALS["ODESLANA_POSTA"] <> 't' && HasRole('zmena-odboru'),
  );
  
  
  //datumy
  //   $FORM_CONFIG["schema"][] = array("elements"=>array(
  //      array("type"=>"valid_fce","name_fce"=>  $datumy_prichozi)),
  //            "visible"=>($is_insert || $is_new || $is_edit) && $GLOBALS["ODESLANA_POSTA"] <> 't',
  //      );
  //
  //   //datumy odchozi
  //   $FORM_CONFIG["schema"][] = array("elements"=>array(
  //      array("type"=>"valid_fce","name_fce"=>  $datumy_odchozi)),
  //            "visible"=>($is_insert || $is_new || $is_edit) && $GLOBALS["ODESLANA_POSTA"] == 't',
  //      );
  
  $FORM_CONFIG["schema"][] = array("elements"=>array(
    array("type"=>"valid_fce","name_fce"=>  $datumy_odpoved)),
    "visible"=>($is_new || $is_edit) && $GLOBALS["ODESLANA_POSTA"] == 't' && $GLOBALS['ID_PUVODNI'],
  );
  
  
  //varovani pro rejst. cislo
  $FORM_CONFIG["schema"][] = array("elements"=>array(
    array("type"=>"valid_fce","name_fce"=>$fce_rejst_cislo)),
    "visible"=>$is_filter_all && $GLOBALS['CONFIG']['UKLADACI_ZNACKY'],
  );
  
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
  
  $fce_ruk_znak = "
  if (document.forms[0].DATUM_PODATELNA_PRIJETI.value && !document.forms[0].SKARTACE.value) {
    alert('Při zadání datumu odeslání je nutné vyplnit spisový znak!');
    return(false);
  }
  if (document.forms[0].ODESL_EMAIL.value) {
    var email = document.forms[0].ODESL_EMAIL;
    var filter = /^[a-zA-Z0-9.!#$%&'*+/=?^_`{|}~-]+@[a-zA-Z0-9](?:[a-zA-Z0-9-]{0,61}[a-zA-Z0-9])?(?:\.[a-zA-Z0-9](?:[a-zA-Z0-9-]{0,61}[a-zA-Z0-9])?)*$/;
      
    if (!filter.test(email.value)) {
      alert('Email není zadán ve správném tvaru!');
      document.forms[0].ODESL_PRIJMENI.focus();
      return(false);
    }
  }
  ";
  
  
  $fce_ruk_adresat = "
  var val = document.forms[0].ODES_TYP.value;
  if(val=='P' && !document.forms[0].ODESL_PRIJMENI_FIRMA.value)   {
    alert('Při zadání právnické osoby je nutné zadat název firmy!');
    document.forms[0].ODESL_PRIJMENI_FIRMA.focus();
    return(false);
  }
  if(val=='U' && !document.forms[0].ODESL_PRIJMENI_FIRMA.value)   {
    alert('Při zadání orgánu veřejné moci je nutné zadat její název!');
    document.forms[0].ODESL_PRIJMENI_FIRMA.focus();
    return(false);
  }
      
  if(val=='O' && (!document.forms[0].ODESL_PRIJMENI.value || !document.forms[0].ODESL_JMENO.value))   {
    alert('Při zadání fyzické osoby je nutné zadat její příjmení a jméno!');
    document.forms[0].ODESL_PRIJMENI.focus();
    return(false);
  }
      
  if(val=='F' && (!document.forms[0].ODESL_PRIJMENI.value || !document.forms[0].ODESL_JMENO.value))   {
    alert('Při zadání podnikající fyzické osoby je nutné zadat její příjmení a jméno!');
    document.forms[0].ODESL_PRIJMENI.focus();
    return(false);
  }
      
  if((val=='N' || val=='B' || val=='E' || val=='T' || val=='D') && (!document.forms[0].ODESL_PRIJMENI.value || !document.forms[0].ODESL_JMENO.value))   {
    alert('Je nutné zadat její příjmení a jméno osoby!');
    document.forms[0].ODESL_PRIJMENI.focus();
    return(false);
  }
      
      
  ";
  
  $FORM_CONFIG["schema"][] = array("elements"=>array(
    array("type"=>"valid_fce","name_fce"=>$fce_ruk_znak)),
    "visible"=>!$is_multiedit && ($GLOBALS['ODESLANA_POSTA']=='t'),
  );
  
  $FORM_CONFIG["schema"][] = array("elements"=>array(
    array("type"=>"valid_fce","name_fce"=>$fce_ruk_adresat)),
    "visible"=>!$is_multiedit,
  );
  
  
  
  reset ($GLOBALS["CONFIG_POSTA"]["PLUGINS"]);
  foreach($GLOBALS["CONFIG_POSTA"]["PLUGINS"] as $plug_name => $plug) {
    if ($plug['enabled']){
      $file = FileUp2('plugins/'.$plug['dir'].'/.admin/form_schema_vnejsi_end.inc');
      if (File_Exists($file)) include($file);
    }
  }
  