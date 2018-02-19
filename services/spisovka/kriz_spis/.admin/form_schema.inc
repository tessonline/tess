<?php
//echo $GLOBALS["spis1"]."a".$spis2;
include_once(FileUp2(".admin/config.inc"));

if ($GLOBALS['PUVODNI_SPIS']) {
  $puv = LoadClass('EedCj', $GLOBALS['PUVODNI_SPIS']);
  $puv_cj = $puv->cislo_jednaci_zaklad;
}
if ($GLOBALS['NOVY_SPIS']) {
  $nov = LoadClass('EedCj', $GLOBALS['NOVY_SPIS']);
  $nov_cj = $nov->cislo_jednaci_zaklad;
}

if ($GLOBALS['smer']==1)
{
  $FORM_CONFIG["schema"][] = array("elements"=>array(
              array( "type"=>"hidden", "name"=>"NOVY_SPIS","value"=>$cislo_spisu),
              ));
  /*
$FORM_CONFIG["schema"][] = array( 
  "elements"=>array(
      "type"=>"hidden", 
      "name"=>"NEM_ID",
    ),
  "format"=>"'<span id=\"OBJEKT_KOD_SPAN\" style=\"font-weight:bold;\">".$cislo_spisu."</span><input class=\"button\" type=\"button\" value=\"$text\" onclick=\"".
            "window.open('".GetAgendaPath('POSTA',false,true)."/guide.php?G_NAME=posta_krizspisy&IDP=".$GLOBALS["ID"]."', 'guide', 'height=600px,width=600px,scrollbars,resizable');\">$url'",
  "label"=>"Původní ".$CONFIG["CISLO_SPISU"]
);
*/

}
else
{

  $FORM_CONFIG["schema"][] = array("elements"=>array(
              array( "type"=>"text", "name"=>"PUVODNI_SPIS","frozen"=>true,"value"=>$puv_cj),
              array( "type"=>"text", "name"=>"NOVY_SPIS","frozen"=>true,"value"=>$nov_cj,"label"=>'a'),
              ),
              "label"=>"Vazba mezi ",
              );


/*
$FORM_CONFIG["schema"][] = array( 
  "elements"=>array(
      "type"=>"hidden", 
      "name"=>"NEM_ID",
    ),
  "format"=>"'<span id=\"OBJEKT_KOD_SPAN\" style=\"font-weight:bold;\">".$cislo_spisu."</span><input class=\"button\" type=\"button\" value=\"$text\" onclick=\"".
            "window.open('".GetAgendaPath('POSTA',false,true)."/guide.php?G_NAME=posta_dalsispisy&IDP=".$GLOBALS["ID"]."', 'guide', 'height=600px,width=600px,scrollbars,resizable');\">$url'",
  "label"=>"Nové ".$CONFIG["CISLO_SPISU"]
);



  $FORM_CONFIG["schema"][] = array("elements"=>array(
              array( "type"=>"hidden", "name"=>"NOVY_SPIS","value"=>$cislo_spisu),
              ));
*/
}
//include(FileUp2(".admin/el/urednik_id_zmena_dat_cas.inc"));

