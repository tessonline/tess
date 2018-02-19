<?php

//Funkce vrati nove cislo jednaci k dane zadosti... 
Function DorucenyDokumentZalozeniRequest($UdalostiPredchazejici, $DorucenyDokument, $Autorizace) {
  //nastaveni parametru
  global $server, $soap;
  $server->responseMethodname = str_replace("Request", "", $server->methodname).'Response';
  $server->methodURI = $soap["methodURI"];
  
  //print_r($server->methodparams);
  $UdalostiPredchazejici = $server->methodparams["UdalostiPredchazejici"];
  $DorucenyDokument = $server->methodparams["DorucenyDokument"];
  $Autorizace = $server->methodparams["Autorizace"];
  //print_r($UdalostiPredchazejici);
  //print_r($DorucenyDokument);
  //print_r($Autorizace);

  if (VratReferenta($Autorizace)==0)
    return VratChybu($log,'Nepovedlo se identifikovat uzivatele v parametru ProvedlKdo');

  //response null
  Response_Dokument($response_DorucenyDokument, false, 'f');

  //Zpracovani...
  if (ErmsAsynUdalosti($UdalostiPredchazejici, $vysledek)) {
    //Zalozeni dokumentu
    $res = DokumentZalozeni($DorucenyDokument, 'f', $Autorizace, $id, $msg_popis);

    //Nacteni dokumentu
    if ($id>0) Response_Dokument($response_DorucenyDokument, $id, 'f');
  }
  else
    $msg_popis = NastavPopis('DokumentZalozeni','2000');

  //response
  Response_OperaceStatus($response_OperaceStatus, $msg_popis["Kod"], $msg_popis["Popis"]);
  NastavLog($log, $msg_popis["Kod"].': '.$msg_popis["Popis"].($msg_popis["ErrSql"] ? ' | '.$msg_popis["ErrSql"] : '') , 'DorucenyDokumentZalozeniRequest', $msg_popis["Kod"]);
  
  $vysledek = array(
    'DorucenyDokument'=>new soapval('DorucenyDokument', false, $response_DorucenyDokument), //tns:tDorucenyDokument
    'OperaceStatus'=>new soapval('OperaceStatus', false, $response_OperaceStatus), //'tns:tOperaceStatus'
  );
  
  //print_r($vysledek);
  
  ZapisLog($log);  

  return VratVysledek($vysledek);
}

?>
