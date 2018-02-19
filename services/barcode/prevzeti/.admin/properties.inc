<?php
include_once(FileUp2(".admin/db/db_default.inc"));
include_once(FileUp2(".admin/db/db_posta.inc"));
//$GLOBALS["PROPERTIES_DEBUG"]["SHOW_SQL"] = true; 

$PROPERTIES = array(
  "AGENDA_NAME" => "Převzetí dokumentů",
  "AGENDA_IDENT" => "POSTA_PODACI_RAZITKO",
  "AGENDA_ID" => "POSTA_PODACI_RAZITKO",

  "DEFAULT_LANG"=>"cz_utf-8",

  "INSERT_REFRESH" => true,

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
