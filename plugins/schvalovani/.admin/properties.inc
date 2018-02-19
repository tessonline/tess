<?php
include_once(FileUp2(".admin/db/db_posta.inc"));
include_once(FileUp2(".admin/schvalovani.inc"));
include_once(FileUp2(".admin/db/db_default.inc"));

//$GLOBALS["PROPERTIES_DEBUG"]["SHOW_SQL"] = true; 

$PROPERTIES = array(
  "AGENDA_NAME" => "Schvalovací proces",
  "AGENDA_TABLE" => "posta_schvalovani",
  "AGENDA_IDENT" => "POSTA_SCHVALOVANI",
  "AGENDA_ID" => "ID",
  "DEFAULT_LANG"=>"cz_utf-8",
  "DB_NAME"=>"DB_POSTA",
  "INSERT_REFRESH" => true,

  "SECURITY_REGISTRATION" => false,

  "ACCESS_IDENT" => "POSTA",

  "GUIDE_WIDTH" => 700,
  "GUIDE_HEIGHT" => 550,
  "GUIDE_LEFT" => 10,
  "GUIDE_TOP" => 30,
 
  "BROW_ORDER_BY"=>"ID",

  "DELETE_LEFT"=>20,
  "DELETE_TOP"=>20,
  "DELETE_HEIGHT"=>250,
  "DELETE_WIDTH"=>600,

  "EDIT_LEFT"=>20,
  "EDIT_TOP"=>20,
  "EDIT_HEIGHT"=>450,
  "EDIT_WIDTH"=>300,

//  "EDIT_BUTTONS_UP"=>true


);


?>
