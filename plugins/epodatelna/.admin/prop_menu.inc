<?php
if (!$_SERVER['HTTPS'] == 'on') Die();

$PROPERTIES["MENU2L"]["brow"] = false;

$PROPERTIES["MENU2L"]["filter"] = false;
$PROPERTIES["MENU2L"]["filterall"] = false;
$PROPERTIES["MENU2L"]["new"] = false;

$PROPERTIES['MENU2L']['ePodbrow'] = array('Zobrazit příchozí emaily', 'prichozi.php');
$PROPERTIES['MENU2L']['ePodfilter'] = array('Zobrazit odchozí emaily', 'odchozi.php');
$PROPERTIES['MENU2L']['ePodnew'] = array('Nastavení ePodatelny', '../../services/nastaveni/konfigurace/index.php?frame&KATEGORIE=EPODATELNA','nastaveni');
$PROPERTIES['MENU2L']['ePodcis'] = array('test ePodatelny', 'stav.php');

include(FileUp2('posta/.admin/prop_menu_theme.inc'));