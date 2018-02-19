<?php

$server->wsdl->addComplexType(
  'tZpravy','complexType','struct','sequence','',
  array(
    'Zprava'=>array('name'=>'Zprava', 'type'=>'tns:tZprava', 'nillable'=>'false'),
  )
);

?>