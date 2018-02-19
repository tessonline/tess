<?php
//$GLOBALS["PROPERTIES_DEBUG"]["SHOW_SQL"] = true;
include_once(FileUp2(".admin/db/db_posta.inc"));

$PROPERTIES = array(
  "AGENDA_NAME" => "Workflow",
  "AGENDA_TABLE" => "POSTA_WORKFLOW",
  "AGENDA_ID" => "ID",
  "AGENDA_IDENT" => "POSTA_WORKFLOW",
  "DB_NAME" => "db_posta",
  "DEFAULT_LANG"=>"cz_utf-8",

  "EDIT_LEFT"=>20,
  "EDIT_TOP"=>20,
  "EDIT_HEIGHT"=>300,
  "EDIT_WIDTH"=>500,

  "DELETE_HEIGHT" => 200,
  "DELETE_WIDTH" => 500,
  "DELETE_LEFT" => 50,
  "DELETE_TOP" => 50,

  "UPLOAD_DIRS" => array(
     "ID"=>array(),
  ),
  'UPLOAD_CONFIG' => array(
    'USE_ANONYM_ACCESS' => true,
  ),
);

$PROPERTIES["ACCESS_IDENT"] = 'POSTA';
// UNSET($GLOBALS['SERVER_CONFIG']['UPLOAD_CONFIG']['MODULES']['table']['ONLY_FILE_TYPES']);

