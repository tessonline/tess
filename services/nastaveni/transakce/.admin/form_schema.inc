<?php
UNSET($GLOBALS[ODBOR]);

 if (!HasRole('access_all')) $GLOBALS['ID_SUPERODBOR'] = EedTools::VratSuperOdbor();

  $FORM_CONFIG["schema"][] = array("elements"=>array(
    array(
      "type"=>"select_superodbor",
      "name"=>"omez_zarizeni",
      "insertnull"=>true,
      "frozen" => !HasRole('access_all')
   ),
  ),
    "visible" => ($GLOBALS['CONFIG']['USE_SUPERODBOR'] ? true : false),
    "label"=>$GLOBALS["CONFIG"]["NAZEV_SUPERODBOR"].":");



      $FORM_CONFIG["schema"][] = array( "elements"=>array(
                  array( "type"=>"select_typ_transakcniho_protokolu", "name"=>"TYP",'insertnull'=>true),
                   ),
                  "label"=>"Typ");
                   

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
                  array( "type"=>"text_number", "name"=>"ROK","size"=>8,"label"=>"Rok"),
                  array( "type"=>"text", "name"=>"ZNACKA","label"=>"Značka ČJ","size"=>"30"),
//                  array( "type"=>"text", "name"=>"NAZEV_SPISU","label"=>"Název:"),
//                  array( "type"=>"checkbox", "name"=>"SEZNAM_SPISU","label"=>"Jen seznam"),
                   ),
                  "format"=>"CISLO_SPISU1...'/'...CISLO_SPISU2...'&nbsp;-&nbsp;'...NAZEV_SPISU...'&nbsp;&nbsp;jen seznam:&nbsp;'...SEZNAM_SPISU",
                  "label"=>"Číslo jednací");

      $FORM_CONFIG["schema"][] = array( "elements"=>array(
                  array( "type"=>"text", "name"=>"JMENO","size"=>70,'add_star'=>true),
//                  array( "type"=>"text", "name"=>"NAZEV_SPISU","label"=>"Název:"),
//                  array( "type"=>"checkbox", "name"=>"SEZNAM_SPISU","label"=>"Jen seznam"),
                   ),
                  "label"=>"Kdo");

      $FORM_CONFIG["schema"][] = array( "elements"=>array(
                  array( "type"=>"text", "name"=>"TEXT","size"=>70,'add_star'=>true),
//                  array( "type"=>"text", "name"=>"NAZEV_SPISU","label"=>"Název:"),
//                  array( "type"=>"checkbox", "name"=>"SEZNAM_SPISU","label"=>"Jen seznam"),
                   ),
                  "label"=>"Text");
                   
   $FORM_CONFIG["schema"][] = array("elements"=>array(
              array( "type"=>"date_db", "name"=>"LAST_TIME_od","insertdatebutton"=>true, "insertcalendar"=>true,"label"=>"Datum od"),
              array( "type"=>"date_db", "name"=>"LAST_TIME_do","insertdatebutton"=>true, "insertcalendar"=>true,"label"=>"Datum do"),
              ),
              "format"=>"DATUM_OD...'&nbsp;do&nbsp;'...DATUM_DO...'&nbsp;&nbsp;&nbsp;Způsob&nbsp;podání:&nbsp;'...ZPUSOB_PODANI",
              "visible"=>$is_filter,
              "label"=>"Datum od:");

foreach($FORM_CONFIG["schema"] as $key => $val) {
    $FORM_CONFIG["schema"][$key]['theme_config'] = array('square' => array('format' => ''));

}
