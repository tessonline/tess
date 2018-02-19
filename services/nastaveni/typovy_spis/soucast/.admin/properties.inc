<?php
include_once(FileUp2(".admin/db/db_posta.inc"));

$PROPERTIES = array(
  "AGENDA_NAME" => "Součásti typového spisu",
  "AGENDA_TABLE" => "posta_cis_typ_spis_soucasti",
  "AGENDA_ID" => "ID",
  "AGENDA_IDENT" => "POSTA_CIS_TYPOVY_SPIS_SOUCAST",
  "DEFAULT_LANG"=>"cz_utf-8",

  "DB_NAME"=>"DB_POSTA",

  "BROW_PAGE_SIZE" => 100,
    
  "INSERT_REFRESH" => true,

  "EDIT_WIDTH" => 790,
  "EDIT_HEIGHT" => 420,
  "EDIT_LEFT" => 10,
  "EDIT_TOP" => 50,

  "DELETE_WIDTH" => 700,
  "DELETE_HEIGHT" => 250,
  "DELETE_LEFT" => 50,
  "DELETE_TOP" => 50,

);

