<?php
include_once(FileUp2(".admin/oth_funkce_2D.inc"));

$htp = $HTTPS?"https://":"http://";
//$PROPERTIES["MENU1P"]["agenda"]=array("", $htp.$GLOBALS["HTTP_HOST"]."/".$SERVER_CONFIG["AGENDA_PATH"][$AGENDA_ID]."/"."index.php?frame");

$PROPERTIES["MENU2L"]["filterall"] = array("Skartační kniha", "../skartacni_kniha/index.php", "_top");

//if (!HasRole('spisovna')) $PROPERTIES["MENU2L"]["new"] = false;

$PROPERTIES["MENU2P"]["cis"] = false;

include(FileUp2('.admin/prop_menu_theme.inc'));