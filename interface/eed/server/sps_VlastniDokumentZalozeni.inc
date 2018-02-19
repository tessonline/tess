<?php

//Funkce vrati nove cislo jednaci k dane zadosti... 
function VlastniDokumentZalozeniRequest($UdalostiPredchazejici, $VlastniDokument, $Autorizace) {
  //nastaveni parametru
  global $server, $soap;
  $server->responseMethodname = str_replace("Request", "", $server->methodname).'Response';
  $server->methodURI = $soap["methodURI"];
  
  //print_r($server->methodparams);
  $UdalostiPredchazejici = $server->methodparams["UdalostiPredchazejici"];
  $VlastniDokument = $server->methodparams["VlastniDokument"];
  $Autorizace = $server->methodparams["Autorizace"];
  //print_r($UdalostiPredchazejici);
  //print_r($VlastniDokument);
  //print_r($Autorizace);

  $VlastniDokument['Doruceni']['Odesilatel'] = $VlastniDokument['Vypraveni']['Adresat'];
  $VlastniDokument['Doruceni']['ZasilkaInfo'] = $VlastniDokument['Vypraveni']['ZasilkaInfo'];


  if (VratReferenta($Autorizace)==0)
    return VratChybu($log,'Nepovedlo se identifikovat uzivatele v parametru ProvedlKdo');

  //response null
  Response_Dokument($response_VlastniDokument, false, 't');

  //Zpracovani...
  if (ErmsAsynUdalosti($UdalostiPredchazejici, $vysledek)) {
    //Zalozeni dokumentu
    $res = DokumentZalozeni($VlastniDokument, 't', $Autorizace, $id, $msg_popis);

    //Nacteni dokumentu
    If ($id>0) Response_Dokument($response_VlastniDokument, $id, 't');
  }
  else
    $msg_popis = NastavPopis('DokumentZalozeni','2000');
  
  //response
  Response_OperaceStatus($response_OperaceStatus, $msg_popis["Kod"], $msg_popis["Popis"]);
  NastavLog($log, $msg_popis["Kod"].': '.$msg_popis["Popis"].($msg_popis["ErrSql"] ? ' | '.$msg_popis["ErrSql"] : '') , 'VlastniDokumentZalozeniRequest', $msg_popis["Kod"]);
  
  $vysledek = array(
    'VlastniDokument'=>new soapval('VlastniDokument', false, $response_VlastniDokument), //tns:tVlastniDokument
    'OperaceStatus'=>new soapval('OperaceStatus', false, $response_OperaceStatus),  //'tns:tOperaceStatus'
  );  
  
  ZapisLog($log); 

  return VratVysledek($vysledek);
}
