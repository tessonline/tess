<?php
//$GLOBALS["PROPERTIES_DEBUG"]["SHOW_SQL"] = true; 
include_once(FileUp2(".admin/db/db_posta.inc"));


$PROPERTIES = array(
  "AGENDA_NAME" => "Česká pošta - protokoly",
  "AGENDA_TABLE" => "posta_cis_ceskaposta",
  "AGENDA_IDENT" => "POSTA_CPOST",
  "AGENDA_ID" => "ID",
  "DB_NAME" => "db_posta",

  "INSERT_REFRESH" => true,
  "DEFAULT_LANG"=>"cz_utf-8",

  "ACCESS_IDENT" => "POSTA",


//  "BROW_SELECT" => "SELECT p.* from posta p",
//  "BROW_FIELD_PREFIX" => "p.",
  "BROW_ORDER_BY"=>"rok desc, protokol desc",

  "GUIDE_WIDTH" => 700,
  "GUIDE_HEIGHT" => 550,
  "GUIDE_LEFT" => 10,
  "GUIDE_TOP" => 30,

  "DELETE_LEFT"=>20,
  "DELETE_TOP"=>20,
  "DELETE_HEIGHT"=>250,
  "DELETE_WIDTH"=>600,

  "EDIT_LEFT"=>20,
  "EDIT_TOP"=>20,
  "EDIT_HEIGHT"=>500,
  "EDIT_WIDTH"=>590,

//  "EDIT_BUTTONS_UP"=>true


);

?>
