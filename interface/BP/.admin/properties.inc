<?php
//$GLOBALS["PROPERTIES_DEBUG"]["SHOW_SQL"] = true;
include_once(FileUp2(".admin/db/db_posta.inc"));

$PROPERTIES = array(
  "AGENDA_NAME" => "UNISPIS modul",
  "AGENDA_TABLE" => "POSTA_INTERFACE_BP",
  "AGENDA_ID" => "ID",
  "AGENDA_IDENT" => "POSTA_INTERFACE_BP",
  "DB_NAME" => "db_posta",
  "DEFAULT_LANG"=>"cz_utf-8",

//  "DATA_TYPE" => "ARRAY",
//  "DATA_ARRAY_NAME" => "DS_DATA",

  "EDIT_LEFT"=>20,
  "EDIT_TOP"=>20,
  "EDIT_HEIGHT"=>200,
  "EDIT_WIDTH"=>750,

  "DELETE_HEIGHT" => 300,
  "DELETE_WIDTH" => 600,
  "DELETE_LEFT" => 50,
  "DELETE_TOP" => 50,

  "UPLOAD_DIRS" => array(
        "ID"=>array("min_dir_cif"=>6),
  ),

//  "MAIN_WINDOW"=>"prichozi.php",
);

$PROPERTIES["ACCESS_IDENT"] = 'POSTA_EPODATELNA';
