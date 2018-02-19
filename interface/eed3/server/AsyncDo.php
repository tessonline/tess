<?php
require('tmapy_config.inc');
include(FileUp2('.admin/run2_.inc'));
require(FileUp2('.admin/soap_funkce.inc'));
require(FileUp2('.admin/fce.inc'));

require(FileUp2('.admin/isds_.inc'));
require_once(FileUp2('.admin/upload_.inc'));
require(FileUp2('.admin/upload_funkce.inc'));

//Asynchroni funkce a zpracovani
require('sps_Asyn_func.inc');
require('sps_ErmsAsyn.inc');

//Response
include('sps_Response.inc');

//Message
require('sps_Message.inc');


$q = new DB_POSTA;
$a = new DB_POSTA;
$sql = 'select * from posta_eed_udalosti where kod is null order by id asc';
$a->query($sql);

while ($a->Next_Record()) {

  $eedUdalostiId = $a->Record['ID'];
  $UdalostId = $a->Record['UDALOSTID'];
  $udalostRequest = $a->Record['UDALOST'];
  $davka = $a->Record['PORADI'];

  $kod = $a->Record['KOD'];
  $udalostData = unserialize($a->Record['HODNOTY']);

  if ($kod <> '') break; //jiz je uloha zpracovana nebo odmitnuta
  if ($udalostRequest=='DokumentOtevreni')
    $res = DokumentOtevreni($udalostData, $q, $sqlTranFce, $poradi, $response_Zprava, $log);
  elseif ($udalostRequest=='DokumentPostoupeni')
    $res = DokumentPostoupeni($udalostData, $q, $sqlTranFce, $poradi, $response_Zprava, $log);
  elseif ($udalostRequest=='DokumentUprava')
    $res = DokumentUprava($udalostData, $q, $sqlTranFce, $poradi, $response_Zprava, $log);
  elseif ($udalostRequest=='DokumentVlozeniDoSpisu')
    $res = DokumentVlozeniDoSpisu($udalostData, $q, $sqlTranFce, $poradi, $response_Zprava, $log);
  elseif ($udalostRequest=='DokumentVraceni')
    $res = DokumentVraceni($udalostData, $q, $sqlTranFce, $poradi, $response_Zprava, $log);
  elseif ($udalostRequest=='DokumentVyjmutiZeSpisu')
    $res = DokumentVyjmutiZeSpisu($udalostData, $q, $sqlTranFce, $poradi, $response_Zprava, $log);
  elseif ($udalostRequest=='DokumentZmenaZpracovatele')
    $res = DokumentZmenaZpracovatele($udalostData, $q, $sqlTranFce, $poradi, $response_Zprava, $log);
  elseif ($udalostRequest=='DokumentZruseni')
    $res = DokumentZruseni($udalostData, $q, $sqlTranFce, $poradi, $response_Zprava, $log);
  elseif ($udalostRequest=='DoruceniUprava')
    $res = DoruceniUprava($udalostData, $q, $sqlTranFce, $poradi, $response_Zprava, $log);
  elseif ($udalostRequest=='SouborNovaVerze')
    $res = SouborNovaVerze($udalostData, $q, $sqlTranFce, $poradi, $response_Zprava, $log);
  elseif ($udalostRequest=='SouborVlozitKDokumentu')
    $res = SouborVlozitKDokumentu($udalostData, $q, $sqlTranFce, $poradi, $response_Zprava, $log);
  elseif ($udalostRequest=='SouborVlozitKVypraveni')
    $res = SouborVlozitKVypraveni($udalostData, $q, $sqlTranFce, $poradi, $response_Zprava, $log);
  elseif ($udalostRequest=='SouborVyjmoutZVypraveni')
    $res = SouborVyjmoutZVypraveni($udalostData, $q, $sqlTranFce, $poradi, $response_Zprava, $log);
  elseif ($udalostRequest=='SouborZalozeni')
    $res = SouborZalozeni($udalostData, $q, $sqlTranFce, $poradi, $response_Zprava, $log);
  elseif ($udalostRequest=='SouborZruseni')
    $res = SouborZruseni($udalostData, $q, $sqlTranFce, $poradi, $response_Zprava, $log);
  elseif ($udalostRequest=='SpisOtevreni')
    $res = SpisOtevreni($udalostData, $q, $sqlTranFce, $poradi, $response_Zprava, $log);
  elseif ($udalostRequest=='SpisPostoupeni')
    $res = SpisPostoupeni($udalostData, $q, $sqlTranFce, $poradi, $response_Zprava, $log);
  elseif ($udalostRequest=='SpisVraceni')
    $res = SpisVraceni($udalostData, $q, $sqlTranFce, $poradi, $response_Zprava, $log);
  elseif ($udalostRequest=='SpisVyrizeni')
    $res = SpisVyrizeni($udalostData, $q, $sqlTranFce, $poradi, $response_Zprava, $log);
  elseif ($udalostRequest=='SpisZalozeni')
    $res = SpisZalozeni($udalostData, $q, $sqlTranFce, $poradi, $response_Zprava, $log);
  elseif ($udalostRequest=='SpisZmenaZpracovatele')
    $res = SpisZmenaZpracovatele($udalostData, $q, $sqlTranFce, $poradi, $response_Zprava, $log);
  elseif ($udalostRequest=='SpisZruseni')
    $res = SpisZruseni($udalostData, $q, $sqlTranFce, $poradi, $response_Zprava, $log);
  elseif ($udalostRequest=='VypraveniDoruceno')
    $res = VypraveniDoruceno($udalostData, $q, $sqlTranFce, $poradi, $response_Zprava, $log);
  elseif ($udalostRequest=='VypraveniPredatVypravne')
    $res = VypraveniPredatVypravne($udalostData, $q, $sqlTranFce, $poradi, $response_Zprava, $log);
  elseif ($udalostRequest=='VypraveniUprava')
    $res = VypraveniUprava($udalostData, $q, $sqlTranFce, $poradi, $response_Zprava, $log);
  elseif ($udalostRequest=='VypraveniVypraveno')
    $res = VypraveniVypraveno($udalostData, $q, $sqlTranFce, $poradi, $response_Zprava, $log);
  elseif ($udalostRequest=='VypraveniZalozeni')
    $res = VypraveniZalozeni($udalostData, $q, $sqlTranFce, $poradi, $response_Zprava, $log);
  elseif ($udalostRequest=='VypraveniZruseni')
    $res = VypraveniZruseni($udalostData, $q, $sqlTranFce, $poradi, $response_Zprava, $log);

  if ($response_Zprava['Kod'] <> '0000') {
    //musime stopnout vsechny ostatni davky
    $sql = "update posta_eed_udalosti set kod='".$response_Zprava['Kod']."',zpracovano='".$response_Zprava['DatumVzniku']."', popis='".$response_Zprava['Popis']."',chyba=1 where id=".$eedUdalostiId;
    $q->query($sql);
    $sql = "update posta_eed_udalosti set kod='".$response_Zprava['Kod']."',zpracovano='".$response_Zprava['DatumVzniku']."', popis='Nezpracovano pro chybu v udalosti ".$UdalostId." v davce ".$davka."',chyba=1 where kod is null";
    $q->query($sql);
  }
  else {
    $sql = "update posta_eed_udalosti set kod='".$response_Zprava['Kod']."', popis='".$response_Zprava['Popis']."', zpracovano='".$response_Zprava['DatumVzniku']."' where id=".$eedUdalostiId;
    $q->query($sql);
  }
}
echo 'ok';
