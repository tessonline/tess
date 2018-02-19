<?php
include_once(FileUp2(".config/settings/agenda_path.inc"));
include_once(FileUp2(".admin/db/db_default.inc"));

//$GLOBALS["PROPERTIES_DEBUG"]["SHOW_SQL"] = true;
//$GLOBALS["PROPERTIES_DEBUG"]["SHOW_DEBUG"] = true;
include_once(FileUp2(".admin/db/db_posta.inc"));

$PROPERTIES = array(
  "AGENDA_NAME" => "Spisový přehled",
  "AGENDA_TABLE" => "posta_spisprehled_zaznamy",
  "AGENDA_ID" => "ID",
  "AGENDA_IDENT" => "POSTA_SPISPREHLED_ZAZNAMY",
  "DEFAULT_LANG"=>"cz_utf-8",

  "DB_NAME"=>"db_posta",

  "BROW_PAGE_SIZE" => 100,
    
  "HISTORY_SHOW"=>false,

  "BROW_SELECT" => "
    SELECT psz.*
    FROM posta_spisprehled_zaznamy psz
  ", 
  "BROW_FIELD_PREFIX" => "psz.",
  "BROW_ORDER_BY"=>"datum_podatelna_prijeti desc",

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

//$PROPERTIES["MAIN_WINDOW"] = "edit.php?filter";

?>
