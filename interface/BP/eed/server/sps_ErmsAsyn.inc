<?php

$GLOBALS['async_fce'] = array(
  'DokumentOtevreni',
  'DokumentPostoupeni',
  'DokumentUprava',
  'DokumentVlozeniDoSpisu',
  'DokumentVraceni',
  'DokumentVyjmutiZeSpisu',
  'DokumentZmenaZpracovatele',
  'DokumentZruseni',
  'DoruceniUprava',
  'SouborNovaVerze',
  'SouborVlozitKDokumentu',
  'SouborVlozitKVypraveni',
  'SouborVyjmoutZVypraveni',
  'SouborZalozeni',
  'SouborZruseni',
  'SpisOtevreni',
  'SpisPostoupeni',
  'SpisVraceni',
  'SpisVyrizeni',
  'SpisZalozeni',
  'SpisZmenaZpracovatele',
  'SpisZruseni',
  'VypraveniDoruceno',
  'VypraveniPredatVypravne',
  'VypraveniUprava',
  'VypraveniVypraveno',
  'VypraveniZalozeni',
  'VypraveniZruseni'
);

//Funkce zpracovavajici asyn. funkce v davce...
function BPermsAsyn($Udalosti, $poradi, $app_id) {
  //nastaveni parametru
  global $server, $soap;


  $q=new DB_POSTA;
  $q->ShowError = false;
	$q->Error_Die = false;

  $cil = $server->methodparams['!Cil'];
  $datumVzniku = $server->methodparams['!DatumVzniku'];
  $poradi = $server->methodparams['!Poradi'] ? $server->methodparams['!Poradi'] : 1;
  $zdroj = $server->methodparams['!Zdroj'];

  $sql = 'select max(poradi) as MAX_PORADI from posta_eed_udalosti where chyba=0 and app_id=' . $app_id;
  $q->query($sql);
  $q->Next_Record();
  $poradi_old = ($q->Record['MAX_PORADI'] ? $q->Record['MAX_PORADI'] : 0) +1;
  if ($poradi_old <> $poradi) {
    //odmitneme davku, poradi musi byt +1
    $msg_popis = NastavPopis('ermsAsyn','1112',key($udalost));
    $msg_popis['Popis'] = 'Ocekavano cislo davky ' . $poradi_old . ', misto toho prislo ' . $poradi;
    Response_Zprava($response_Zprava, $msg_popis["Kod"], $msg_popis["Popis"], $udalostId, $poradi);
    NastavLog($log, $msg_popis["Kod"].': '.$msg_popis["Popis"].($msg_popis["ErrSql"] ? ' | '.$msg_popis["ErrSql"] : '') , Date('dmYHis').' - ermsAsyn'.': '.$poradi.'|'.$udalostId, $msg_popis["Kod"]);
  }
  else {
    $server->methodURI = $soap["methodURI"].'" DatumVzniku="'.ConvertDatumToXML(date("d.m.Y H:i")).'" Poradi="'.$poradi.'" Zdroj="'.$cil;
    $res = ErmsAsynUdalosti($Udalosti,$response_Zprava,$poradi, $app_id);
  }


  $result = array(
//    'Zpravy' => array('Zprava' => $response_Zprava),
    'OperaceStatus' => $response_OperaceStatus
  );

  $ret = array(
    'Dod' => 1,
    'Popis'=> 'aaaa' );

  return $ret;
  return false;
}

function ErmsAsynUdalosti($Udalosti,&$response_Zprava,$poradi=0, $app_id) {
  $res = true;
  $sqlTranFce = false;
    
  $q=new DB_POSTA;
  $q->ShowError = false;
	$q->Error_Die = false;
	$q->Tran_Begin();
  $server->methodURI = $soap["methodURI"].'" DatumVzniku="'.ConvertDatumToXML(date("d.m.Y H:i")).'" Poradi="'.$poradi.'" Zdroj="'.$cil;

  $UdalostiSort = array();
  foreach ($Udalosti as $key => $val) {
    foreach ($val as $key2 => $val2) {
      if (is_int($key2)) 
        $UdalostiSort[$val2['UdalostId']] = array($key => $val2);
      else {
        $UdalostiSort[$val['UdalostId']] = array($key => $val);
        break;
      }
    }
  }
  ksort($UdalostiSort);
  //print_r($UdalostiSort);
  $q=new DB_POSTA;
  $udalostId = $udalostId ? $udalostId : 0;

  $msg_popis = NastavPopis('ermsAsyn','0000',key($udalost));

    //Zpracovani...
  foreach ($UdalostiSort as $key => $udalost) {
    if (!$res) break;
    //unset($response_Zprava);

    $udalostId = $udalost[key($udalost)]['UdalostId'];
    $sql = 'select * from posta_eed_udalosti where chyba=0 and udalostId=' . $udalostId.' and poradi=' . $poradi .' and app_id=' . $app_id;
    $q->query($sql);
    if ($q->Num_Rows()>0) {
      $msg_popis = NastavPopis('ermsAsyn','1111',key($udalost));
      Response_Zprava($response_Zprava, $msg_popis["Kod"], $msg_popis["Popis"], $udalostId, $poradi);
      NastavLog($log, $msg_popis["Kod"].': '.$msg_popis["Popis"].($msg_popis["ErrSql"] ? ' | '.$msg_popis["ErrSql"] : '') , Date('dmYHis').' - ermsAsyn'.': '.$poradi.'|'.$udalostId, $msg_popis["Kod"]);
      return false;
    }
    if (!in_array(key($udalost), $GLOBALS['async_fce'])) {
      $msg_popis = NastavPopis('ermsAsyn','1000',key($udalost));
      Response_Zprava($response_Zprava, $msg_popis["Kod"], $msg_popis["Popis"], $udalostId, $poradi);
      NastavLog($log, $msg_popis["Kod"].': '.$msg_popis["Popis"].($msg_popis["ErrSql"] ? ' | '.$msg_popis["ErrSql"] : '') , Date('dmYHis').' - ermsAsyn'.': '.$poradi.'|'.$udalostId, $msg_popis["Kod"]);
      return false;
    }

    $sql = "insert into posta_eed_udalosti (udalost,hodnoty,poradi,udalostId,vlozeno,app_id) VALUES ('".key($udalost)."','".serialize($udalost[key($udalost)])."',".$poradi.", '".$udalostId."','".Date('Y-m-d H:i:s')."',".$app_id.")";
    $q->query($sql);
  }

  $msg_popis = NastavPopis('ermsAsyn','0000',key($udalost));
  Response_Zprava($response_Zprava, $msg_popis["Kod"], $msg_popis["Popis"], $udalostId, $poradi);

  if ($res) {
    $q->Tran_Commit();
  } else {
    $q->Tran_Rollback();
  }
  ZapisLog($log);

  return $res;
}
