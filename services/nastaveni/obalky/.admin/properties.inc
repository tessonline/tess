<?php
//$GLOBALS["PROPERTIES_DEBUG"]["SHOW_SQL"] = true;
include_once(FileUp2(".admin/db/db_posta.inc"));

$PROPERTIES = array(
  "AGENDA_NAME" => "Nastavení obálek",
  "AGENDA_TABLE" => "POSTA_CIS_OBALKY",
  "AGENDA_ID" => "ID",
  "AGENDA_IDENT" => "POSTA_OBALKY",
  "DB_NAME" => "db_posta",
  "DEFAULT_LANG"=>"cz_utf-8",

  "ACCESS_IDENT" => "POSTA_CISELNIKY",

 "BROW_SELECT"=>"SELECT a.* FROM posta_cis_obalky a",
 "BROW_FIELD"=>"a.",
 "BROW_ORDER_BY"=>"a.poradi asc, a.id",

  "INSERT_REFRESH"=>true,

  "EDIT_LEFT"=>20,
  "EDIT_TOP"=>20,
  "EDIT_HEIGHT"=>300,
  "EDIT_WIDTH"=>500,

  "DELETE_HEIGHT" => 300,
  "DELETE_WIDTH" => 600,
  "DELETE_LEFT" => 50,
  "DELETE_TOP" => 50
);
?>
