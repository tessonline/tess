<?php
include_once(FileUp2(".config/settings/agenda_path.inc"));
include_once(FileUp2(".admin/db/db_default.inc"));
include_once(FileUp2(".admin/db/db_monumnis.inc"));
include_once(FileUp2(".admin/config.inc"));

//$GLOBALS["PROPERTIES_DEBUG"]["SHOW_SQL"] = true;
//$GLOBALS["PROPERTIES_DEBUG"]["SHOW_DEBUG"] = true;
include_once(FileUp2(".admin/db/db_posta.inc"));

$PROPERTIES = array(
  "AGENDA_NAME" => "Přiřazení památky",
//  "AGENDA_TABLE" => "POSTA_SPIS",
  "AGENDA_TABLE" => "EssPam",
  "AGENDA_ID" => "IDPAM",
  "AGENDA_IDENT" => "POSTA_SPIS",
  "DEFAULT_LANG"=>"cz_iso",

  "DB_NAME"=>"DB_MONUMNIS",

  "BROW_PAGE_SIZE" => 100,
    
//  "HISTORY_SHOW"=>false,

  //po insertu se refreshne okno main
  "INSERT_REFRESH" => true,

  "EDIT_WIDTH" => 790,
  "EDIT_HEIGHT" => 420,
  "EDIT_LEFT" => 10,
  "EDIT_TOP" => 50,

  "DELETE_WIDTH" => 700,
  "DELETE_HEIGHT" => 250,
  "DELETE_LEFT" => 50,
  "DELETE_TOP" => 50,

//  "vazba"=>GetAgendaPath('NPU_KULTPAM',0,1)."/brow.php",  
  "vazba"=>"http://monumnet.npu.cz/spis/esspam.php?dol=",  
//  "ACCESS_BY_BROW_SELECT"=>true
);

