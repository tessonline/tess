<?php
include_once(FileUp2(".admin/db/db_posta.inc"));
include_once(FileUp2(".admin/db/db_default.inc"));

//$GLOBALS["PROPERTIES_DEBUG"]["SHOW_SQL"] = true; 

$PROPERTIES = array(
  "AGENDA_NAME" => "Předávací protokoly",
  "AGENDA_TABLE" => "posta_protokoly",
  "AGENDA_IDENT" => "POSTA_PROTOKOLY",
  "AGENDA_ID" => "ID",
  "DEFAULT_LANG"=>"cz_utf-8",
  "DB_NAME"=>"DB_POSTA",
  "INSERT_REFRESH" => true,

  "DELETE_LEFT"=>20,
  "DELETE_TOP"=>20,
  "DELETE_HEIGHT"=>250,
  "DELETE_WIDTH"=>600,

  "EDIT_LEFT"=>20,
  "EDIT_TOP"=>20,
  "EDIT_HEIGHT"=>450,
  "EDIT_WIDTH"=>300,

//  "EDIT_BUTTONS_UP"=>true


);


?>
