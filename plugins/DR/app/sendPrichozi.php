<?php
require("tmapy_config.inc");
require(FileUp2(".admin/run2_.inc"));
require(FileUp2(".admin/classes/DRKlient.inc"));
require(FileUp2("interface/.admin/soap_funkce.inc"));
require(FileUp2(".admin/config.inc"));
require(FileUp2("html_header_full.inc"));

$ID = (int) $ID;
if (!$ID || $ID == 0) Die('chyba, nebyl predan parametr');
$q = new DB_POSTA;

$upl = LoadClass('EedUpload', $ID);


//zjistime APPID
$sql = 'select * from posta where id=' . $ID;
$q->query($sql);
$q->Next_Record();
$stav = $q->Record['STAV'];
$app_id = floor(($stav-1000)/10);

$IDDZ = EedTools::getIDDZ($ID);
$dz = LoadClass('EedDatovaZprava', $IDDZ);
$zprava = $dz->getDZinfo($IDDZ);

$sql = 'select * from posta_plugins_dr_app where id='.$app_id;
$q->query($sql);
$q->Next_Record();
$muzo_klient = $q->Record['KLIENT_MUZO'];
if ($muzo_klient>0) {
  include('sendPrichoziMUZO.php');
  Die();
}
$sql = 'select * from posta where id=' . $ID;
$q->query($sql);
$q->Next_Record();


$typ_adr = strtr($q->Record['ODES_TYP'], $typ_odesl_tess2unispis);

$cjodesl =
$dokument = array(
  'Identifikator' => array(
    'HodnotaID' => $IDDZ,
    'ZdrojID' => 'ISDS'
  ),
  'Nazev' => mb_substr($q->Record['VEC'], 0, 100),
  'DatumCasVytvoreni' => substr($zprava['dmAcceptanceTime'],0,-3),
  'CjOdesilatel' => $zprava['dmSenderRefNumber'],
  'Doruceni' => array(
    'Odesilatel' => array(
      'Subjekt' => array(
        'Identifikator' => array(
          'HodnotaID' => $IDDZ,
          'ZdrojID' => 'DR'
        ),
        'TypSubjektu' => $typ_adr,
        'ObchodniNazev' => $q->Record['ODESL_PRIJMENI'],
        'Prijmeni' => mb_substr($q->Record['ODESL_PRIJMENI'], 0, 35),
        'Jmeno' => $q->Record['ODESL_JMENO'],
        'IC' => $q->Record['ODESL_ICO'],
        'Adresy' => array(
          'AdresaPostovni' => array(
            'Obec' => $q->Record['ODESL_POSTA'],
            'Ulice' => $q->Record['ODESL_ULICE'],
            'EvidencniCislo' => $q->Record['ODESL_CP'],
            'OrientacniCislo' => $q->Record['ODESL_COR'],
            'Psc' => $q->Record['ODESL_PSC'],
            'Zeme' => 'CZ'
          )
        ),
        'DoplnujiciData' => array(
          'DoplnujiciDataSPSL' => array(
            'SenderType' => $typ_adr
          ),
        ),
      ),
      'Adresa' => array(
        'AdresaDS' => array(
          'IdDb' => $q->Record['ODESL_DATSCHRANKA']
        )
      )
    ),
    'ZasilkaInfo' => array(
      'ZpusobManipulaceId' =>'DatovaSchranka',
      'ZpusobZachazeniText' => ($q->Record['PRIVATE'] =='1' ? 'do_vl_rukou' : ''),
      'DatumVypraveni' => mb_substr($zprava['dmDeliveryTime'],0, strpos($zprava['dmDeliveryTime'],'T')),
      'DatumDoruceni' => mb_substr($zprava['dmAcceptanceTime'],0, strpos($zprava['dmDeliveryTime'],'T')),
      'dmID' => $IDDZ,
    )
  ),
  'Soubory' => array()
);

$add = array();
//$add['DoplnujiciDataSPSL']->SenderType = $typ_adr;

$temp1 = array(
  'ns1:FormaDokumentu' => 'D'
);

$temp = array(
  'ns1:SenderType' => $typ_adr,
);

$temp2 = array(
  'ns1:TypDokumentu' => new SoapVar($temp1, SOAP_ENC_OBJECT, '', '', 'TypDokumentu' )
);


//$add['ns1:DoplnujiciDataSPSL'] = new SoapVar($temp2, SOAP_ENC_OBJECT, 'ns1:DoplnujiciDataSPSL', '', 'SenderType' );;
$add['ns1:DoplnujiciDataSPSL'] = new SoapVar($temp2, SOAP_ENC_OBJECT, '', '', 'SenderType' );;
$dokument['DoplnujiciData'] = new SoapVar($add, SOAP_ENC_OBJECT, '', 'ns2', 'SenderType' );

$add2['ns1:DoplnujiciDataSPSL'] = new SoapVar($temp, SOAP_ENC_OBJECT, 'ns1:DoplnujiciDataSPSL', '', 'SenderType' );;
$dokument['Doruceni']['Odesilatel']['Subjekt']['DoplnujiciData'] = new SoapVar($add2, SOAP_ENC_OBJECT, '', 'ns2', 'SenderType' );



//print_r($dokument); Die();
$vec =  $q->Record['VEC'];
$datum = $q->Record['DATUM_PODATELNA_PRIJETI'];

$pocet = 1;



foreach($upl->uplobj_records as $file) {
  $name = $file['NAME'];
  $typ = 'enclosure';

  if ($file['NAME'] == 'prichozi_datova_zprava.zfo') {
    $name = 'DDZ_' . $IDDZ . '.zfo';
    $typ = 'main';
  }

  if ($file['NAME'] == 'dorucenka_'.$IDDZ.'.zfo') {
    $name = 'DOR_' . $IDDZ . '.zfo';
  }

  $dokument[Soubory][dmFile][] = array(
      "_" => '',
      'dmMimeType'=>$file[TYPEFILE], //mimetype, nevyuziva se
      'dmFileMetaType'=>$typ, //druh pisemnosti, prvni musi byt typ main!
//      'dmFileGuid'=>$file[DIRECTORY], //interni oznaceni dokumentu, nepouziva se v DS
      'dmFileGuid'=>'', //interni oznaceni dokumentu, nepouziva se v DS
      'dmFileDescr'=>$name, //popis souboru
	    'dmEncodedContent'=>$upl->getContent($file),
  );
  $pocet ++;
}


$sql = 'select * from posta_plugins_dr_app where id='.$app_id;
$q->query($sql);
$q->Next_Record();
$emaily = $q->Record['EMAILY'];
$so = $q->Record['SUPERODBOR'] ? $q->Record['SUPERODBOR'] : 0;

$klient = new Drklient($app_id);
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
