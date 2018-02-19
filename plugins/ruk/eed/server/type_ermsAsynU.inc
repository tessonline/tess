<?php

$server->wsdl->addComplexType(
  'tZprava','complexType','struct','sequence','',
  array(
    'Kod'=>array('name'=>'Kod', 'type'=>'xsd:string', 'maxLength'=>'8', 'nillable'=>'false'),
    'Popis'=>array('name'=>'Popis', 'type'=>'xsd:string', 'maxLength'=>'255', 'nillable'=>'true'),
  ),
  array(
    'UdalostId' => array('name' => 'UdalostId', 'type' => 'tns:tUdalostId', 'use'=>'required'),
    'Poradi' => array('name' => 'Poradi', 'type' => 'xsd:string', 'use'=>'required'),
    'DatumVzniku' => array('name' => 'DatumVzniku', 'type' => 'xsd:dateTime'),
  )
);

?>