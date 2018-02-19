<?php
include_once(FileUp2(".admin/db/db_default.inc"));
include_once(FileUp2(".admin/db/db_posta.inc"));
$PROPERTIES = array(
  "AGENDA_NAME" => "Vážení na XERTECu",
  "AGENDA_TABLE" => "posta",
  "AGENDA_IDENT" => "XERTEX",

  "INSERT_REFRESH" => true,
  "DEFAULT_LANG"=>"cz_utf-8",
  "DB_NAME" => "db_posta",

  "BROW_SELECT" => "SELECT p.* from posta p",
  "BROW_FIELD_PREFIX" => "p.",
  "BROW_ORDER_BY"=>"EV_CISLO DESC",

  "GUIDE_WIDTH" => 700,
  "GUIDE_HEIGHT" => 550,
  "GUIDE_LEFT" => 10,
  "GUIDE_TOP" => 30,

  "DELETE_LEFT"=>20,
  "DELETE_TOP"=>20,
  "DELETE_HEIGHT"=>250,
  "DELETE_WIDTH"=>600,

  "EDIT_LEFT"=>20,
  "EDIT_TOP"=>20,
  "EDIT_HEIGHT"=>500,
  "EDIT_WIDTH"=>590,

//  "EDIT_BUTTONS_UP"=>true


);

?>
