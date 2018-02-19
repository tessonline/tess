<?php
include_once(FileUp2(".config/settings/agenda_path.inc"));
include_once(FileUp2(".admin/db/db_posta.inc"));
include_once(FileUp2(".admin/db/db_default.inc"));

//$GLOBALS["PROPERTIES_DEBUG"]["SHOW_SQL"] = true;
//$GLOBALS["PROPERTIES_DEBUG"]["SHOW_DEBUG"] = true;

If (!$GLOBALS["ZADEJ_SQL"]) $GLOBALS["ZADEJ_SQL"]="p.*";
If (!$GLOBALS["ZADEJ_ORDER_BY"]) $GLOBALS["ZADEJ_ORDER_BY"]="EV_CISLO DESC";

$PROPERTIES = array(
  "AGENDA_NAME" => "Evidence dokumentů",
  "AGENDA_TABLE" => "POSTA",
  "AGENDA_ID" => "ID",
  "AGENDA_IDENT" => "POSTA_C_JEDNACI",
  "DEFAULT_LANG"=>"cz_utf-8",
  "DB_NAME" =>"DB_POSTA",
//  "DB_NAME"=>$GLOBALS["SERVER_CONFIG"]["SECURITY"]["AUTH_DATABASE"],

  "BROW_PAGE_SIZE" => 100,
    
  "HISTORY_SHOW"=>true,


//  "BROW_SELECT" => "SELECT DISTINCT p.*,s.lname from posta p LEFT JOIN security_user s ON p.referent=s.id WHERE p.CISLO_SPISU1<>'' ",
//"BROW_SELECT" => "SELECT p.*,s.lname,g.name from posta p LEFT JOIN security_user s ON p.referent=s.id ".
//  "LEFT JOIN  cis_posta_odbory o ON p.odbor=o.id ". 
//  "LEFT JOIN  security_group g ON o.id_odbor=g.id", 
  "BROW_SELECT" => "SELECT ".$GLOBALS["ZADEJ_SQL"]." from posta p where p.stornovano is null",
  "BROW_FIELD_PREFIX" => "p.",
  "BROW_ORDER_BY"=>$GLOBALS["ZADEJ_ORDER_BY"],

  //po insertu se refreshne okno main
  "INSERT_REFRESH" => true,

  "EDIT_WIDTH" => 790,
  "EDIT_HEIGHT" => 420,
  "EDIT_LEFT" => 10,
  "EDIT_TOP" => 50,

  "DELETE_WIDTH" => 700,
  "DELETE_HEIGHT" => 250,
  "DELETE_LEFT" => 50,
  "DELETE_TOP" => 50

  
  
//  "ACCESS_BY_BROW_SELECT"=>true
);

//$PROPERTIES["MAIN_WINDOW"] = "edit.php?filter";

?>
