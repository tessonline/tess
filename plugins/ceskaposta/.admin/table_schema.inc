<?php

  
//return $stav;
//$TABLE_CONFIG["callback"]="ChangeClassBarva";

//Die($CONFIG["CISLO_SPISU"]);
//$TABLE_CONFIG["schema"][]= array( field=>"Ukaz(ODESLANA_POSTA)", width=>"1%", label=>"","class"=>$GLOBALS["barva_sipky"]);

if ($GLOBALS['CONFIG']['USE_SUPERODBOR']) {
  $GLOBALS['of_superodbor_prefix'] = getSelectDataEed(new of_select_superodbor_prefix(array()));
  $TABLE_CONFIG["schema"][]= array( field=>"ShowProtokolSuperodbor(SUPERODBOR,PROTOKOL,ROK)", label=>"Číslo protokolu", width=>"10%","add"=>"align=center");
}
else
  $TABLE_CONFIG["schema"][]= array( field=>"'<b>'...PROTOKOL...'&nbsp;/&nbsp;'...ROK...'</b>'", label=>"Číslo protokolu", width=>"10%","add"=>"align=center");
$TABLE_CONFIG["schema"][]= array( field=>"DATUM_OD", label=>"Datum od", width=>"10%","add"=>"align=center");
$TABLE_CONFIG["schema"][]= array( field=>"DATUM_DO", label=>"Datum do", width=>"10%","add"=>"align=center");

$TABLE_CONFIG['schema'][] = array(
  field => 'UkazOdbor(ODBOR, true)',
  label => 'Spis. uzel',
  width => '4%',
  );


if ($GLOBALS['CONFIG_POSTA']['PLUGINS']['deniky']['enabled']) {
  $GLOBALS['of_select_deniky'] = getSelectDataEed(new of_select_deniky(array('short'=>true)));

  $TABLE_CONFIG['schema'][] = array(
    field => 'TableDeniky(MAIN_DOC)',
    label => 'Deník',
    width => '4%',
    );

}
$TABLE_CONFIG["schema"][]= array( field=>"UkazTlacitka('1')", label=>"Načíst", width=>"20%","add"=>"align=center");
$TABLE_CONFIG['schema'][] = array(
  field => 'PocetDoc(ID)',
  label => 'Počet',
  width => '4%',
  );

$TABLE_CONFIG["schema"][]= array( field=>"UkazTlacitka('2')", label=>"Tisky", width=>"20%","add"=>"align=center");

$TABLE_CONFIG["schema"][]= array( field=>"UkazTlacitka('3')", label=>"Uzavření", width=>"20%","add"=>"align=center");

$TABLE_CONFIG["schema"][]= array( field=>"Epa(ID)", label=>"ePa", width=>"5%","add"=>"align=center");

//$TABLE_CONFIG["schema"][]= array( field=>"Precteno(ID,REFERENT)", "label"=>"", "add"=>"align=center");
//$TABLE_CONFIG["schema"][]= array( field=>"UkazOdpoved(ID)", "label"=>"", "add"=>"align=center", width=>"1%");



$TABLE_CONFIG['syscolumns'] = array(
 'edit' => array ('theme'=>array('dropdown'=>true, 'column'=>true)),
 'delete' => array ('theme'=>array('dropdown'=>true, 'column'=>true))
);


?>
