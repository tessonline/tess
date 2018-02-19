<?php
Access();
$htp = $HTTPS?"https://":"http://";
//$PROPERTIES["MENU1P"]["agenda"]=array("", $htp.$GLOBALS["HTTP_HOST"]."/".$SERVER_CONFIG["AGENDA_PATH"][$AGENDA_ID]."/"."index.php?frame");

$PROPERTIES["MENU2L"]["filterall"] = array(
  "Vložení ze souboru",
  "javascript:NewWindow('edit.php?insert&app=csv');",
  'icon' => InsertImage('images/file-add', '', '', array('img_sizes'=>false)),
);

if (HasRole('spisovna') || HasRole('spisovna-odbor') || HasRole('access_all')) {

}
else {
//  $PROPERTIES["MENU2L"]["new"] = false;
}

$PROPERTIES["MENU2P"]["cis"] = false;

include(FileUp2('.admin/prop_menu_theme.inc'));