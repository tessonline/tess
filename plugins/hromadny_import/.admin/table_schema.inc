<?php
include_once(FileUp2("js/window.inc"));



$TABLE_CONFIG = array(
  'schema' => array( 
/*    array(
      'field' => 'TID',
      'label' => 'ID',
      
    ),*/
    array(
      'field' => 'POPIS',
      'label' => $GLOBALS['RSTR_IMPORT']['import_nazev'],
    ),
    array(
      'field' => 'importStavImporteru(STAV,TID,ZAMCENO)',
      'label' => $GLOBALS['RSTR_IMPORT']['import'],
    ),
    
  )
);



$TABLE_CONFIG['schema'][]
= array(
  'field' => 'testSablony(TID)',
  'label' => ' ',
  'add' => 'align = center',
  'width' => '1%',
  'class' => 'image',
  'add' => 'NOWRAP',
  'settings' => 'function',
  'theme' => array(
    'dropdown'=>true,
    'column'=>true
  ),
);

$TABLE_CONFIG['schema'][] 
  = array(
    'field' => 'DownloadZip(TID,STAV)',
    'label' => ' ',
    'add' => 'align = center',
    'width' => '1%',
    'class' => 'image',
    'add' => 'NOWRAP',
    'settings' => 'function',
    'theme' => array(
      'dropdown'=>true,
      'column'=>true
  ),
);
  
  
  $TABLE_CONFIG['schema'][]
  = array(
    'field' => 'delete(TID,ZAMCENO)',
    'label' => ' ',
    'add' => 'align = center',
    'width' => '1%',
    'class' => 'image',
    'add' => 'NOWRAP',
    'settings' => 'function',
    'theme' => array(
      'dropdown'=>false,
      'column'=>true
    ),
  );


$TABLE_CONFIG['syscolumns'] = array(
  'upload' => array ('theme'=>array('dropdown'=>false, 'column'=>true)),
  'edit' => array ('theme'=>array('dropdown'=>false, 'column'=>true)),
  'delete' => array ('theme'=>array('dropdown'=>false, 'column'=>false)),
  'info' => array ('theme'=>array('dropdown'=>false, 'column'=>true)),
  'history' => array ('theme'=>array('dropdown'=>false, 'column'=>false))
);