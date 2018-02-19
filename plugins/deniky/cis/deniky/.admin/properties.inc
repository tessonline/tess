<?php
include_once(FileUp2(".admin/db/db_posta.inc"));

$PROPERTIES = array(
  'AGENDA_NAME' => 'Další evidence',
  'AGENDA_TABLE' => 'POSTA_CIS_DENIKY',
  'AGENDA_ID' => 'ID',
  'AGENDA_IDENT' => 'POSTA_CIS_DENIKY',
  'DB_NAME' => 'db_posta',
  'DEFAULT_LANG' => 'cz_utf-8',

  'INSERT_REFRESH'=>true,

  'EDIT_LEFT'=>20,
  'EDIT_TOP'=>20,
  'EDIT_HEIGHT'=>200,
  'EDIT_WIDTH'=>750,

  'DELETE_HEIGHT' => 300,
  'DELETE_WIDTH' => 600,
  'DELETE_LEFT' => 50,
  'DELETE_TOP' => 50
);
