<?php
require_once(FileUp2(".admin/config.inc"));
Include_once(FileUp2(".admin/form_func.inc"));
Include_once(FileUp2(".admin/table_funkce.inc"));
Include_once(FileUp2(".admin/oth_funkce.inc"));
Include_once(FileUp2(".admin/security_name.inc"));

If ($GLOBALS["CONFIG"]["UPLOAD_NAS"])
  Include_once(FileUp2(".admin/table_func_upload.inc"));

If ($GLOBALS["CONFIG"]["UPLOAD_ELO"])
  Include_once(FileUp2(".admin/table_func_upload_elo.inc"));
 
$TABLE_CONFIG["callback"]="ChangeClassBarva";

$TABLE_CONFIG["schema"][]= array( field=>"Ukaz(ODESLANA_POSTA)", width=>"1%", label=>"","class"=>$GLOBALS["barva_sipky"]);

If ($GLOBALS["CONFIG"]["SHOW_TABLE_EV_CISLO"])
  $TABLE_CONFIG["schema"][]= array( field=>"'<i><font size=1>'...VratCarovyKod(ID)...'</font></i>'", label=>"ID", width=>"4%","order_by"=>"p.EV_CISLO");
//  $TABLE_CONFIG["schema"][]= array( field=>"'<i><font size=1>'...VratPodaciCislo(ID)...'</font></i>'", label=>"Č.&nbsp;podací", width=>"4%","order_by"=>"p.EV_CISLO");

If ($GLOBALS["CONFIG"]["SHOW_TABLE_C_JEDNACI"])
  $TABLE_CONFIG["schema"][]= array( field=>"FormatCJednaci(ID)", "label"=>$GLOBALS["CONFIG"]["JEDNACI_CISLO"], "order_by"=>"cislo_jednaci2 asc,cislo_jednaci1 asc", width=>"4%","add"=>"NOWRAP align=center");

$TABLE_CONFIG["schema"][]= array( field=>"FormatSpis(ID)", "label"=>$GLOBALS["CONFIG"]["CISLO_SPISU"], "order_by"=>"cislo_spisu2 asc,cislo_spisu1 asc,podcislo_spisu asc", width=>"4%","add"=>"NOWRAP");

If ($GLOBALS[CONFIG][DB]=='psql')
  $TABLE_CONFIG["schema"][]= array( field=>"DatumPrijeti(DATUM_PODATELNA_PRIJETI)...'&nbsp;'", label=>"Datum", "order_by"=>"(DATUM_PODATELNA_PRIJETI,\'FMDD.FMMM.YYYY\')  asc ", width=>"4%");
If ($GLOBALS[CONFIG][DB]=='mssql')
  $TABLE_CONFIG["schema"][]= array( field=>"DatumPrijeti(DATUM_PODATELNA_PRIJETI)...'&nbsp;'", label=>"Datum", "order_by"=>"CONVERT(datetime,datum_podatelna_prijeti,104) asc ", width=>"4%");

$TABLE_CONFIG["schema"][]= array( field=>"Ukaz2(ODES_TYP,ZPUSOB_PODANI,VLASTNICH_RUKOU)...'&nbsp;'...UkazJmeno()", label=>"Odesílatel/Adresát","order_by"=>"odesl_prijmeni asc, odesl_jmeno asc", width=>"35%");
$TABLE_CONFIG["schema"][]= array( field=>"FormatujVec(VEC)", label=>"Věc", "order_by"=>"vec", width=>"30%");

If ($GLOBALS["CONFIG"]["UKAZOVAT_ZKRATKU_ODBORU"])
//  $TABLE_CONFIG["schema"][]= array( field=>"UkazOdbor(ODBOR,'true')", label=>$GLOBALS['CONFIG']['NAZEV_TABLE_ODBOR'],"add"=>"align=center", "order_by"=>"odbor", width=>"4%");
  $TABLE_CONFIG["schema"][]= array( field=>"UkazOdbor(ODBOR,'true')", label=>$GLOBALS['CONFIG']['NAZEV_TABLE_ODBOR'],"add"=>"align=center", "order_by"=>"odbor", width=>"4%");
else  
//  $TABLE_CONFIG["schema"][]= array( field=>"UkazOdbor(ODBOR)", label=>$GLOBALS['CONFIG']['NAZEV_TABLE_ODBOR'],"add"=>"align=center", "order_by"=>"odbor", width=>"4%");
  $TABLE_CONFIG["schema"][]= array( field=>"UkazOdbor(ODBOR)", label=>$GLOBALS['CONFIG']['NAZEV_TABLE_ODBOR'],"add"=>"align=center", "order_by"=>"odbor", width=>"4%");

If ($GLOBALS["CONFIG"]["ODDELENI"])
//  $TABLE_CONFIG["schema"][]= array( field=>"UkazOdbor(ODDELENI,'true')", label=>"Oddělení","add"=>"align=center", "order_by"=>"oddeleni", width=>"4%");
  $TABLE_CONFIG["schema"][]= array( field=>"UkazOdbor(ODDELENI,'true')", label=>$GLOBALS['CONFIG']['NAZEV_TABLE_ODBOR'],"add"=>"align=center", "order_by"=>"oddeleni", width=>"4%");

$TABLE_CONFIG["schema"][]= array( field=>"'&nbsp;'...UkazZpracovatele(REFERENT)", label=>$GLOBALS["CONFIG"]["NAZEV_TABLE_REFERENT"],"add"=>"align=left", "order_by"=>"referent", width=>"10%","add"=>"NOWRAP");





?>
<iframe id="ifrm_get_value" name="ifrm_get_value" style="position:absolute;z-index:0;left:0;top:0;visibility:hidden" src="cis.php"></iframe>
