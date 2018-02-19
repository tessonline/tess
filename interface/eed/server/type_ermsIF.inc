<?php

// $server->wsdl->addComplexType(
//   'UdalostiRequestResponse ','complexType','array','sequence','',
//   array(
//     'UdalostiRequestResponse'=>array('name'=>'UdalostiRequestResponse', 'type'=>'tns:tUdalostiResponse', 'minOccurs'=>'0'),
//   )
// );

$server->wsdl->addComplexType(
  'UdalostiResponse','complexType','array','sequence','',
  array(
    'UdalostiResponse'=>array('name'=>'UdalostiResponse', 'type'=>'tns:tZpravy', 'minOccurs'=>'0'),
  )
);

// $server->wsdl->addComplexType(
//   'tUdalostiResponse','complexType','array','sequence','',
//   array(
//     'tUdalostiResponse'=>array('name'=>'tUdalostiResponse', 'type'=>'tns:tZpravy', 'minOccurs'=>'0'),
//   )
// );
//

$server->wsdl->addComplexType(
  'tZpravy','complexType','struct','sequence','',
  array(
    'Zprava'=>array('name'=>'Zprava', 'type'=>'tns:tZprava', 'nillable'=>'false'),
  )
);

?>