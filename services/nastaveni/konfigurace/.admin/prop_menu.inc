<?php
if (!$_SERVER['HTTPS'] == 'on') Die();
include_once(FileUp2(".admin/agenda_func.inc"));
require_once(FileUp2(".admin/security_obj.inc"));
require_once(FileUp2(".admin/config.inc"));
require_once(FileUp2(".admin/access_.inc"));

include_once(FileUp2(".admin/agenda_func.inc"));
require_once(FileUp2(".admin/security_obj.inc"));


$USER_INFO = $GLOBALS["TMAPY_SECURITY"]->GetUserInfo(); 
$REFERENT = $USER_INFO["ID"]; 

$htp = $HTTPS?"https://":"http://";
$PROPERTIES["MENU1P"]["agenda"]=array("Zpět k agendě", $htp.$GLOBALS["HTTP_HOST"]."/".$SERVER_CONFIG["AGENDA_PATH"][$AGENDA_ID]."/"."index.php?frame");

if (HasRole('spravce') || HasRole('lokalni-spravce')) 
//if (HasRole('spravce'))
  $PROPERTIES["MENU2L"]["brow"] = array("Nastavení DB hodnot", "settings.php","main");
else
  $PROPERTIES["MENU2L"]["brow"] = false;

$PROPERTIES["MENU2L"]["filter"] = false;
$PROPERTIES["MENU2L"]["filterall"] = false;

if ($USER_INFO["LOGIN"]=='onma')
{
  $PROPERTIES["MENU2L"]["new2"] = array("Export", "export2.php");
  $PROPERTIES["MENU2L"]["new3"] = array("Import", "import.php");
}
else
  $PROPERTIES["MENU2L"]["new"] = false;

$PROPERTIES["MENU2P"]["cis"] = false;

include(FileUp2('posta/.admin/prop_menu_theme.inc'));