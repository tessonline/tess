<?php
//$GLOBALS["PROPERTIES_DEBUG"]["SHOW_SQL"] = true;
include_once(FileUp2(".admin/db/db_posta.inc"));
include_once(FileUp2(".admin/db/db_default.inc"));

$PROPERTIES = array(
  "AGENDA_NAME" => "Agendy",
  "AGENDA_TABLE" => "CIS_POSTA_AGENDA",
  "AGENDA_ID" => "ID",
  "AGENDA_IDENT" => "CIS_POSTA_AGENDA",
  "DB_NAME" => "db_posta",
  "DEFAULT_LANG"=>"cz_utf-8",

  "ACCESS_IDENT" => "POSTA_CISELNIKY",
  
 
  "BROW_ORDER_BY"=>"PORADI",

  "INSERT_REFRESH"=>true,

  "EDIT_LEFT"=>20,
  "EDIT_TOP"=>20,
  "EDIT_HEIGHT"=>600,
  "EDIT_WIDTH"=>900,

  "DELETE_HEIGHT" => 300,
  "DELETE_WIDTH" => 600,
  "DELETE_LEFT" => 50,
  "DELETE_TOP" => 50
);

