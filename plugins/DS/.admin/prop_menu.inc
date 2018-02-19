<?php
if (!$_SERVER['HTTPS'] == 'on') Die();

  $PROPERTIES["MENU2L"]["brow"] = false;

$PROPERTIES["MENU2L"]["filter"] = false;
  $PROPERTIES["MENU2L"]["filterall"] = false;
  $PROPERTIES["MENU2L"]["new"] = false;



$PROPERTIES["MENU1P"]["DSbrow"] = array("Zobrazit příchozí zprávy", "/".GetAgendaPath('POSTA_DS')."/prichozi.php");
//$PROPERTIES["MENU1P"]["DSfilter"] = array("Zobrazit odchozí zprávy", "javascript:NewWindow('edit.php?insert&cacheid=');");
$PROPERTIES["MENU1P"]["DSfilter"] = array("Zobrazit odchozí zprávy", "/".GetAgendaPath('POSTA_DS')."/edit.php?insert&cacheid=");
$PROPERTIES["MENU1P"]["DSfilterall"] = array("Načíst doručenky", "/".GetAgendaPath('POSTA_DS')."/dorucenky.php");
//$PROPERTIES["MENU1P"]["DSnew"] = array("Protokol příchozích DZ", "javascript:NewWindow('edit.php?insert&smer=prichozi&cacheid=');");
//$PROPERTIES["MENU1P"]["DSnew2"] = array("Protokol odchozích DZ", "javascript:NewWindow('edit.php?insert&smer=odchozi&cacheid=');");
$PROPERTIES["MENU1P"]["DSnew"] = array("Protokol příchozích DZ", "/".GetAgendaPath('POSTA_DS')."/edit.php?insert&smer=prichozi&cacheid=");
$PROPERTIES["MENU1P"]["DSnew2"] = array("Protokol odchozích DZ", "/".GetAgendaPath('POSTA_DS')."/edit.php?insert&smer=odchozi&cacheid=");
$PROPERTIES["MENU1P"]["DSnew3"] = array("Historie dat.schránky", "/".GetAgendaPath('POSTA_DS')."/historieDS.php");

$PROPERTIES["MENU1P"]["DSag_all"] = array("log", "/ost/posta/services/nastaveni/logy/brow.php?SW=DS");


//$PROPERTIES["MENU2P"]["new3"] = array("Uživatel: <b>".TxtEncodingFromSoap($UserInfo['pnFirstName'])." ".TxtEncodingFromSoap($UserInfo['pnLastName'])."</b>,&nbsp;heslo vyprší:&nbsp;<b>".ConvertDatumToString($PasswordInfo)."</b>&nbsp;&nbsp;", "password.php");
if (HasRole('access_all') || HasRole('spravce')) {
  $PROPERTIES["MENU1P"]["filtry_ds"] = array("Filtry DS", '/'.GetAgendaPath('POSTA_DS_FILTRY'),'_top');
  $PROPERTIES["MENU1P"]["new3"] = array("Informace o DS", "password.php");
  $PROPERTIES["MENU1P"]["new4"] = array("Nastavení DS", "/".GetAgendaPath('POSTA_KONFIGURACE')."?frame&KATEGORIE=DS","nastaveni");
}
//$PROPERTIES["MENU1P"]["help"] = array("EED", "/".GetAgendaPath('POSTA').'/index.php?frame');

 
include(FileUp2('posta/.admin/prop_menu_theme.inc'));