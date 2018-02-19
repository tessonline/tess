<?php
require_once(FileUp2(".admin/config.inc"));
Include_once(FileUp2(".admin/form_func.inc"));
Include_once(FileUp2(".admin/table_funkce.inc"));
Include_once(FileUp2(".admin/security_name.inc"));

/*seznam moznych formatu vystupu s nastavenim*/
$EXPORT_CONFIG['format'] = array(
  'csv'    => array('label'=>'Excel (CSV)'),
  'tabbed' => array('label'=>'Excel (Tabbed)' ),
  'xml'    => array('label'=>'XML'),
  'xhtml'  => array(
    'label'=>'XHTML',
    'css' => FileUpURL('xhtml.css'),
    'title'=>'Elektronická evidence dokumentů - tisk',
    'header'=>"''",
    'footer'=>"'<div>Tisk dne ".Date('d.m.Y H:m')."</div>'",
    'default'=>true,
  ),
  
);

/*
If ($GLOBALS["CONFIG"]["UPLOAD_NAS"])
  Include_once(FileUp2(".admin/table_func_upload.inc"));

If ($GLOBALS["CONFIG"]["UPLOAD_ELO"])
  Include_once(FileUp2(".admin/table_func_upload_elo.inc"));
 */

//$EXPORT_CONFIG["schema"][]= array( field=>"Ukaz(ODESLANA_POSTA)", width=>"1%", label=>"","class"=>$GLOBALS["barva_sipky"]);


If ($GLOBALS["CONFIG"]["SHOW_TABLE_EV_CISLO"])
  $EXPORT_CONFIG["schema"][]= array( field=>"ID", label=>"Č.&nbsp;podací", width=>"4%","order_by"=>"p.EV_CISLO");
		
If ($GLOBALS["CONFIG"]["SHOW_TABLE_C_JEDNACI"])
  $EXPORT_CONFIG["schema"][]= array( field=>"FormatCJednaci(ID)", "label"=>$GLOBALS["CONFIG"]["JEDNACI_CISLO"], "order_by"=>"cislo_jednaci2,cislo_jednaci1", width=>"4%","add"=>"NOWRAP align=center");

$EXPORT_CONFIG["schema"][]= array( field=>"FormatSpis(ID)", "label"=>$GLOBALS["CONFIG"]["CISLO_SPISU"], "order_by"=>"cislo_spisu2,cislo_spisu1,podcislo_spisu", width=>"4%","add"=>"WRAP");
$EXPORT_CONFIG["schema"][]= array( field=>"DatumPrijeti(DATUM_PODATELNA_PRIJETI)...'&nbsp;'", label=>"Datum", "order_by"=>"datum_podatelna_prijeti", width=>"4%");
$EXPORT_CONFIG["schema"][]= array( field=>"UkazJmeno()", label=>"Odesílatel/Adresát","order_by"=>"odes_typ", width=>"35%");
$EXPORT_CONFIG["schema"][]= array( field=>"VEC", label=>"Věc", "order_by"=>"vec", width=>"30%");

If ($GLOBALS["CONFIG"]["UKAZOVAT_ZKRATKU_ODBORU"])
  $EXPORT_CONFIG["schema"][]= array( field=>"UkazOdbor(ODBOR,'true')", label=>"Odbor","add"=>"align=center", "order_by"=>"odbor", width=>"4%");
else  
  $EXPORT_CONFIG["schema"][]= array( field=>"UkazOdbor(ODBOR)", label=>"Odbor","add"=>"align=center", "order_by"=>"odbor", width=>"4%");

$EXPORT_CONFIG["schema"][]= array( field=>"'&nbsp;'...UkazUsera(REFERENT)", label=>"Zpracovatel","add"=>"align=center", "order_by"=>"referent", width=>"10%","add"=>"NOWRAP align=center");
