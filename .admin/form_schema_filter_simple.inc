<?php

access();
$zpracovatel = !(HasRole('spravce') || HasRole('podatelna') || HasRole('vedouci-odbor') || HasRole('editace_admin') || HasRole('editace_uzel') || HasRole('editace_vse_pracoviste'));
$vedouci = !(HasRole('spravce') || HasRole('podatelna') || HasRole('editace_admin') || HasRole('editace_vse_pracoviste'));


if ($vedouci) {
  $GLOBALS['ODBOR'] = VratOdbor();
}

if ($zpracovatel) {
  $GLOBALS['ODBOR'] = VratOdbor();
  $USER_INFO = $GLOBALS["POSTA_SECURITY"]->GetUserInfo();
  $GLOBALS['REFERENT'] = $USER_INFO['ID'];
}

//If (!(HasRole('spravce')||HasRole('podatelna')||HasRole('spisovna')||HasRole('podatelna-odbor')) && (HasRole('zpracovatel'))) {

if (strpos($_SERVER['QUERY_STRING'], 'posta_dalsicj') || strpos($_SERVER['QUERY_STRING'], 'posta_spisy')) {
  $GLOBALS["CONFIG"]["CISLO_SPISU"] = 'Číslo spisu';
}

      $FORM_CONFIG["schema"][] = array( "elements"=>array(
                  array( "type"=>"text_number", "name"=>"CISLO_SPISU1","size"=>15, 'label' => 'Pořadové číslo','extrahtml'=>'placeholder="pořadové číslo spisu"'),
                  array( "type"=>"text_number", "name"=>"CISLO_SPISU2","size"=>15, 'label' => 'Rok','extrahtml'=>'placeholder="rok spisu"'),
                  array( "type"=>"text", "name"=>"NAZEV_SPISU", 'label' => 'Název spisu (značka)','extrahtml'=>'placeholder="název spisu nebo název typového spisu"'),
                   ),
                  //"format"=>"CISLO_SPISU1...'/'...CISLO_SPISU2...'&nbsp;-&nbsp;'...NAZEV_SPISU",
                  "label"=>$GLOBALS["CONFIG"]["CISLO_SPISU"].":");
  

    
    $FORM_CONFIG["schema"][] = array("elements"=>array(
              array( "type"=>"select_vsechny_spisuzly", "name"=>"ODBOR","insertnull"=>true,"frozen"=>$vedouci,"add"=>"style=\"width:670px;\""),
              ),
              "label"=>'<b>' . $GLOBALS["CONFIG"]["NAZEV_ODBOR"] . ':</b>',
              // zruseni format pro tema square
            'theme_config' => array(
              'square' => array(
                'format' => '',
              )
            )
      );


      $FORM_CONFIG["schema"][] = array("elements"=>array(
              array( "type"=>"text", "name"=>"VEC", "size"=>90,'extrahtml'=>'placeholder=""'),
              array( "type"=>"hidden", "name"=>"arch"),
              array( "type"=>"hidden", "name"=>"spis"),
              ),
              "label"=>"<b>Věc:</b>");										 
  


    
   $FORM_CONFIG["schema"][] = array("elements"=>array(
              array( "type"=>"date_db", "name"=>"DATUM_OD","insertdatebutton"=>true, 'label' => 'Datum od'),
              array( "type"=>"date_db", "name"=>"DATUM_DO","insertdatebutton"=>true, 'label' => 'Datum do'),
              ),   
              "format"=>"DATUM_OD...'&nbsp;do&nbsp;'...DATUM_DO",
              "label"=>"Datum od:",
              // zruseni format pro tema square
            'theme_config' => array(
              'square' => array(
                'format' => '',
              )
            )
      );


   $FORM_CONFIG["schema"][] = array("elements"=>array(
              array( "type"=>"select_referent", "name"=>"REFERENT","insertnull"=>true,"label"=>'Zpracovatel',
              "jenUser"=>$zpracovatel, "frozen"=>$zpracovatel,"add"=>"style=\"width:670px;\""),
              ),
              "format"=>"'<span id=REFERENT>'...REFERENT...'</span>'",
              "label"=>'<b>' . $GLOBALS["CONFIG"]["NAZEV_REFERENT"] . ':</b>');		


   $FORM_CONFIG["schema"][] = array("elements"=>array(
              array( "type"=>"select_skartace", "name"=>"SKARTACE","size"=>"1", "insertnull"=>true,"add"=>"style=\"width:670px;\""),
  ),
              "label"=>$GLOBALS["CONFIG"]["NAZEV_SKARTACE"].":");		


