<?php
  $TABLE_CONFIG['schema'][] = array(
//    field => "'<i><font size = 1>'...tableBarcode(ID)...'</font></i>'",
    field => "tableBarcode(ID)",
    label => 'JID',
    width => '4%',
    order_by => 'ID',
    ident => 'CK',
    settings => 'default'
  );
$TABLE_CONFIG['schema'][] = array(
  field => "DatumPrijeti(DATUM_PODATELNA_PRIJETI)...'<br/>'...DatumVyrizeni(LHUTA_VYRIZENI)",
  label => 'Datum&nbsp;přijetí,<br/>K&nbsp;vyřízení&nbsp;do',
  order_by => 'datum_podatelna_prijeti',
  width => '4%',
  add => 'NOWRAP',
  ident => 'PRIJETI',
  settings => 'default'
);

$TABLE_CONFIG['schema'][] = array(
  field => "UkazJmeno()",
  label => 'Odesílatel, Adresát',
  order_by => 'odesl_prijmeni asc, odesl_jmeno asc',
  order_by => 'odesl_prijmeni asc, odesl_jmeno asc, odesl_ulice asc, odesl_posta asc, odesl_osoba asc',
  width => '35%',
  ident => 'JMENO',
  settings => 'default'
);


$TABLE_CONFIG['schema'][] = array(
  field => 'tableVec(ID)',
  label => 'Věc',
  order_by => 'vec',
  width => '30%',
  ident => 'VEC',
  settings => 'default'
);

$TABLE_CONFIG['schema'][] = array(
  field => "JeDokumentDr(ID,'ODZ')",
  label => 'ODZ',
  width => '10%',
);

$TABLE_CONFIG['schema'][] = array(
  field => "JeDokumentDr(ID,'DOR')",
  label => 'Dor',
  width => '10%',
);

