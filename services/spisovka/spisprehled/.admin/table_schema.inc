<?php
require_once(FileUp2(".admin/table_funkce_denik.inc"));
require_once(FileUp2(".admin/security_obj.inc"));

$TABLE_CONFIG["schema"][] = array( field=>"DatumPrijeti(DATUM_PODATELNA_PRIJETI)", label=>"Datum", add=>"align=\"center\"", "order_by"=>"DATUM_PODATELNA_PRIJETI");
$TABLE_CONFIG["schema"][] = array( field=>"Ukaz2(ODES_TYP,ZPUSOB_PODANI,VLASTNICH_RUKOU)...'&nbsp;'...UkazJmeno()", label=>"Odesílatel/Adresát","order_by"=>"odes_typ", width=>"35%");

$TABLE_CONFIG["schema"][] = array( field=>"VEC", label=>"Věc", add=>"align=\"left\"", "order_by"=>"VEC");
//$TABLE_CONFIG["schema"][] = array( field=>"POCET_LISTU", label=>"Listů", add=>"align=\"left\"", "order_by"=>"POCET_LISTU");
//$TABLE_CONFIG["schema"][] = array( field=>"POCET_PRILOH", label=>"Příloh", add=>"align=\"left\"", "order_by"=>"POCET_PRILOH");
//$TABLE_CONFIG["schema"][] = array( field=>"DRUH_PRILOH", label=>"Druh příloh", add=>"align=\"left\"", "order_by"=>"DRUH_PRILOH");

$TABLE_CONFIG["schema"][]= array( field=>"UkazOdbor(ODBOR,1)", label=>"Odbor","add"=>"align=center", "order_by"=>"odbor", width=>"4%");
$TABLE_CONFIG["schema"][] = array( field=>"UkazUsera(REFERENT)", label=>$GLOBALS["CONFIG"]["NAZEV_TABLE_REFERENT"], add=>"align=\"left\"", "order_by"=>"REFERENT_JM");

$TABLE_CONFIG['syscolumns'] = array(
 'upload' => array ('theme'=>array('dropdown'=>true, 'column'=>true)),
 'edit' => array ('theme'=>array('dropdown'=>true, 'column'=>true))
);

