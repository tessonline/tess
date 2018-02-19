<?php
use tmapy\jasperserver\File;

require_once(FileUp2('.config/config_posta.inc'));
$config = TW_AppConfig::getInstance('ders-uk-test');

$PROPERTIES = array(
  'AGENDA_NAME' => 'Statistika počtu dokumentů ', 
  'AGENDA_IDENT' => 'pocet_dokumentu', 
  'AGENDA_DESCRIPTION' => 'Statistika počtu dokumentů s grafem',
  'JASPER' => array(
    'type' => array('app', 'table', 'row'),
    'category' => array('statistika'),
    'format' => array('pdf','xlsx','docx','rtf','html'),
    'fileName' => 'pocet_dokumentu',
    'rightName' => 'REPORT-Počet dokumentů',
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
