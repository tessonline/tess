<?php

//Funkce vrati nove cislo jednaci k dane zadosti... 
function ProfilDokumentuZadostRequest($UdalostiPredchazejici, $dokument, $Autorizace) {
  //nastaveni parametru
  global $server, $soap;
  $server->responseMethodname = str_replace("Request", "", $server->methodname).'Response';
  $server->methodURI = $soap["methodURI"];
  
  //print_r($server->methodparams);
  $UdalostiPredchazejici = $server->methodparams["UdalostiPredchazejici"];
  $dokument = $server->methodparams["IdDokument"];
  $Autorizace = $server->methodparams["Autorizace"];
  //print_r($UdalostiPredchazejici);
  //print_r($Autorizace);

  //response null
  if (ExistujeDokument($id,$dokument['Identifikator']['HodnotaID'],$dokument['Identifikator']['ZdrojID'])) {
    Response_Dokument($response_DorucenyDokument, $id, 't');
    $msg_popis = NastavPopis('ProfilDOkumentuZadost','0000');

//    print_r($response_DorucenyDokument);
  }
  else 
    $msg_popis = NastavPopis('ProfilDOkumentuZadost','1000');

  //response 
  Response_OperaceStatus($response_OperaceStatus, $msg_popis["Kod"], $msg_popis["Popis"]);
  
  NastavLog($log, $msg_popis["Kod"].': '.$msg_popis["Popis"].($msg_popis["ErrSql"] ? ' | '.$msg_popis["ErrSql"] : '') , 'DorucenyDokumentZalozeniRequest', $msg_popis["Kod"]);
//  print_r($response_OperaceStatus);
  $vysledek = array(
    'ProfilDokumentu'=>new soapval('ProfilDokumentu', false, $response_DorucenyDokument), //tns:tDorucenyDokument
    'OperaceStatus'=>new soapval('OperaceStatus', false, $response_OperaceStatus), //'tns:tOperaceStatus'
  );
  
  //print_r($vysledek);
  
  ZapisLog($log);  

  return VratVysledek($vysledek);
}

