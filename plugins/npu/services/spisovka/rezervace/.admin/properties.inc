<?php
include_once(FileUp2(".admin/db/db_posta.inc"));
include_once(FileUp2(".admin/db/db_default.inc"));

//$GLOBALS["PROPERTIES_DEBUG"]["SHOW_SQL"] = true; 

$PROPERTIES = array(
  "AGENDA_NAME" => "Rezervace jednacích čísel",
  "AGENDA_TABLE" => "posta",
  "AGENDA_IDENT" => "POSTA_REZERVACE",
  "AGENDA_ID" => "ID",
  "DEFAULT_LANG"=>"cz_iso",
  "DB_NAME"=>"DB_POSTA",
  "INSERT_REFRESH" => true,

  "BROW_SELECT" => "SELECT p.* from posta p",
  "BROW_FIELD_PREFIX" => "p.",
//  "BROW_ORDER_BY"=>"ID DESC, ROK DESC, EV_CISLO DESC",
  "BROW_ORDER_BY"=>"ID ASC",

  "DELETE_LEFT"=>20,
  "DELETE_TOP"=>20,
  "DELETE_HEIGHT"=>250,
  "DELETE_WIDTH"=>600,

  "EDIT_LEFT"=>20,
  "EDIT_TOP"=>20,
  "EDIT_HEIGHT"=>450,
  "EDIT_WIDTH"=>300,

//  "EDIT_BUTTONS_UP"=>true


);


?>
