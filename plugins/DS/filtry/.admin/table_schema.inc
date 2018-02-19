<?php

include_once(FileUp2('.admin/db/db_posta.inc'));
include_once(FileUp2('.admin/security_name.inc'));
include_once(FileUp2('.config/config_posta.inc'));

$TABLE_CONFIG['schema'][] =	array( 
  'field' => 'PRIORITY', 
  'label' => 'Priorita filtru',
  'add' => 'align="center"',
  'order_by' => 'PRIORITY',
);

$TABLE_CONFIG['schema'][] =	array( 
  'field' => 'getDmItemLabel(DM_ITEM)', 
  'label' => 'Položka DS ...',
  'add' => 'align="center"',
);

$style = 'style="width: 250px; display: inline-block; overflow: hidden; text-overflow: ellipsis;"';
$TABLE_CONFIG['schema'][] =	array( 
//  'field' => "'<span $style>'...ShowDmItem(DM_ITEM_COMPARED_VALUES)...'</span>'",
  'field' => "ShowDmItem(DM_ITEM_COMPARED_VALUES)",
  'label' => '... obsahuje hodnoty',
//  'width' => "255px"
);

$TABLE_CONFIG['schema'][] =	array( 
  'field' => 'UkazOdbor(ED_ITEM_SUPERODBOR, TRUE)', 
  'label' => 'Zařízení',
  'add' => 'align="center"',
);

$TABLE_CONFIG['schema'][] =	array( 
  'field' => 'UkazOdbor(ED_ITEM_ODBOR, TRUE)', 
  'label' => 'Odbor',
  'add' => 'align="center"',
);

$TABLE_CONFIG['schema'][] =	array( 
  'field' => 'UkazUsera(ED_ITEM_REFERENT)', 
  'label' => $GLOBALS["CONFIG"]["NAZEV_TABLE_REFERENT"],
  'add' => 'align="center"',
);

$TABLE_CONFIG['schema'][] =	array(
  'field' => 'selectVita(ED_STAV)',
  'label' => 'Vyřizuje',
  'add' => 'align="center"',
);

/*
$TABLE_CONFIG['schema'][] =	array( 
  'field' => "SLOUPEC1...' '...SLOUPEC2", 
  'label' => 'NAZEV2', 
  'order_by' => 'sloupec3 asc'
);
$TABLE_CONFIG['schema'][] =	array( 
  'field' => 'Funkce(SLOUPEC4)', 
  'label' => 'NAZEV3'
);
$TABLE_CONFIG['schema'][] =	array( 
  'field' => "\$q->dbdate2str(DATUM, '1')", 
  'label' => 'datum', 
  'order_by' => 'datum desc'
);
*/
