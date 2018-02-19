<?php
//$GLOBALS['PROPERTIES_DEBUG']['SHOW_SQL'] = true;
//$GLOBALS['PROPERTIES_DEBUG']['SHOW_ACCESS'] = true; 
include_once(FileUp2(".admin/db/db_posta.inc"));
include_once(FileUp2(".admin/db/db_default.inc"));

$PROPERTIES = array(
  'AGENDA_NAME' => 'Nastavení skupin adresátů',
  'AGENDA_TABLE' => 'posta_nastaveni_vnejsi_adresati_skupiny',
  'AGENDA_ID' => 'ID',
  'AGENDA_IDENT' => 'POSTA_NASTAVENI_VNEJSIADR',
  'AGENDA_DESCRIPTION' => '',
  'SECURITY_REGISTRATION' => true,
  
  "ACCESS_UPDATE_OWNER_ID" => 'OWNER_ID',

  //'DEFAULT_LANG'=>'cz_utf-8',
  
  //'BROW_SELECT'=>'SELECT k.*, o.sloupec1, o.sloupec2 FROM tabulka1 k '
  //             . 'LEFT JOIN tabulka2 o ON (k.sloupec1 = o.sloupec3)',
  //'BROW_ORDER_BY'=>'',
  //'BROW_FIELD_PREFIX'=>'k.',

  'EDIT_LEFT' => 100,
  'EDIT_TOP' => 10,
  'EDIT_HEIGHT' => 600,
  'EDIT_WIDTH' => 900,

  'DELETE_HEIGHT' => 260,
  'DELETE_WIDTH' => 600,
  'DELETE_LEFT' => 0,
  'DELETE_TOP' => 0,
  
  'INSERT_REFRESH' => true,
  
);
