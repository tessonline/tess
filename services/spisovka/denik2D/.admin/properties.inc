<?php
//include_once(FileUp2(".config/settings/agenda_path.inc"));
include_once(FileUp2(".admin/db/db_default.inc"));

if ($_SERVER['HTTPS'])
  include_once(FileUp2(".admin/has_access.inc"));
include_once(FileUp2(".admin/db/db_posta.inc"));
include_once(FileUp2(".admin/security_name.inc"));
//security_func vraci odbory atd.
include_once(FileUp2("security/.admin/security_func.inc"));
include_once(FileUp2(".admin/status.inc"));

if ($GLOBALS['CONFIG']['UPLOAD_ELO'])
  include_once(FileUp2("services/dms/elo/aktualizace.php"));

$PROPERTIES = array(
  'AGENDA_NAME' => 'Podací deník',
  'AGENDA_TABLE' => 'posta',
  'AGENDA_ID' => 'ID',
  'AGENDA_IDENT' => 'POSTA_DENIK',
  'AGENDA_DESCRIPTION' => '',
  'SECURITY_REGISTRATION' => true,
  'DB_NAME' => 'DB_POSTA',
  
  //'DEFAULT_LANG'=>'cz_utf-8',
  
  //'BROW_SELECT'=>'SELECT k.*, o.sloupec1, o.sloupec2 FROM tabulka1 k '
  //             . 'LEFT JOIN tabulka2 o ON (k.sloupec1 = o.sloupec3)',
  "BROW_SELECT" => "SELECT p.* from posta p LEFT JOIN security_user u ON p.referent=u.id",
  "BROW_FIELD_PREFIX" => "p.",
//  "BROW_ORDER_BY"=>"ID DESC, ROK DESC, EV_CISLO DESC",
  "BROW_ORDER_BY"=>"ID DESC",
  //'BROW_FIELD_PREFIX'=>'k.',

  'EDIT_LEFT' => 100,
  'EDIT_TOP' => 10,
  'EDIT_HEIGHT' => 400,
  'EDIT_WIDTH' => 600,

  'DELETE_HEIGHT' => 260,
  'DELETE_WIDTH' => 600,
  'DELETE_LEFT' => 0,
  'DELETE_TOP' => 0,
  
  'INSERT_REFRESH' => true,
  
);
