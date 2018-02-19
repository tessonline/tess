<?php
include_once(FileUp2(".admin/agenda_func.inc"));
require_once(FileUp2(".admin/security_obj.inc"));


$USER_INFO = $GLOBALS["POSTA_SECURITY"]->GetUserInfo(); 
$REFERENT = $USER_INFO["ID"]; 

$url = "/".GetAgendaPath('POSTA')."/";

if (substr( $url, 0, 3 ) === "/./") $url = substr($url, 1);

$PROPERTIES["MENU2L"]["brow"] = array("Přehled", "brow.php?posta2=f");

/*
$PROPERTIES["MENU2L"]["filter"] = false;

if (HasRole("spravce") || HasRole("podatelna") || HasRole("podatelna-odbor") || HasRole("vedouci-odbor")) {
  $PROPERTIES["MENU2L"]["filter"] = array(
   '0' => "Mé dokumenty",
   '1' => "".$url."brow.php?REFERENT=".$REFERENT."&cacheid=",
   'icon' => InsertImage('images/person', '', '', array('img_sizes'=>false)),
  );
}
*/

//$PROPERTIES["MENU2L"]["filter"] = array("RV", "javascript:NewWindow('edit.php?filter&cacheid=');");


$PROPERTIES["MENU2P"]["help"] = array(
  '0' => "Výběr",
  '1' => "edit.php?filter",
  'icon' => InsertImage('images/filter', '', '', array('img_sizes'=>false)),
);

if (HasRole("cteni_uzel") || HasRole("cteni_vse_pracoviste") || HasRole("cteni_admin")) {
  $PROPERTIES["MENU2L"]["filter"] = array(
   '0' => "Mé dokumenty",
   '1' => "".$url."brow.php?REFERENT=".$REFERENT."&cacheid=",
   'icon' => InsertImage('images/person', '', '', array('img_sizes'=>false)),
  );
}
else
  $PROPERTIES["MENU2L"]["filter"] = false;


if (HasRole("vloz_prichozi")) {
  $PROPERTIES["MENU2L"]["filterall"] = array(
   '0' => "Vlož příchozí",
   '1' => "javascript:NewWindow('".$url."edit.php?insert&cacheid=');",
   '2' => '_self',
   'icon' => InsertImage('images/forward', '', '', array('img_sizes'=>false)),
  );

}
else {
  $PROPERTIES["MENU2L"]["filterall"] = false;
}

if (HasRole("vloz_odchozi")) {
	$PROPERTIES["MENU2L"]["new"] = array(
	 '0' => "Vlož odchozí",
	 '1' => "javascript:NewWindow('".$url."edit.php?insert&odeslana=t&cacheid=');",
	 'icon' => InsertImage('images/add', '', '', array('img_sizes'=>false)),
	);
}
else {
	$PROPERTIES["MENU2L"]["new"] = false;
}

//}
/*
else {
  $PROPERTIES["MENU2L"]["new"] = array(
   '0' => "Vlož odchozí",
   '1' => "javascript:NewWindow('".$url."edit.php?insert&odeslana=t&cacheid=');",
   'icon' => InsertImage('images/add', '', '', array('img_sizes'=>false)),
  );

}
*/
//  $PROPERTIES["MENU2L"]["new"] = false;

//$PROPERTIES["MENU2L"]["new2"] = array("Vlož odchozí", "javascript:NewWindow('".$url."edit.php?insert&odeslana=t&cacheid=');");




If ($GLOBALS["CONFIG"]["VNITRNI_POSTA"])
 $PROPERTIES["MENU2L"]["new3"] = array("Vlož vnitřní", "javascript:NewWindowAgenda('".$url."edit.php?insert&odeslana=t&vnitrni=t&cacheid=');");


reset ($GLOBALS["CONFIG_POSTA"]["PLUGINS"]);
foreach($GLOBALS["CONFIG_POSTA"]["PLUGINS"] as $plug_name => $plug) {
  if ($plug['enabled']){
    $file = FileUp2('plugins/'.$plug['dir'].'/.admin/prop_menu_end.inc');
		if (File_Exists($file)) include($file);
  }
}

include(FileUp2('.admin/prop_menu_theme.inc'));