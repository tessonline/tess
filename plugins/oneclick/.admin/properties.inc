<?php

include(FileUp2('.config/config.inc'));

$PROPERTIES = array(
  'AGENDA_NAME'  => 'Rozhranní pro slubu 1click',
  'AGENDA_TABLE' => $CONFIG['POSTA_INTERFACE_ONE_CLICK']['AGENDA_TABLE'],
  'AGENDA_ID'    => '',
  'AGENDA_IDENT' => 'POSTA_INTERFACE_ONE_CLICK',
  'AGENDA_DESCRIPTION'    => '',
  'SECURITY_REGISTRATION' => false,
  //'ACCESS_IDENT' => '',
  
  'DEFAULT_LANG' => $CONFIG['POSTA_INTERFACE_ONE_CLICK']['DEFAULT_LANG'],
  'DB_NAME'      => $CONFIG['POSTA_INTERFACE_ONE_CLICK']['DB_NAME'],
  
  //'BROW_SELECT' => 'SELECT k.*, o.sloupec1, o.sloupec2 FROM tabulka1 k ' .
  //                 'LEFT JOIN tabulka2 o ON (k.sloupec1 = o.sloupec3)',
  
  //'BROW_ORDER_BY'     => '',
  //'BROW_FIELD_PREFIX' => 'k.',

  'EDIT_LEFT'   => 100,
  'EDIT_TOP'    => 10,
  'EDIT_HEIGHT' => 400,
  'EDIT_WIDTH'  => 600,

  'DELETE_HEIGHT' => 260,
  'DELETE_WIDTH'  => 600,
  'DELETE_LEFT'   => 0,
  'DELETE_TOP'    => 0,
  
  'INSERT_REFRESH' => true,
  
  // Konfigurace Delete formu  
  //'CAPTION_DELETE' => 'Prázdná agenda T-WIST - Stornovat',
  //'MESSAGE_DELETE'  => 'Chcete skutečně stornovat následující záznam?',
  'USE_DELETE_FORM' => false
  
);
