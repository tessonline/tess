<?php
if (!$_SERVER['HTTPS'] == 'on') Die();


$PROPERTIES["MENU2L"]["filter"] = false;
  $PROPERTIES["MENU2L"]["filterall"] = false;
  $PROPERTIES["MENU2L"]["new"] = false;


/*
$PROPERTIES["MENU1P"]["DSbrow"] = array("Zobrazit příchozí zprávy", "/".GetAgendaPath('POSTA_DS')."/prichozi.php");
//$PROPERTIES["MENU1P"]["DSfilter"] = array("Zobrazit odchozí zprávy", "javascript:NewWindow('edit.php?insert&cacheid=');");
$PROPERTIES["MENU1P"]["DSfilter"] = array("Zobrazit odchozí zprávy", "/".GetAgendaPath('POSTA_DS')."/edit.php?insert&cacheid=");
$PROPERTIES["MENU1P"]["DSfilterall"] = array("Načíst doručenky", "/".GetAgendaPath('POSTA_DS')."/dorucenky.php");
//$PROPERTIES["MENU1P"]["DSnew"] = array("Protokol příchozích DZ", "javascript:NewWindow('edit.php?insert&smer=prichozi&cacheid=');");
//$PROPERTIES["MENU1P"]["DSnew2"] = array("Protokol odchozích DZ", "javascript:NewWindow('edit.php?insert&smer=odchozi&cacheid=');");
$PROPERTIES["MENU1P"]["DSnew"] = array("Protokol příchozích DZ", "/".GetAgendaPath('POSTA_DS')."/edit.php?insert&smer=prichozi&cacheid=");
$PROPERTIES["MENU1P"]["DSnew2"] = array("Protokol odchozích DZ", "/".GetAgendaPath('POSTA_DS')."/edit.php?insert&smer=odchozi&cacheid=");
$PROPERTIES["MENU1P"]["DSnew3"] = array("Historie dat.schránky", "/".GetAgendaPath('POSTA_DS')."/historieDS.php");
*/
$PROPERTIES["MENU1P"]["DSag_all"] = array("log", "/ost/posta/services/nastaveni/logy/brow.php?SW=RADAR");

 
include(FileUp2('posta/.admin/prop_menu_theme.inc'));