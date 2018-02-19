<?php
require_once(FileUp2('.admin/config.inc'));
Include_once(FileUp2('.admin/form_func.inc'));
Include_once(FileUp2('.admin/table_funkce_denik.inc'));
Include_once(FileUp2('.admin/oth_funkce.inc'));
Include_once(FileUp2('.admin/security_name.inc'));

$TABLE_CONFIG["callback"] = 'ChangeClassPosta';

if ($GLOBALS['SHOW_BARCODE'])
$TABLE_CONFIG['schema'][] = array(
//  field => "'<i><font size = 1>'...tableBarcode(ID)...'</font></i>'",
  field => "tableBarcode(ID)",
  label => 'JID',
  width => '4%',
  order_by => 'ID',
  ident => 'CK',
  settings => 'default'
);

$TABLE_CONFIG['schema'][] = array(
  field => 'tableFormatCJednaci(ID)',
  label => $GLOBALS['CONFIG']['CISLO_SPISU'],
  width => '30%',
  //add => 'NOWRAP',
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
//  add => "'align = left style = 'padding:0 0.3em' NOWRAP'",
  width => '30%%',
  ident => 'ODBREF'
);

