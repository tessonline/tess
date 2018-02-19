<?php

$server->wsdl->addComplexType(
  'tAutorizace','complexType','struct','sequence','',
  array(
    'provedlKdo'=>array('name'=>'provedlKdo', 'type'=>'xsd:string', 'maxLength'=>'50', 'nillable'=>'false'),
    'provedlKdy'=>array('name'=>'provedlKdy', 'type'=>'xsd:dateTime', 'nillable'=>'false'),
  )
);

$server->wsdl->addComplexType(
  'tDoplnujiciDataDokument','complexType','struct','sequence','',
  array(
    'PocetListu'=>array('name'=>'PocetListu', 'type'=>'xsd:int'),
    'PocetPriloh'=>array('name'=>'PocetPriloh', 'type'=>'xsd:int'),
    'DruhPriloh'=>array('name'=>'DruhPriloh', 'type'=>'xsd:string'),
  )
);

$server->wsdl->addComplexType(
  'tDorucenyDokument','complexType','struct','sequence','',
  array(
    'Identifikator'=>array('name'=>'Identifikator','type'=>'tns:tIdentifikator'),
//gSpolecneDokSpis>>
    'Nazev'=>array('name'=>'Nazev', 'type'=>'xsd:string', 'maxLength'=>'100'),
    'Popis'=>array('name'=>'Popis', 'type'=>'xsd:string', 'minOccurs'=>'0', 'maxLength'=>'255'),
    'CisloJednaci'=>array('name'=>'CisloJednaci', 'type'=>'xsd:string', 'minOccurs'=>'0', 'maxLength'=>'50'),
    'SpisovaZnacka'=>array('name'=>'SpisovaZnacka', 'type'=>'xsd:string', 'minOccurs'=>'0', 'maxLength'=>'50'),
    'PodaciDenikPoradi'=>array('name'=>'PodaciDenikPoradi', 'type'=>'xsd:int', 'minOccurs'=>'0', 'minInclusive'=>'1', 'maxInclusive'=>'2147483647'),
    'PodaciDenikRok'=>array('name'=>'PodaciDenikRok', 'type'=>'xsd:gYear'),
    'PodaciDenik'=>array('name'=>'PodaciDenik', 'type'=>'xsd:string', 'minOccurs'=>'0', 'maxLength'=>'12'),
    'DatumCasVytvoreni'=>array('name'=>'DatumCasVytvoreni', 'type'=>'xsd:dateTime'),
    'TypDokumentu'=>array('name'=>'TypDokumentu', 'type'=>'xsd:string', 'minOccurs'=>'0', 'maxLength'=>'100'),
    'SpisovyPlan'=>array('name'=>'SpisovyPlan', 'type'=>'xsd:string', 'minOccurs'=>'0', 'maxLength'=>'100'),
    'SpisovyZnak'=>array('name'=>'SpisovyZnak', 'type'=>'xsd:string', 'minOccurs'=>'0', 'maxLength'=>'255'),
    'SkartacniZnak'=>array('name'=>'SkartacniZnak', 'type'=>'xsd:string', 'minOccurs'=>'0', 'length'=>'1'), //<xs:enumeration value="A"/>,<xs:enumeration value="S"/>,<xs:enumeration value="V"/>
    'SkartacniLhuta'=>array('name'=>'SkartacniLhuta', 'type'=>'xsd:unsignedShort', 'minOccurs'=>'0', 'minInclusive'=>'1', 'maxInclusive'=>'999'),
    'Poznamka'=>array('name'=>'Poznamka', 'type'=>'xsd:string', 'minOccurs'=>'0', 'maxLength'=>'255'),
    //Zmocneni
    //SouvisejiciSubjekty
//gSpolecneDokSpis<<
    'CjOdesilatel'=>array('name'=>'CjOdesilatel', 'type'=>'xsd:string', 'minOccurs'=>'0', 'maxLength'=>'50'),
    'DoplnujiciData'=>array('name'=>'DoplnujiciData', 'type'=>'tns:tDoplnujiciDataDokument', 'minOccurs'=>'0'),
    'Doruceni'=>array('name'=>'Doruceni','type'=>'tns:ttDoruceni', 'nillable'=>'false'),
    //Soubory
  )
);
//addComplexType($name,$typeClass='complexType',$phpType='array',$compositor='',$restrictionBase='',$elements=array(),$attrs=array(),$arrayType=''){

$server->wsdl->addComplexType(
  'tFile',
  'attribute',
  'struct',
  'sequence',
  '',
  array(
    'dmEncodedContent'=>array('name'=>'dmEncodedContent', 'type'=>'xsd:base64Binary'), //mimetype, nevyuziva se
    'dmXMLContent'=>array('name'=>'dmXMLContent', 'type'=>'xsd:string','minOccurs'=>'0'), //mimetype, nevyuziva se
  ),
  array(
    'dmMimeType'=>array('name'=>'dmMimeType', 'type'=>'xsd:string',  'use' => 'required'), //mimetype, nevyuziva se
    'dmFileMetaType'=>array('name'=>'dmFileMetaType', 'type'=>'xsd:string',  'use' => 'required'), //druh pisemnosti, prvni musi byt typ main!
    'dmFileGuid'=>array('name'=>'dmFileGuid', 'type'=>'xsd:string',  'use' => 'optional'), //interni oznaceni dokumentu, nepouziva se v DS
    'dmUpFileGuid'=>array('name'=>'dmUpFileGuid', 'type'=>'xsd:string', 'use'=>'optional'), //interni oznaceni dokumentu, nepouziva se v DS
    'dmFileDescr'=>array('name'=>'dmFileDescr', 'type'=>'xsd:string',  'use' => 'required'), //popis souboru
    'dmFormat'=>array('name'=>'dmFormat', 'type'=>'xsd:string',  'use' => 'optional'), //nepovinne,
  )
);

$server->wsdl->addComplexType(
  'dmFiles',
  'complexType',
  'array',
  'sequence',
  '',
  array(
    'dmFile'=>array('name'=>'dmFile', 'type'=>'tns:tFile', 'maxOccurs'=>"unbounded"), //mimetype, nevyuziva se
  )
);


$server->wsdl->addComplexType(
  'tVlastniDokument','complexType','struct','sequence','',
  array(
    'Identifikator'=>array('name'=>'Identifikator','type'=>'tns:tIdentifikator'),
//gSpolecneDokSpis>>
    'Nazev'=>array('name'=>'Nazev', 'type'=>'xsd:string', 'maxLength'=>'100'),
    'Popis'=>array('name'=>'Popis', 'type'=>'xsd:string', 'minOccurs'=>'0', 'maxLength'=>'255'),
    'CisloJednaci'=>array('name'=>'CisloJednaci', 'type'=>'xsd:string', 'minOccurs'=>'0', 'maxLength'=>'50'),
    'SpisovaZnacka'=>array('name'=>'SpisovaZnacka', 'type'=>'xsd:string', 'minOccurs'=>'0', 'maxLength'=>'50'),
    'PodaciDenikPoradi'=>array('name'=>'PodaciDenikPoradi', 'type'=>'xsd:int', 'minOccurs'=>'0', 'minInclusive'=>'1', 'maxInclusive'=>'2147483647'),
    'PodaciDenikRok'=>array('name'=>'PodaciDenikRok', 'type'=>'xsd:gYear'),
    'PodaciDenik'=>array('name'=>'PodaciDenik', 'type'=>'xsd:string', 'minOccurs'=>'0', 'maxLength'=>'12'),
    'DatumCasVytvoreni'=>array('name'=>'DatumCasVytvoreni', 'type'=>'xsd:dateTime'),
    'TypDokumentu'=>array('name'=>'TypDokumentu', 'type'=>'xsd:string', 'minOccurs'=>'0', 'maxLength'=>'100'),
    'SpisovyPlan'=>array('name'=>'SpisovyPlan', 'type'=>'xsd:string', 'minOccurs'=>'0', 'maxLength'=>'100'),
    'SpisovyZnak'=>array('name'=>'SpisovyZnak', 'type'=>'xsd:string', 'minOccurs'=>'0', 'maxLength'=>'255'),
    'SkartacniZnak'=>array('name'=>'SkartacniZnak', 'type'=>'xsd:string', 'minOccurs'=>'0', 'length'=>'1'), //<xs:enumeration value="A"/>,<xs:enumeration value="S"/>,<xs:enumeration value="V"/>
    'SkartacniLhuta'=>array('name'=>'SkartacniLhuta', 'type'=>'xsd:unsignedShort', 'minOccurs'=>'0', 'minInclusive'=>'1', 'maxInclusive'=>'999'),
    'Poznamka'=>array('name'=>'Poznamka', 'type'=>'xsd:string', 'minOccurs'=>'0', 'maxLength'=>'255'),
    //Zmocneni
    'SouvisejiciSubjekty'=>array('name'=>'SouvisejiciSubjekty', 'type'=>'tns:tSouvisejiciSubjekty'),
//gSpolecneDokSpis<<
    'CjOdesilatel'=>array('name'=>'CjOdesilatel', 'type'=>'xsd:string', 'minOccurs'=>'0', 'maxLength'=>'50'),
    'DoplnujiciData'=>array('name'=>'DoplnujiciData', 'type'=>'tns:tDoplnujiciDataDokument', 'minOccurs'=>'0'),
    'Vypraveni'=>array('name'=>'Vypraveni','type'=>'tns:ttVypraveni', 'nillable'=>'false'),
    'Soubory'=>array('name'=>'Soubory','type'=>'tns:dmFiles', 'minOccurs'=>'0'),
   )
);

$server->wsdl->addComplexType(
  'tCelyDokument','complexType','struct','sequence','',
  array(
    'Identifikator'=>array('name'=>'Identifikator','type'=>'tns:tIdentifikator'),
//gSpolecneDokSpis>>
    'Nazev'=>array('name'=>'Nazev', 'type'=>'xsd:string', 'maxLength'=>'100'),
    'Popis'=>array('name'=>'Popis', 'type'=>'xsd:string', 'minOccurs'=>'0', 'maxLength'=>'255'),
    'CisloJednaci'=>array('name'=>'CisloJednaci', 'type'=>'xsd:string', 'minOccurs'=>'0', 'maxLength'=>'50'),
    'SpisovaZnacka'=>array('name'=>'SpisovaZnacka', 'type'=>'xsd:string', 'minOccurs'=>'0', 'maxLength'=>'50'),
    'PodaciDenikPoradi'=>array('name'=>'PodaciDenikPoradi', 'type'=>'xsd:int', 'minOccurs'=>'0', 'minInclusive'=>'1', 'maxInclusive'=>'2147483647'),
    'PodaciDenikRok'=>array('name'=>'PodaciDenikRok', 'type'=>'xsd:gYear'),
    'PodaciDenik'=>array('name'=>'PodaciDenik', 'type'=>'xsd:string', 'minOccurs'=>'0', 'maxLength'=>'12'),
    'DatumCasVytvoreni'=>array('name'=>'DatumCasVytvoreni', 'type'=>'xsd:dateTime'),
    'TypDokumentu'=>array('name'=>'TypDokumentu', 'type'=>'xsd:string', 'minOccurs'=>'0', 'maxLength'=>'100'),
    'SpisovyPlan'=>array('name'=>'SpisovyPlan', 'type'=>'xsd:string', 'minOccurs'=>'0', 'maxLength'=>'100'),
    'SpisovyZnak'=>array('name'=>'SpisovyZnak', 'type'=>'xsd:string', 'minOccurs'=>'0', 'maxLength'=>'255'),
    'SkartacniZnak'=>array('name'=>'SkartacniZnak', 'type'=>'xsd:string', 'minOccurs'=>'0', 'length'=>'1'), //<xs:enumeration value="A"/>,<xs:enumeration value="S"/>,<xs:enumeration value="V"/>
    'SkartacniLhuta'=>array('name'=>'SkartacniLhuta', 'type'=>'xsd:unsignedShort', 'minOccurs'=>'0', 'minInclusive'=>'1', 'maxInclusive'=>'999'),
    'Poznamka'=>array('name'=>'Poznamka', 'type'=>'xsd:string', 'minOccurs'=>'0', 'maxLength'=>'255'),
    //Zmocneni
    //SouvisejiciSubjekty
//gSpolecneDokSpis<<
    'CjOdesilatel'=>array('name'=>'CjOdesilatel', 'type'=>'xsd:string', 'minOccurs'=>'0', 'maxLength'=>'50'),
    'DoplnujiciData'=>array('name'=>'DoplnujiciData', 'type'=>'tns:tDoplnujiciDataDokument', 'minOccurs'=>'0'),
    'Vypraveni'=>array('name'=>'Vypraveni','type'=>'tns:ttVypraveni'),
    'Doruceni'=>array('name'=>'Doruceni','type'=>'tns:ttDoruceni'),
    //Soubory
  )
);

$server->wsdl->addComplexType(
  'ttDoruceni','complexType','struct','sequence','',
  array(
    'Odesilatel'=>array('name'=>'Odesilatel','type'=>'tns:tAdresat', 'nillable'=>'false'),
    'Adresat'=>array('name'=>'Adresat','type'=>'tns:tAdresat', 'minOccurs'=>'0'),
    'ZasilkaInfo'=>array('name'=>'ZasilkaInfo', 'type'=>'tns:tZasilkaInfo'),
    'Soubory'=>array('name'=>'Soubory','type'=>'tns:dmFiles', 'minOccurs'=>'0'),
  )
);

$server->wsdl->addComplexType(
  'ttVypraveni','complexType','struct','sequence','',
  array(
    'Odesilatel'=>array('name'=>'Odesilatel','type'=>'tns:tAdresat', 'nillable'=>'false'),
    'Adresat'=>array('name'=>'Adresat','type'=>'tns:tAdresat', 'minOccurs'=>'0'),
    'ZasilkaInfo'=>array('name'=>'ZasilkaInfo', 'type'=>'tns:tZasilkaInfo'),
    'Soubory'=>array('name'=>'Soubory','type'=>'tns:dmFiles', 'minOccurs'=>'0'),
  )
);

$server->wsdl->addComplexType(
  'tZasilka','complexType','struct','sequence','',
  array(
    'Odesilatel'=>array('name'=>'Odesilatel','type'=>'tns:tAdresat', 'minOccurs'=>'0'),
    'Adresat'=>array('name'=>'Adresat','type'=>'tns:tAdresat', 'minOccurs'=>'0'),
    'ZasilkaInfo'=>array('name'=>'ZasilkaInfo', 'type'=>'tns:tZasilkaInfo'),
  )
);

$server->wsdl->addComplexType(
  'tZasilkaInfo','complexType','struct','sequence','',
  array(
    'IdZasilky'=>array('name'=>'IdZasilky', 'type'=>'xsd:string', 'maxLength'=>'50', 'nillable'=>'false'),                                              
    'ZpusobManipulaceId'=>array('name'=>'ZpusobManipulaceId', 'type'=>'xsd:string'),                                              
    'DatumVypraveni'=>array('name'=>'DatumVypraveni', 'type'=>'xsd:dateTime'),                                              
    'DatumDoruceni'=>array('name'=>'DatumDoruceni', 'type'=>'xsd:dateTime'),                                              
    'Poznamka'=>array('name'=>'Poznamka', 'type'=>'xsd:string'),                                              
  )
);


$server->wsdl->addComplexType(
  'tOperaceStatus','complexType','struct','sequence','',
  array(
    'StatusCode'=>array('name'=>'StatusCode', 'type'=>'xsd:string', 'maxLength'=>'20', 'nillable'=>'false'),
    'StatusMessage'=>array('name'=>'StatusMessage', 'type'=>'xsd:string'),                                          
  )
);

$server->wsdl->addComplexType(
  'tProfilSpisu','complexType','struct','sequence','',
  array(
    'Identifikator'=>array('name'=>'Identifikator','type'=>'tns:tIdentifikator'),
//gSpolecneDokSpis>>
    'Nazev'=>array('name'=>'Nazev', 'type'=>'xsd:string', 'maxLength'=>'100'),
    'Popis'=>array('name'=>'Popis', 'type'=>'xsd:string', 'minOccurs'=>'0', 'maxLength'=>'255'),
    'CisloJednaci'=>array('name'=>'CisloJednaci', 'type'=>'xsd:string', 'minOccurs'=>'0', 'maxLength'=>'50'),
    'SpisovaZnacka'=>array('name'=>'SpisovaZnacka', 'type'=>'xsd:string', 'minOccurs'=>'0', 'maxLength'=>'50'),
    'PodaciDenikPoradi'=>array('name'=>'PodaciDenikPoradi', 'type'=>'xsd:int', 'minOccurs'=>'0', 'minInclusive'=>'1', 'maxInclusive'=>'2147483647'),
    'PodaciDenikRok'=>array('name'=>'PodaciDenikRok', 'type'=>'xsd:gYear'),
    'PodaciDenik'=>array('name'=>'PodaciDenik', 'type'=>'xsd:string', 'minOccurs'=>'0', 'maxLength'=>'12'),
    'DatumCasVytvoreni'=>array('name'=>'DatumCasVytvoreni', 'type'=>'xsd:dateTime'),
    'TypDokumentu'=>array('name'=>'TypDokumentu', 'type'=>'xsd:string', 'minOccurs'=>'0', 'maxLength'=>'100'),
    'SpisovyPlan'=>array('name'=>'SpisovyPlan', 'type'=>'xsd:string', 'minOccurs'=>'0', 'maxLength'=>'100'),
    'SpisovyZnak'=>array('name'=>'SpisovyZnak', 'type'=>'xsd:string', 'minOccurs'=>'0', 'maxLength'=>'255'),
    'SkartacniZnak'=>array('name'=>'SkartacniZnak', 'type'=>'xsd:string', 'minOccurs'=>'0', 'length'=>'1'), //<xs:enumeration value="A"/>,<xs:enumeration value="S"/>,<xs:enumeration value="V"/>
    'SkartacniLhuta'=>array('name'=>'SkartacniLhuta', 'type'=>'xsd:unsignedShort', 'minOccurs'=>'0', 'minInclusive'=>'1', 'maxInclusive'=>'999'),
    'Poznamka'=>array('name'=>'Poznamka', 'type'=>'xsd:string', 'minOccurs'=>'0', 'maxLength'=>'255'),
    //Zmocneni
    //SouvisejiciSubjekty
//gSpolecneDokSpis<<
    'DoplnujiciData'=>array('name'=>'DoplnujiciData', 'type'=>'tns:tDoplnujiciDataSpis'),
  )
);

$server->wsdl->addComplexType(
  'tDoplnujiciDataSpis','complexType','struct','sequence','',
  array(
    'ZpusobVedeni'=>array('name'=>'ZpusobVedeni', 'type'=>'xsd:string'),
  )
);

$server->wsdl->addComplexType(
  'tIdDokument','complexType','struct','sequence','',
  array(
    'Identifikator'=>array('name'=>'Identifikator','type'=>'tns:tIdentifikator'),
    //'DoplnujiciData'=>array('name'=>'DoplnujiciData', 'type'=>'tns:tDoplnujiciData', 'minOccurs'=>'0'),
  )
);

$server->wsdl->addSimpleType('tUdalostId', 'xsd:int', 'simpleType', '', array());

