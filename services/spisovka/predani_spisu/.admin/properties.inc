<?php
//$GLOBALS["PROPERTIES_DEBUG"]["SHOW_SQL"] = true; 
include_once(FileUp2(".admin/db/db_posta.inc"));
include_once(FileUp2(".admin/config.inc"));

$PROPERTIES = array(
  "AGENDA_NAME" => "Předání ".$CONFIG["CISLO_SPISU_2P"]." jiné osobě či spisovému uzlu",
  "AGENDA_TABLE" => "CIS_POSTA_PREDANI",
  "AGENDA_IDENT" => "CIS_POSTA_PREDANI",
  "DEFAULT_LANG"=>"cz_utf-8",
  "DB_NAME"=>"DB_POSTA",
  "INSERT_REFRESH" => true,

  "ACCESS_IDENT" => "POSTA",

  "GUIDE_WIDTH" => 700,
  "GUIDE_HEIGHT" => 550,
  "GUIDE_LEFT" => 10,
  "GUIDE_TOP" => 30,

  "DELETE_LEFT"=>20,
  "DELETE_TOP"=>20,
  "DELETE_HEIGHT"=>250,
  "DELETE_WIDTH"=>600,

  "EDIT_LEFT"=>20,
  "EDIT_TOP"=>20,
  "EDIT_HEIGHT"=>500,
  "EDIT_WIDTH"=>590,

//  "EDIT_BUTTONS_UP"=>true


);

?>
