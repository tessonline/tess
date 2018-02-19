<?php
require_once(FileUp2('plugins/npu/.admin/classes/PKident.inc'));
include_once(FileUp2(".admin/upload_.inc"));
$uplobj = Upload(array('create_only_objects'=>true,'agenda'=>'POSTA','noshowheader'=>true));

$GLOBALS['chyby']['R1'] = 'Není vyplněn spisový znak. Opravte to prosím.';


$GLOBALS['chyby'] = array(
  10 => 'Není zadána věcná klasifikace',
  38 => 'Chybí Ukládací značka k spisu zakládanému ve spisovně.',
  47 => 'Nemůže být dříve Termín než Přišlo dne.',
  48 => 'Nemůže být dříve Vyřízeno než Přišlo dne.',
  53 => 'Nemůže být dříve Zpracováno dne než Přiděleno dne.',


  76 => 'Chybí fáze k dané klasifikaci.',
  77 => 'Pro danou klasifikaci se fáze neurčuje.',
  78 => 'Pro vyřízený spis musí být určena i věcná klasifikace.',
  81 => 'Pokud <b>Přišlo jak</b> je vlastní, pak věcná fáze může být jen vyjádření vlastní, vč. návrhu, případně ostatní.',
  82 => 'Pokud <b>Přišlo jak</b> není vlastní, pak věcná fáze nemůže být vyjádření vlastní, vč. návrhu.',

  95 => 'K dané věcné klasifikaci musí být i odkaz na památku (nebo je chybně určena věcná klasifikace)',
  96 => 'K dané věcné klasifikaci nesmí být odkaz na památku (nebo je chybně určena věcná klasifikace)',

);

$q = new DB_POSTA;
$d = new DB_MONUMNIS;


$chyba = array();
//  Die(print_r($GLOBALS['CONFIG']['DEFAULT_UKLZNACKA']));


$sql = " select odeslana_posta from posta where id=" . $spis_id;

$q->query($sql); $q->Next_Record();
$doc = $q->Record;

if ($doc['ODESLANA'] == 'f')
  $sql = " select *,
   to_timestamp(DATUM_PODATELNA_PRIJETI,'FMDD.FMMM.YYYY HH24:MI') < to_timestamp(DATUM_VYRIZENI,'FMDD.FMMM.YYYY HH24:MI') AS ok_vyrizeni,
   to_timestamp(DATUM_PODATELNA_PRIJETI,'FMDD.FMMM.YYYY HH24:MI') < to_timestamp(DATUM_REFERENT_PRIJETI,'FMDD.FMMM.YYYY HH24:MI') AS ok_precetl,
   to_timestamp(DATUM_PODATELNA_PRIJETI,'FMDD.FMMM.YYYY HH24:MI') < LHUTA_VYRIZENI AS ok_lhuty
   from posta where id=" . $spis_id;
else
$sql = " select *,
 to_timestamp(DATUM_PODATELNA_PRIJETI,'FMDD.FMMM.YYYY HH24:MI') < to_timestamp(DATUM_VYPRAVENI,'FMDD.FMMM.YYYY HH24:MI') AS ok_vyrizeni,
 1 AS ok_precetl,
 to_timestamp(DATUM_PODATELNA_PRIJETI,'FMDD.FMMM.YYYY HH24:MI') < LHUTA_VYRIZENI AS ok_lhuty
 from posta where id=" . $spis_id;
$q->query($sql); $q->Next_Record();
$doc = $q->Record;

//47 - Nemůže být dříve Termín než Přišlo dne.
if ($doc["OK_LHUTY"] == 'f') $chyba[] = 47;
//48 - Nemůže být dříve Vyřízeno než Přišlo dne.
//  if ($doc["OK_VYRIZENI"] == 'f') $chyba[] = 48;
//53 - Nemůže být dříve Zpracováno dne než Přiděleno dne.
if ($doc["OK_PRECETL"] == 'f') $chyba[] = 53;

$klasifikace = $doc['TYP_POSTY']?$doc['TYP_POSTY']:0;
$faze = $doc['JINE']?$doc['JINE']:0;

$EedCj = LoadClass('EedCj', $spis_id);
$docIDS = $EedCj->GetDocsInCj($spis_id);
foreach($docIDS as $doc) {
  $pom =  PKIdent::getCountOfIdent($doc);
  if ($pom>0) $pocet_pam = $pom;
}

if ($klasifikace>0) {
  $sql = 'select * from cis_posta_typ where id='.$klasifikace;
  $q->query($sql); $q->Next_Record();

  // 76 - Chybí fáze k dané klasifikaci.
  if ($q->Record['FAZE'] == 1 && $faze == 0) $chyba[] = 76;
  // 77 - Pro danou klasifikaci se fáze neurčuje.
  if ($q->Record['FAZE'] == 0 && $faze>0) $chyba[] = 77;

  //95 - K dané věcné klasifikaci musí být i odkaz na památku (nebo je chybně určena věcná klasifikace) [tabulka Spis_vecklasif - v číselníku zpřesněn obsah sloupce Kpam pro zjednodušení křížové kontroly VecKlasif a odkazů na památky ve SpisPam: hodnota = 1 -> odkaz na památku musí být; hodnota = -1 -> odkaz na památku nesmí být (je-li, je chybně určena věcná klasifikace)
  if ($q->Record['KPAM'] == 1 && $pocet_pam == 0)  $chyba[] = 95;

  //96 - K dané věcné klasifikaci nesmí být odkaz na památku (nebo je chybně určena věcná klasifikace)
  if ($q->Record['KPAM'] == 0 && $pocet_pam > 0) $chyba[] = 96;

}
else {
 // 78 - Pro vyřízený spis musí být určena i věcná klasifikace.
 $chyba[] = 78;
}

// 81 - Pokud Přišlo jak je vlastní, pak věcná fáze může být jen vyjádření vlastní, vč. návrhu, případně ostatní.
//if ($doc['ODESLANA_POSTA'] == 't' && $doc['JINE']<>7) $chyba[] = 81;

// 82 - Pokud Přišlo jak není vlastní, pak věcná fáze nemůže být vyjádření vlastní, vč. návrhu.
if ($doc['ODESLANA_POSTA']<>'t' && $doc['JINE'] == 7) $chyba[] = 82;


