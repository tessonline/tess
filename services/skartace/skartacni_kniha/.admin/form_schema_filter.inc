<?php
     include_once(FileUp2("$path_posta/.admin/javascript.inc"));
//include_once(FileUp2(".admin/table_funkce.inc"));

$FORM_CONFIG = array(
  'theme_config' => array(
    'square' => array(
      'theme' => array(
        'columns' => true
      ),
    )
  )
);
$GLOBALS['SPISOVNA_ID'] = $_SESSION['SESSION_SPISOVNA_ID'];

    $FORM_CONFIG["schema"][] = array( "label"=>"Hledání");

    $USER_INFO = $GLOBALS["POSTA_SECURITY"]->GetUserInfo();
                       
    $FORM_CONFIG["schema"][] = array( "elements"=>array(
                array( "type"=>"text", "name"=>"CISLO_SPISU1",'label'=>'Pořadové číslo'),
                array( "type"=>"text", "name"=>"CISLO_SPISU2","size"=>8,'label'=>'Rok'),
                array( "type"=>"text", "name"=>"NAZEV_SPISU",'label'=>'Značka'),
                 ),
                "format"=>"CISLO_SPISU1...'/'...CISLO_SPISU2...'&nbsp;-&nbsp;'...NAZEV_SPISU",
                "label"=>$GLOBALS["CONFIG"]["CISLO_SPISU"].":",
            // zruseni format pro tema square
          'theme_config' => array(
            'square' => array(
              'format' => '',
            )
          )
    );


      $FORM_CONFIG["schema"][] = array("elements"=>array(
              array( "type"=>"text", "name"=>"TEXT_CJ", "size"=>50,'add_star'=>true),
              ),
              "visible"=>$is_filter_all ,
              "label"=>"Ručné zapsané čj. do spisovny:");


//  If (HasRole('spisovna') || HasRole('spravce') || HasRole(' zmena-odboru') || HasRole('zmena-odboru-nahoru')) {
    //if ($is_filter_all) UNSET($GLOBALS[ODBOR]);
    $FORM_CONFIG["schema"][] = array("elements"=>array(
              array( "type"=>"select_vsechny_spisuzly", "name"=>"ODBOR","insertnull"=>true,"add"=>"id=\"ODBOR\" onChange=\"UkazPracovnika(this,'REFERENT');\""),
              ),
              "label"=>'<b>' . $GLOBALS["CONFIG"]["NAZEV_ODBOR"] . ':</b>');
//  }


  $FORM_CONFIG["schema"][] = array("elements"=>array(
            array( "type"=>"select_typ_posty", "name"=>"TYP_POSTY", "width"=>10,"insertnull"=>true)),
            "visible"=>$is_filter_all ,										 
            "label"=>"Druh dokumentu");

  $FORM_CONFIG["schema"][] = array("elements"=>array(
            array( "type"=>"text", "name"=>"VEC", "size"=>80),
            ),
            "visible"=>$is_filter_all ,										 
            "label"=>"<b>Věc:</b>");										 

  //nacteme adresaty
  $is_filter_all = true;
  include(FileUp2('.admin/form_schema_adresat.inc'));



 $FORM_CONFIG["schema"][] = array("elements"=>array(
            array( "type"=>"date_db", "name"=>"DATUM_OD", "insertcalendar"=>true,"insertdatebutton"=>true,'label'=>'Datum od'),
            array( "type"=>"date_db", "name"=>"DATUM_DO", "insertcalendar"=>true,"insertdatebutton"=>true,'label'=>'Datum do'),
            array( "type"=>"select_druh_prijeti", "name"=>"ZPUSOB_PODANI","insertnull"=>true,"label"=>"Způsob podání"),   
            ),   
            "format"=>"DATUM_OD...'&nbsp;do&nbsp;'...DATUM_DO...'&nbsp;&nbsp;&nbsp;Způsob&nbsp;podání:&nbsp;'...ZPUSOB_PODANI",
            "visible"=>$is_filter_all,										 
            "label"=>"Datum od:",
            // zruseni format pro tema square
          'theme_config' => array(
            'square' => array(
              'format' => '',
            )
          )
    );


 $FORM_CONFIG["schema"][] = array("elements"=>array(
            array( "type"=>"select_referent", "name"=>"REFERENT","insertnull"=>true,"fullselect"=>true,"label"=>$GLOBALS["CONFIG"]["NAZEV_REFERENT"] ,'label'=>'Zpracovatel'),
),
            "visible"=>$is_filter_all,										 
            "label"=>$GLOBALS["CONFIG"]["NAZEV_REFERENT"],
            // zruseni format pro tema square
          'theme_config' => array(
            'square' => array(
              'format' => '',
            )
          )
    );


 $FORM_CONFIG["schema"][] = array("elements"=>array(
            array( "type"=>"select_skartace", "name"=>"SKARTACE","size"=>"1", "insertnull"=>true),
),
            "visible"=>$is_filter_all,										 
            "label"=>$GLOBALS["CONFIG"]["NAZEV_SKARTACE"].":");		

 $FORM_CONFIG["schema"][] = array("elements"=>array(
            array( "type"=>"text", "name"=>"SPIS_ZNAK",'label'=>'Spisový znak (kod)'),
            array( "type"=>"text", "name"=>"SPIS_ZNAK_TEXT",'size'=>40,'label'=>'Spisový znak (text)'),
            ),   
            "format"=>"SPIS_ZNAK...'&nbsp;&nbsp;&nbsp;text&nbsp;spisového&nbsp;znaku:&nbsp;'...SPIS_ZNAK_TEXT",
            "visible"=>$is_filter_all,										 
            "label"=>"Spisový znak:",
            // zruseni format pro tema square
          'theme_config' => array(
            'square' => array(
              'format' => '',
            )
          )
    );



  $FORM_CONFIG["schema"][] = array( "label"=>"Spisovna");

  $FORM_CONFIG["schema"][] = array("elements"=>array(
                 array( "type"=>"select_spisovna", "name"=>"SPISOVNA_ID","insertnull"=>true,'label'=>'Spisovna'),
                 array( "type"=>"text_number", "name"=>"ROK_SKARTACE","size"=>"4",'label'=>'Rok skartace'),
                 array( "type"=>"select_skartacni_pismeno", "name"=>"SKAR_ZNAK","insertnull"=>true,'label'=>'Písmeno'),
                 array( "type"=>"text_number", "name"=>"DOBA","insertnull"=>true,"size"=>"2",'label'=>'Lhůta'),
              ),
              "format"=>"SPISOVNA_ID...'&nbsp;&nbsp;&nbsp;Rok skartace:'...ROK_SKARTACE...'&nbsp;&nbsp;&nbsp;Písmeno:'...SKAR_ZNAK...'&nbsp;&nbsp;&nbsp;Lhůta:'...DOBA",
              "visible"=>$is_filter,
              "label"=>"Spisovna:",
            // zruseni format pro tema square
          'theme_config' => array(
            'square' => array(
              'format' => '',
            )
          )
    );

    $FORM_CONFIG["schema"][] = array("elements"=>array(
              array( "type"=>"text_number", "name"=>"LISTU","label"=>"Počet listů"),
              array( "type"=>"text", "name"=>"PRILOHY","size"=>40,"label"=>"Přílohy"),

            ),
            "label"=>"Počet listů:");


    $FORM_CONFIG["schema"][] = array("elements"=>array(
            array( "type"=>"text", "name"=>"POZNAMKA", "size"=>80),
            ),
            "visible"=>$is_filter_all ,										 
            "label"=>"Poznámka pro uložení:"); 


  $FORM_CONFIG["schema"][] = array( "elements"=>array(
                array( "type"=>"select_typ_spisu", "name"=>"ULOZENI","insertnull"=>true),
                 ),
                "visible"=>$is_filter,
                "label"=>"Uložení ve spisovně:");  

//echo $prijemci;

    $FORM_CONFIG["schema"][] = array("elements"=>array(
              array( "type"=>"date_db", "name"=>"DATUM_PREDANI_od", "insertcalendar"=>true, "insertdatebutton"=>true,'label'=>'Uložení do spisovny'),
              array( "type"=>"date_db", "name"=>"DATUM_PREDANI_do", "insertcalendar"=>true, "insertdatebutton"=>true,'label'=>'od'),
              array( "type"=>"select_referent", "name"=>"PREVZAL_ID", "insertcalendar"=>true,"insertnull"=>true,"fullselect"=>true,'label'=>'do'),
            ),
            "visible"=>$is_filter_all ,
            "format"=>"'v obodbí od:&nbsp;'...DATUM_PREDANI_od...'&nbsp;&nbsp;&nbsp;do:&nbsp;'...DATUM_PREDANI_do...'&nbsp;&nbsp;&nbsp;kým:&nbsp;'...PREVZAL_ID",										 
            "label"=>"Uložení do spisovny:",
            // zruseni format pro tema square
          'theme_config' => array(
            'square' => array(
              'format' => '',
            )
          )
    );


  $FORM_CONFIG["schema"][] = array("elements"=>array(
    array( "type"=>"text","name"=>"UKLADACI_ZNACKA_TEXT","size"=>80)),
    "visible"=>$is_filter_all && $GLOBALS['CONFIG']['UKLADACI_ZNACKY'],
    "label"=>"Ukládací značka:"
  );
// $FORM_CONFIG['schema'][] = array('elements'=>array(
// 	array( "type"=>"text", "name"=>"LOKACE_TEXT", 'size'=>80, 'add'=>'id="txtAuto"','label'=>'Fyzická lokace'),
//     array( "type"=>"hidden", "name"=>"LOKACE_ID", 'add'=>'id="LokaceId"')
//    ),
//
// "label"=>"Lokace ve spisovně:");


  $FORM_CONFIG["schema"][] = array("elements"=>array(
    array( "type"=>"select_skartacni_rizeni","name"=>"SKARTACNI_RIZENI_ID","insertnull"=>true)),
    "visible"=>$is_filter_all,
    "label"=>"Skartační řízení:"
  );


  include_once(FileUp2(".admin/form_schema_lokace.inc"));

  $FORM_CONFIG["schema"][] = array( "label"=>"Úložiště el. dokumentů");

  $FORM_CONFIG["schema"][] = array("elements"=>array(
                 array( "type"=>"date_db", "name"=>"TSA_od","size"=>"4", "insertcalendar"=>true,"insertdatebutton"=>true,'label'=>'Platnost razítka od'),
                 array( "type"=>"date_db", "name"=>"TSA_do", "insertcalendar"=>true, "insertdatebutton"=>true, 'label'=>'Platnost razítka do'),
              ),
              "visible"=>$is_filter,
              "label"=>"Platnost razítek:",
    );

if ($is_filter_all) {
  reset ($GLOBALS["CONFIG_POSTA"]["PLUGINS"]);
  foreach($GLOBALS["CONFIG_POSTA"]["PLUGINS"] as $plug_name => $plug) {
    if ($plug['enabled']){
      $file = FileUp2('plugins/'.$plug['dir'].'/.admin/form_schema_filter_all_end.inc');

  		if (File_Exists($file)) include($file);
    }
  }

}



$fce1="
if ((document.forms[0].POZNAMKA.value ||document.forms[0].TEXT_CJ.value ||document.forms[0].DATUM_PREDANI_od.value || document.forms[0].DATUM_PREDANI_do.value || document.forms[0].LAST_USER_ID.value) && !document.forms[0].SPISOVNA_ID.value) {
  alert('V případě výběru Ručně zapsaného čj. nebo Poznámky pro uložení nebo Uložení do spisovny je nutné vybrat, v které spisovně se má prohledávat.');
  return(false);
}
";

//pokud je zapnuta volba pro nutnost spisu, tak udelame alert okno u dokumentu, ktery je dan do spisu a pokud nema skartacni znak
$FORM_CONFIG["schema"][] = array("elements"=>array(
   array("type"=>"valid_fce","name_fce"=>$fce1)),
         "visible"=>$is_filter,
    );

foreach($FORM_CONFIG["schema"] as $key => $val) {
  $FORM_CONFIG["schema"][$key]['theme_config'] = array('square' => array('format' => ''));
  if ($val['elements'])
    foreach($val['elements'] as $key1 => $val1) {
       if ($val1['type'] == 'text' && $val1['name'] <> 'CISLO_SPISU1' && $val1['name'] <> 'CISLO_SPISU2' && $val1['name'] <> 'JEN_CISLO_SPISU2')
         $FORM_CONFIG["schema"][$key]['elements'][$key1]['add_star'] = true;
    }
}

