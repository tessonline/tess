<?php

//$htp = $HTTPS?"https://":"http://";
//$PROPERTIES["MENU1P"]["agenda"]=array("Zpět k agendě", $htp.$GLOBALS["HTTP_HOST"]."/".$SERVER_CONFIG["AGENDA_PATH"][$AGENDA_ID]."/"."index.php?frame");

$PROPERTIES["MENU2L"]["filter"] = false;
$PROPERTIES["MENU2L"]["filterall"] = false;

$PROPERTIES["MENU2P"]["cis"] = false;


include(FileUp2('.admin/prop_menu_theme.inc'));