<?php
use tmapy\jasperserver\File;

require_once(FileUp2('.config/config_posta.inc'));
$config = TW_AppConfig::getInstance('ders-uk-test');

$PROPERTIES = array(
  'AGENDA_NAME' => 'Testovací sestava ', 
  'AGENDA_IDENT' => 'test_parametry', 
  'AGENDA_DESCRIPTION' => 'Testovací sestava pro test předávaných parametrů',
  'JASPER' => array(
    'type' => array('app', 'table', 'row'),
    'category' => array('statistika'),
    'format' => array('xlsx','docx'),
    'fileName' => 'test_parametry',
    'rightName' => 'REPORT-Testovací sestava',
    'parameters' => array(
      'zakaznik' => 'Nazev zakaznika'
    ),
    'files' => array(
      array(
        'localFilePath' => 'images/tmapy_inverse.png',
        'repositoryPath' => 'images', 
        'label' => 'tmapy_inverse.png',
        'type' => File::TYPE_IMG
      )
    )    
  )
);

return $PROPERTIES;
