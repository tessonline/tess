<?php
//$GLOBALS["PROPERTIES_DEBUG"]["SHOW_SQL"] = true;
include_once(FileUp2(".admin/db/db_posta.inc"));
include_once(FileUp2(".admin/db/db_default.inc"));

$PROPERTIES = array(
  "AGENDA_NAME" => "Archivační boxy",
  "AGENDA_TABLE" => "POSTA_SPISOVNA_BOXY_IDS",
  "AGENDA_ID" => "ID",
  "AGENDA_IDENT" => "POSTA_SPISOVNA_BOXY_VLOZENI",
  "DB_NAME" => "db_posta",
  "DEFAULT_LANG"=>"cz_utf-8",

  "ACCESS_IDENT" => "POSTA",

  //"DELETE_SELECT"=>"SELECT i.* FROM POSTA_SPISOVNA_BOXY_IDS i",

  "INSERT_REFRESH"=>true,

  "EDIT_LEFT"=>20,
  "EDIT_TOP"=>20,
  "EDIT_HEIGHT"=>200,
  "EDIT_WIDTH"=>750,

  "DELETE_HEIGHT" => 300,
  "DELETE_WIDTH" => 600,
  "DELETE_LEFT" => 50,
  "DELETE_TOP" => 50
);
?>
