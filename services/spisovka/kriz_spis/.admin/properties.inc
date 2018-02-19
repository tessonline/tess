<?php
//$GLOBALS["PROPERTIES_DEBUG"]["SHOW_SQL"] = true;
include_once(FileUp2(".admin/db/db_posta.inc"));
include_once(FileUp2(".admin/db/db_default.inc"));
$PROPERTIES = array(
  "AGENDA_NAME" => "Křížová vazba",
  "AGENDA_TABLE" => "POSTA_KRIZOVY_SPIS",
  "AGENDA_ID" => "ID",
  "AGENDA_IDENT" => "POSTA_KRIZOVY_SPIS",
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
