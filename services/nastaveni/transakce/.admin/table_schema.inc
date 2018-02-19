<?php
$a = new DB_POSTA;
/*
$TABLE_CONFIG['schema'][] = array(
  field => "ID",
  label => 'ID',
  width => '4%',
);
*/
$TABLE_CONFIG['schema'][] = array(
  field => "tableBarcode(DOC_ID)",
  label => 'JID',
  width => '4%',
);
$TABLE_CONFIG['schema'][] = array(
  field => "CeskyDate(LAST_TIME)",
  label => 'Datum',
  width => '10%',
  add => 'NOWRAP',
);

$TABLE_CONFIG['schema'][] = array(
  field => "ShowTypProtokolu(TYP)",
  label => 'Typ',
  width => '10%',
);

$TABLE_CONFIG['schema'][] = array(
  field => "JMENO",
  label => 'Zpracovatel',
  width => '20%',
);

$TABLE_CONFIG['schema'][] = array(
  field => "TEXT",
  label => 'Úkon',
  width => '60%',
  is_html => true
);

