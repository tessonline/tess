<?php
// include_once(FileUp2(".config/settings/agenda_path.inc"));
include_once(FileUp2(".admin/db/db_posta.inc"));
//include_once(FileUp2("posta/.admin/properties.inc"));
// include_once(FileUp2(".admin/db/db_default.inc"));

//$GLOBALS["PROPERTIES_DEBUG"]["SHOW_SQL"] = true;
//$GLOBALS["PROPERTIES_DEBUG"]["SHOW_DEBUG"] = true;

//echo "Jsme tam";

$PROPERTIES = array(
  "AGENDA_NAME" => "Spisová a skartační kniha",
//  "AGENDA_TABLE" => "POSTA",
  "AGENDA_TABLE" => "POSTA_SPISOVNA",
  "AGENDA_ID" => "ID",
  "AGENDA_IDENT" => "SKARTACNI_KNIHA",
  "DEFAULT_LANG"=>"cz_utf-8",

  "DB_NAME"=>"db_posta",

  "BROW_PAGE_SIZE" => 100,
  "SECURITY_REGISTRATION" => false,
  "ACCESS_IDENT" => "SKARTACNI_KNIHA",
  "HISTORY_SHOW" => true ,

//  "BROW_SELECT" => "SELECT p.id as id2,p.*,k.*,x.referent,x.typ_posty,x.datum_podatelna_prijeti,x.oddeleni,x.odbor,x.datum_vyrizeni as vyrizeni_doc,p.spisovna_id as idxxx from posta_view_spisy p ".
  "BROW_SELECT" => "SELECT s.*,p.id as id2,p.referent,p.skartace FROM posta_spisovna s left join posta_view_spisy p ON (s.dokument_id=p.id) LEFT JOIN  cis_posta_skartace k ON p.skartace = k.id",
//  "BROW_SELECT" => "SELECT s.* FROM posta_spisovna s ",

  "BROW_FIELD_PREFIX" => "s.",
  "BROW_ORDER_BY"=>"id desc",

  //po insertu se refreshne okno main
  "INSERT_REFRESH" => true,

  "EDIT_WIDTH" => 790,
  "EDIT_HEIGHT" => 750,
  "EDIT_LEFT" => 1,
  "EDIT_TOP" => 1,

  "DELETE_WIDTH" => 700,
  "DELETE_HEIGHT" => 250,
  "DELETE_LEFT" => 20,
  "DELETE_TOP" => 10

);

IF (!$GLOBALS['SPISOVNA_ID'] && $GLOBALS['SHOW_BOX']) {
  $PROPERTIES["BROW_SELECT"] = "SELECT p.* FROM posta_spisovna_boxy p  ";
  $PROPERTIES["BROW_FIELD_PREFIX"] = "p.";
  $PROPERTIES["BROW_ORDER_BY"] = "p.ID ASC";
  $PROPERTIES["HISTORY_SHOW"]=true;

}
IF ($GLOBALS['PREDANI']) {
  $PROPERTIES["BROW_SELECT"] = "SELECT p.* from posta_view_spisy p ".
  "LEFT JOIN  cis_posta_skartace k ON p.skartace = k.id ".
//  "LEFT JOIN security_user u ON p.referent=u.id ".
//  " WHERE p.skartace<>''",
  " WHERE (p.status=1 or p.status=-4 or p.status=-5) and p.skartace>0";
  $PROPERTIES["BROW_FIELD_PREFIX"] = "p.";
  $PROPERTIES["BROW_ORDER_BY"] = "p.ID ASC";
  $PROPERTIES["HISTORY_SHOW"]=true;

}

IF (strpos($_SERVER[SCRIPT_NAME],'delete.php') || strpos($_SERVER[SCRIPT_NAME],'edit.php') || strpos($_SERVER[SCRIPT_NAME],'run.php') || strpos($_SERVER[SCRIPT_NAME],'history.php') || strpos($_SERVER[SCRIPT_NAME],'ug_file.php') || strpos($_SERVER[SCRIPT_NAME],'delete.php')) {
  $PROPERTIES["AGENDA_TABLE"] = "POSTA_SPISOVNA";
  $PROPERTIES["BROW_ORDER_BY"]="id desc";
  $PROPERTIES["BROW_SELECT"] = "SELECT s.*,p.id as id2,p.referent,p.skartace FROM posta_spisovna s left join posta_view_spisy p ON (s.dokument_id=p.id) LEFT JOIN  cis_posta_skartace k ON p.skartace = k.id";
  $PROPERTIES["BROW_FIELD_PREFIX"] = "s.";
  $PROPERTIES["HISTORY_SHOW"]=true;

}


IF ($GLOBALS['SKARTACNI_RIZENI_ID']) {
  $PROPERTIES["AGENDA_TABLE"] = "POSTA_SPISOVNA";
  $PROPERTIES["BROW_ORDER_BY"]="cislo_spisu2 asc, cislo_spisu1 asc";
//  $PROPERTIES["BROW_SELECT"] = "SELECT s.*,p.odbor,p.id as id2,p.oddeleni,p.referent,p.skartace,p.superodbor as superodbor2 FROM posta_spisovna s left join posta_view_spisy p ON (s.cislo_spisu1=p.cislo_spisu1) and (s.cislo_spisu2=p.cislo_spisu2) and (s.superodbor=p.superodbor) LEFT JOIN  cis_posta_skartace k ON p.skartace = k.id WHERE s.id in (select spisovna_id from posta_skartace_id where  skartace_id=".$GLOBALS['SKARTACNI_RIZENI_ID']."))";
  $PROPERTIES["BROW_SELECT"] = "SELECT s.* FROM posta_spisovna s WHERE s.id in (select spisovna_id from posta_skartace_id where skartace_id=".$GLOBALS['SKARTACNI_RIZENI_ID']."))";
  $PROPERTIES["BROW_FIELD_PREFIX"] = "s.";
  $PROPERTIES["HISTORY_SHOW"]=true;

}

