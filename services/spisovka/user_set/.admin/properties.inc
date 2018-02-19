<?php
include_once(FileUp2(".admin/config.inc"));


$PROPERTIES = array(
  "AGENDA_NAME" => "Vlastní nastavení",
  "AGENDA_TABLE" => "POSTA",
  "AGENDA_ID" => "ID",
  "AGENDA_IDENT" => "POSTA_USER_SETTINGS",
  "DEFAULT_LANG"=>"cz_utf-8",
  "ACCESS_IDENT" => "POSTA",

  "DB_NAME"=>"db_posta",

  "BROW_PAGE_SIZE" => 100,
    
  "HISTORY_SHOW"=>false,

  //po insertu se refreshne okno main
  "INSERT_REFRESH" => true,

  "EDIT_WIDTH" => 790,
  "EDIT_HEIGHT" => 420,
  "EDIT_LEFT" => 10,
  "EDIT_TOP" => 50,

  "DELETE_WIDTH" => 700,
  "DELETE_HEIGHT" => 250,
  "DELETE_LEFT" => 50,
  "DELETE_TOP" => 50,

);

