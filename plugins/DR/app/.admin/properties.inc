<?php
include_once(FileUp2(".admin/db/db_posta.inc"));

$PROPERTIES = array(
  "AGENDA_NAME" => "Datový rozcestník",
  "AGENDA_TABLE" => "POSTA_PLUGINS_DR_APP",
  "AGENDA_ID" => "ID",
  "AGENDA_IDENT" => "POSTA_PLUGINS_DR_APP",
  "DEFAULT_LANG"=>"cz_utf-8",

  "DB_NAME"=>"db_posta",

  "BROW_PAGE_SIZE" => 100,
    
  "HISTORY_SHOW"=>false,
  "SECURITY_REGISTRATION" => true,


  //po insertu se refreshne okno main
  "INSERT_REFRESH" => true,

  "EDIT_WIDTH" => 790,
  "EDIT_HEIGHT" => 420,
  "EDIT_LEFT" => 10,
  "EDIT_TOP" => 50,

  "DELETE_WIDTH" => 700,
  "DELETE_HEIGHT" => 250,
  "DELETE_LEFT" => 50,
  "DELETE_TOP" => 50

  
  
//  "ACCESS_BY_BROW_SELECT"=>true
);

