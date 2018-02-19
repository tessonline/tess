<?php
include_once(FileUp2(".admin/db/db_posta.inc"));

$PROPERTIES = array(
  "AGENDA_NAME" => "Modul Best-Practices rozhraní",
  "AGENDA_TABLE" => "POSTA_INTERFACE_BP_APP",
  "AGENDA_ID" => "ID",
  "AGENDA_IDENT" => "POSTA_INTERFACE_BP_APP",
  "DEFAULT_LANG"=>"cz_utf-8",

  "DB_NAME"=>"db_posta",

  "BROW_PAGE_SIZE" => 100,
    
  "HISTORY_SHOW"=>false,
  "SECURITY_REGISTRATION" => false,
  "ACCESS_IDENT" => "POSTA_INTERFACE_BP",

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
