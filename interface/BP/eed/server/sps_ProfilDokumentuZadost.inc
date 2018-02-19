<?php

//Funkce vrati nove cislo jednaci k dane zadosti... 
function ProfilDokumentuZadostRequest($UdalostiPredchazejici, $dokument, $Autorizace) {
  //nastaveni parametru
  global $server, $soap;
  $server->responseMethodname = str_replace("Request", "", $server->methodname).'Response';
  $server->methodURI = $soap["methodURI"];
  
 if (VratReferenta($Autorizace)==0)
    return VratChybuBP($log,'Nepovedlo se identifikovat uzivatele v parametru ProvedlKdo');

  //response null
  if (ExistujeDokument($id,$dokument['Identifikator']['HodnotaID'],$dokument['Identifikator']['ZdrojID'])) {
    Response_Dokument($response_DorucenyDokument, $id, 't');
    $msg_popis = NastavPopis('ProfilDOkumentuZadost','0000');

  }
  else 
    $msg_popis = NastavPopis('ProfilDOkumentuZadost','1000');

  //response 
  Response_OperaceStatus($response_OperaceStatus, $msg_popis["Kod"], $msg_popis["Popis"]);
  
  NastavLog($log, $msg_popis["Kod"].': '.$msg_popis["Popis"].($msg_popis["ErrSql"] ? ' | '.$msg_popis["ErrSql"] : '') , 'DorucenyDokumentZalozeniRequest', $msg_popis["Kod"]);

//   $vysledek = array(
//     'ProfilDokumentu'=>new soapval('ProfilDokumentu', false, $response_DorucenyDokument), //tns:tDorucenyDokument
//     'OperaceStatus'=>new soapval('OperaceStatus', false, $response_OperaceStatus), //'tns:tOperaceStatus'
//   );
//
  $result = array(
    'ProfilDokumentu' => $response_DorucenyDokument,
    'OperaceStatus' => $response_OperaceStatus
  );

  //print_r($vysledek);
  
  ZapisLog($log);  
  return $result;
//  return VratVysledek($vysledek);
}

