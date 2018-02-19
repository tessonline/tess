<?php

$PROPERTIES_ACCESS['POSTA_PLUGINS_DR_APP'] = array(
  'desc' => 'Datový rozcestník',
  'rights' => array(
    'all_read'       => array('desc' => $GLOBALS['RESOURCE_STRING']['all_read'], 'ceu_invisible'  =>  true),
    'all_insert'     => array('desc' => $GLOBALS['RESOURCE_STRING']['all_insert'], 'ceu_invisible'  =>  true),  
    'all_update'     => array('desc' => $GLOBALS['RESOURCE_STRING']['all_update'], 'ceu_invisible'  =>  true),
    'all_delete'     => array('desc' => $GLOBALS['RESOURCE_STRING']['all_delete'], 'ceu_invisible'  =>  true),
  ),  
  'rightgroups' => array(
    'spravce' => array(
      'desc' => 'plný přístup do datového rozcestníku',
      'contains' => array('all_read','all_insert','all_update','all_delete')
    ),
  )  
);

$spravce = HasRole('spravce')||HasRole('super_spravce');
if (!$spravce) {
  foreach ($PROPERTIES_ACCESS as $key => $value) {
    unset($PROPERTIES_ACCESS[$key]['rightgroups']['spravce']);
  }
}
