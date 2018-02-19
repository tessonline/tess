<?php
include_once(FileUpUrl('plugins/ruk/.admin/table_func_ruk.inc'));

//print_r($TABLE_CONFIG);

$TABLE_CONFIG['schema'][1] = array(
  field => "'<i><font size = 1>'...tableBarcode_RUK(ID,KOPIE)...'</font></i>'",
  label => 'PID',
  width => '4%',
  order_by => 'ID',
  ident => 'CK',
  settings => 'default'
);
