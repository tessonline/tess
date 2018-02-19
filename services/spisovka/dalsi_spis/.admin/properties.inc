<?php
include_once(FileUp2(".admin/db/db_posta.inc"));
include_once(FileUp2(".admin/db/db_default.inc"));
$PROPERTIES = array(
  "AGENDA_NAME" => "Práce se spisem",
  "AGENDA_TABLE" => "CIS_POSTA_SPISY",
  "AGENDA_ID" => "ID",
  "AGENDA_IDENT" => "POSTA_PRIDANI_SPISU",
  "DB_NAME" => "db_posta",
  "DEFAULT_LANG"=>"cz_utf-8",

 
  "INSERT_REFRESH"=>true,
  "DELETE_REFRESH"=>true,

  "EDIT_LEFT"=>20,
  "EDIT_TOP"=>20,
  "EDIT_HEIGHT"=>300,
  "EDIT_WIDTH"=>750,

  "DELETE_HEIGHT" => 300,
  "DELETE_WIDTH" => 750,
  "DELETE_LEFT" => 50,
  "DELETE_TOP" => 50
);
