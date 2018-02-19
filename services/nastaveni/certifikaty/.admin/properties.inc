<?php
//$GLOBALS["PROPERTIES_DEBUG"]["SHOW_SQL"] = true;
include_once(FileUp2(".admin/db/db_posta.inc"));
include_once(FileUp2(".admin/db/db_default.inc"));

$PROPERTIES = array(
  "AGENDA_NAME" => "Správce cerfikátů",
  "AGENDA_TABLE" => "POSTA_CERTIFIKATY",
  "AGENDA_ID" => "ID",
  "AGENDA_IDENT" => "POSTA_CERTIFIKATY",
  "DB_NAME" => "db_posta",
  "DEFAULT_LANG"=>"cz_utf-8",

 
//  "BROW_SELECT"=>"SELECT a.*,b.zkratka FROM cis_posta_typ a LEFT JOIN cis_posta_odbory b ON a.odbor=b.id",
//  "BROW_FIELD_PREFIX" => "a.",
  "BROW_ORDER_BY"=>"ID DESC",

  "INSERT_REFRESH"=>true,

  "EDIT_LEFT"=>20,
  "EDIT_TOP"=>20,
  "EDIT_HEIGHT"=>200,
  "EDIT_WIDTH"=>750,

  "DELETE_HEIGHT" => 300,
  "DELETE_WIDTH" => 600,
  "DELETE_LEFT" => 50,
  "DELETE_TOP" => 50,

  "UPLOAD_DIRS" => array(
     "odbor"=>array("min_dir_cif"=>6),
  ),

);
?>
