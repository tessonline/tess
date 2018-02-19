<?php
  $FORM_CONFIG["schema"][] = array("elements"=>array(
            array( "type"=>"select_stitek", "name"=>"STITEK"),
            array( "type"=>"hidden", "name"=>"ID","value"=>$GLOBALS["ID"]),
 
            ),
            "label"=>"Štítek:");							
            
  $FORM_CONFIG["schema"][] = array("elements"=>array(
            array( "type"=>"text_number", "name"=>"POZICE","size"=>4),
            ),
            "label"=>"Pozice:");							
            
  if (!HasRole('soravce')) $GLOBALS['SUPERODBOR'] = EedTools::VratSuperOdbor();

  $FORM_CONFIG["schema"][] = array("elements"=>array(
    array(
      "type"=>"select_superodbor",
      "name"=>"SUPERODBOR",
      "insertnull"=>true,
      "frozen" => !HasRole('spravce')
    ),
  ),
    "visible" => ($GLOBALS['CONFIG']['USE_SUPERODBOR'] ? true : false),
    "label"=>$GLOBALS["CONFIG"]["NAZEV_SUPERODBOR"].":");



  $FORM_CONFIG["schema"][] = array("elements"=>array(
            array( "type"=>"select_odbor", "name"=>"ODBOR","insertnull"=>true),
            ),
            "visible"=>!$GLOBALS["ID"],
            "label"=>"Spisový uzel:");
            
 $FORM_CONFIG["schema"][] = array("elements"=>array(
            array( "type"=>"date_db", "name"=>"DATUM_OD","insertdatebutton"=>true,"required"=>true,"label"=>"Datum od:"),
            array( "type"=>"date_db", "name"=>"DATUM_DO","insertdatebutton"=>true,"required"=>true,"label"=>"Datum do:")
            ),   
            "format"=>"DATUM_OD...'&nbsp;do&nbsp;'...DATUM_DO",
            "visible"=>!$GLOBALS["ID"],
            "label"=>"Datum od:",
              // zruseni format pro tema square
            'theme_config' => array(
              'square' => array(
                'format' => '',
              )
            ));


 $FORM_CONFIG["schema"][] = array("elements"=>array(
            array( "type"=>"text_number", "name"=>"EV_CISLO_OD","size"=>8,"label"=>"Ev.číslo od:"),
            array( "type"=>"text_number", "name"=>"EV_CISLO_DO","size"=>8,"label"=>"Ev.číslo do:",'tooltip' => 'Ev. čísla se používají pro předtištěné archy pro skenování.')
            ),   
            "format"=>"EV_CISLO_OD...'&nbsp;do&nbsp;'...EV_CISLO_DO",
            "visible"=>!$GLOBALS["ID"],
            "label"=>"Ev.číslo od:",
              // zruseni format pro tema square
            'theme_config' => array(
              'square' => array(
                'format' => '',
              )
            ));
/*
 $FORM_CONFIG["schema"][] = array("elements"=>array(
            array( "type"=>"text_number", "name"=>"CISLO_JEDNACI1_OD","size"=>8),   
            array( "type"=>"text_number", "name"=>"CISLO_JEDNACI1_DO","size"=>8)),   
            "format"=>"CISLO_JEDNACI1_OD...'&nbsp;do&nbsp;'...CISLO_JEDNACI1_DO",
            "visible"=>!$GLOBALS["ID"],
            "label"=>"Číslo jednací od:",
              // zruseni format pro tema square
            'theme_config' => array(
              'square' => array(
                'format' => '',
              )
            ));
*/
 $FORM_CONFIG["schema"][] = array("elements"=>array(
            array( "type"=>"checkbox", "name"=>"CELE","size"=>8,"values"=>1,"add"=>($GLOBALS['CONFIG']['STAMP_CELE']?"CHECKED":""))),
            "visible"=>($GLOBALS["ODESLANA"]=='f' || !$GLOBALS["ID"]),
            "label"=>"Celé razítko?:");		


$FORM_CONFIG["schema"][] = array("elements"=>array(
            array( "type"=>"checkbox", "name"=>"PRAC_KOPIE","size"=>8,"values"=>1)),
            "visible"=>($GLOBALS["ODESLANA"]=='f' || !$GLOBALS["ID"]),
            "label"=>"Pracovní kopie");


 $FORM_CONFIG["schema"][] = array("elements"=>array(
            array( "type"=>"checkbox", "name"=>"POMLCKA","size"=>8,"values"=>1)),
            "visible"=>($GLOBALS["ODESLANA"]=='f' || !$GLOBALS["ID"]),
            "label"=>"Generovat pomlčku u ev.čísla:");

