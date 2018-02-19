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
    'IdSpisu' => array('name' => 'IdSpisu', 'type' => 'tns:tIdSpisu')
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
    'Soubory'=>array('name'=>'Soubory','type'=>'tns:tFilesArray'),
    //Soubory
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
    //SouvisejiciSubjekty
//gSpolecneDokSpis<<
    'CjOdesilatel'=>array('name'=>'CjOdesilatel', 'type'=>'xsd:string', 'minOccurs'=>'0', 'maxLength'=>'50'),
    'DoplnujiciData'=>array('name'=>'DoplnujiciData', 'type'=>'tns:tDoplnujiciDataDokument', 'minOccurs'=>'0'),
    'Vypraveni'=>array('name'=>'Vypraveni', 'type'=>'tns:tZasilkaOdchozi'),

    //Vypraveni
    //'Soubory'=>array('name'=>'Soubory','type'=>'tns:tFileArry'),
  )
);

$server->wsdl->addComplexType(
  'ttDoruceni','complexType','struct','sequence','',
  array(
    'Odesilatel'=>array('name'=>'Odesilatel','type'=>'tns:tAdresat', 'nillable'=>'false'),
    'ZasilkaInfo'=>array('name'=>'ZasilkaInfo', 'type'=>'tns:tZasilkaInfo'),
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
  'tZasilkaOdchozi','complexType','struct','sequence','',
  array(
    'Identifikator'=>array('name'=>'Identifikator','type'=>'tns:tIdentifikator'),
    'Adresat'=>array('name'=>'Adresat','type'=>'tns:tAdresat', 'minOccurs'=>'0'),
    'ZasilkaInfo'=>array('name'=>'ZasilkaInfo', 'type'=>'tns:tZasilkaInfo'),
  )
);

$server->wsdl->addComplexType(
  'tZasilkaInfo','complexType','struct','sequence','',
  array(
    'IdZasilky'=>array('name'=>'IdZasilky', 'type'=>'xsd:string', 'maxLength'=>'50'),
    'ZpusobManipulaceId'=>array('name'=>'ZpusobManipulaceId', 'type'=>'xsd:string'),                                              
    'DatumVypraveni'=>array('name'=>'DatumVypraveni', 'type'=>'xsd:dateTime'),                                              
    'DatumDoruceni'=>array('name'=>'DatumDoruceni', 'type'=>'xsd:dateTime'),                                              
    'Poznamka'=>array('name'=>'Poznamka', 'type'=>'xsd:string'),                                              
  )
);


$server->wsdl->addComplexType(
  'tOperaceStatus','complexType','struct','sequence','',
  array(
    'Kod'=>array('name'=>'Kod', 'type'=>'xsd:string', 'maxLength'=>'20', 'nillable'=>'false'),                                              
    'Popis'=>array('name'=>'Popis', 'type'=>'xsd:string', 'nillable'=>'true', 'maxLength'=>'200'),                                          
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

$server->wsdl->addComplexType(
  'tIdSpisu','complexType','struct','sequence','',
  array(
    'Identifikator'=>array('name'=>'Identifikator','type'=>'tns:tIdentifikator'),
    //'DoplnujiciData'=>array('name'=>'DoplnujiciData', 'type'=>'tns:tDoplnujiciData', 'minOccurs'=>'0'),
  )
);

$server->wsdl->addComplexType(
  'tIdDokumenty','complexType','array','sequence','',
  array(
    'Identifikator'=>array('name'=>'Identifikator','type'=>'tns:tIdentifikator', 'nillable'=>'false', 'minOccurs'=>'0', 'maxOccurs'=>'unbounded'),
  )
);

$server->wsdl->addSimpleType('tUdalostId', 'xsd:int', 'simpleType', '', array());

