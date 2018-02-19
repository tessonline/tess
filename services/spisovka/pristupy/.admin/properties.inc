<?php
include_once(FileUp2(".config/settings/agenda_path.inc"));
include_once(FileUp2("posta/.admin/properties.inc"));
include_once(FileUp2(".admin/db/db_default.inc"));

//$GLOBALS["PROPERTIES_DEBUG"]["SHOW_SQL"] = true;
//$GLOBALS["PROPERTIES_DEBUG"]["SHOW_DEBUG"] = true;
include_once(FileUp2(".admin/db/db_posta.inc"));

$PROPERTIES = array(
  "AGENDA_NAME" => "Oprávnění",
  "AGENDA_TABLE" => "POSTA_PRISTUPY",
  "AGENDA_ID" => "ID",
  "AGENDA_IDENT" => "POSTA_PRISTUPY",
  "DEFAULT_LANG"=>"cz_utf-8",

  "DB_NAME"=>"db_posta",

  "BROW_PAGE_SIZE" => 100,
  
//  "BROW_SELECT"=>"SELECT DISTINCT ON (access, odbor, referent) * FROM   posta_pristupy ";
//  "BROW_FIELD_PREFIX" => "p.",
  
  "BROW_ORDER_BY"=>"spis",
  
  //"BROW_GROUP_BY"=>"id,access, odbor, referent",
    
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

