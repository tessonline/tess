<?php
include_once(FileUp2(".admin/db/db_posta.inc"));

$PROPERTIES = array(
  "AGENDA_NAME" => "Nastavení vlastních filtrů",
//  "AGENDA_TABLE" => "POSTA_SPIS",
  "AGENDA_TABLE" => "posta_user_filtry",
  "AGENDA_ID" => "ID",
  "AGENDA_IDENT" => "POSTA_USER_FILTRY",
  "DEFAULT_LANG"=>"cz_utf-8",

  "BROW_PAGE_SIZE" => 100,
  "ACCESS_UPDATE_OWNER_ID" => "OWNER_ID",
//  "HISTORY_SHOW"=>false,

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

