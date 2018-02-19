<?php

//Funkce vrati nove cislo jednaci k dane zadosti... 
function WsTestRequest($text) {
  //nastaveni parametru
  global $server, $soap;
  $server->responseMethodname = str_replace("Request", "", $server->methodname).'Response';
  $server->methodURI = $soap["methodURI"];
  
  //print_r($server->methodparams);
  $UdalostiPredchazejici = $server->methodparams["UdalostiPredchazejici"];
  $ProfilSpisu = $server->methodparams["ProfilSpisu"];
  $DokumentyVlozene = $server->methodparams["DokumentyVlozene"];
  $Autorizace = $server->methodparams["Autorizace"];

  if (VratReferenta($Autorizace)==0) 
    return VratChybu($log,'Nepovedlo se identifikovat uzivatele v parametru ProvedlKdo');

  $msg_popis = NastavPopis('wsTestRequest','0000');
  
  //response 
  Response_OperaceStatus($response_OperaceStatus, $msg_popis["Kod"], $msg_popis["Popis"]);
  NastavLog($log, $msg_popis["Kod"].': '.$msg_popis["Popis"].($msg_popis["ErrSql"] ? ' | '.$msg_popis["ErrSql"] : '') , 'WsTestRequest', $msg_popis["Kod"]);
  
  $vysledek = array(
    'WsTestId'=>'ok', //tns:tProfilSpisu
    'OperaceStatus'=>new soapval('OperaceStatus', false, $response_OperaceStatus), //tns:tOperaceStatus
  );
  
  ZapisLog($log); 

  return VratVysledek($vysledek);
}

?>
