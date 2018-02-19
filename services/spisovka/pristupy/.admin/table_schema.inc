<?php
Include_once(FileUp2('.admin/table_funkce_denik.inc'));

function ShowEdit($text) {
  if ($text == 'read') $res = 'čtení';
  if ($text == 'edit') $res = 'čtení, editace';
  if ($text == 'delete') $res = 'čtení, editace, storno';
  return $res;
}

$TABLE_CONFIG['schema'][] = array(
  field => 'ShowEdit(ACCESS)',
  label => '<font color=black>Právo</font>',
  settings => 'default');

$TABLE_CONFIG['schema'][] = array(
  field => 'ShowRange(SPIS)',
  label => '<font color=black>Rozsah</font>',
  settings => 'default');


$TABLE_CONFIG['schema'][] = array(
  field => 'UkazOdbor(ODBOR)',
  label => '<font color=black>' . $GLOBALS['CONFIG']['NAZEV_TABLE_ODBOR'] . '</font>',
  settings => 'default');

$TABLE_CONFIG['schema'][] = array(
  field => 'UkazOtocUsera(REFERENT,false,false,true)',
  label => '<font color=black> ' . $GLOBALS['CONFIG']['NAZEV_TABLE_REFERENT'] . '</font>',
  width => '30%',
);
$TABLE_CONFIG['schema'][] = array(
  field => 'ShowPIDs(ID)',
  label => '<font color=black>PID</font>',
  width => '20%',
);
//

  $TABLE_CONFIG['syscolumns'] = array(
    'upload' => array ('theme'=>array('dropdown'=>false, 'column'=>false)),
    'info' => array ('theme'=>array('dropdown'=>false, 'column'=>false)),
    'edit' => array ('theme'=>array('dropdown'=>true, 'column'=>true)),
    'delete' => array ('theme'=>array('dropdown'=>true, 'column'=>true)),
  );


