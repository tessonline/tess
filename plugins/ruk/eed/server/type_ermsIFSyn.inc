<?php

$server->wsdl->addComplexType(
  'ttDokumentyVlozene_response','complexType','struct','sequence','',
  array(
    'DokumentZkracenyVlozeny'=>array('name'=>'DokumentZkracenyVlozeny','type'=>'tns:ttDokumentZkracenyVlozeny'),
  )
);

$server->wsdl->addComplexType(
  'ttDokumentZkracenyVlozeny','complexType','struct','sequence','',
  array(
    'IdDokument'=>array('name'=>'IdDokument','type'=>'tns:tIdDokument', 'nillable'=>'false'),
    'CisloJednaci'=>array('name'=>'CisloJednaci', 'type'=>'xsd:string', 'maxLength'=>'50'),
    'PodaciDenikPoradi'=>array('name'=>'PodaciDenikPoradi', 'type'=>'xsd:int', 'minOccurs'=>'0', 'minInclusive'=>'1', 'maxInclusive'=>'2147483647'),
    'PodaciDenikRok'=>array('name'=>'PodaciDenikRok', 'type'=>'xsd:gYear', 'minOccurs'=>'0'),
    'PodaciDenik'=>array('name'=>'PodaciDenik', 'type'=>'xsd:string', 'minOccurs'=>'0', 'maxLength'=>'12'),
  )
);
/*
$server->wsdl->addComplexType(
  'tIdDb','SimpleType','struct','sequence','',
  array(
    'DbID'=>array('name'=>'DbID','type'=>'xsd:string', 'maxLength'=>'7'),
  )
);


$server->wsdl->addComplexType(
  'tIdentificationNumber','SimpleType','struct','sequence','',
  array(
    'tIdentificationNumber'=>array('name'=>'tIdentificationNumber','type'=>'xsd:string', 'maxLength'=>'11'),
  )
);
*/
$server->wsdl->addComplexType(
  'tDbOwnerInfo','complexType','struct','all','',
  array(
//    'dbID'=>array('name'=>'dbID','type'=>'tns:tIdDb', 'nillable'=>'true'),
//    'dbType'=>array('name'=>'dbType','type'=>'tns:tIdDb', 'nillable'=>'true'),
//    'ic'=>array('name'=>'ic','type'=>'tns:tIdentificationNumber', 'nillable'=>'true'),
    'dbID'=>array('name'=>'dbID','type'=>'xsd:string', 'nillable'=>'true'),
    'dbType'=>array('name'=>'dbType','type'=>'xsd:string', 'nillable'=>'true'),
    'ic'=>array('name'=>'ic','type'=>'xsd:string', 'nillable'=>'true'),
    'pnFirstName'=>array('name'=>'pnFirstName','type'=>'xsd:string', 'nillable'=>'true'),
    'pnMiddleName'=>array('name'=>'pnMiddleName','type'=>'xsd:string', 'nillable'=>'true'),
    'pnLastName'=>array('name'=>'pnLastName','type'=>'xsd:string', 'nillable'=>'true'),
    'pnLastNameAtBirth'=>array('name'=>'pnLastNameAtBirth','type'=>'xsd:string', 'nillable'=>'true'),
    'firmName'=>array('name'=>'firmName','type'=>'xsd:string', 'nillable'=>'true'),
    'biDate'=>array('name'=>'biDate','type'=>'xsd:string', 'nillable'=>'true'),
    'biCity'=>array('name'=>'biCity','type'=>'xsd:string', 'nillable'=>'true'),
    'biCounty'=>array('name'=>'biCounty','type'=>'xsd:string', 'nillable'=>'true'),
    'biState'=>array('name'=>'biState','type'=>'xsd:string', 'nillable'=>'true'),
    'adCity'=>array('name'=>'adCity','type'=>'xsd:string', 'nillable'=>'true'),
    'adStreet'=>array('name'=>'adStreet','type'=>'xsd:string', 'nillable'=>'true'),
    'adNumberInStreet'=>array('name'=>'adNumberInStreet','type'=>'xsd:string', 'nillable'=>'true'),
    'adNumberInMunicipality'=>array('name'=>'adNumberInMunicipality','type'=>'xsd:string', 'nillable'=>'true'),
    'adZipCode'=>array('name'=>'adZipCode','type'=>'xsd:string', 'nillable'=>'true'),
    'adState'=>array('name'=>'adState','type'=>'xsd:string', 'nillable'=>'true'),
    'nationality'=>array('name'=>'nationality','type'=>'xsd:string', 'nillable'=>'true'),
  )
);


$server->wsdl->addComplexType(
  'tDbOwnersArray','complexType','array','sequence','',
  array(
    'DbOwnerInfo'=>array('name'=>'DbOwnerInfo','type'=>'tns:tDbOwnerInfo', 'maxOccurs'=>'unbounded', 'minOccurs'=>'0', 'nillable'=>'true'),
  )
);

