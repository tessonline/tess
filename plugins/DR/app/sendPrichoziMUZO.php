<?php
require(FileUp2(".admin/classes/DRKlientMUZO.inc"));

$username = $q->Record['KLIENT_USERNAME'];
$passwd = $q->Record['KLIENT_PASSWD'];

$ID = (int) $ID;
if (!$ID || $ID == 0) Die('chyba, nebyl predan parametr');
$q = new DB_POSTA;

$upl = LoadClass('EedUpload', $ID);


//zjistime APPID
$sql = 'select * from posta where id=' . $ID;
$q->query($sql);
$q->Next_Record();

$IDDZ = EedTools::getIDDZ($ID);

$dz = LoadClass('EedDatovaZprava', $IDDZ);
$zprava = $dz->getDZinfo($IDDZ);

$typ_adr = strtr($q->Record['ODES_TYP'], $typ_odesl_tess2unispis);

$xml = '<?xml version = "1.0" encoding = "UTF-8"?>
<SOAP-ENV:Envelope xmlns:SOAP-ENV="http://schemas.xmlsoap.org/soap/envelope/" xmlns:ns1="http://mvcr.cz/ess/v_1.0.0.0"
                   xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance" xmlns:ns2="http://isds.czechpoint.cz/v20"
                   xmlns:ns3="http://ess.bbm/"
                   xmlns:ns4="http://docs.oasis-open.org/wss/2004/01/oasis-200401-wss-wssecurity-secext-1.0.xsd">
    <SOAP-ENV:Header>
        <ns4:Security SOAP-ENV:mustUnderstand="1">
            <ns4:UsernameToken>
                <ns4:Username>' . $username . '</ns4:Username>
                <ns4:Password>' . $passwd . '</ns4:Password>
            </ns4:UsernameToken>
        </ns4:Security>
    </SOAP-ENV:Header>
    <SOAP-ENV:Body>
        <ns3:vlozDokument>
            <Dokument>
                <ns1:Identifikator>
                    <ns1:HodnotaID>' . $IDDZ . '</ns1:HodnotaID>
                    <ns1:ZdrojID>ISDS</ns1:ZdrojID>
                </ns1:Identifikator>
                <ns1:Nazev>'.mb_substr($q->Record['VEC'], 0, 100) . '</ns1:Nazev>
                <ns1:Popis>'.mb_substr($q->Record['VEC'], 0, 100) . '</ns1:Popis>
                <ns1:DatumCasVytvoreni>'.substr($zprava['dmAcceptanceTime'],0,-3) . '</ns1:DatumCasVytvoreni>
                <ns1:CjOdesilatel>' . $zprava['dmSenderRefNumber'] . '</ns1:CjOdesilatel>
                <ns1:Doruceni>
                    <ns1:Odesilatel>
                        <ns1:Subjekt>
                            <ns1:Identifikator>
                                <ns1:HodnotaID>' . $IDDZ . '</ns1:HodnotaID>
                                <ns1:ZdrojID>DR</ns1:ZdrojID>
                            </ns1:Identifikator>
                            <ns1:TypSubjektu>' . $typ_adr . '</ns1:TypSubjektu>
                            <ns1:ObchodniNazev>' . $q->Record['ODESL_PRIJMENI']  . ' '. $q->Record['ODESL_JMENO'] . '</ns1:ObchodniNazev>
                            <ns1:IC>' . $q->Record['ODESL_ICO'] . '</ns1:IC>
                            <ns1:Adresy>
                                <ns1:AdresaPostovni>
                                    <ns1:Obec>' . $q->Record['ODESL_POSTA'] . '</ns1:Obec>
                                    <ns1:Ulice>' . $q->Record['ODESL_ULICE'] . '</ns1:Ulice>
                                    <ns1:EvidencniCislo>' . $q->Record['ODESL_CP'] . '</ns1:EvidencniCislo>
                                    <ns1:OrientacniCislo>' . $q->Record['ODESL_COR'] . '</ns1:OrientacniCislo>
                                    <ns1:Psc>' . $q->Record['ODESL_PSC'] . '</ns1:Psc>
                                    <ns1:Zeme>CZ</ns1:Zeme>
                                </ns1:AdresaPostovni>
                            </ns1:Adresy>
                            <ns1:DoplnujiciData>
                                <ns1:DoplnujiciDataSPSL xsi:type="ns1:DoplnujiciDataSPSL">
                                    <ns1:SenderType>' . $typ_adr . '</ns1:SenderType>
                                </ns1:DoplnujiciDataSPSL>
                            </ns1:DoplnujiciData>
                        </ns1:Subjekt>
                        <ns1:Adresa>
                            <ns1:AdresaDS>
                                <ns1:IdDb>' . $q->Record['ODESL_DATSCHRANKA'] . '</ns1:IdDb>
                            </ns1:AdresaDS>
                        </ns1:Adresa>
                    </ns1:Odesilatel>
                    <ns1:Adresat>
                        <ns1:Subjekt>
                            <ns1:Identifikator>
                                <ns1:HodnotaID>piyj9b4</ns1:HodnotaID>
                                <ns1:ZdrojID>uk.e-podatelna.ruk</ns1:ZdrojID>
                            </ns1:Identifikator>
                            <ns1:TypSubjektu>Neurceno</ns1:TypSubjektu>
                            <ns1:ObchodniNazev>Univerzita Karlova</ns1:ObchodniNazev>
                            <ns1:IC>00216208</ns1:IC>
                            <ns1:Adresy>
                                <ns1:AdresaPostovni>
                                    <ns1:Obec>Praha 1</ns1:Obec>
                                    <ns1:Ulice>Ovocný trh</ns1:Ulice>
                                    <ns1:EvidencniCislo>5</ns1:EvidencniCislo>
                                    <ns1:OrientacniCislo>560</ns1:OrientacniCislo>
                                    <ns1:Psc>11000</ns1:Psc>
                                    <ns1:Zeme>CZ</ns1:Zeme>
                                </ns1:AdresaPostovni>
                            </ns1:Adresy>
                        </ns1:Subjekt>
                        <ns1:Adresa>
                            <ns1:AdresaDS>
                                <ns1:IdDb>piyj9b4</ns1:IdDb>
                            </ns1:AdresaDS>
                        </ns1:Adresa>
                    </ns1:Adresat>
                    <ns1:ZasilkaInfo>
                        <ns1:ZpusobManipulaceId>DatovaSchranka</ns1:ZpusobManipulaceId>
                        <ns1:ZpusobZachazeniText>'.($q->Record['PRIVATE'] =='1' ? 'do_vl_rukou' : '') . '</ns1:ZpusobZachazeniText>
                        <ns1:DatumVypraveni>'.mb_substr($zprava['dmDeliveryTime'],0, strpos($zprava['dmDeliveryTime'],'T')) . '</ns1:DatumVypraveni>
                        <ns1:DatumDoruceni>'.mb_substr($zprava['dmAcceptanceTime'],0, strpos($zprava['dmDeliveryTime'],'T')) . '</ns1:DatumDoruceni>
                        <ns1:dmID>' . $IDDZ . '</ns1:dmID>
                    </ns1:ZasilkaInfo>
                </ns1:Doruceni>
                SOUBORY
            </Dokument>
        </ns3:vlozDokument>
    </SOAP-ENV:Body>
</SOAP-ENV:Envelope>
';



/*
                <ns1:Soubory>
                    <ns2:dmFile dmMimeType="application/pdf" dmFileMetaType="enclosure"
                                dmFileDescr="odpoved_zverejneni.pdf">
                        <ns2:dmEncodedContent>
                        </ns2:dmEncodedContent>
                    </ns2:dmFile>
                    <ns2:dmFile dmMimeType="text/xml" dmFileMetaType="main" dmFileDescr="odpoved_zverejneni.xml">
                        <ns2:dmEncodedContent>
                        </ns2:dmEncodedContent>
                    </ns2:dmFile>
                    <ns2:dmFile dmMimeType="application/vnd.software602.filler.form-xml-zip" dmFileMetaType="signature"
                                dmFileDescr="DDZ_419641095.zfo">
                        <ns2:dmEncodedContent>
                        </ns2:dmEncodedContent>
                    </ns2:dmFile>
                </ns1:Soubory>

*/


$soubory = '<ns1:Soubory>';
$jeISRS = false;
foreach($upl->uplobj_records as $file) {
  if ($file['NAME'] == 'odpoved_zverejneni.xml') $jeISRS = true;
  if ($file['NAME'] == 'odpoved_modifikace.xml') $jeISRS = true;
  if ($file['NAME'] == 'odpoved_znepristupneni.xml') $jeISRS = true;
  if ($file['NAME'] == 'chyba.xml') $jeISRS = true;
}
foreach($upl->uplobj_records as $file) {
  $name = $file['NAME'];
  $typ = 'enclosure';

  if ($file['NAME'] == 'prichozi_datova_zprava.zfo' && !$jeISRS) {
    $name = 'DDZ_' . $IDDZ . '.zfo';
    $typ = 'main';
  }

  if ($file['NAME'] == 'odpoved_zverejneni.xml' && $jeISRS) {
    $typ = 'main';
  }

  if ($file['NAME'] == 'odpoved_modifikace.xml' && $jeISRS) {
    $typ = 'main';
  }

  if ($file['NAME'] == 'odpoved_znepristupneni.xml' && $jeISRS) {
    $typ = 'main';
  }

  if ($file['NAME'] == 'chyba.xml' && $jeISRS) {
    $typ = 'main';
  }

  if ($file['NAME'] == 'dorucenka_'.$IDDZ.'.zfo') {
    $name = 'DOR_' . $IDDZ . '.zfo';
  }

$soubory.='
                    <ns2:dmFile dmMimeType="' . $file[TYPEFILE] . '" dmFileMetaType="' . $typ . '" dmFileDescr="' . $name . '">
                        <ns2:dmEncodedContent>' . base64_encode($upl->getContent($file)) . '
                        </ns2:dmEncodedContent>
                    </ns2:dmFile>
';
  $pocet ++;
}
$soubory .= '</ns1:Soubory>';


$dokument = str_replace('SOUBORY',$soubory, $xml);

$sql = 'select * from posta_plugins_dr_app where id='.$app_id;
$q->query($sql);
$q->Next_Record();
$emaily = $q->Record['EMAILY'];
$so = $q->Record['SUPERODBOR'] ? $q->Record['SUPERODBOR'] : 0;

$file = '/tmp/vystup.xml';
$fp = fopen($file, 'w');
fwrite($fp, $dokument);
fclose($fp);
$klient = new DrklientMUZO($app_id);
$vysledek = $klient->vlozDokument($dokument);

if ($vysledek->StatusCode == '0000') {
  echo '<h2>OK: ' . $vysledek->StatusMessage . '</h2>';
  $vysl = $vysledek->Identifikatory->Identifikator->HodnotaID;
  echo '<p>ID: ' . $vysl . '</p>';
  $sql = "update posta set stav=stav+1,superodbor=$so,datum_vyrizeni='" . Date('Y-m-d H:i:s'). "', status=9 where id=" . $ID;
  $q->query($sql);
  include_once(FileUp2('plugins/emaily/.admin/emaily_funkce.inc'));
  if (strlen($emaily)>3)
    OdesliEmail('nova_datova_zprava_dr', $emaily,$datum,$vec,$IDDZ,'ESSS UK','Nová datová zpráva');


}
else {
  echo '<h2>CHYBA: <br/>'.
  'Kod: ' . $vysledek->StatusCode . '<br/>'.
  'Text: ' . $vysledek->StatusMessage . '</h2>';
}

echo "<a href='#' class='btn' onclick='window.opener.document.location.reload(); '>Zavřít</a>";
require(FileUp2('html_footer.inc'));
