<?php
$TABLE_CONFIG['schema'][] = array(
  field => 'DATUM',
  label => 'Datum',
  width => '10%',
  order_by => 'DATUM'
);

$TABLE_CONFIG['schema'][] = array(
  field => 'PLUGIN',
  label => 'Plugin',
  width => '10%',
  order_by => 'PLUGIN'
);

$TABLE_CONFIG['schema'][] = array(
  field => "POPIS",
  label => 'Nová funkcionalita',
  width => '40%',
  is_html => true,
  order_by => 'POPIS'
);

$TABLE_CONFIG['schema'][] = array(
  field => "OPRAVY",
  label => 'Opravy',
  width => '40%',
  is_html => true,
  order_by => 'OPRAVY'
);
