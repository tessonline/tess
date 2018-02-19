<?php
require_once(FileUpUrl('.admin/form_js_global.inc'));
If ((!$GLOBALS["HISTORY_ID"])) {
   //nacteme JS pro praci s ruznejma promennejma
   include_once(FileUp2("$path_posta/.admin/javascript.inc"));
}
$multiple = true;
$is_filter =true;
$is_filter_all = true;
if ($GLOBALS['CONFIG']['VYHLEDAVANI_NAPRIC_DB'] && $is_filter && !$GLOBALS['SUPERODBOR']) $GLOBALS['SUPERODBOR']=VratSuperOdbor();
  if ($is_filter && !$is_multiedit) $GLOBALS['VYHLEDAVANI']=true; //do of_select se spatne prehnaselo, kvuli referentum
  //zrusime DALSI_PRIJEMCI
  If (strpos($GLOBALS["DALSI_PRIJEMCI"],':')) $GLOBALS["DALSI_PRIJEMCI"]='';

       $FORM_CONFIG["schema"][] = array("elements"=>array(
          array( "type"=>"button", "value"=>"Vynulovat výběr","onclick"=>"document.location.href='edit.php?filter&NULL_SESSION=true'"),
          ),
          "label"=>""); 
  

$FORM_CONFIG = array(
  'theme_config' => array(
    'square' => array(
      'theme' => array(
        'columns' => true
      ),
    )
  )
);

reset ($GLOBALS["CONFIG_POSTA"]["PLUGINS"]);
foreach($GLOBALS["CONFIG_POSTA"]["PLUGINS"] as $plug_name => $plug) {
  if ($plug['enabled']){
    $file = FileUp2('plugins/'.$plug['dir'].'/.admin/form_schema_filter_all_start.inc');

		if (File_Exists($file)) include($file);
  }
}

$FORM_CONFIG['schema'][] = array(
  'label' => 'Základní údaje',
  'visible' => true,
  'theme_config' => array(
    'square' => array(
      'theme' => array(
        'column' => 1,
      )
    )
  )
);

    $FORM_CONFIG["schema"][] = array( "elements"=>array(
                       array( "type"=>"text", "name"=>"ID_X","label"=>"JID Dokumentu","size"=>32),
                       array( "type"=>"text_number", "name"=>"ID_DZ","label"=>"ID datové zprávy","size"=>32),
                       ),
//                       "visible"=>HasRole('spravce'),
                       "format"=>"'<span id=\"ID_span\">'...ID...'<a onclick=\"javascript:ReplaceIDSpan()\" style=\"cursor:pointer\"><img src=\"/images/arrow3l.gif\" title=\"Změnit pole\"></a></span>&nbsp;&nbsp;&nbsp;ID datové zprávy:&nbsp;'...ID_DZ",
                      "visible"=>$is_filter_all,
                       "label"=>"JID dokumentu:");
                       
      $FORM_CONFIG["schema"][] = array( "elements"=>array(
                  array( "type"=>"text", "name"=>"CISLO_SPISU1_TEXT","Jednací číslo dokumentu"),
                  array( "type"=>"text_number", "name"=>"CISLO_SPISU2","size"=>8,"label"=>"Rok"),
                  array( "type"=>"text", "name"=>"ZNACKA","label"=>"Značka ČJ","size"=>"30"),
//                  array( "type"=>"text", "name"=>"NAZEV_SPISU","label"=>"Název:"),
//                  array( "type"=>"checkbox", "name"=>"SEZNAM_SPISU","label"=>"Jen seznam"),
                   ),
                  "format"=>"CISLO_SPISU1...'/'...CISLO_SPISU2...'&nbsp;-&nbsp;'...NAZEV_SPISU...'&nbsp;&nbsp;jen seznam:&nbsp;'...SEZNAM_SPISU",
                  "label"=>"Číslo jednací");

      $FORM_CONFIG["schema"][] = array( "elements"=>array(
                  array( "type"=>"text", "name"=>"JEN_CISLO_SPISU1","Číslo spisu"),
                  array( "type"=>"text", "name"=>"JEN_CISLO_SPISU2","size"=>8,"label"=>"Rok spisu"),
                  array( "type"=>"text", "name"=>"NAZEV_SPISU_TEXT","label"=>"Název spisu","size"=>"30"),
                   ),
                  "format"=>"CISLO_SPISU1...'/'...CISLO_SPISU2...'&nbsp;-&nbsp;'...NAZEV_SPISU...'&nbsp;&nbsp;jen seznam:&nbsp;'...SEZNAM_SPISU",
                  "label"=>"Číslo spisu");

      $FORM_CONFIG["schema"][] = array( "elements"=>array(
                  array( "type"=>"checkbox", "name"=>"SEZNAM_SPISU","label"=>"Jen seznam spisů"),
                   ),
                  "label"=>"Jen seznam spisů");
/*
    $FORM_CONFIG["schema"][] = array("elements"=>array(
              array( "type"=>"select_superodbor", "name"=>"SUPERODBOR","insertnull"=>true),
              ),
              "visible" => ($GLOBALS['CONFIG']['USE_SUPERODBOR'] ? true : false),
              "label"=>$GLOBALS["CONFIG"]["NAZEV_SUPERODBOR"].":");
  */
                 
             // if ($is_filter_all) UNSET($GLOBALS[ODBOR]);
    
    $FORM_CONFIG["schema"][] = array("elements"=>array(
                array( "type"=>"select_vsechny_spisuzly", "name"=>"ODBOR", "size"=>6,"multiple"=>$multiple,"insertnull"=>true,"label"=>'Spisový uzel',"add"=>"style=\"width:530px;\" onChange=\"UkazPracovnika(this,'REFERENT[]');\""),
    ),
                "visible"=>$is_filter_all,
                "label"=>$GLOBALS["CONFIG"]["NAZEV_ODBOR"]);
              
    $fullselect = HasRole('spravce');          
    
    $FORM_CONFIG["schema"][] = array("elements"=>array(
              array( "type"=>"select_referent", "name"=>"REFERENT","size"=>8,"multiple"=>$multiple,"insertnull"=>true,"label"=>$GLOBALS["CONFIG"]["NAZEV_REFERENT"],"add"=>"style=\"width:530px;\"","fullselect"=>$fullselect,"label"=>'Zpracovatel'),
              ),
              "visible"=>$is_filter_all ,
              "label"=>"Zpracovatel");


      $FORM_CONFIG["schema"][] = array("elements"=>array(
              array( "type"=>"text", "name"=>"VEC", "size"=>70),
              ),
              "visible"=>$is_filter_all ,
              "label"=>"Věc:");


/*
    $FORM_CONFIG['schema'][] = array('elements'=>array(
             array( 
                  'type'=>'radio', 
                  'name'=>'TYP_DOKUMENTU_FILTER', 
                  'value'=>'',
      					  'options'=>array(
                    'příchozí dokument, vnitřní pošta' => 'fx',
                    'příchozí dokument, ostatní' => 'fa',
                    'vlastní záznam' => 'z',
                    'odchozí dokument, vnitřní pošta' => 'tx',
                    'odchozí dokument, ostatní' => 'ta',
                   ),
                  ),
             array( 
                  'type'=>'radio', 
                  'name'=>'UKAZ_SPISY', 
                  'value'=>'',
      					  'options'=>array(
      						 'Pouze uzavřené čj.'=>'1', 
      						 'Pouze otevřené čj.'=>'2',
                   ),
                ),
  
              ),
              "format"=>"'<table><td>'...TYP_DOKUMENTU_FILTER...'</td><td>'...UKAZ_SPISY...'</td></table>'",
              "visible"=>$is_filter_all ,										 
          "label"=>"Druhy dokumentů:");	
 */
$FORM_CONFIG['schema'][] = array(
  'label' => 'Další údaje'
);


   $FORM_CONFIG["schema"][] = array("elements"=>array(
                array( "type"=>"select_stavy_filtr", "name"=>"omez_stav","insertnull"=>true,"multiple"=>$multiple, "add"=>"style=\"width:265px;\""),
                array( "type"=>"select_typ_dokumentu", "name"=>"TYP_DOKUMENTU","insertnull"=>true,"multiple"=>$multiple,"label"=>"Typ dokumentu","add"=>"style=\"width:265px;\""),
                ),
                "visible"=>$is_filter_all,
                "label"=>"Stav dokumentu:");

   $FORM_CONFIG["schema"][] = array("elements"=>array(
                  array( "type"=>"select_agenda_dokumentu", "name"=>"AGENDA_DOKUMENTU","insertnull"=>true,"multiple"=>$multiple,"add"=>"style=\"width:530px;\" onChange=\"UkazTypPosty(this,'TYP_POSTY[]',0,0);\""),
                ),
                  "visible"=>$is_filter_all,
                  "label"=>"Agenda");
                
                
   $FORM_CONFIG["schema"][] = array("elements"=>array(
              array( "type"=>"select_typ_posty", "name"=>"TYP_POSTY","insertnull"=>true,"multiple"=>$multiple,"label"=>"Druh dokumentu","add"=>"style=\"width:530px;\""),
              ),
              "visible"=>$is_filter_all ,
              "label"=>"Druh dokumentu:");

   $FORM_CONFIG["schema"][] = array("elements"=>array(
                array( "type"=>"select_stav_posty", "name"=>"STAV_POSTY","insertnull"=>true,"multiple"=>$multiple,"add"=>"style=\"width:530px;\"")),
                "visible"=>$is_filter_all,
                "label"=>"Přednastavené filtry:");




   $FORM_CONFIG["schema"][] = array("elements"=>array(
              array( "type"=>"select_vita", "name"=>"STAV","fullselect"=>true,"insertnull"=>true,"multiple"=>$multiple,"add"=>"style=\"width:530px;\"")
              ),
              "visible"=>$is_filter_all,	
              "label"=>"Kde se vyřizuje:");

  $FORM_CONFIG["schema"][] = array("elements"=>array(
            array( "type"=>"text", "name"=>"ODESL_REKOMANDO","size"=>"32","label"=>"Rekomando"),
            array( "type"=>"text", "name"=>"ODESL_POSTAODESL","size"=>"32","label"=>"Odesílací pošta")),
            "format"=>"ODESL_REKOMANDO...'&nbsp;&nbsp;&nbsp;Odesílací pošta&nbsp;'...ODESL_POSTAODESL",
            "label"=>"Rekomando:");		

    $FORM_CONFIG["schema"][] = array("elements"=>array(
              array( "type"=>"text", "name"=>"JEJICH_CJ","label"=>"Číslo jednací firmy","add"=>' id="JEJICH_CJ"',"size"=>50,"label"=>"Číslo jednací firmy"),
              array( "type"=>"date_db", "name"=>"JEJICH_CJ_DNE","label"=>"Číslo jednací firmy","insertdatebutton"=>true, "insertcalendar"=>true,"label"=>"Ze dne","size"=>15),
              ),
              "format"=>"JEJICH_CJ...'&nbsp;&nbsp;&nbsp;ze&nbsp;dne:&nbsp;'...JEJICH_CJ_DNE",
             "visible"=>$is_edit or $is_info or $is_insert or $is_filter_all,
            "label"=>"Vaše čj.:");


    $FORM_CONFIG["schema"][] = array("elements"=>array(
              array( "type"=>"text_number", "name"=>"POCET_LISTU","label"=>"Počet listů"),   
              array( "type"=>"text", "name"=>"DRUH_PRILOH","size"=>40,"label"=>"Druh příloh"),
              array( "type"=>"text_number", "name"=>"POCET_PRILOH","label"=>"Počet příloh")),   
            "format"=>"POCET_LISTU...'&nbsp;&nbsp;&nbsp;Druh příloh:&nbsp;'...DRUH_PRILOH...'&nbsp;&nbsp;&nbsp;Počet(velikost) příloh:&nbsp;'...POCET_PRILOH...'(ks/kB)'",										 
            "visible"=>$is_filter_all,
            "label"=>"Počet listů:");		

    
 /*$FORM_CONFIG["schema"][] = array("elements"=>array(
              array( "type"=>"date_db", "name"=>"DATUM_OD","insertdatebutton"=>true, "insertcalendar"=>true,"label"=>"Datum přijetí od"),
              array( "type"=>"date_db", "name"=>"DATUM_DO","insertdatebutton"=>true, "insertcalendar"=>true,"label"=>"Datum přijetí do"),
              array( "type"=>"select_druh_prijeti", "name"=>"ZPUSOB_PODANI","insertnull"=>true,"label"=>"Způsob podání","add"=>"style=\"width:245px;\""),
              ),   
              "format"=>"DATUM_OD...'&nbsp;do&nbsp;'...DATUM_DO...'&nbsp;&nbsp;&nbsp;Způsob&nbsp;podání:&nbsp;'...ZPUSOB_PODANI",
              "visible"=>$is_filter_all,										 
              "label"=>"Datum od:");*/		

   //nastavení filtrů
               
   if (!isset($validFullText)) {
          $validFullText = '';
  }
              
              
   $validDate = "      
      var rtr;
      try {
        rtr = ret;
      }
      catch (e) {
        rtr = true;
      }
      var v_do = valDate('DATUM_OD');
      if (v_do) {
        var v_od = valDate('DATUM_DO');
        v_do = v_do && v_od;
      }
      rtr = rtr && v_do;
      return (rtr);    ";
   
   $validFunc = $validFullText.$validDate;

   
   $FORM_CONFIG["schema"][] = array("elements"=>array(
                array( "type"=>"text", "name"=>"DATUM_OD","label"=>"Datum přijetí od"),
                array( "type"=>"text", "name"=>"DATUM_DO","label"=>"Datum přijetí do"),
                array( "type"=>"select_druh_prijeti", "name"=>"ZPUSOB_PODANI","insertnull"=>true,"multiple"=>$multiple,"multiple"=>$multiple,"label"=>"Způsob podání","add"=>"style=\"width:168px;\""),
              ),
                "format"=>"DATUM_OD...'&nbsp;do&nbsp;'...DATUM_DO...'&nbsp;&nbsp;&nbsp;Způsob&nbsp;podání:&nbsp;'...ZPUSOB_PODANI",
                "visible"=>true,
                "label"=>"Datum od:");
              
   $FORM_CONFIG["schema"][] = array("elements"=>array(
                array("type"=>"valid_fce","name_fce"=>$validFunc)),
   );

   $FORM_CONFIG["schema"][] = array("elements"=>array(
              array( "type"=>"date_db", "name"=>"DATUM_REFERENT_PRIJETI","label"=>"Zpracovatel přečetl","insertdatebutton"=>true, "insertcalendar"=>true,"size"=>"20"),
              array( "type"=>"text_number", "name"=>"LHUTA","size"=>"29"),
              array( "type"=>"date_db", "name"=>"DATUM_VYRIZENI","label"=>"Datum vyřízení","insertdatebutton"=>true, "insertcalendar"=>true,"size"=>"20"),
              ),
              "format"=>"LHUTA...'&nbsp;&nbsp;&nbsp;Datum vyřízení&nbsp;'...DATUM_VYRIZENI",
              "visible"=>$is_filter_all,
              "label"=>"Lhůta k vyřízení:");

       $FORM_CONFIG["schema"][] = array("elements"=>array(
              array( "type"=>"select_vyrizeno", "name"=>"VYRIZENO","insertnull"=>true,"add"=>"style=\"width:530px;\""),
              ),
              "label"=>"Způsob vyřízení:");


    $FORM_CONFIG["schema"][] = array("elements"=>array(
              array( "type"=>"select_typ_odeslani", "name"=>"DOPORUCENE", "width"=>10,"insertnull"=>"true","multiple"=>$multiple,"label"=>"Způsob odeslání","add"=>"style=\"width:265px;\""),
              array( "type"=>"select_druh_odeslani", "name"=>"VLASTNICH_RUKOU", "width"=>10,"insertnull"=>"true","multiple"=>$multiple,"label"=>"Způsob vypravení","add"=>"style=\"width:265px;\"")
              ),
              "format"=>"DOPORUCENE...'&nbsp;&nbsp;&nbsp;Doručení:&nbsp;'...VLASTNICH_RUKOU",
              "label"=>"Způsob odeslání:");


    If ($GLOBALS["CONFIG"]["UKAZ_ULOZENO"])
       $FORM_CONFIG["schema"][] = array("elements"=>array(
              array( "type"=>"select_ulozeno", "name"=>"ULOZENO","insertnull"=>true,"frozen"=>!(HasRole('spravce')||HasRole('vedouci-odbor')||HasRole('vedouci-odd')||HasRole('zpracovatel'))),   
              ),
              "label"=>"Uloženo:");		

   $FORM_CONFIG["schema"][] = array("elements"=>array(
//              array( "type"=>"text", "name"=>"POZNAMKA","size"=>"80","maxlength"=>250),
              array( "type"=>"text", "name"=>"POZNAMKA","cols"=>"80", "size"=>70),
              array( "type"=>"hidden", "name"=>"VYHLEDAVANI","value"=>1),
  ),
  "label"=>"Poznámka:");

   $FORM_CONFIG["schema"][] = array("elements"=>array(
//              array( "type"=>"text", "name"=>"POZNAMKA","size"=>"80","maxlength"=>250),
              array( "type"=>"text", "name"=>"POZNAMKA_ULOZENO", "size"=>70),
  ),
  "label"=>"Poznámka pro uložení:");

   $FORM_CONFIG["schema"][] = array("elements"=>array(
              array( "type"=>"select_skartace", "name"=>"SKARTACE","size"=>"5","add"=>"style=\"width:530px;\"", "insertnull"=>true,"multiple"=>$multiple,"no_frozen"=>true),
  ),
              "visible"=>$is_filter_all,										 
              "label"=>$GLOBALS["CONFIG"]["NAZEV_SKARTACE"].":");		
  //******************************************
//     include(FileUp2(".admin/form_schema_xertec.inc"));
  
/*
  if ($is_filter_all)
  {
    include(FileUp2(GetAgendaPath('POSTA_SPIS')."/.admin/properties.inc"));  
    include(FileUp2(GetAgendaPath('POSTA_SPIS')."/.admin/form_schema.inc"));  
  }
*/  
$FORM_CONFIG['schema'][] = array(
  'label' => 'Odesilatel/adresát',
  'visible' => true,
  'theme_config' => array(
    'square' => array(
      'theme' => array(
        'column' => 2,
      )
    )
  )
);
    //nacteme adresaty

     include(FileUp2(".admin/form_schema_adresat.inc"));

/*
  $FORM_CONFIG["schema"][] = array("elements"=>array(
            array( "type"=>"select_odes_typ", "name"=>"ODES_TYP", "width"=>10,"insertnull"=>true)),
            "label"=>"Odesílatel:");

  $FORM_CONFIG["schema"][] = array("elements"=>array(
            array( "type"=>"text", "name"=>"ODESL_PRIJMENI","size"=>"40","label"=>"Příjmení","size"=>32),
            array( "type"=>"text", "name"=>"ODESL_JMENO","size"=>"20","label"=>"Jméno"),
            array( "type"=>"text", "name"=>"ODESL_TITUL","size"=>"5","label"=>"Titul")),
            "format"=>"ODESL_PRIJMENI...'&nbsp;&nbsp;&nbsp;Jméno:&nbsp;'...ODESL_JMENO...'&nbsp;&nbsp;&nbsp;Titul:&nbsp;'...ODESL_TITUL",
            "label"=>'<b>' . $GLOBALS["CONFIG"]["NAZEV_ADRESAT_JMENO"] . ':</b>');

  $FORM_CONFIG["schema"][] = array("elements"=>array(
            array( "type"=>"text", "name"=>"ODESL_ICO","size"=>"12","label"=>$GLOBALS["CONFIG"]["NAZEV_ODESL_ICO"]),
            array( "type"=>"text", "name"=>"ODESL_ODD","size"=>"25","label"=>"Oddělení"),
            array( "type"=>"text", "name"=>"ODESL_OSOBA","size"=>"20","label"=>"Osoba")
            ),
            "format"=>"ODESL_ICO...'&nbsp;&nbsp;&nbsp;Oddělení&nbsp;'...ODESL_ODD...'&nbsp;&nbsp;&nbsp;Kont.&nbsp;osoba&nbsp;'...ODESL_OSOBA",
            "label"=>$GLOBALS["CONFIG"]["NAZEV_ODESL_ICO"].":");

  $FORM_CONFIG["schema"][] = array("elements"=>array(
            array( "type"=>"text", "name"=>"ODESL_ULICE","size"=>"40","label"=>"Ulice","size"=>27),
            array( "type"=>"text", "name"=>"ODESL_CP","label"=>"č.p."),
            array( "type"=>"text", "name"=>"ODESL_COR","label"=>"č.orient."),
            ),
            "format"=>"ODESL_ULICE...'&nbsp;&nbsp;&nbsp;č.p.:&nbsp;'...ODESL_CP...'&nbsp;&nbsp;&nbsp;č.or.:&nbsp;'...ODESL_COR",
            "label"=>"Ulice:");

  $FORM_CONFIG["schema"][] = array("elements"=>array(
              array( "type"=>"text", "name"=>"ODESL_PSC","size"=>"8","label"=>"PSČ"),
              array( "type"=>"text", "name"=>"ODESL_POSTA","size"=>"40","label"=>$GLOBALS["CONFIG"]["NAZEV_ADRESAT_POSTA"]),
              array( "type"=>"text", "name"=>"ODESL_DATSCHRANKA","size"=>"9","label"=>"Datová schránka"),
            ),
            "format"=>"ODESL_PSC...'&nbsp;&nbsp;&nbsp;{$GLOBALS["CONFIG"]["NAZEV_ADRESAT_POSTA"]}&nbsp;'...ODESL_POSTA...'&nbsp;&nbsp;&nbsp;Dat.schránka:&nbsp;'...ODESL_DATSCHRANKA",
            "label"=>"PSČ:");
*/
  $FORM_CONFIG["schema"][] = array("elements"=>array(
    array( "type"=>"hidden","name"=>"KOPIE_SOUBORU","value"=>$GLOBALS['EDIT_ID'])),
    "visible"=>($GLOBALS['EDIT_ID'] && $GLOBALS['add_adresat']==1),
    "label"=>""
  );



reset ($GLOBALS["CONFIG_POSTA"]["PLUGINS"]);
foreach($GLOBALS["CONFIG_POSTA"]["PLUGINS"] as $plug_name => $plug) {
  if ($plug['enabled']){
    $file = FileUp2('plugins/'.$plug['dir'].'/.admin/form_schema_filter_all_end.inc');

		if (File_Exists($file)) include($file);
  }
}


$select_file = FileUp2('.admin/el/owner_user_date_form_add.inc');
if (file_exists($select_file)) {
  include_once($select_file);
}
else {
  @include(FileUp2(".admin/el/urednik_id_zmena_dat_cas.inc"));
}



foreach($FORM_CONFIG["schema"] as $key => $val) {
  $FORM_CONFIG["schema"][$key]['theme_config'] = array('square' => array('format' => ''));
  if ($val['elements'])
    foreach($val['elements'] as $key1 => $val1) {
       if ($val1['type'] == 'text' && $val1['name'] <> 'CISLO_SPISU1_TEXT' && $val1['name'] <> 'JEN_CISLO_SPISU1' && $val1['name'] <> 'JEN_CISLO_SPISU2' && $val1['name'] <> 'ID_X' && $val1['name'] <> 'FULLTEXT_SEARCH')
         $FORM_CONFIG["schema"][$key]['elements'][$key1]['add_star'] = true;
    }
}
?>
<script language="javascript" type="text/javascript">

function valDate(elementName) {
	  var err = false;
	  var textInput = window.document.getElementsByName(elementName)[0];
	  if (textInput.value != '') {
	    if (window.RegExp) {
	      var reg = new RegExp('*', 'g');
	      textInput.value = textInput.value.replace(reg, '');
	      var reg2 = new RegExp('[+-]{0,1}[0-9]{1,2}[dmryDMRY]{1}');
	      if (reg2.test(textInput.value)) return true;
	      alert(textInput.value);
	      alert(err);
	      var reg = new RegExp('^[0-9]{1,2}[.][0-9]{1,2}[.][0-9]{4}$', 'g');
	      if (!reg.test(textInput.value)) err = true;
	      alert(err);
	    };
	    dt = textInput.value.split('.');
	    y = dt[2];
	    m = dt[1];
	    d = dt[0];
	    if (m < 1 || m > 12) err = true;
	    if (d < 1 || d > 31) err = true;
	    if ((d == 31) && (m == 4 || m == 6 || m == 9 || m == 11)) err = true;
	    if ((m == 2) && (d > 29)) err = true;
	  } else err = false;
	  if (err == true){
	    alert('Datum nemá správnou hodnotu nebo formát. Správný formát je \'d.m.yyyy\' (p\u0159: 31.12.1999) nebo můžete použít hodnoty +-nD (kde n je počet dní, např: -1D) +-nM (pro měsíce) a +- nY (pro roky)');
	    textInput.focus();
	  }
	  return !err;
	}

</script>
<?php 
//print_r($FORM_CONFIG);