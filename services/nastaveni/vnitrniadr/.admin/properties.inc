<?php
//$GLOBALS["PROPERTIES_DEBUG"]["SHOW_SQL"] = true;
include_once(FileUp2(".admin/db/db_posta.inc"));
include_once(FileUp2(".admin/db/db_default.inc"));

$PROPERTIES = array(
  "AGENDA_NAME" => "Nastavení skupin adresátů vnitřní pošty",
  "AGENDA_TABLE" => "posta_nastaveni_vnitrni_adresati_skupiny",
  "AGENDA_ID" => "ID",
  "AGENDA_IDENT" => "POSTA_NASTAVENI_VNITRNIADR",
  "DB_NAME" => "DB_POSTA",
  "DEFAULT_LANG"=>"cz_utf-8",

  "ACCESS_UPDATE_OWNER_ID" => 'OWNER_ID',

  "INSERT_REFRESH"=>true,

  "EDIT_LEFT"=>20,
  "EDIT_TOP"=>20,
  "EDIT_HEIGHT"=>500,
  "EDIT_WIDTH"=>900,

  "DELETE_HEIGHT" => 300,
  "DELETE_WIDTH" => 600,
  "DELETE_LEFT" => 50,
  "DELETE_TOP" => 50
);
