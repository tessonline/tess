<?php
//$GLOBALS["PROPERTIES_DEBUG"]["SHOW_SQL"] = true;
include_once(FileUp2(".admin/db/db_posta.inc"));
include_once(FileUp2(".admin/db/db_default.inc"));

$PROPERTIES = array(
  "AGENDA_NAME" => "Historie",
  "AGENDA_TABLE" => "posta_stare_zaznamy",
  "AGENDA_ID" => "ID",
  "AGENDA_IDENT" => "STARA_POSTA",
  "DB_NAME" => "db_posta",
  "DEFAULT_LANG"=>"cz_utf-8",

  "INSERT_REFRESH"=>true,
  "BROW_SELECT" =>"
    select *
    from posta_stare_zaznamy
  ",
//    where spis_vyrizen is not null

//  "BROW_FIELD_PREFIX" => "p.",
//  "BROW_ORDER_BY"=>"odesl_prijmeni",

  //"BROW_GROUP_BY"=>"",

  "EDIT_LEFT"=>20,
  "EDIT_TOP"=>20,
  "EDIT_HEIGHT"=>400,
  "EDIT_WIDTH"=>500,

  "DELETE_HEIGHT" => 300,
  "DELETE_WIDTH" => 600,
  "DELETE_LEFT" => 50,
  "DELETE_TOP" => 50
);
$PROPERTIES["MAIN_WINDOW"] = "edit.php?filterall";
