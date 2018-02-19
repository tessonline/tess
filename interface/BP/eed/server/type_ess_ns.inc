<?php

$server->wsdl->addComplexType(
  'tIdentifikator','complexType','struct','sequence','',
  array(
    $GLOBALS["soap"]["namespace_ess"].'HodnotaID'=>array('name'=>'HodnotaID', 'type'=>'xsd:string', 'maxLength'=>'50'),
    $GLOBALS["soap"]["namespace_ess"].'ZdrojID'=>array('name'=>'ZdrojID', 'type'=>'xsd:string', 'maxLength'=>'50')
  )
);

$server->wsdl->addComplexType(
  'tAdresat','complexType','struct','sequence','',
  array(
    $GLOBALS["soap"]["namespace_ess"].'Subjekt'=>array('name'=>'Subjekt', 'type'=>'tns:tSubjekt'),
    $GLOBALS["soap"]["namespace_ess"].'Adresa'=>array('name'=>'Adresa', 'type'=>'tns:tAdresa')
  )
);

$server->wsdl->addComplexType(
  'tSubjekt','complexType','struct','sequence','',
  array(
    $GLOBALS["soap"]["namespace_ess"].'Identifikator'=>array('name'=>'Identifikator', 'type'=>'tns:tIdentifikator', 'minOccurs'=>'0', 'maxOccurs'=>'unbounded'),
    $GLOBALS["soap"]["namespace_ess"].'TypSubjektu'=>array('name'=>'TypSubjektu', 'type'=>'xsd:string'), //Neurceno, Fyzicka, Osvc, Pravnicka, Zamestnanec, Utvar
    $GLOBALS["soap"]["namespace_ess"].'ObchodniNazev'=>array('name'=>'ObchodniNazev', 'type'=>'xsd:string', 'minOccurs'=>'0', 'maxLength'=>'255'),
    $GLOBALS["soap"]["namespace_ess"].'DatumNarozeni'=>array('name'=>'DatumNarozeni', 'type'=>'xsd:date', 'minOccurs'=>'0'),
    $GLOBALS["soap"]["namespace_ess"].'MistoNarozeni'=>array('name'=>'MistoNarozeni', 'type'=>'xsd:string', 'minOccurs'=>'0', 'maxLength'=>'48'),
    $GLOBALS["soap"]["namespace_ess"].'Jmeno'=>array('name'=>'Jmeno', 'type'=>'xsd:string', 'minOccurs'=>'0', 'maxLength'=>'24'),
    $GLOBALS["soap"]["namespace_ess"].'Prijmeni'=>array('name'=>'Prijmeni', 'type'=>'xsd:string', 'minOccurs'=>'0', 'maxLength'=>'35'),
    $GLOBALS["soap"]["namespace_ess"].'Osloveni'=>array('name'=>'Osloveni', 'type'=>'xsd:string', 'minOccurs'=>'0', 'maxLength'=>'50'),
    $GLOBALS["soap"]["namespace_ess"].'TitulPred'=>array('name'=>'TitulPred', 'type'=>'xsd:string', 'minOccurs'=>'0', 'maxLength'=>'35'),
    $GLOBALS["soap"]["namespace_ess"].'TitulZa'=>array('name'=>'TitulZa', 'type'=>'xsd:string', 'minOccurs'=>'0', 'maxLength'=>'10'),
    $GLOBALS["soap"]["namespace_ess"].'FunkceUtvarPopis'=>array('name'=>'FunkceUtvarPopis', 'type'=>'xsd:string', 'minOccurs'=>'0', 'maxLength'=>'100'),
    $GLOBALS["soap"]["namespace_ess"].'FunkceUtvarIdentifikator'=>array('name'=>'FunkceUtvarIdentifikator', 'type'=>'xsd:string', 'minOccurs'=>'0', 'maxLength'=>'100'),
    $GLOBALS["soap"]["namespace_ess"].'Poznamka'=>array('name'=>'Poznamka', 'type'=>'xsd:string', 'minOccurs'=>'0', 'maxLength'=>'255'),
    $GLOBALS["soap"]["namespace_ess"].'Adresy'=>array('name'=>'Adresy', 'type'=>'tns:tAdresy'),
    //DoplnujiciData
  )
);

//  'tDokument','complexType','struct','sequence','',
/*
$server->wsdl->addComplexType(
  'tDokument','complexType','struct','sequence','',
  array(
    $GLOBALS["soap"]["namespace_ess"].'Identifikator'=>array('name'=>'Identifikator','type'=>'tns:tIdentifikator'),
//gSpolecneDokSpis>>
    $GLOBALS["soap"]["namespace_ess"].'Nazev'=>array('name'=>'Nazev', 'type'=>'xsd:string', 'maxLength'=>'100'),
    $GLOBALS["soap"]["namespace_ess"].'Popis'=>array('name'=>'Popis', 'type'=>'xsd:string', 'minOccurs'=>'0', 'maxLength'=>'255'),
    $GLOBALS["soap"]["namespace_ess"].'CisloJednaci'=>array('name'=>'CisloJednaci', 'type'=>'xsd:string', 'minOccurs'=>'0', 'maxLength'=>'50'),
    $GLOBALS["soap"]["namespace_ess"].'SpisovaZnacka'=>array('name'=>'SpisovaZnacka', 'type'=>'xsd:string', 'minOccurs'=>'0', 'maxLength'=>'50'),
    $GLOBALS["soap"]["namespace_ess"].'PodaciDenikPoradi'=>array('name'=>'PodaciDenikPoradi', 'type'=>'xsd:int', 'minOccurs'=>'0', 'minInclusive'=>'1', 'maxInclusive'=>'2147483647'),
    $GLOBALS["soap"]["namespace_ess"].'PodaciDenikRok'=>array('name'=>'PodaciDenikRok', 'type'=>'xsd:gYear'),
    $GLOBALS["soap"]["namespace_ess"].'PodaciDenik'=>array('name'=>'PodaciDenik', 'type'=>'xsd:string', 'minOccurs'=>'0', 'maxLength'=>'12'),
    $GLOBALS["soap"]["namespace_ess"].'DatumCasVytvoreni'=>array('name'=>'DatumCasVytvoreni', 'type'=>'xsd:dateTime'),
    $GLOBALS["soap"]["namespace_ess"].'TypDokumentu'=>array('name'=>'TypDokumentu', 'type'=>'xsd:string', 'minOccurs'=>'0', 'maxLength'=>'100'),
    $GLOBALS["soap"]["namespace_ess"].'SpisovyPlan'=>array('name'=>'SpisovyPlan', 'type'=>'xsd:string', 'minOccurs'=>'0', 'maxLength'=>'100'),
    $GLOBALS["soap"]["namespace_ess"].'SpisovyZnak'=>array('name'=>'SpisovyZnak', 'type'=>'xsd:string', 'minOccurs'=>'0', 'maxLength'=>'255'),
    $GLOBALS["soap"]["namespace_ess"].'SkartacniZnak'=>array('name'=>'SkartacniZnak', 'type'=>'xsd:string', 'minOccurs'=>'0', 'length'=>'1'), //<xs:enumeration value="A"/>,<xs:enumeration value="S"/>,<xs:enumeration value="V"/>
    $GLOBALS["soap"]["namespace_ess"].'SkartacniLhuta'=>array('name'=>'SkartacniLhuta', 'type'=>'xsd:unsignedShort', 'minOccurs'=>'0', 'minInclusive'=>'1', 'maxInclusive'=>'999'),
    $GLOBALS["soap"]["namespace_ess"].'Poznamka'=>array('name'=>'Poznamka', 'type'=>'xsd:string', 'minOccurs'=>'0', 'maxLength'=>'255'),
    //Zmocneni
    //SouvisejiciSubjekty
//gSpolecneDokSpis<<
    $GLOBALS["soap"]["namespace_ess"].'CjOdesilatel'=>array('name'=>'CjOdesilatel', 'type'=>'xsd:string', 'minOccurs'=>'0', 'maxLength'=>'50'),
    $GLOBALS["soap"]["namespace_ess"].'Vypraveni'=>array('name'=>'Vypraveni', 'type'=>'tns:tZasilka', 'minOccurs'=>'0'),
    $GLOBALS["soap"]["namespace_ess"].'Doruceni'=>array('name'=>'Doruceni','type'=>'tns:tZasilka', 'nillable'=>'false'),
    //Soubory
    //Souvisejici
  )
);
*/
$server->wsdl->addComplexType(
  'tProfilDokumentu','complexType','struct','sequence','',
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
    'Vypraveni'=>array('name'=>'Vypraveni', 'type'=>'tns:tZasilka', 'minOccurs'=>'0'),
    'Doruceni'=>array('name'=>'Doruceni','type'=>'tns:tZasilka', 'nillable'=>'false'),
    //Soubory
    //Souvisejici
  )
);

$server->wsdl->addComplexType(
  'tAdresa','complexType','struct','choice','',
  array(
    $GLOBALS["soap"]["namespace_ess"].'AdresaPostovni'=>array('name'=>'AdresaPostovni', 'type'=>'tns:tAdresaPostovni'),
    //'AdresaDS'=>array('name'=>'AdresaDS', 'type'=>'tns:tAdresaDS'),
    //'AdresaElektronicka'=>array('name'=>'AdresaElektronicka', 'type'=>'tns:tAdresaElektronicka')
  )
);

$server->wsdl->addComplexType(
  'tAdresy','complexType','struct','sequence','',
  array(
    //'AdresaPostovni'=>array('name'=>'AdresaPostovni', 'type'=>'tns:tAdresaPostovni', 'minOccurs'=>'0', 'maxOccurs'=>'unbounded'),
    //'AdresaDS'=>array('name'=>'AdresaDS', 'type'=>'tns:tAdresaDS', 'minOccurs'=>'0'),
    //'AdresaElektronicka'=>array('name'=>'AdresaElektronicka', 'type'=>'tns:tAdresaElektronicka', 'minOccurs'=>'0', 'maxOccurs'=>'unbounded')
  )
);

$server->wsdl->addComplexType(
  'tAdresaPostovni','complexType','struct','sequence','',
  array(
    $GLOBALS["soap"]["namespace_ess"].'Identifikator'=>array('name'=>'Identifikator', 'type'=>'tns:tIdentifikator', 'minOccurs'=>'0'),
    $GLOBALS["soap"]["namespace_ess"].'Obec'=>array('name'=>'Obec', 'type'=>'xsd:string', 'minOccurs'=>'0', 'maxLength'=>'48'),
    $GLOBALS["soap"]["namespace_ess"].'CastObce'=>array('name'=>'CastObce', 'type'=>'xsd:string', 'minOccurs'=>'0', 'maxLength'=>'48'),
    $GLOBALS["soap"]["namespace_ess"].'MestskaCast'=>array('name'=>'MestskaCast', 'type'=>'xsd:string', 'minOccurs'=>'0', 'maxLength'=>'48'),
    $GLOBALS["soap"]["namespace_ess"].'Ulice'=>array('name'=>'Ulice', 'type'=>'xsd:string', 'minOccurs'=>'0', 'maxLength'=>'48'),
    $GLOBALS["soap"]["namespace_ess"].'EvidencniCislo'=>array('name'=>'EvidencniCislo', 'type'=>'xsd:string', 'minOccurs'=>'0', 'maxLength'=>'4'),
    $GLOBALS["soap"]["namespace_ess"].'OrientacniCislo'=>array('name'=>'OrientacniCislo', 'type'=>'xsd:string', 'minOccurs'=>'0', 'maxLength'=>'6'),
    $GLOBALS["soap"]["namespace_ess"].'PopisneCislo'=>array('name'=>'PopisneCislo', 'type'=>'xsd:string', 'minOccurs'=>'0'),
    $GLOBALS["soap"]["namespace_ess"].'Psc'=>array('name'=>'Psc', 'type'=>'xsd:string', 'minOccurs'=>'0', 'maxLength'=>'10'),
    $GLOBALS["soap"]["namespace_ess"].'Zeme'=>array('name'=>'Zeme', 'type'=>'xsd:string', 'minOccurs'=>'0', 'minLength'=>'2', 'maxLength'=>'3'),
    $GLOBALS["soap"]["namespace_ess"].'RuianVazba'=>array('name'=>'RuianVazba', 'type'=>'xsd:string', 'minOccurs'=>'0', 'maxLength'=>'100'),
    $GLOBALS["soap"]["namespace_ess"].'Poznamka'=>array('name'=>'Poznamka', 'type'=>'xsd:string', 'minOccurs'=>'0', 'maxLength'=>'255'),
    $GLOBALS["soap"]["namespace_ess"].'POBOX'=>array('name'=>'POBOX', 'type'=>'xsd:string', 'minOccurs'=>'0', 'maxLength'=>'10'),
    $GLOBALS["soap"]["namespace_ess"].'TypAdresy'=>array('name'=>'TypAdresy', 'type'=>'xsd:string', 'minOccurs'=>'0'), //Neurceno,Dorucovaci,TrvaleBydliste,PrechodneBydliste,SidloFirmy,PobockaFirmy
    $GLOBALS["soap"]["namespace_ess"].'DodaciPosta'=>array('name'=>'DodaciPosta', 'type'=>'xsd:string', 'minOccurs'=>'0'),
    $GLOBALS["soap"]["namespace_ess"].'Okres'=>array('name'=>'Okres', 'type'=>'xsd:string', 'minOccurs'=>'0', 'maxLength'=>'48'),
  )
);


