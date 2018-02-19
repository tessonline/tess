<?php
include_once(FileUp2('.admin/config.inc'));

$PROPERTIES = array(
  "AGENDA_NAME" => "Statistika evidence dokumentů",
  "AGENDA_TABLE" => "POSTA_STATISTIKA",
  "AGENDA_ID" => "ID",
  "AGENDA_IDENT" => "POSTA_STATISTIKA",
  "DB_NAME" => "db_posta",
  "DEFAULT_LANG"=>"cz_utf-8",

  "EDIT_LEFT"=>20,
  "EDIT_TOP"=>20,
  "EDIT_HEIGHT"=>200,
  "EDIT_WIDTH"=>750,

  "DELETE_HEIGHT" => 300,
  "DELETE_WIDTH" => 600,
  "DELETE_LEFT" => 50,
  "DELETE_TOP" => 50,
  
//  "DATA_TYPE" => "ARRAY",
//  "DATA_ARRAY_NAME" => "POSTA_STATISTIKA_DATA"

);
$PROPERTIES["MAIN_WINDOW"] = "edit.php?filter";
