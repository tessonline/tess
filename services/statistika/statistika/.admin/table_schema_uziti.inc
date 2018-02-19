<?php
include_once(FileUpUrl('.admin/table_funkce.inc'));

$TABLE_CONFIG['schema'][] =	array( 
  'field' => 'NAZEV',
  'label' => 'Název',
  'order_by' => 'nazev',
);
$TABLE_CONFIG['schema'][] =	array(
  'field' => 'ShowOdkaz(ID,POCET_UZITI)',
//  'field' => 'POCET_UZITI',
  'label' => 'Využito',
  'order_by' => 'pocet_uziti',
);

