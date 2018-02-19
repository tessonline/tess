<?php
include(FileUp2('.admin/javascript.inc'));
require_once(Fileup2(".admin/vnitrni_adresati.inc"));

$is_filter = In_Array($form_params["formtype"], array($f_filter, $f_filter_all));
$is_filter_all = In_Array($form_params["formtype"], array($f_filter_all));
$is_filter_simple = In_Array($form_params["formtype"], array($f_filter));
$is_insert = In_Array($form_params["formtype"], array($f_insert));
$is_update = In_Array($form_params["formtype"], array($f_insert, $f_edit, $f_insertfrom));
$is_edit = In_Array($form_params["formtype"], array($f_edit));
$is_info = In_Array($form_params["formtype"], array($f_info));
$is_history = In_Array($form_params["formtype"], array($f_history));
$is_new = In_Array($form_params["formtype"], array($f_insertfrom));


if ($f_insertfrom && $GLOBALS['ODESLANA_POSTA'] == 'f' && $GLOBALS['ODES_TYP'] == 'X') {
  $doc_puvodni = LoadClass('EedDokument', $GLOBALS['ID_PUVODNI']);
  $referent_id = $doc_puvodni->referent_id;

  $uzel_id = $doc_puvodni->VratSpisovyUzelPracovnika($referent_id);
  $odbor_id = $doc_puvodni->VratOdborZSpisUzlu($uzel_id);

//   $user = LoadClass('EedUser', $referent_id);
//   
//   $odbor_id = $user->odbor_id;
// print_r($user);

  $GLOBALS['ORGANIZACNI_VYBOR'] = $odbor_id;
  $GLOBALS['ZPRACOVATEL'] = $referent_id;
}

$doc = LoadClass('EedDokument', $GLOBALS['EDIT_ID']?$GLOBALS['EDIT_ID']:0);


$FORM_CONFIG["schema"][] = array("label"=>"Vnitřní pošta:");

//vezmeme cislo spisu z hlavniho form schematu, pres global promennou, jinak to neproleze.
$cislo_spisu=$GLOBALS["cislo_spisu"];

//if (($is_edit||$is_new) && !(HasRole('spravce') || HasRole('podatelna') || HasRole('podatelna-odbor') || HasRole('vedouci-odbor') || HasRole('vedouci-odd')))
if (($is_edit||$is_new) && !(HasRole('spravce'))) {
  //pokud jsem jjen referent, tak musi byt kontrola, jestli tu pisemnost muzu editovat
//  include('.admin/has_access.inc');
//   if (!MaPristupKDokumentu_old($GLOBALS['REFERENT']))  {
//     require(FileUp2('html_footer.inc'));
//     Die('<br/><br/><h3>Nemáte právo pro editaci cizího dokumentu</h3>');;
//   }
}

If ($GLOBALS[CISLO_SPISU1]>0)
{
  $text="Přiřadit k jinému ".$GLOBALS["CONFIG"]["CISLO_SPISU_3P"];
  $VYTVOR_SPIS="";
}
else
{
  $VYTVOR_SPIS="<input class=\"button\" type=\"button\" value=\"Vytvoř spis\" onclick=\"".
                "window.open('guide.php?G_NAME=posta_vytvorspis&ID=".$GLOBALS["ID"]."&CISLO_JEDNACI1=".$GLOBALS["CISLO_JEDNACI1"]."&CISLO_JEDNACI2=".$GLOBALS["CISLO_JEDNACI2"]."&ODBOR=".$GLOBALS["ODBOR"]."',   'guide', 'height=600px,width=600px,scrollbars,resizable');\">";	
  $text="Přiřadit k ".$GLOBALS["CONFIG"]["CISLO_SPISU_3P"];
}
If ($is_insert) $VYTVOR_SPIS="";
$cislo_jednaci = $doc->text_cj;

$USER_INFO = $GLOBALS["POSTA_SECURITY"]->GetUserInfo(); 
if (!$is_info)
{ 
  $REFERENT = $USER_INFO["ID"];
  $odbor=VratOdbor();
}

If ($is_edit || $is_new)
{
  $REFERENT = $GLOBALS["REFERENT"]; 
  $odbor=$GLOBALS["ODBOR"];
}
If ($is_new) {$GLOBALS["EDITOVANE_ID"]=$GLOBALS["EDIT_ID"];} // rychla odpoved

If ($is_insert || $is_new)
{
  if (!$GLOBALS['LHUTA'] || $GLOBALS['LHUTA']>29) $GLOBALS['LHUTA']=10;

//  $GLOBALS['SKARTACE']=2398; //onma, 2011.1.11, na zaklade tel. rozhovoru s Krejsarovou
  echo '<iframe id="ifrm_get_value" style="position:absolute;z-index:0;left:0;top:0;visibility:hidden" src="services/spisovka/get_value.php?ODBOR='.$odbor.'">blabla</iframe>';
}
//echo '<iframe id="ifrm_get_value" style="position:absolute;z-index:0;left:10;top:10" src="services/spisovka/get_value.php?ODBOR='.$odbor.'">blabla</iframe>';
echo '

<script language="JavaScript" type="text/javascript">
<!--
function ChangeOdbor(el,cislo) {
  var ifrm = window.document.getElementById("ifrm_get_value");
//  alert(el);
  ifrm.src = "services/spisovka/get_value.php?type=SUBZAK&cislo="+cislo+"&ODBOR="+el.options[el.selectedIndex].value;
}  
function DelPrijemci(id,zpusob) {
   newwindow=window.open("./services/spisovka/prijemci/del_adr.php?prijemci="+document.forms[0].DALSI_PRIJEMCI.value+"&DEL_ID="+id+"&zpusob="+zpusob, "guideXXX",   "height=10px,width=10px,scrollbars,resizable=0");
}

function ChangeSuperOdbor(el) {
  var ifrm = window.document.getElementById("ifrm_get_value");
  ifrm.src = "services/spisovka/get_superodbor.php?type=SUBZAK&ODBOR="+el.options[el.selectedIndex].value;
  ChangeOdbor(document.frm_edit.ODBOR2);
}
//-->
 
</script>
';

If ($is_edit) include_once(FileUp2('.admin/form_schema_obalky.inc'));

If ($is_new)
{
  $GLOBALS["ODESLANA_POSTA"]='t';
  $GLOBALS["ODES_TYP"]='X';
  $GLOBALS["DATUM_PODATELNA_PRIJETI"]='';
  $GLOBALS["DALSI_PRIJEMCI"]='';
}

  If (($is_insert||$is_filter) && $GLOBALS["CONFIG"]["ODDELENI"]) {
    $jaky_odbor=UkazOdbor(VratOdbor(),0,0,1);
    If (GetParentGroup($jaky_odbor)<30)
    {
      //jsem v odboru, nejsem v oddeleni
      $GLOBALS["ODBOR"]=VratOdbor();
      $GLOBALS["ODDELENI"]='';
    }
    else
    {
      //jsem v odboru, a jsem v oddeleni
      $GLOBALS["ODBOR"]=VratOdbor(GetParentGroup($jaky_odbor));
      $GLOBALS["ODDELENI"]=VratOdbor();
    }
  }



  // Tohle byl nesmysl pro CHODOV, aby bylo mozne pridavat cislo jednaci k NOVYM pisemnostem...
   If ($GLOBALS["CONFIG"]["SHOW_C_JEDNACI"])
    $FORM_CONFIG["schema"][] = array( 
      "elements"=>array(
     array( "type"=>"text", "name"=>"ZNACKA"),      
        ),
      "format"=>"'<span id=\"CJEDNACI_KOD_SPAN\" style=\"font-weight:bold;\"></span><input class=\"button\" type=\"button\" value=\"Přiřadit číslo jednací\"   onclick=\"".
                "window.open('guide.php?G_NAME=posta_cjednaci', 'guide', 'height=600px,width=600px,scrollbars,resizable');\">$url&nbsp;-&nbsp;Zn:&nbsp;'...ZNACKA",
      "visible"=>$is_insert,
      "label"=>"Údaje:"
    );

$FORM_CONFIG["schema"][] = array( 
  "elements"=>array(
      "type"=>"hidden", 
      "name"=>"NEM_ID",
    ),
  "format"=>"'<span id=\"CJEDNACI_KOD_SPAN\" style=\"font-weight:bold;\">$cislo_jednaci</span>'",
//  "format"=>"'<span id=\"CJEDNACI_KOD_SPAN\" style=\"font-weight:bold;\">$cislo_jednaci</span><input class=\"button\" type=\"button\" value=\"Přiřadit číslo jednací\" onclick=\"".
            "window.open('guide.php?G_NAME=posta_cjednaci', 'guide', 'height=600px,width=600px,scrollbars,resizable');\">
            <span id=\"CJEDNACI_TEXT_SPAN\" style=\"font-weight:italic;\"><input class=\"button\" type=\"button\" value=\"Vytvořit číslo jednací\" onclick=\"".
            "window.open('services/spisovka/c_jednaci/nula.php?nula=ne', 'guide2', 'height=10px,width=10px,scrollbars,resizable');\"></span> 
            '",
//  "visible"=>$is_insert,
  "visible"=>($is_new or $is_edit or $is_edit) && $GLOBALS["CONFIG"]["SHOW_C_JEDNACI"],
  "label"=>"Číslo jednací:"
);
/*
$FORM_CONFIG["schema"][] = array( 
  "elements"=>array(
      "type"=>"hidden", 
      "name"=>"NEM_ID",
    ),
  "format"=>"'<span id=\"CJEDNACI_KOD_SPAN\" style=\"font-weight:bold;\">$cislo_jednaci</span><input class=\"button\" type=\"button\" value=\"Přiřadit číslo jednací\" onclick=\"".
            "window.open('guide.php?G_NAME=posta_cjednaci', 'guide', 'height=600px,width=600px,scrollbars,resizable');\">'",
  "visible"=>$is_new or $is_edit or $is_edit,
  "label"=>"Číslo jednací:"
);
*/
/*
$FORM_CONFIG["schema"][] = array( 
  "format"=>"'<span id=\"CJEDNACI_KOD_SPAN\" style=\"font-weight:bold;\">$cislo_jednaci</span>'",
  "visible"=>$is_info,
  "label"=>"Číslo jednací:"
);
*/
 $FORM_CONFIG["schema"][] = array( 
//  "format"=>"'<span id=\"OBJEKT_KOD_SPAN\" style=\"font-weight:bold;\">".$cislo_spisu."'",

  "format"=>"'<span id=\"OBJEKT_KOD_SPAN\" style=\"font-weight:bold;\">".$GLOBALS["cislo_spisu"]."</span><input class=\"button\" type=\"button\" value=\"$text\" onclick=\"".
            "window.open('guide.php?G_NAME=posta_spisy&IDPspis=99999', 'guide', 'height=600px,width=600px,scrollbars,resizable');\">$url $VYTVOR_SPIS'",
  "visible"=>$is_insert or $is_new or $is_edit,
  "label"=>$GLOBALS["CONFIG"]["CISLO_SPISU"].":"
  );
  
 
  

   $FORM_CONFIG["schema"][] = array("elements"=>array(
                array( "type"=>"hidden", "name"=>"ODESLANA_POSTA","value"=>$GLOBALS["ODESLANA_POSTA"]),
                array( "type"=>"hidden", "name"=>"CISLO_SPISU1","value"=>$GLOBALS["CISLO_SPISU1"]),
                array( "type"=>"hidden", "name"=>"CISLO_SPISU2","value"=>$GLOBALS["CISLO_SPISU2"]),
                array( "type"=>"hidden", "name"=>"NAZEV_SPISU","value"=>$GLOBALS["NAZEV_SPISU"]),
                array( "type"=>"hidden", "name"=>"ODBOR_SPISU","value"=>$GLOBALS["ODBOR_SPISU"]),
                array( "type"=>"hidden", "name"=>"DATUM_REFERENT_PRIJETI2","value"=>""),
                array( "type"=>"hidden", "name"=>"ODES_TYP","value"=>"X"),
                array( "type"=>"hidden", "name"=>"PRIRAD_PODCISLO","value"=>0),
                //array( "type"=>"hidden", "name"=>"SKARTACE","value"=>""),
                array( "type"=>"hidden", "name"=>"CISLO_JEDNACI1","value"=>$GLOBALS["CISLO_JEDNACI1"]),
                array( "type"=>"hidden", "name"=>"CISLO_JEDNACI2","value"=>$GLOBALS["CISLO_JEDNACI2"]),
                array( "type"=>"hidden", "name"=>"PODCISLO_SPISU","value"=>$GLOBALS["PODCISLO_SPISU"]),

//                array( "type"=>"hidden", "name"=>"CISLO_SPISU2","value"=>$GLOBALS["CISLO_SPISU2"]),
                ),
                "visible"=>$is_edit,
  );


If ($is_new or $is_insert or $GLOBALS["ODESLANA_POSTA"]=='t')
{
    if ($is_new || $is_insert) $GLOBALS['TYP_DOKUMENTU']='D';

//     $FORM_CONFIG["schema"][] = array("elements"=>array(
// //              array( "type"=>"select_typ_posty", "name"=>"TYP_POSTY", "width"=>10,"required"=>($insert||$GLOBALS['MAIN_DOC']==1),"frozen"=>!($insert||$GLOBALS['MAIN_DOC']==1),"add"=>"onChange=\"ZmenaTypuDokumentu(this)\""),
//               array( "type"=>"select_typ_posty", "name"=>"TYP_POSTY", "width"=>10,"required"=>true,"add"=>"onChange=\"ZmenaTypuDokumentu(this)\"",
//               "lhuta"=>getLhutaDleKlasifikace()),
//               array( "type"=>"select_typ_dokumentu", "name"=>"TYP_DOKUMENTU","insertnull"=>false),
//               ),
//               "visible"=>($is_edit or $is_info or $is_insert or $is_new) && $GLOBALS['MAIN_DOC']==1,
//               "format"=>"TYP_POSTY...'&nbsp;&nbsp;&nbsp;Typ dokumentu:&nbsp;'...TYP_DOKUMENTU",
//               "label"=>"Věcná klasifikace:");

//     $FORM_CONFIG["schema"][] = array("elements"=>array(
//               array( "type"=>"select_typ_dokumentu", "name"=>"TYP_DOKUMENTU","insertnull"=>false,"disabled_onoff"=>$is_multiedit),
//               ),
// //              "visible"=>($is_edit or $is_info or $is_insert) && ($GLOBALS['MAIN_DOC']==0),
//               "label"=>"Typ dokumentu:");
//
//     If ($GLOBALS["CONFIG"]["UKAZ_JINE"]  && $GLOBALS['MAIN_DOC']==1)
//        $FORM_CONFIG["schema"][] = array("elements"=>array(
//                   array( "type"=>"select_jine", "name"=>"JINE","insertnull"=>true,"frozen"=>!(HasRole('spravce')||HasRole('vedouci-odbor')||HasRole('vedouci-odd')||HasRole('zpracovatel'))),
//        ),
//        "visible"=>!$is_filter,
//        "label"=>"Věcná fáze:");

//     $FORM_CONFIG["schema"][] = array("elements"=>array(
//               array( "type"=>"select_typ_dokumentu", "name"=>"TYP_DOKUMENTU","insertnull"=>false),
//               ),
//               "visible"=>$is_edit or $is_info or $is_new,
//               "label"=>$GLOBALS['CONFIG']['NAZEV_TYP_POSTY']);
//
    $FORM_CONFIG["schema"][] = array("elements"=>array(
               array( "type"=>"select_typ_posty", "name"=>"TYP_POSTY", "width"=>10,"required"=>true,"insertnull"=>true,"add"=>"onChange=\"ZmenaTypuDokumentu(this)\""),
              array( "type"=>"select_typ_dokumentu", "name"=>"TYP_DOKUMENTU","insertnull"=>false),
              ),
              "visible"=>$is_edit or $is_info or $is_new or $is_insert,
              "label"=>$GLOBALS['CONFIG']['NAZEV_TYP_POSTY']);


$GLOBALS[EV_CISLO]=0;
    $FORM_CONFIG["schema"][] = array("elements"=>array(
                array( "type"=>"hidden", "name"=>"CISLO_SPISU1","value"=>$GLOBALS["CISLO_SPISU1"]),
                array( "type"=>"hidden", "name"=>"NAZEV_SPISU","value"=>$GLOBALS["NAZEV_SPISU"]),
                array( "type"=>"hidden", "name"=>"CISLO_SPISU2","value"=>$GLOBALS["CISLO_SPISU2"]),
                array( "type"=>"hidden", "name"=>"PODCISLO_SPISU","value"=>$GLOBALS["PODCISLO_SPISU"]),
                array( "type"=>"hidden", "name"=>"ID_PUVODNI","value"=>$GLOBALS["EDIT_ID"]),
                array( "type"=>"hidden", "name"=>"ODESLANA_POSTA","value"=>"t"),
                array( "type"=>"hidden", "name"=>"ODESL_ADRKOD","value"=>$GLOBALS["ODESL_ADRKOD"]),
                array( "type"=>"hidden", "name"=>"OBJEKT_KOD","value"=>"$objkod"),
                array( "type"=>"hidden", "name"=>"PRIRAD_PODCISLO","value"=>0),
                array( "type"=>"hidden", "name"=>"OKRES_KOD","value"=>"$okreskod"),
                array( "type"=>"hidden", "name"=>"CISLO_JEDNACI1","value"=>'0'),
                array( "type"=>"hidden", "name"=>"CISLO_JEDNACI2","value"=>'0'),
                array( "type"=>"hidden", "name"=>"ODBOR_SPISU","value"=>$GLOBALS["ODBOR_SPISU"]),
                array( "type"=>"hidden", "name"=>"EV_CISLO", "value"=>$GLOBALS[EV_CISLO]),
                array( "type"=>"hidden", "name"=>"ODBOR", "value"=>$odbor),
                array( "type"=>"hidden", "name"=>"ODES_TYP","value"=>"X"),
                array( "type"=>"hidden", "name"=>"ODDELENI","value"=>$GLOBALS["ODDELENI"]),
                array( "type"=>"hidden", "name"=>"REFERENT", "value"=>$REFERENT),
                array( "type"=>"hidden", "name"=>"KOPIE_SOUBORU", "value"=>$GLOBALS['EDIT_ID']),
                array( "type"=>"hidden", "name"=>"EDITOVANE_ID","value"=>$GLOBALS["EDITOVANE_ID"]),
                ),
                "visible"=>$is_new or $is_insert,
  );
    $FORM_CONFIG["schema"][] = array("elements"=>array(
              array( "type"=>"hidden", "name"=>"ODES_TYP", "value"=>"X")),
              "label"=>"");									

    $FORM_CONFIG["schema"][] = array("elements"=>array(
              array( "type"=>"text", "name"=>"ODESL_PRIJMENI", "value"=>UkazOdbor($odbor),"frozen"=>true,'size'=>50),
              array( "type"=>"text", "name"=>"ODESL_JMENO", "value"=>UkazUsera($REFERENT),"frozen"=>true,'size'=>50),
              ),
              "format"=>"ODESL_PRIJMENI...'&nbsp;&nbsp;&nbsp;Referent:&nbsp;'...ODESL_JMENO",
              "visible"=>!$is_info,
              "label"=>"Odesílatel:");										 
  								 
    $FORM_CONFIG["schema"][] = array("elements"=>array(
              array( "type"=>"text", "name"=>"ODBOR", "value"=>UkazOdbor($GLOBALS["ODBOR"]),"frozen"=>true),
              array( "type"=>"text", "name"=>"REFERENT", "value"=>UkazUsera($GLOBALS["REFERENT"]),"frozen"=>true),
              ),
              "format"=>"ODBOR...'&nbsp;&nbsp;&nbsp;Referent:&nbsp;'...REFERENT",
              "visible"=>$is_info,
              "label"=>"Odesílatel:");										 
    $FORM_CONFIG["schema"][] = array("elements"=>array(
              array( "type"=>"text", "name"=>"VEC", "size"=>90,"required"=>"true"),
              array( "type"=>"hidden", "name"=>"ROK","value"=>date('20y')),
              ),
              "label"=>"<b>Věc:</b>");										 

    $FORM_CONFIG["schema"][] = array("elements"=>array(
              array( "type"=>"text_number", "name"=>"POCET_LISTU","label"=>"Počet listů"),   
              array( "type"=>"text", "name"=>"DRUH_PRILOH","size"=>20,"label"=>"Počet listů"),
              array( "type"=>"text_number", "name"=>"POCET_PRILOH","label"=>"Počet příloh")),   
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
              array( "type"=>"datetime_db", "name"=>"DATUM_PODATELNA_PRIJETI","insertdatebutton"=>true,"required"=>true,"frozen"=>!(HasRole('spravce')||HasRole('podatelna')||HasRole('podatelna-odbor')))),   
              "visible"=>!($is_insert or $is_new),
              "label"=>"Datum odeslání:");		
    
   $FORM_CONFIG["schema"][] = array("elements"=>array(
              array( "type"=>"datetime_db", "name"=>"DATUM_PODATELNA_PRIJETI","insertdatebutton"=>true,"required"=>true)),   
              "visible"=>$is_insert or $is_new,
              "label"=>"Datum odeslání:");		
    
  
  
   $FORM_CONFIG["schema"][] = array("elements"=>array(
              array( "type"=>"text_number", "name"=>"LHUTA","size"=>"5","frozen"=>!(HasRole('spravce')||HasRole('podatelna')||HasRole('podatelna-odbor')))),   
              "format"=>"LHUTA",
              "visible"=>!($is_insert or $is_new),
              "label"=>"Lhůta k vyřízení:");		
   $FORM_CONFIG["schema"][] = array("elements"=>array(
              array( "type"=>"text_number", "name"=>"LHUTA","size"=>"5"),   
              ),
              "format"=>"LHUTA",
              "visible"=>$is_insert or $is_new,
              "label"=>"Lhůta k vyřízení:");		
    
  
   $FORM_CONFIG["schema"][] = array("elements"=>array(
//              array( "type"=>"text", "name"=>"POZNAMKA","size"=>"80"),   
              array( "type"=>"textarea", "name"=>"POZNAMKA","cols"=>"90","rows"=>5),
              ),
              "label"=>"Poznámka:");
  

   $FORM_CONFIG["schema"][] = array("elements"=>array(
              array( "type"=>"select_skartace", "name"=>"SKARTACE","size"=>"1","ukazjenaktivni"=>$is_insert,"insertnull"=>true, "width"=>"15","frozen"=>!(HasRole('spravce')||HasRole('vedouci-odbor')||HasRole('vedouci-odd')||HasRole('zpracovatel') ))              

              ),
              "visible"=>(($is_edit or $is_info or $is_insert)  && ($GLOBALS['MAIN_DOC']==1)) || $is_insert,
              "label"=>$GLOBALS["CONFIG"]["NAZEV_SKARTACE"].":");


    if ($GLOBALS['DATUM_VYPRAVENI']) $is_send = true; else $is_send = false;
    
  
   $FORM_CONFIG["schema"][] = array("label"=>"Adresáti:");

   $url_nastaveni = GetAgendaPath('POSTA_NASTAVENI_VNITRNIADR', 0, 1) . '/index.php';

   $FORM_CONFIG["schema"][] = array(
     "elements"=>array(
       array( 
         "type" => "select_vnitrni_adresati_skupina", 
         "name" => "VNITRNI_ADRESATI_SKUPINY"
       ),
       array( 'type' => 'button', 'name' => 'pridatAdresaty', 'add'=>' class="pridatAdresaty"', 'value' => 'Vložit', 'onclick' => '', 'label' => 'pridatAdresaty'),
     ),
     "format"   => "VNITRNI_ADRESATI_SKUPINY...'&nbsp;&nbsp;&nbsp;<a href=\"#\" class=\"pridatAdresaty\">Přidat</a>&nbsp;&nbsp;&nbsp;<a href=\"$url_nastaveni\" target=\"blank\">Nastavení</a>'",
     "label"    => "Přednastavení adresáti:",
     "visible"  => $is_update && !$is_send
   );		

   

    if ($is_new || $is_insert) $GLOBALS['MULTI_ODBOR'] = VratSuperOdbor();

    // MULTI ITEMS SUPPORT - BEGIN
         
    $isZpracovatelRequired = $GLOBALS['CONFIG']['VNITRNI_POSTA_JEN_ZPRACOVATELI'];
    $zpracovatelAdd = $isZpracovatelRequired ? ' data-required="ZPRACOVATEL" class="required"' : '';
    if ($is_edit || $is_info) {
      
      // Jeden zaznam posty (jeden spis) muze mit nekolik adresatu.
      // Ti se ukladaji do vedlejsi tabulky posta_vnitrni_adresati.
      // Mezi tabulkami posta a posta_vnitrni_adresati je vazba 1:N.
      // Zde se tedy vygeneruji vsechni adresati daneho spisu.
      $vnitrniAdresati = getVnitrniAdresaty(intval($GLOBALS['EDIT_ID']));

      foreach ($vnitrniAdresati as $id => $adresat) {

        $organizacniVyborName = 'ORGANIZACNI_VYBOR-' . $id;
        $zpracovatelName = 'ZPRACOVATEL-' . $id;

        $FORM_CONFIG["schema"][] = array(
          "elements"=>array(
            array(
              "type"=>"select_spisuzly",
              "name"=> $organizacniVyborName,
              'value'=> $adresat['ov'],
              "insertnull"=>"true",
              "frozen"=>$is_send,
              'add' => 'data-multiple-item="true"
                        data-required="ORGANIZACNI_VYBOR"
                        class="required"
                        style="width: 350px;"'
            ),
            array(
              "type"=>"select_referent",
               "name"=> $zpracovatelName,
              'value'=> $adresat['zp'],
              'odbor'=> $adresat['ov'],
              "insertnull"=>"true",
              "frozen"=>$is_send,
              'add' => 'data-multiple-item="true"' . $zpracovatelAdd,
              'fullselect' => false,
              'label' => 'Zpracovatel'
            )
          ),
          "format"=>"$organizacniVyborName...'&nbsp;Zpracovatel:'...$zpracovatelName",
          "label"=>$is_edit ? '<b>' . $GLOBALS["CONFIG"]["NAZEV_ODBOR"] . ':</b>' : $GLOBALS["CONFIG"]["NAZEV_ODBOR"] . ':',
              // zruseni format pro tema square
            'theme_config' => array(
              'square' => array(
                'format' => '',
              )
            )
      );

      }
    }
    else {

      $FORM_CONFIG["schema"][] = array(
        "elements"=>array(
          array(
            "type"=>"select_spisuzly",
            "name"=> 'ORGANIZACNI_VYBOR',
            "insertnull"=>"true",
            'add' => 'data-multiple-item="true"
                      data-required="ORGANIZACNI_VYBOR"
                      class="required"
                      style="width: 350px;"'
          ),
          array(
            "type"=>"select_referent",
            "name"=> 'ZPRACOVATEL',
            "insertnull"=>"true",
            'add' => 'disabled="disabled" data-multiple-item="true"' . $zpracovatelAdd,
            'label' => 'Zpracovatel',
            'fullselect' => true
          )
        ),
        "format"=>"ORGANIZACNI_VYBOR...'&nbsp;Zpracovatel:'...ZPRACOVATEL",
        "visible"=>$is_update,
        "label"=>$GLOBALS["CONFIG"]["NAZEV_ODBOR"] . ':',
              // zruseni format pro tema square
            'theme_config' => array(
              'square' => array(
                'format' => '',
              )
            )
      );
    }
    
    // MULTI ITEMS SUPPORT - END
    
}
else
{
  If (HasRole('podatelna-odbor') && !HasRole('spravce') && !HasRole('podatelna') &&!HasRole('zmena-odboru')) {
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
              array( "type"=>"select_vsechny_spisuzly", "name"=>"ODBOR","frozen"=>!(HasRole('spravce')||HasRole('podatelna')||HasRole('zmena-odboru')),"add"=>"id=\"ODBOR\" onChange=\"UkazPracovnika(this,'REFERENT');\"","insertnull"=>true),
              array( "type"=>"select_referent", "name"=>"REFERENT","insertnull"=>true,"label"=>"Zpracovatel","frozen"=>!$GLOBALS["POSTA_SECURITY"]->IsUserInGroups(array("posta-spravce-r","posta-spravce-ruid","posta-vedouci-odbor-ruid","posta-vedouci-oddeleni-ruid","posta-podatelna-ruid")), add=>"onChange=\"REFERENT_ON()\""),
              array( "type"=>"hidden", "name"=>"PODATELNA_ID","value"=>($is_insert?$REFERENT:$GLOBALS[PODATELNA_ID])),
              ),
              "visible"=>$is_edit or $is_info or $is_insert ,										 
              "label"=>'<b>' . $GLOBALS["CONFIG"]["NAZEV_ODBOR"] . ':</b>');										   

    $FORM_CONFIG["schema"][] = array("elements"=>array(
              array( "type"=>"hidden", "name"=>"DATUM_PREDANI","value"=>($is_insert?Date('d.m.Y H:m:s'):$GLOBALS[DATUM_PREDANI])),
              ),
              "visible"=>($is_edit or $is_info or $is_insert) && HasRole('podatelna-odbor') ,										 
              "label"=>"");										 

  }
  If (!HasRole('zpracovatel'))        
  {
    if ($is_filter_all) UNSET($GLOBALS[ODBOR]);
    $FORM_CONFIG["schema"][] = array("elements"=>array(
              array( "type"=>"select_odbor", "name"=>"ODBOR","insertnull"=>true,"add"=>"onChange=UkazOddeleni(this,'ODDELENI');"),
              ),
              "format"=>"'<div id=\"ODBOR\">'...ODBOR...'</div>'",
              "visible"=>$is_filter_all ,
              "label"=>'<b>' . $GLOBALS["CONFIG"]["NAZEV_ODBOR"] . ':</b>');										 
  }
  

  IF ($GLOBALS[CONFIG][ODDELENI])
  {
    If (HasRole('podatelna-odbor') && !HasRole('spravce'))        
    {
      //pouzivame oddeleni - editace a info okno
      $FORM_CONFIG["schema"][] = array("elements"=>array(
                array( "type"=>"select_oddeleni", "name"=>"ODDELENI","frozen"=>!(HasRole('spravce')||HasRole('podatelna')||HasRole('podatelna-odbor') ),"insertnull"=>true),
                ),
                "format"=>"'<div id=\"ODDELENI\">'...ODDELENI...'</div>'",
                "visible"=>!$is_filter,										 
                "label"=>"Oddělení:");										 
    }
    else
    {
      //aby pracovnice podatelny nemely hned vyplneny odddeleni
      if ($is_insert) $GLOBALS["ODDELENI"]="";
      $FORM_CONFIG["schema"][] = array("elements"=>array(
              array( "type"=>"select_oddeleni", "name"=>"ODDELENI","disabled_onoff"=>$is_multiedit,"frozen"=>!(HasRole('spravce')||HasRole('podatelna')||HasRole('vedouci-odbor')||HasRole('vedouci-odd')||HasRole('podatelna-odbor')),"insertnull"=>true),
              ),
              "format"=>"'<div id=\"ODDELENI\">'...ODDELENI...'</div>'",
              "visible"=>!$is_filter ,										 
              "label"=>"Oddělení:");										 
    
    }
  }  
    $FORM_CONFIG["schema"][] = array("elements"=>array(
//              array( "type"=>"select_typ_posty", "name"=>"TYP_POSTY", "width"=>10,"required"=>($insert||$GLOBALS['MAIN_DOC']==1),"frozen"=>!($insert||$GLOBALS['MAIN_DOC']==1),"add"=>"onChange=\"ZmenaTypuDokumentu(this)\""),
              array( "type"=>"select_typ_posty", "name"=>"TYP_POSTY", "width"=>10,"required"=>true,"add"=>"onChange=\"ZmenaTypuDokumentu(this)\""),
              array( "type"=>"select_typ_dokumentu", "name"=>"TYP_DOKUMENTU","insertnull"=>false),
              ),
              "visible"=>($is_edit or $is_info or $is_insert or $is_new) && $GLOBALS['MAIN_DOC']==1,	
              "format"=>"TYP_POSTY...'&nbsp;&nbsp;&nbsp;Typ dokumentu:&nbsp;'...TYP_DOKUMENTU",										 
              "label"=>"Věcná klasifikace:");										 

    $FORM_CONFIG["schema"][] = array("elements"=>array(
              array( "type"=>"select_typ_dokumentu", "name"=>"TYP_DOKUMENTU","insertnull"=>false,"disabled_onoff"=>$is_multiedit),
              ),
              "visible"=>($is_edit or $is_info or $is_insert) && ($GLOBALS['MAIN_DOC']==0),
              "label"=>"Typ dokumentu:");										 

    $FORM_CONFIG["schema"][] = array("elements"=>array(
              array( "type"=>"text", "name"=>"VEC", "size"=>90,"required"=>"true"),
              ),
              "label"=>"<b>Věc:</b>");										 
  
    $FORM_CONFIG["schema"][] = array("elements"=>array(
              array( "type"=>"datetime_db", "name"=>"DATUM_PODATELNA_PRIJETI","insertdatebutton"=>true,"required"=>true,"frozen"=>true,"label"=>"Datum přijetí"),   
              ),
//              "format"=>"DATUM_PODATELNA_PRIJETI...'&nbsp;&nbsp;&nbsp;Způsob podání:&nbsp;'...ZPUSOB_PODANI",
//              "visible"=>$is_edit or $is_info or $is_insert,										 
              "label"=>"Datum přijetí:");		
    $FORM_CONFIG["schema"][] = array("elements"=>array(
              array( "type"=>"text_number", "name"=>"POCET_LISTU","label"=>"Počet listů"),   
              array( "type"=>"text", "name"=>"DRUH_PRILOH","size"=>20,"label"=>"Druh příloh"),   
              array( "type"=>"text_number", "name"=>"POCET_PRILOH","label"=>"Počet příloh")),   
            "format"=>"POCET_LISTU...'&nbsp;&nbsp;&nbsp;Druh příloh:&nbsp;'...DRUH_PRILOH...'&nbsp;&nbsp;&nbsp;Počet(velikost) příloh:&nbsp;'...POCET_PRILOH...'(ks/kB)'",										 
            "label"=>"Počet listů:");		

  $FORM_CONFIG["schema"][] = array("elements"=>array(
              array( "type"=>"datetime_db", "name"=>"DATUM_REFERENT_PRIJETI","label"=>"Zpracovatel přečetl","insertdatebutton"=>true,"frozen"=>$frozen_ref),
              ),
//              "format"=>"REFERENT...'&nbsp;&nbsp;&nbsp;Referent přečetl&nbsp;'...DATUM_REFERENT_PRIJETI",
              "format"=>"'<span id=REFERENT>'...REFERENT...'</span>&nbsp;&nbsp;&nbsp;Zpracovatel přečetl&nbsp;'...DATUM_REFERENT_PRIJETI",
              "visible"=>!$odeslana,										 
              "label"=>'<b>' . $GLOBALS["CONFIG"]["NAZEV_REFERENT"] . ':</b>');		

  $FORM_CONFIG["schema"][] = array("elements"=>array(
              array( "type"=>"text", "name"=>"LHUTA","size"=>"5","frozen"=>$frozen_ref),   
              array( "type"=>"datetime_db", "name"=>"DATUM_VYRIZENI","label"=>"Datum vyřízení","insertdatebutton"=>true),
              ),
              "format"=>"LHUTA...'&nbsp;&nbsp;&nbsp;Datum vyřízení&nbsp;'...DATUM_VYRIZENI",
              "visible"=>$is_edit or $is_info or $is_insert,										 
              "label"=>"Lhůta k vyřízení:");		
  
   $FORM_CONFIG["schema"][] = array("elements"=>array(
              array( "type"=>"text", "name"=>"LHUTA","size"=>"5"),   
              array( "type"=>"date_db", "name"=>"DATUM_VYRIZENI","label"=>"Datum vyřízení","insertdatebutton"=>true),
              ),
              "format"=>"LHUTA...'&nbsp;&nbsp;&nbsp;Datum vyřízení&nbsp;'...DATUM_VYRIZENI",
              "visible"=>$is_filter_all,										 
              "label"=>"Lhůta k vyřízení:");		

   $FORM_CONFIG["schema"][] = array(
     "elements"=>array(array(
       "type"=>"select_vyrizeno",
       "name"=>"VYRIZENO",
       "insertnull"=>true,
     )),
     "visible"=>$is_edit or $is_info or $is_insert or $is_filter_all,										 
     "label"=>"Způsob vyřízení:"
   );		

   $FORM_CONFIG["schema"][] = array("elements"=>array(
//              array( "type"=>"text", "name"=>"POZNAMKA","size"=>"80"),   
              array( "type"=>"textarea", "name"=>"POZNAMKA","cols"=>"90","rows"=>5),
              ),
              "label"=>"Poznámka:");
  
   $FORM_CONFIG["schema"][] = array("elements"=>array(
              array( "type"=>"select_skartace", "name"=>"SKARTACE","size"=>"1","ukazjenaktivni"=>$is_insert,"insertnull"=>true, "width"=>"15"),
  ),
              "visible"=>($is_edit or $is_info or $is_insert),
              "label"=>$GLOBALS["CONFIG"]["NAZEV_SKARTACE"].":");

}

    $FORM_CONFIG["schema"][] = array("elements"=>array(
              array( "type"=>"text", "name"=>"SPIS_VYRIZEN","label"=>"Datum uzavření spisu"),
              array( "type"=>"text", "name"=>"PODCISLO_SPISU","label"=>"Přiřazené podčíslo v spisovém archu")),
              "visible"=>$is_history and !$is_filter,	
              "label"=>"");										 

  //include(FileUp2(".admin/el/urednik_id_zmena_dat_cas.inc"));
//  include(FileUp2(".admin/el/owner_user_date_form_add.inc"));

 if ($is_update) {
?>
  <style>
  /* Tlacitka pro duplikovani polozek ve formulari */
form a.button {
  display: inline-block;
  width: 22px;
  height: 22px;
  vertical-align: middle;
  cursor: pointer;
}

form a.button.add {
  background: url('images/add.png');
}

form a.button.remove {
  background: url('images/delete.png');
}
</style>

  <script defer src="<?php echo fileUpUrl('js/multiple_items.js'); ?>" type="text/javascript"></script>
  <script defer src="<?php echo fileUpUrl('js/vnitrni_adresati.js'); ?>" type="text/javascript"></script>

<?php
}

foreach($FORM_CONFIG["schema"] as $key => $val) {
    $FORM_CONFIG["schema"][$key]['theme_config'] = array('square' => array('format' => ''));

}
reset ($GLOBALS["CONFIG_POSTA"]["PLUGINS"]);
foreach($GLOBALS["CONFIG_POSTA"]["PLUGINS"] as $plug_name => $plug) {
  if ($plug['enabled']){
    $file = FileUp2('plugins/'.$plug['dir'].'/.admin/form_schema_vnitrni_end.inc');
		if (File_Exists($file)) include($file);
  }
}

