<?php
//require_once(FileUp2('.admin/table_func_oneclick.inc'));


$TABLE_CONFIG['schema'][] = array(
  field => 'createOneClickLink(ID, REFERENT)',
  label => '',
  add => 'align = center',
  'width' => '1%',
  'class' => 'image',
  ident => 'oneclick',
  'add' => 'NOWRAP',
  settings => 'default',
  'theme' => array(
    'dropdown'=>true,
    'column'=>true
  ),
);
