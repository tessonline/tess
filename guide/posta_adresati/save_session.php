<?php
require("tmapy_config.inc");
include(FileUp2(".admin/brow_.inc"));
include_once(FileUp2(".admin/oth_funkce.inc"));
include(FileUp2(".admin/config.inc"));
session_start();

//setcookie("TWIST_POSTA_VybranaObalka",$GLOBALS[OBALKA],time()+86400*300, "/"); //30 dnu
//$nazev='TWIST_POSTA_ADRESATI_'.$typ;
//$_SESSION[$nazev][$ID]=$hodnota;

//echo "Hodnota je".$hodnota_set;
//If ($GLOBALS["CONFIG"]["POUZIVAT_COOKIES"]) 
setcookie("TWIST_POSTA_ADRESATI_".$typ."_".$ID,$hodnota_set,time()+86400*300, "/"); //30 dnu


