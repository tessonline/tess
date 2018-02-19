<?php

If ($GLOBALS["kniha"]==1)

{
  $FORM_CONFIG["schema"][] = array("elements"=>array(
            array( "type"=>"select_rok_rocnikniha", "name"=>"ROK","insertnull"=>true,"required"=>true,"add"=>"onChange=\"ShowTime(this)\""),
            ),
            "label"=>"Zadejte rok:");

  $FORM_CONFIG["schema"][] = array("elements"=>array(
            array( "type"=>"select_mesic", "name"=>"MESIC","insertnull"=>true,"required"=>false,"add"=>"onChange=\"ShowTime(this)\""),
            ),
            "label"=>"Zadejte měsíc:");

  $FORM_CONFIG["schema"][] = array("elements"=>array(
            array( "type"=>"hidden", "name"=>"KNIHA","value"=>1),
            ),
            "label"=>"");							

}
else
{

If (!(HasRole('podatelna') || HasRole('spravce'))) $GLOBALS['ODBOR'] = VratOdbor();
{  
  UNSET($GLOBALS['referent']);
$FORM_CONFIG["schema"][] = array("elements"=>array(
            array( "type"=>"select_vsechny_spisuzly", "name"=>"ODBOR","insertnull"=>true),
//            array( "type"=>"hidden", "name"=>"SUPERODBOR","value"=>VratSuperOdbor()),
            ),
            "label"=>"Spisový uzel:");
 }
 $FORM_CONFIG["schema"][] = array("elements"=>array(
            array( "type"=>"datetime_db", "name"=>"DATUM_OD","insertdatebutton"=>true,"required"=>true,'label'=>'Datum od'),
            array( "type"=>"datetime_db", "name"=>"DATUM_DO","insertdatebutton"=>true,"required"=>true,'label'=>'Datum do')),
            "format"=>"DATUM_OD...'&nbsp;do&nbsp;'...DATUM_DO",
            "label"=>"Datum od:",
              // zruseni format pro tema square
            'theme_config' => array(
              'square' => array(
                'format' => '',
              )
            )
      );



// If ($GLOBALS[smer]=='prichozi')
/*
 $FORM_CONFIG["schema"][] = array("elements"=>array(
            array( "type"=>"text_number", "name"=>"EV_CISLO_OD","size"=>8,'label'=>'podací číslo od'),
            array( "type"=>"text_number", "name"=>"EV_CISLO_DO","size"=>8,'label'=>'podací číslo do')),
            "format"=>"EV_CISLO_OD...'&nbsp;do&nbsp;'...EV_CISLO_DO",
            "label"=>"podací číslo od:",
           // zruseni format pro tema square
            'theme_config' => array(
              'square' => array(
                'format' => '',
              )
            )
      );

*/

 $FORM_CONFIG["schema"][] = array("elements"=>array(
            array( "type"=>"text_number", "name"=>"CISLO_JEDNACI1_OD","size"=>8,'label'=>'Číslo jednací od'),
            array( "type"=>"text_number", "name"=>"CISLO_JEDNACI1_DO","size"=>8,'label'=>'Číslo jednací do')),
            "format"=>"CISLO_JEDNACI1_OD...'&nbsp;do&nbsp;'...CISLO_JEDNACI1_DO",
            "label"=>"Číslo jednací od:",
              // zruseni format pro tema square
            'theme_config' => array(
              'square' => array(
                'format' => '',
              )
            )
      );



 $FORM_CONFIG["schema"][] = array("elements"=>array(
            array( "type"=>"hidden", "name"=>"SMER","value"=>$GLOBALS["smer"]),   
            array( "type"=>"hidden", "name"=>"REFERENT","value"=>$GLOBALS["referent"]),   
            array( "type"=>"hidden", "name"=>"PODATELNA_ID","value"=>$GLOBALS["podatelna_id"])),   
            "label"=>"");		

}
reset ($GLOBALS["CONFIG_POSTA"]["PLUGINS"]);
foreach($GLOBALS["CONFIG_POSTA"]["PLUGINS"] as $plug_name => $plug) {
  if ($plug['enabled']){
    $file = FileUp2('plugins/'.$plug['dir'].'/services/spisovka/protokoly/.admin/form_schema_end.inc');
		if (File_Exists($file)) include($file);
  }
}
