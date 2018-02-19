<?php

Include_once(FileUp2(".admin/form_func.inc"));
Include_once(FileUp2(".admin/table_funkce.inc"));
Include_once(FileUp2(".admin/table_funkce_denik.inc"));
Include_once(FileUp2(".admin/security_name.inc"));
include_once(FileUp2(".admin/config.inc"));

  
//return $stav;
//Die($CONFIG["CISLO_SPISU"]);
$TABLE_CONFIG["schema"][]= array( field=>"Ukaz(ODESLANA_POSTA)", width=>"1%", label=>"","class"=>$GLOBALS["barva_sipky"]);

$TABLE_CONFIG['schema'][] = array(
//    field => "'<i><font size = 1>'...tableBarcode(ID)...'</font></i>'",
  field => "tableBarcode(ID)",
  label => 'JID',
  width => '4%',
  order_by => 'ID',
  ident => 'CK',
  settings => 'default'
);


$TABLE_CONFIG['schema'][] = array(
  field => 'tableFormatCJednaci(ID, 1)',
  label => $GLOBALS['CONFIG']['CISLO_SPISU'] .', evidenční, spis',
  order_by => 'cislo_spisu2 asc, cislo_spisu1 asc, main_doc asc',
  width => '4%',
  add => 'NOWRAP',
  ident => 'SIS',
  settings => 'default'
);


// $TABLE_CONFIG["schema"][]= array( field=>"FormatCJednaci(ID)", "label"=>$GLOBALS["CONFIG"]["JEDNACI_CISLO"],  width=>"4%","add"=>"NOWRAP align=center");

$TABLE_CONFIG["schema"][]= array( field=>"DatumPrijeti(DATUM_PODATELNA_PRIJETI)...'&nbsp;'", label=>"Datum", width=>"4%");
$TABLE_CONFIG["schema"][]= array( field=>"Ukaz2(ODES_TYP,ZPUSOB_PODANI,VLASTNICH_RUKOU)...'&nbsp;'...UkazJmeno()", label=>"Odesílatel/Adresát", width=>"35%");
$TABLE_CONFIG["schema"][]= array( field=>"VEC", label=>"Věc", width=>"30%");
$TABLE_CONFIG["schema"][]= array( field=>"UkazOdbor(ODBOR)", label=>"Odbor","add"=>"align=center", width=>"4%");
$TABLE_CONFIG["schema"][]= array( field=>"UkazUsera(REFERENT)", label=>"Referent","add"=>"align=center", width=>"10%","add"=>"NOWRAP align=center");
//$TABLE_CONFIG["schema"][]= array( field=>"Precteno(ID,REFERENT)", "label"=>"", "add"=>"align=center");
//$TABLE_CONFIG["schema"][]= array( field=>"UkazOdpoved(ID)", "label"=>"", "add"=>"align=center", width=>"1%");





?>
