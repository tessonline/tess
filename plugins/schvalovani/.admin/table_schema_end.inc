<?php
require_once(FileUp2('plugins/schvalovani/.admin/schvalovani.inc'));


$TABLE_CONFIG['schema'][] = array(
  field => 'UkazSchvalovani(ID)',
  label => ' ',
  add => 'align = center',
  'width' => '1%',
  'class' => 'image',
  ident => 'schvalovani',
  'add' => 'NOWRAP',
  settings => 'default',
  'theme' => array(
    'dropdown'=>true,
    'column'=>true
  ),
);
