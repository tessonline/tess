<?php
include_once(FileUp2(".admin/db/db_posta.inc"));

$PROPERTIES = array(
  "AGENDA_NAME" => "Součásti typového spisu",
  "AGENDA_TABLE" => "cis_posta_spisy",
  "AGENDA_ID" => "ID",
  "AGENDA_IDENT" => "POSTA_TYP_SPIS_SOUCASTIADILY",
  "DB_NAME" => "db_posta",
  "DEFAULT_LANG"=>"cz_utf-8",

  "BROW_ORDER_BY" => "ID ASC",
 
  "INSERT_REFRESH"=>true,
  "DELETE_REFRESH"=>true,

  "EDIT_LEFT"=>20,
  "EDIT_TOP"=>20,
  "EDIT_HEIGHT"=>300,
  "EDIT_WIDTH"=>750,

  "DELETE_HEIGHT" => 300,
  "DELETE_WIDTH" => 750,
  "DELETE_LEFT" => 50,
  "DELETE_TOP" => 50
);
