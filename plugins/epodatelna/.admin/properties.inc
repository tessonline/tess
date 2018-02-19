<?php
//$GLOBALS["PROPERTIES_DEBUG"]["SHOW_SQL"] = true;
include_once(FileUp2(".admin/db/db_posta.inc"));

$PROPERTIES = array(
  "AGENDA_NAME" => "ePodatelna",
  "AGENDA_TABLE" => "POSTA_EPODATELNA",
  "AGENDA_ID" => "ID",
  "AGENDA_IDENT" => "POSTA_EPODATELNA",
  "DB_NAME" => "db_posta",
  "DEFAULT_LANG"=>"cz_utf-8",

//  "DATA_TYPE" => "ARRAY",
//  "DATA_ARRAY_NAME" => "EMAIL_DATA",
 
  "ACCESS_IDENT" => "POSTA_EPODATELNA",
//  "SECURITY_REGISTRATION" => true,
 

  "EDIT_LEFT"=>20,
  "EDIT_TOP"=>20,
  "EDIT_HEIGHT"=>800,
  "EDIT_WIDTH"=>1024,

  "DELETE_HEIGHT" => 300,
  "DELETE_WIDTH" => 600,
  "DELETE_LEFT" => 50,
  "DELETE_TOP" => 50,

  "UPLOAD_DIRS" => array(
     "odbor"=>array("min_dir_cif"=>6),
  ),

  //"MAIN_WINDOW"=>"prichozi.php",
);

$PROPERTIES["ACCESS_IDENT"] = 'POSTA_EPODATELNA';

if (strpos($_SERVER['SCRIPT_NAME'], 'odeslat.php')) {
  $PROPERTIES["ACCESS_IDENT"] = 'POSTA';
}

UNSET($GLOBALS['SERVER_CONFIG']['UPLOAD_CONFIG']['MODULES']['table']['ONLY_FILE_TYPES']);