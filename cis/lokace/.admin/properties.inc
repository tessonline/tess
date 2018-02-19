<?php
//$GLOBALS["PROPERTIES_DEBUG"]["SHOW_SQL"] = true;
include_once(FileUp2(".admin/db/db_posta.inc"));

$PROPERTIES = array(
  "AGENDA_NAME" => "Lokace ve spisovně",
  "AGENDA_TABLE" => "POSTA_SPISOVNA_CIS_LOKACE",
  "AGENDA_ID" => "ID",
  "AGENDA_IDENT" => "POSTA_SPISOVNA_CIS_LOKACE",
  "DB_NAME" => "db_posta",
  "DEFAULT_LANG"=>"cz_utf-8",

  "ACCESS_IDENT" => "SKARTACNI_KNIHA",

  "BROW_SELECT" => "SELECT * "
                .  "FROM posta_spisovna_cis_lokace ",
                //.  "WHERE id_parent IS NULL",
  "BROW_ORDER_BY"=>"ID ASC",

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