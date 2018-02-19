<?php
$USER_INFO = $GLOBALS["POSTA_SECURITY"]->GetUserInfo();

if ($GLOBALS['vraceno']) {
  $GLOBALS['VRACENO_KOMU'] = $USER_INFO['ID'];
  $GLOBALS['VRACENO'] = Date('Y-m-d');
}

    $FORM_CONFIG["schema"][] = array("elements"=>array(
                   array("type" => "select_spisovna", "name" => "SPISOVNA_ID", "insertnull"=>true),   
                ), 
                "label" => "Spisovna:");


  $FORM_CONFIG["schema"][] = array(
          "elements"=>array(
            array("type" => "textarea", "name" => "RUCNE_CJ", "cols"=>50, "rows"=>5), 
          ), 
          "visible" => !$is_info,
          "label" => "Seznam čj.:"); 
  
  $FORM_CONFIG["schema"][] = array(
          "elements"=>array(
            array("type" => "textarea", "name" => "RUCNE_CJ", "cols"=>50, "rows"=>5), 
          ), 
          "visible" => $is_info && ($GLOBALS['RUCNE'] == 1),
          "label" => "Seznam čj.:"); 
  


  $FORM_CONFIG["schema"][] = array(
          "elements"=>array(
            array("type" => "select_referent", "name" => "PUJCENO_KOMU", "insertnull"=>true, "fullselect"=>true, "required"=>true), 
            array("type" => "hidden", "name" => "VYTVORENO_KYM", "value" => $USER_INFO['ID']), 
            array("type" => "hidden", "name" => "RUCNE", "value" => 1), 
          ), 
          "visible" => !$is_info,
          "label" => "Půjčeno komu:"); 

  $FORM_CONFIG["schema"][] = array(
          "elements"=>array(
            array("type" => "date_db", "name" => "VYTVORENO", "insertdatebutton"=>true), 
          ), 
          "visible" => !$is_info,
          "label" => "Půjčeno dne:"); 

  $FORM_CONFIG["schema"][] = array(
          "elements"=>array(
            array("type" => "select_referent", "name" => "VRACENO_KOMU", "insertnull"=>true, "fullselect"=>true), 
          ), 
          "visible" => !$is_info && !$is_insert,
          "label" => "Vráceno komu:"); 

  $FORM_CONFIG["schema"][] = array(
          "elements"=>array(
            array("type" => "date_db", "name" => "VRACENO", "insertdatebutton"=>true), 
          ), 
          "visible" => !$is_info && !$is_insert,
          "label" => "Vráceno dne:"); 

  $FORM_CONFIG["schema"][] = array(
          "elements"=>array(
            array("type" => "date_db", "name" => "VYTVORENO", "insertdatebutton"=>true), 
            array("type" => "select_referent", "name" => "PUJCENO_KOMU", "insertnull"=>true, "fullselect"=>true), 
          ), 
          "format" => "'Dne:&nbsp;'...VYTVORENO...'&nbsp;&nbsp;&nbsp;Komu:&nbsp;'...PUJCENO_KOMU",
          "visible" => $is_info,
          "label" => "Půjčeno:"); 

  $FORM_CONFIG["schema"][] = array(
          "elements"=>array(
            array("type" => "select_referent", "name" => "VYTVORENO_KYM", "fullselect"=>true), 
          ), 
          "visible" => $is_info,
          "label" => "Zapůjčil:"); 


  $FORM_CONFIG["schema"][] = array(
          "elements"=>array(
            array("type" => "date_db", "name" => "VRACENO", "insertdatebutton"=>true), 
            array("type" => "select_referent", "name" => "VRACENO_KOMU", "insertnull"=>true, "fullselect"=>true), 
          ), 
          "format" => "'Dne:&nbsp;'...VRACENO...'&nbsp;&nbsp;&nbsp;Komu:&nbsp;'...VRACENO_KOMU",
          "visible" => $is_info,
          "label" => "Vráceno:"); 


  $FORM_CONFIG["schema"][] = array(
          "elements"=>array(
            array("type" => "textarea", "name" => "POZNAMKA", "cols"=>50, "rows"=>5), 
          ), 
          "label" => "Poznámka:"); 
  

/*
  $FORM_CONFIG["schema"][] = array(
          "elements"=>array(
            array("type" => "select_referent", "name" => "PREDAL_ID", "insertnull"=>true, "fullselect"=>true), 
            array("type" => "hidden", "name" => "PREVZAL_ID", "value" => $USER_INFO['ID']), 
          ), 
          "label" => "Půjčeno komu:"); 


                       
      $FORM_CONFIG["schema"][] = array("elements"=>array(
                  array("type" => "text", "name" => "CISLO_SPISU1"), 
                  array("type" => "text", "name" => "CISLO_SPISU2", "size"=>8), 
                  array("type" => "text", "name" => "NAZEV_SPISU"), 
                   ), 
                  "format" => "CISLO_SPISU1...'/'...CISLO_SPISU2...'&nbsp;-&nbsp;'...NAZEV_SPISU", 
                  "label"=>$GLOBALS["CONFIG"]["CISLO_SPISU"].":");


  IF ($GLOBALS[CONFIG][ODDELENI])
  {
    //pouzivame oddeleni - vyhledavani
    $FORM_CONFIG["schema"][] = array("elements"=>array(
              array("type" => "select_oddeleni", "name" => "ODDELENI", "insertnull"=>true), 
              ), 
              "visible"=>$is_filter_all , 										 
              "format" => "'<div id=\"ODDELENI\">'...ODDELENI...'</div>'", 
              "label" => "Oddělení:");										 
  }  

    $FORM_CONFIG["schema"][] = array("elements"=>array(
              array("type" => "select_typ_posty", "name" => "TYP_POSTY", "width"=>10, "insertnull"=>true)), 
              "visible"=>$is_filter_all , 										 
              "label" => "Druh dokumentu:");			

      $FORM_CONFIG["schema"][] = array("elements"=>array(
              array("type" => "text", "name" => "VEC", "size"=>80), 
              ), 
              "visible"=>$is_filter_all , 										 
              "label" => "<b>Věc:</b>");										 

    //nacteme adresaty
    $is_filter_all = true;
    include(FileUp2('.admin/form_schema_adresat.inc'));

  

   $FORM_CONFIG["schema"][] = array("elements"=>array(
              array("type" => "date_db", "name" => "DATUM_OD", "insertdatebutton"=>true),   
              array("type" => "date_db", "name" => "DATUM_DO", "insertdatebutton"=>true), 
              array("type" => "select_druh_prijeti", "name" => "ZPUSOB_PODANI", "insertnull"=>true, "label" => "Způsob podání"),   
              ),   
              "format" => "DATUM_OD...'&nbsp;do&nbsp;'...DATUM_DO...'&nbsp;&nbsp;&nbsp;Způsob&nbsp;podání:&nbsp;'...ZPUSOB_PODANI", 
              "visible"=>$is_filter_all, 										 
              "label" => "Datum od:");		

   $FORM_CONFIG["schema"][] = array("elements"=>array(
              array("type" => "select_referent", "name" => "REFERENT", "insertnull"=>true, "label"=>'<b>' . $GLOBALS["CONFIG"]["NAZEV_REFERENT"] . ':</b>'),   
              array("type" => "date_db", "name" => "DATUM_REFERENT_PRIJETI", "label" => "Zpracovatel přečetl", "insertdatebutton"=>true),   
  ), 
              "format" => "'<span id=REFERENT>'...REFERENT...'</span>&nbsp;&nbsp;&nbsp;Zpracovatel přečetl&nbsp;'...DATUM_REFERENT_PRIJETI", 
              "visible"=>$is_filter_all, 										 
              "label"=>'<b>' . $GLOBALS["CONFIG"]["NAZEV_REFERENT"] . ':</b>');		
  
   $FORM_CONFIG["schema"][] = array("elements"=>array(
              array("type" => "select_skartace", "name" => "SKARTACE", "size" => "1", "insertnull"=>true),   
  ), 
              "visible"=>$is_filter_all, 										 
              "label"=>$GLOBALS["CONFIG"]["NAZEV_SKARTACE"].":");		
  

      $FORM_CONFIG["schema"][] = array("elements"=>array(
              array("type" => "text", "name" => "POZNAMKA", "size"=>80), 
              ), 
              "visible"=>$is_filter_all , 										 
              "label" => "Poznámka pro uložení:"); 

  //echo $prijemci;
    $FORM_CONFIG["schema"][] = array("elements"=>array(
                   array("type" => "select_spisovna", "name" => "SPISOVNA_ID", "insertnull"=>true, "required"=>false),   
                   array("type" => "text_number", "name" => "ROK_SKARTACE", "size" => "4"), 
                   array("type" => "select_skartacni_pismeno", "name" => "SKAR_ZNAK", "insertnull"=>true), 
                   array("type" => "text_number", "name" => "DOBA", "insertnull"=>true, "size" => "2"), 
                ), 
                "format" => "SPISOVNA_ID...'&nbsp;&nbsp;&nbsp;Rok skartace:'...ROK_SKARTACE...'&nbsp;&nbsp;&nbsp;Písmeno:'...SKAR_ZNAK...'&nbsp;&nbsp;&nbsp;Lhůta:'...DOBA", 
                "visible"=>$is_filter, 										 
                "label" => "Spisovna:");
  

    $FORM_CONFIG["schema"][] = array("elements"=>array(
      array("type" => "text", "name" => "UKLADACI_ZNACKA_TEXT", "size"=>80)), 
      "visible"=>$is_filter_all && $GLOBALS['CONFIG']['UKLADACI_ZNACKY'], 
      "label" => "Ukládací značka:"
    );




  $fce1="
  if ((document.forms[0].POZNAMKA.value ||document.forms[0].DATUM_PREDANI_od.value || document.forms[0].DATUM_PREDANI_do.value || document.forms[0].LAST_USER_ID.value) && !document.forms[0].SPISOVNA_ID.value) {
    alert('V případě výběru Poznámky pro uložení nebo Uložení do spisovny je nutné vybrat, v které spisovně se má prohledávat.');
    return(false);
  }
  ";

  //pokud je zapnuta volba pro nutnost spisu, tak udelame alert okno u dokumentu, ktery je dan do spisu a pokud nema skartacni znak
  $FORM_CONFIG["schema"][] = array("elements"=>array(
     array("type" => "valid_fce", "name_fce"=>$fce1)), 
           "visible"=>$is_filter, 
      );
*/
