<?php
include_once(FileUp2(".config/settings/agenda_path.inc"));
include_once(FileUp2(".admin/db/db_default.inc"));
include_once(FileUp2(".admin/db/db_monumnis.inc"));

//$GLOBALS["PROPERTIES_DEBUG"]["SHOW_SQL"] = true;
//$GLOBALS["PROPERTIES_DEBUG"]["SHOW_DEBUG"] = true;
include_once(FileUp2(".admin/db/db_posta.inc"));

$PROPERTIES = array(
  "AGENDA_NAME" => "Ukládací značka ",
  "AGENDA_TABLE" => "POSTA_UKLZNACKA",
  "AGENDA_ID" => "ID",
  "AGENDA_IDENT" => "POSTA_UKLZNACKA",
  "DEFAULT_LANG"=>"cz_iso",

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
  
//  "ACCESS_BY_BROW_SELECT"=>true
);

