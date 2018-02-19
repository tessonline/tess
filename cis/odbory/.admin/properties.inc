<?php
//$GLOBALS["PROPERTIES_DEBUG"]["SHOW_SQL"] = true;
include_once(FileUp2(".admin/db/db_posta.inc"));
include_once(FileUp2(".admin/db/db_default.inc"));

$PROPERTIES = array(
  "AGENDA_NAME" => "Spisové uzly",
  "AGENDA_TABLE" => "CIS_POSTA_ODBORY",
  "AGENDA_ID" => "ID",
  "AGENDA_IDENT" => "CIS_POSTA_ODBORY",
  "DB_NAME" => "db_posta",
  "DEFAULT_LANG"=>"cz_utf-8",

  "ACCESS_IDENT" => "POSTA_CISELNIKY",

  "BROW_SELECT" => "SELECT p.*,g.name from cis_posta_odbory p LEFT JOIN  security_group g ON p.id_odbor=g.id", 
  "BROW_FIELD_PREFIX" => "p.",
 // "BROW_ORDER_BY"=>"KOD DESC",
 
  "BROW_ORDER_BY"=>"p.ID",

  "MAIN_WINDOW"=>"strom.php",

  "INSERT_REFRESH"=>true,

  "EDIT_LEFT"=>20,
  "EDIT_TOP"=>20,
  "EDIT_HEIGHT"=>600,
  "EDIT_WIDTH"=>800,

  "DELETE_HEIGHT" => 300,
  "DELETE_WIDTH" => 600,
  "DELETE_LEFT" => 50,
  "DELETE_TOP" => 50
);
