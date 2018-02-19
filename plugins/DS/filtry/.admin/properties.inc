<?php 

$PROPERTIES = array(
  'AGENDA_NAME' => 'Filtry DS',
  'AGENDA_TABLE' => 'POSTA_DS_FILTRY',
  'AGENDA_ID' => 'ID',
  'AGENDA_IDENT' => 'POSTA_DS_FILTRY',
  'AGENDA_DESCRIPTION' => 'Filtry pro převod datových zpráv do EED',
  'SECURITY_REGISTRATION' => false,
  //'ACCESS_IDENT' => '',
  
  'DEFAULT_LANG' => $config['POSTA_DS_FILTRY']['DEFAULT_LANG'],
  'DB_NAME' => $config['POSTA_DS_FILTRY']['DB_NAME'],
  
  //'BROW_SELECT'=>'SELECT k.*, o.sloupec1, o.sloupec2 FROM tabulka1 k '
  //             . 'LEFT JOIN tabulka2 o ON (k.sloupec1 = o.sloupec3)',
  //'BROW_ORDER_BY'=>'',
  //'BROW_FIELD_PREFIX'=>'k.',

  'EDIT_LEFT' => 100,
  'EDIT_TOP' => 10,
  'EDIT_HEIGHT' => 400,
  'EDIT_WIDTH' => 800,

  'DELETE_HEIGHT' => 260,
  'DELETE_WIDTH' => 600,
  'DELETE_LEFT' => 0,
  'DELETE_TOP' => 0,
  
  'INSERT_REFRESH' => true,
  
);
