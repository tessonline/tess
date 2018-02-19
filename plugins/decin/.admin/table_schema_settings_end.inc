<?php

$TABLE_CONFIG['schema'][] = array(
  field => 'DecinKopieDokumentu(ID)',
  label => ' ',
  add => 'align = center',
  'width' => '1%',
  'class' => 'image',
  ident => 'kopie',
  'add' => 'NOWRAP',
  settings => 'function',
  'theme' => array(
    'dropdown'=>true,
    'column'=>true
  ),
);
