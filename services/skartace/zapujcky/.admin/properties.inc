<?php
include_once(FileUp2(".config/settings/agenda_path.inc"));
include_once(FileUp2(".admin/db/db_posta.inc"));
include_once(FileUp2(".admin/db/db_default.inc"));
//include_once(FileUp2("posta/.admin/properties.inc"));

//$GLOBALS["PROPERTIES_DEBUG"]["SHOW_SQL"] = true;
//$GLOBALS["PROPERTIES_DEBUG"]["SHOW_DEBUG"] = true;

//echo "Jsme tam";

$PROPERTIES = array(
  "AGENDA_NAME" => "Výpůjčky ze spisovny",
  "AGENDA_TABLE" => "POSTA_SPISOVNA_ZAPUJCKY",
  "AGENDA_ID" => "ID",
  "AGENDA_IDENT" => "POSTA_SPISOVNA_ZAPUJCKY",
  "DEFAULT_LANG"=>"cz_utf-8",

  "DB_NAME"=>"db_posta",

  "SECURITY_REGISTRATION"=>false,

  "BROW_PAGE_SIZE" => 100,
    
//  "HISTORY_SHOW"=>true,
//   "BROW_SELECT" => "SELECT z.*,s.datum_predani,k.id as id2 from posta_spisovna_zapujcky z ".
//   "LEFT JOIN posta_spisovna s ON s.zapujcka_id = z.id ".
//   "LEFT JOIN cis_posta_skartace k ON s.skartace_id = k.id ",

  "BROW_SELECT" => "SELECT DISTINCT on (z.id) z.*,s.vec from posta_spisovna_zapujcky z ".
  "LEFT JOIN posta_spisovna s ON s.zapujcka_id = z.id ".
  "LEFT JOIN cis_posta_skartace k ON s.skartace_id = k.id ",

  "BROW_FIELD_PREFIX" => "z.",
  "BROW_ORDER_BY"=>"z.ID ASC",

  "INSERT_REFRESH" => true,

  "EDIT_WIDTH" => 790,
  "EDIT_HEIGHT" => 550,
  "EDIT_LEFT" => 1,
  "EDIT_TOP" => 1,

  "DELETE_WIDTH" => 700,
  "DELETE_HEIGHT" => 250,
  "DELETE_LEFT" => 20,
  "DELETE_TOP" => 10

  
  
//  "ACCESS_BY_BROW_SELECT"=>true


);

