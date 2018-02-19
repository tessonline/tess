<?php
include_once(FileUp2(".config/settings/agenda_path.inc"));
include_once(FileUp2(".admin/db/db_default.inc"));
include_once(FileUp2(".admin/db/db_posta.inc"));

//$GLOBALS["PROPERTIES_DEBUG"]["SHOW_SQL"] = true;
//$GLOBALS["PROPERTIES_DEBUG"]["SHOW_DEBUG"] = true;
include_once(FileUp2(".admin/db/db_posta.inc"));

$PROPERTIES = array(
  "AGENDA_NAME" => "Oběh spisu",
//  "AGENDA_TABLE" => "POSTA_SPIS",
  "AGENDA_TABLE" => "posta_spisobal",
  "AGENDA_ID" => "POSTA_ID",
  "AGENDA_IDENT" => "POSTA_OBEH",
  "DEFAULT_LANG"=>"cz_utf-8",

  "DB_NAME"=>"DB_POSTA",

  "BROW_PAGE_SIZE" => 100,
    
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

