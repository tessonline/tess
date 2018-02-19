<?php
include_once(FileUp2(".admin/agenda_func.inc"));
require_once(FileUp2(".admin/security_obj.inc"));


$USER_INFO = $GLOBALS["POSTA_SECURITY"]->GetUserInfo(); 
$REFERENT = $USER_INFO["ID"]; 

$url = "/".GetAgendaPath('POSTA')."/";

$PROPERTIES["MENU2L"]["brow"] = array("Přehled", "brow.php?posta2=f");

//pro vedouci a spravce ukazeme volbu pro Me pisemnosti, ostatnim to vypnem
//if (HasRole("spravce") || HasRole("podatelna") || HasRole("podatelna-odbor") || HasRole("vedouci-odbor") || HasRole("vedouci-odd"))
  $PROPERTIES["MENU2L"]["filter"] = array("Mé dokumenty", $url."brow.php?referent=$REFERENT&posta2=f");
//else
//  $PROPERTIES["MENU2L"]["filter"] = false;

//$PROPERTIES["MENU2L"]["filter"] = array("RV", "javascript:NewWindow('edit.php?filter&cacheid=');");


$PROPERTIES["MENU2L"]["filterall"] = array("Výběr", "edit.php?filterall");


if (HasRole("spravce") || HasRole("podatelna") || HasRole("podatelna-odbor"))
  $PROPERTIES["MENU2L"]["new"] = array("Vlož příchozí", "javascript:NewWindow('".$url."edit.php?insert&cacheid=');");
else
  $PROPERTIES["MENU2L"]["new"] = false;


if (HasRole("spravce") || HasRole("podatelna"))
  $PROPERTIES["MENU1P"]["new2"] = array("DS", "/".GetAgendaPath('POSTA_DS')."/index.php?frame");


$PROPERTIES["MENU2L"]["new2"] = array("Vlož odchozí", "javascript:NewWindow('".$url."edit.php?insert&odeslana=t&cacheid=');");


If ($GLOBALS["CONFIG"]["VNITRNI_POSTA"])
 $PROPERTIES["MENU2L"]["new3"] = array("Vlož vnitřní", "javascript:NewWindow('".$url."edit.php?insert&odeslana=t&vnitrni=t&cacheid=');");


If (!(HasRole('spravce') || HasRole('podatelna')))
  $PROPERTIES["MENU2P"]["cis"] = false;
//else
  $PROPERTIES["MENU1P"]["new"] = array("Nastavení", $url."services/nastaveni/menu.php","main");


$PROPERTIES["MENU2P"]["help"] = array("Nápověda", $url."doc/dokumentace_EED.pdf", "_blank");

?>


