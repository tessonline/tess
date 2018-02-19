<?php
require("tmapy_config.inc");
include(FileUp2(".admin/brow_.inc"));
include(FileUp2(".admin/classes/EedRadar.inc"));
require(FileUp2('html_header_full.inc'));
$USER_INFO = $GLOBALS["POSTA_SECURITY"]->GetUserInfo();
$id_user=$USER_INFO["ID"];
$last_date=Date('Y-m-d');
$last_time=Date('H:i:s');
$datum=date('d.m.Y H:m');


$file = 'testPO.xml';

$xml = simplexml_load_file($file, 'SimpleXMLElement',LIBXML_NOCDATA);

    $ns = $xml->getNamespaces(true);;
    $ess = $xml->children($ns['ess']);

    $id = EedRadar::getIDKonfigurace();
    $q = new DB_POSTA;
    $q->query('select * from posta where id=' . $id);
    $q->Next_Record(); $data = $q->Record;

    $doc = $ess->Spis->SouvisejiciSubjekty->SouvisejiciSubjekt->Subjekt->DoplnujiciData;
    $role = $doc->addChild('pr:Role','', 'http://www.vitasw.cz/NS/Prestupky');

    $oznamovatel = $role->addChild('Oznamovatel');

//    $oznamovatel->SpisovyZnak = '276.11';

    if ($data['ODES_TYP'] == 'U' || $data['ODES_TYP'] == 'P') {
      $oznamovatel->Subjekt->TypSubjektu = 'Pravnicka';
      $oznamovatel->Subjekt->ObchodniNazev = $data['ODESL_PRIJMENI'];
      $oznamovatel->Subjekt->IC = $data['ODESL_ICO'];
    }
    else {
      $oznamovatel->Subjekt->TypSubjektu = 'Fyzicka';
      $oznamovatel->Subjekt->Prijmeni = $data['ODESL_PRIJMENI'];
      $oznamovatel->Subjekt->Jmeno = $data['ODESL_JMENO'];
    }
    $oznamovatel->Subjekt->Adresy->AdresaPostovni->Obec = $data['ODESL_POSTA'];
    $oznamovatel->Subjekt->Adresy->AdresaPostovni->Ulice = $data['ODESL_ULICE'];
    $oznamovatel->Subjekt->Adresy->AdresaPostovni->OrientacniCislo = $data['ODESL_COR'];
    $oznamovatel->Subjekt->Adresy->AdresaPostovni->PopisneCislo = $data['ODESL_CP'];
    $oznamovatel->Subjekt->Adresy->AdresaPostovni->Psc = $data['ODESL_PSC'];
    $oznamovatel->Subjekt->Adresy->AdresaPostovni->Zeme = 'CZ';
    echo $xml->asXML();


/*
       <ess:Subjekt>
          <ess:TypSubjektu>Pravnicka</ess:TypSubjektu>
          <ess:ObchodniNazev>GE CAPITAL MULTISERVIS A S</ess:ObchodniNazev>
          <ess:IC>49241150</ess:IC>
          <ess:Adresy>
            <ess:AdresaPostovni>
              <ess:Obec>PRAHA 4</ess:Obec>
              <ess:CastObce></ess:CastObce>
              <ess:MestskaCast></ess:MestskaCast>
              <ess:Ulice>VYSKOCILOVA</ess:Ulice>
              <ess:OrientacniCislo></ess:OrientacniCislo>
              <ess:PopisneCislo>1422</ess:PopisneCislo>
              <ess:Psc>14000</ess:Psc>
              <ess:Zeme>CZ</ess:Zeme>
            </ess:AdresaPostovni>


   $data['%SUBJEKT_JMENO%'] = ($subjekt->TypSubjektu == 'Fyzicka' ? $subjekt->Jmeno.' ' . $subjekt->Prijmeni : (string)$subjekt->ObchodniNazev);
    $data['%SUBJEKT_IC%'] = ($subjekt->TypSubjektu == 'Fyzicka' ? (string)$subjekt->DatumNarozeni[0] : (string)$subjekt->IC);

*/

