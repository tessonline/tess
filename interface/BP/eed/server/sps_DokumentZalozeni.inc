<?php

//Funkce vrati nove cislo jednaci k dane zadosti... 
Function DokumentZalozeniRequest($UdalostiPredchazejici, $ProfilDokumentu, $Autorizace) {
  //nastaveni parametru
  global $server, $soap;
  $server->responseMethodname = str_replace("Request", "", $server->methodname).'Response';
  $server->methodURI = $soap["methodURI"];
  
  //print_r($server->methodparams);
  //print_r($UdalostiPredchazejici);
  //print_r($ProfilDokumentu);
  //print_r($Autorizace);

// ob_start;
// print_r($ProfilDokumentu);
// print_r($Autorizace);
// eb_end_flush; Die();

  if (VratReferenta($Autorizace)==0) 
    return VratChybu($log,'Nepovedlo se identifikovat uzivatele v parametru ProvedlKdo');

  //response null
  Response_Dokument($response_ProfilDokumentu, false, 'f');

  //Zalozeni dokumentu
  $res = DokumentZalozeni($ProfilDokumentu, 'f', $Autorizace, $id, $msg_popis);


  //Nacteni dokumentu
  if ($id>0) Response_Dokument($response_ProfilDokumentu, $id, 'f');

  Response_Dokument($response_Dokument, $id, 't');
  
  //response 
  Response_OperaceStatus($response_OperaceStatus, $msg_popis["Kod"], $msg_popis["Popis"]);
  NastavLog($log, $msg_popis["Kod"].': '.$msg_popis["Popis"].($msg_popis["ErrSql"] ? ' | '.$msg_popis["ErrSql"] : '') , 'DokumentZalozeniRequest', $msg_popis["Kod"]);
  

  $result = array(
    'ProfilDokumentu' => $response_Dokument,
    'OperaceStatus' => $response_OperaceStatus
  );
  
  ZapisLog($log);  

  return $result;
}
