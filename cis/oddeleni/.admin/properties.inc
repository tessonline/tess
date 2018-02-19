<?php
//$GLOBALS["PROPERTIES_DEBUG"]["SHOW_SQL"] = true;
include_once(FileUp2(".admin/db/db_posta.inc"));
include_once(FileUp2(".admin/db/db_default.inc"));

$PROPERTIES = array(
  "AGENDA_NAME" => "Oddělení v odborech",
  "AGENDA_TABLE" => "CIS_POSTA_ODDELENI",
  "AGENDA_ID" => "ID",
  "AGENDA_IDENT" => "CIS_POSTA_ODDELENI",
  "DB_NAME" => "db_posta",
  "DEFAULT_LANG"=>"cz_utf-8",

 "BROW_SELECT"=>"SELECT a.*,b.zkratka FROM cis_posta_oddeleni a LEFT JOIN cis_posta_odbory b ON a.odbor=b.id",
 "BROW_FIELD"=>"a.",
 "BROW_ORDER_BY"=>"a.ODDELENI",

  "INSERT_REFRESH"=>true,

  "EDIT_LEFT"=>20,
  "EDIT_TOP"=>20,
  "EDIT_HEIGHT"=>200,
  "EDIT_WIDTH"=>750,

  "DELETE_HEIGHT" => 300,
  "DELETE_WIDTH" => 600,
  "DELETE_LEFT" => 50,
  "DELETE_TOP" => 50
);
?>
