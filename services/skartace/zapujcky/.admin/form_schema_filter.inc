<?php
$is_filter_all = true;
     include_once(FileUp2("$path_posta/.admin/javascript.inc"));
  $USER_INFO = $GLOBALS["POSTA_SECURITY"]->GetUserInfo(); 
    $FORM_CONFIG["schema"][] = array( "elements"=>array(
                       array( "type"=>"text", "name"=>"ID"),
                       ),
//                       "visible"=>HasRole('spravce'),
                       "label"=>"ID dokumentu:");

      $FORM_CONFIG["schema"][] = array( "elements"=>array(
                  array( "type"=>"text", "name"=>"CISLO_SPISU1","size"=>8),
                  array( "type"=>"text", "name"=>"CISLO_SPISU2","size"=>8),
                  array( "type"=>"text", "name"=>"NAZEV_SPISU"),
                   ),
                  "format"=>"CISLO_SPISU1...'/'...CISLO_SPISU2...'&nbsp;-&nbsp;'...NAZEV_SPISU",
                  "label"=>$GLOBALS["CONFIG"]["CISLO_SPISU"].":");

  If (!HasRole('zpracovatel'))        
  {
    if ($is_filter_all) UNSET($GLOBALS[ODBOR]);
    $FORM_CONFIG["schema"][] = array("elements"=>array(
              array( "type"=>"select_odbor", "name"=>"ODBOR","insertnull"=>true,"add"=>"id=\"ODBOR\" onChange=\"UkazPracovnika(this,'REFERENT');\" "),
              ),
              "format"=>"'<div id=\"ODBOR\">'...ODBOR...'</div>'",
              "visible"=>$is_filter_all ,
              "label"=>'<b>' . $GLOBALS["CONFIG"]["NAZEV_ODBOR"] . ':</b>');
  }
  

   $FORM_CONFIG["schema"][] = array("elements"=>array(
              array( "type"=>"select_typ_posty", "name"=>"TYP_POSTY", "width"=>10,"insertnull"=>true)),
              "visible"=>$is_filter_all ,										 
              "label"=>"Druh dokumentu:");			

   $FORM_CONFIG["schema"][] = array("elements"=>array(
              array( "type"=>"text", "name"=>"VEC", "width"=>10),
              ),
              "visible"=>$is_filter_all ,										 
              "label"=>"Věc:");										 
  

   $FORM_CONFIG["schema"][] = array("elements"=>array(
              array( "type"=>"date_db", "name"=>"VYTVORENO_od","insertdatebutton"=>true),   
              array( "type"=>"date_db", "name"=>"VYTVORENO_do","insertdatebutton"=>true),
              ),   
              "visible"=>$is_filter_all,										 
              "label"=>"Datum od:");		

   $FORM_CONFIG["schema"][] = array("elements"=>array(
              array( "type"=>"select_referent", "name"=>"PUJCENO_KOMU","insertnull"=>true,"label"=>"Zpracovatel"),   
  ),
              "format"=>"'<span id=REFERENT>'...PUJCENO_KOMU...'</span>'",
              "visible"=>$is_filter_all,										 
              "label"=>"Zpracovatel:");		
  
  
   $FORM_CONFIG["schema"][] = array("elements"=>array(
              array( "type"=>"select_spisovna_zapujcky_filtry", "name"=>"FILTR_ZAPUJCKY","size"=>"1", "insertnull"=>true),   
  ),
              "visible"=>$is_filter_all,										 
              "label"=>"Filtr zápůjček:");		


?>
