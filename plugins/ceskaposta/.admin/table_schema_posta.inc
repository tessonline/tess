<?php
require_once(FileUp2('.admin/config.inc'));
Include_once(FileUp2('.admin/form_func.inc'));
Include_once(FileUp2('.admin/table_funkce_denik.inc'));
Include_once(FileUp2('.admin/oth_funkce.inc'));
Include_once(FileUp2('.admin/security_name.inc'));

$GLOBALS['doporucene'] = getSelectDataEed(new of_select_typ_odeslani(array()));

require_once(FileUp2('plugins/ceskaposta/.admin/table_func.inc'));

//$TABLE_CONFIG["callback"] = 'ChangeClassPosta';

$TABLE_CONFIG['schema'][] = array(
  field => 'tableFormatCJednaci(ID)',
  label => $GLOBALS['CONFIG']['CISLO_SPISU'],
  width => '4%',
  add => 'NOWRAP',
  ident => 'SIS',
  settings => 'default'
);


$TABLE_CONFIG['schema'][] = array( 
  field => "Ukaz2(ODES_TYP, ZPUSOB_PODANI, VLASTNICH_RUKOU)...'&nbsp;'...UkazJmeno()",
  label => 'Odesílatel/Adresát',
  width => '35%',
  ident => 'JMENO',
  settings => 'default'
);

$TABLE_CONFIG['schema'][] = array( 
  field => 'tableVec(ID)',
  label => 'Věc',
  width => '30%',
  ident => 'VEC',
  settings => 'default'
);

$TABLE_CONFIG['schema'][] = array(
  field => "tableSpisUzel(ID)...'<br/>'...tableZpracovatel(ID)",
  label => 'Vyřizuje',
  width => '10%',
  ident => 'ODBREF'
);

$TABLE_CONFIG['schema'][] = array(
  field => 'TableCeskaPostaVypraveni(DOPORUCENE)',
  label => 'Vypravení',
  width => '10%',
  ident => 'Vypraveni'
);


