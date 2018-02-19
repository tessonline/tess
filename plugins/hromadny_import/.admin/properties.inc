<?php
require_once(FileUp2(".admin/db/db_posta.inc"));
//nevim proc, ale zlobi to pro upload.
//if (!ereg('ug_file', $_SERVER['SCRIPT_NAME'])) include_once(FileUp2('.config/config.inc'));

$PROPERTIES = array(
  'AGENDA_NAME'  => "Hromadný import",
  'AGENDA_TABLE' => 'POSTA_HROMADNY_IMPORT',
  'AGENDA_ID'    => 'TID',
  'AGENDA_IDENT' => 'POSTA_HROMADNY_IMPORT',
  'DB_NAME' =>      'DB_POSTA',
  'DEFAULT_LANG' => 'cz_utf-8',

  //'BROW_SELECT' => 'SELECT * FROM ' . $GLOBALS['CONFIG_ROB']['TABLE_PREFIX'] . 't_import',
  'BROW_ORDER_BY'     => 'tid desc',
  
  'EDIT_LEFT'   => 100,
  'EDIT_TOP'    => 10,
  'EDIT_HEIGHT' => 600,
  'EDIT_WIDTH'  => 960,

  'DELETE_HEIGHT' => 260,
  'DELETE_WIDTH'  => 600,
  'DELETE_LEFT'   => 0,
  'DELETE_TOP'    => 0,
  
  'INSERT_REFRESH' => true,

  'USE_DELETE_FORM' => false
  
);




