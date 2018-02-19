<?php

//Funkce zpracovavajici asyn. funkce v davce...
function ermsAsyn($Udalosti) {
  //nastaveni parametru
  global $server, $soap;
  //$server->responseMethodname = str_replace("Request", "", $server->methodname).'Response';
  $server->responseMethodname = $server->methodname;
  //print_r($server->methodparams);
  $Udalosti = $server->methodparams["Udalosti"];
  //print_r($Udalosti);
  $Autorizace = $server->methodparams["Autorizace"];

  $q=new DB_POSTA;
  $q->ShowError = false;
	$q->Error_Die = false;
//  if (VratReferenta($Autorizace)==0) 
//    return VratChybu($log,'Nepovedlo se identifikovat uzivatele v parametru ProvedlKdo');
  
  //attr
  $cil = $server->methodparams['!Cil'];
  $datumVzniku = $server->methodparams['!DatumVzniku'];
  $poradi = $server->methodparams['!Poradi'];
  $zdroj = $server->methodparams['!Zdroj'];
  
  $server->methodURI = $soap["methodURI"].'" DatumVzniku="'.ConvertDatumToXML(date("d.m.Y H:i")).'" Poradi="'.$poradi.'" Zdroj="'.$cil;
  
  $res = ErmsAsynUdalosti($Udalosti,$response_Zprava,$poradi);
  
  $vysledek = array(
    'Udalosti'=>new soapval('Udalosti', false, $response_Udalosti), //'tns:tUdalosti'
    'Zpravy'=>new soapval('Zpravy', false, array('Zprava'=>$response_Zprava)), //'tns:Zprava'
  );
  
  return VratVysledek($vysledek);
}

function ErmsAsynUdalosti($Udalosti,&$response_Zprava,$poradi=0) {
  //print_r($Udalosti);
  $res = true;
  $sqlTranFce = false;
    
  $q=new DB_POSTA;
  $q->ShowError = false;
	$q->Error_Die = false;
	$q->Tran_Begin();
  
  //Setrideni udalsoti podle UdalostId (spatne to php generuje)
  //$UdalostiSort[UdalostId] = array(fce() => ...)
  $UdalostiSort = array();
  foreach ($Udalosti as $key => $val) {
    foreach ($val as $key2 => $val2) {
      if (is_int($key2)) 
        $UdalostiSort[$val2['!UdalostId']] = array($key => $val2);
      else {
        $UdalostiSort[$val['!UdalostId']] = array($key => $val);
        break;
      }
    }
  }
  ksort($UdalostiSort);
  //print_r($UdalostiSort);
  
  //Zpracovani...
  foreach ($UdalostiSort as $key => $udalost) {
    //print_r($udalost);
    if (!$res) break;
    //unset($response_Zprava);
    if (key($udalost)=='DokumentOtevreni') 
      $res = DokumentOtevreni($udalost['DokumentOtevreni'],$q,$sqlTranFce,$poradi,$response_Zprava,$log);
    elseif (key($udalost)=='DokumentPostoupeni') 
      $res = DokumentPostoupeni($udalost['DokumentPostoupeni'],$q,$sqlTranFce,$poradi,$response_Zprava,$log);
    elseif (key($udalost)=='DokumentUprava') 
      $res = DokumentUprava($udalost['DokumentUprava'],$q,$sqlTranFce,$poradi,$response_Zprava,$log);
    elseif (key($udalost)=='DokumentVlozeniDoSpisu') 
      $res = DokumentVlozeniDoSpisu($udalost['DokumentVlozeniDoSpisu'],$q,$sqlTranFce,$poradi,$response_Zprava,$log);
    elseif (key($udalost)=='DokumentVraceni') 
      $res = DokumentVraceni($udalost['DokumentVraceni'],$q,$sqlTranFce,$poradi,$response_Zprava,$log);
    elseif (key($udalost)=='DokumentVyjmutiZeSpisu') 
      $res = DokumentVyjmutiZeSpisu($udalost['DokumentVyjmutiZeSpisu'],$q,$sqlTranFce,$poradi,$response_Zprava,$log);
    elseif (key($udalost)=='DokumentZmenaZpracovatele') 
      $res = DokumentZmenaZpracovatele($udalost['DokumentZmenaZpracovatele'],$q,$sqlTranFce,$poradi,$response_Zprava,$log);
    elseif (key($udalost)=='DokumentZruseni') 
      $res = DokumentZruseni($udalost['DokumentZruseni'],$q,$sqlTranFce,$poradi,$response_Zprava,$log);
    elseif (key($udalost)=='DoruceniUprava') 
      $res = DoruceniUprava($udalost['DoruceniUprava'],$q,$sqlTranFce,$poradi,$response_Zprava,$log);
    elseif (key($udalost)=='SouborNovaVerze') 
      $res = SouborNovaVerze($udalost['SouborNovaVerze'],$q,$sqlTranFce,$poradi,$response_Zprava,$log);
    elseif (key($udalost)=='SouborVlozitKVypraveni') 
      $res = SouborVlozitKVypraveni($udalost['SouborVlozitKVypraveni'],$q,$sqlTranFce,$poradi,$response_Zprava,$log);
    elseif (key($udalost)=='SouborVyjmoutZVypraveni') 
      $res = SouborVyjmoutZVypraveni($udalost['SouborVyjmoutZVypraveni'],$q,$sqlTranFce,$poradi,$response_Zprava,$log);
    elseif (key($udalost)=='SouborZalozeni') 
      $res = SouborZalozeni($udalost['SouborZalozeni'],$q,$sqlTranFce,$poradi,$response_Zprava,$log);
    elseif (key($udalost)=='SouborZruseni') 
      $res = SouborZruseni($udalost['SouborZruseni'],$q,$sqlTranFce,$poradi,$response_Zprava,$log);
    elseif (key($udalost)=='SpisOtevreni') 
      $res = SpisOtevreni($udalost['SpisOtevreni'],$q,$sqlTranFce,$poradi,$response_Zprava,$log);
    elseif (key($udalost)=='SpisPostoupeni') 
      $res = SpisPostoupeni($udalost['SpisPostoupeni'],$q,$sqlTranFce,$poradi,$response_Zprava,$log);
    elseif (key($udalost)=='SpisVraceni') 
      $res = SpisVraceni($udalost['SpisVraceni'],$q,$sqlTranFce,$poradi,$response_Zprava,$log);
    elseif (key($udalost)=='SpisVyrizeni') 
      $res = SpisVyrizeni($udalost['SpisVyrizeni'],$q,$sqlTranFce,$poradi,$response_Zprava,$log);
    elseif (key($udalost)=='SpisZalozeni') 
      $res = SpisZalozeni($udalost['SpisZalozeni'],$q,$sqlTranFce,$poradi,$response_Zprava,$log);
    elseif (key($udalost)=='SpisZmenaZpracovatele') 
      $res = SpisZmenaZpracovatele($udalost['SpisZmenaZpracovatele'],$q,$sqlTranFce,$poradi,$response_Zprava,$log);
    elseif (key($udalost)=='SpisZruseni') 
      $res = SpisZruseni($udalost['SpisZruseni'],$q,$sqlTranFce,$poradi,$response_Zprava,$log);
    elseif (key($udalost)=='VypraveniDoruceno') 
      $res = VypraveniDoruceno($udalost['VypraveniDoruceno'],$q,$sqlTranFce,$poradi,$response_Zprava,$log);
    elseif (key($udalost)=='VypraveniPredatVypravne') 
      $res = VypraveniPredatVypravne($udalost['VypraveniPredatVypravne'],$q,$sqlTranFce,$poradi,$response_Zprava,$log);
    elseif (key($udalost)=='VypraveniUprava') 
      $res = VypraveniUprava($udalost['VypraveniUprava'],$q,$sqlTranFce,$poradi,$response_Zprava,$log);
    elseif (key($udalost)=='VypraveniVypraveno') 
      $res = VypraveniVypraveno($udalost['VypraveniVypraveno'],$q,$sqlTranFce,$poradi,$response_Zprava,$log);
    elseif (key($udalost)=='VypraveniZalozeni') 
      $res = VypraveniZalozeni($udalost['VypraveniZalozeni'],$q,$sqlTranFce,$poradi,$response_Zprava,$log);
    elseif (key($udalost)=='VypraveniZruseni') 
      $res = VypraveniZruseni($udalost['VypraveniZruseni'],$q,$sqlTranFce,$poradi,$response_Zprava,$log);
    else {
      $res = false;
      $udalostId = $udalost[key($udalost)]['!UdalostId'];
      
      $msg_popis = NastavPopis('ermsAsyn','1000',key($udalost));
      
      //response 
      Response_Zprava($response_Zprava, $msg_popis["Kod"], $msg_popis["Popis"], $udalostId, $poradi);
      NastavLog($log, $msg_popis["Kod"].': '.$msg_popis["Popis"].($msg_popis["ErrSql"] ? ' | '.$msg_popis["ErrSql"] : '') , Date('dmYHis').' - ermsAsyn'.': '.$poradi.'|'.$udalostId, $msg_popis["Kod"]);
    }
  }
  
  if ($res) {
    $q->Tran_Commit();
  } else {
    $q->Tran_Rollback();
  }
  
  ZapisLog($log);

  return $res;
}
