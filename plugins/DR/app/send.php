<?php
require("tmapy_config.inc");
require(FileUp2(".admin/run2_.inc"));
require(FileUp2(".admin/classes/DRKlient.inc"));
require(FileUp2(".admin/config.inc"));
require(FileUp2("html_header_full.inc"));

$ID = (int) $ID;
if (!$ID || $ID == 0) Die('chyba, nebyl predan parametr');
$q = new DB_POSTA;


$sql = 'select * from posta_plugins_dr_app_dorucenky where posta_id=' . $ID;
$q->query($sql);
if ($q->Num_Rows() == 0) {
  $sql = 'INSERT INTO posta_plugins_dr_app_dorucenky (POSTA_ID) VALUES (' . $ID. ')';
  $q->query($sql);
}

$upl = LoadClass('EedUpload', $ID);

$dorucenka = $odchozi = false;

foreach($upl->uplobj_records as $file) {
  if ($file['NAME'] == 'dorucenka.zfo') {$dorucenka = true; }
  if ($file['NAME'] == 'odchozi_datova_zprava.zfo') $odchozi = true;
}

if (!$dorucenka && !$odchozi) {
  require(FileUp2('html_footer.inc'));
  echo "<h1>Chyba:</h1>";
  echo "<p>Není uložená odchozí datová zprava a doručenka. Je nutné načíst v modulu DS = Doručenky.</p>";
  echo "<a href='#' class='btn' onclick='window.opener.document.location.reload(); '>Zavřít</a>";
  Die();
}

if (!$dorucenka && $typ=='DOR') {
  require(FileUp2('html_footer.inc'));
  echo "<h1>Chyba:</h1>";
  echo "<p>Doručenka ještě není k dispozici. Je nutné načíst v modulu DS = Doručenky pro kontrolu.</p>";
  echo "<a href='#' class='btn' onclick='window.opener.document.location.reload(); '>Zavřít</a>";
  Die();
}
$send_dorucenka = $send_odchozi = false;

if ($odchozi && $typ == 'ODZ') {
  echo "<h1>Odeslání ODZ:</h1>";
  $send_odchozi = true;
}

if ($dorucenka && $typ == 'DOR') {
  echo "<h1>Odeslání DOR:</h1>";
  $send_dorucenka = true;
}

if ($dorucenka && $typ == 'vse') {
  echo "<h1>Odeslání ODZ + DOR:</h1>";
  $send_dorucenka = true;
  $send_odchozi = true;
}

//zjistime APPID
$sql = 'select * from posta where id=' . $ID;
$q->query($sql);
$q->Next_Record();
$dalsi_id_agenda = $q->Record['DALSI_ID_AGENDA'];
list($typ, $app_id, $external_id) = explode('-', $dalsi_id_agenda);
list($ZdrojID, $HodnotaID ) = explode(':', $external_id);

$IDDZ = EedTools::getIDDZ($ID);

if (!$HodnotaID) {
  $ZdrojID = 'ISDS';
  $HodnotaID = $IDDZ;
}

if ($send_dorucenka) {

  $file = $upl->getFile('dorucenka.zfo');

  $dokument = array(
    'Identifikator' => array(
      'HodnotaID' => $HodnotaID,
      'ZdrojID' => $ZdrojID
    ),
    'Nazev' => $q->Record['VEC'],
    'DatumCasVytvoreni' => ConvertDatumToXML($q->Record['DATUM_PODATELNA_PRIJETI']),
    'Soubory' => array(
      "dmFile" =>
        array(
        "_" => '',
        'dmMimeType'=>$file[TYPEFILE], //mimetype, nevyuziva se
        'dmFileMetaType'=>'main', //druh pisemnosti, prvni musi byt typ main!
        'dmFileGuid'=>'', //interni oznaceni dokumentu, nepouziva se v DS
        'dmFileDescr'=>'DOR_' . $IDDZ . '.zfo', //popis souboru
  	    'dmEncodedContent'=>$upl->getContent($file),
      ),
    )
  );

  $klient = new Drklient($app_id);
  $vysledek = $klient->vlozPrilohu($dokument);
  if ($vysledek->StatusCode == '0000') {
    echo '<h2>OK: ' . $vysledek->StatusMessage . '</h2>';
    $vysl = $vysledek->Identifikatory->Identifikator->HodnotaID;
    echo '<p>ID: ' . $vysl . '</p>';
    $sql = 'update posta_plugins_dr_app_dorucenky set dorucenka=1 where posta_id=' . $ID;
    $q->query($sql);
  }
  else {
    echo '<h2>CHYBA: <br/>'.
    'Kod: ' . $vysledek->StatusCode . '<br/>'.
    'Text: ' . $vysledek->StatusMessage . '</h2>';
  }

}


if ($send_odchozi) {

  $file = $upl->getFile('odchozi_datova_zprava.zfo');
  $dokument = array(
    'Identifikator' => array(
      'HodnotaID' => $HodnotaID,
      'ZdrojID' => $ZdrojID
    ),
    'Nazev' => $q->Record['VEC'],
    'DatumCasVytvoreni' => ConvertDatumToXML($q->Record['DATUM_PODATELNA_PRIJETI']),
    'Soubory' => array(
      "dmFile" =>
        array(
        "_" => '',
        'dmMimeType'=>$file[TYPEFILE], //mimetype, nevyuziva se
        'dmFileMetaType'=>'main', //druh pisemnosti, prvni musi byt typ main!
        'dmFileGuid'=>'', //interni oznaceni dokumentu, nepouziva se v DS
        'dmFileDescr'=>'ODZ_' . $IDDZ . '.zfo', //popis souboru
  	    'dmEncodedContent'=>$upl->getContent($file),
//    	    'dmEncodedContent'=>'',
      ),
    )
  );

  $klient = new Drklient($app_id);
  $vysledek = $klient->vlozPrilohu($dokument);
  if ($vysledek->StatusCode == '0000') {
    echo '<h2>OK: ' . $vysledek->StatusMessage . '</h2>';
    $vysl = $vysledek->Identifikatory->Identifikator->HodnotaID;
    echo '<p>ID: ' . $vysl . '</p>';
    $sql = 'update posta_plugins_dr_app_dorucenky set odz=1 where posta_id=' . $ID;
    $q->query($sql);
  }
  else {
    echo '<h2>CHYBA: <br/>'.
    'Kod: ' . $vysledek->StatusCode . '<br/>'.
    'Text: ' . $vysledek->StatusMessage . '</h2>';
  }
}



echo "<a href='#' class='btn' onclick='window.opener.document.location.reload(); '>Zavřít</a>";
require(FileUp2('html_footer.inc'));
