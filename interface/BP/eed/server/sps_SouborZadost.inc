<?php

//Funkce vrati nove cislo jednaci k dane zadosti... 
function SouborZadostRequest ($UdalostiPredchazejici, $dokument, $Autorizace) {
  //nastaveni parametru
  global $server, $soap;
  $server->responseMethodname = str_replace("Request", "", $server->methodname).'Response';
  $server->methodURI = $soap["methodURI"];

 if (VratReferenta($Autorizace)==0)
    return VratChybuBP($log,'Nepovedlo se identifikovat uzivatele v parametru ProvedlKdo');

  $id = getPostaIdFromUpload($dokument['Identifikator']);

  $id = (integer) $id;

  if ($id<1)
    $msg_popis = NastavPopis('getFileContent','1000');
  else {
    $file = fce_getFileCOntent($dokument['Identifikator'], $id);
    $msg_popis = NastavPopis('getFileContent','0000');

  }
//   ob_start();
//   print_r($msg_popis);
//   ob_end_flush();
//
 //response
  Response_OperaceStatus($response_OperaceStatus, $msg_popis["Kod"], $msg_popis["Popis"]);

  NastavLog($log, $msg_popis["Kod"].': '.$msg_popis["Popis"].($msg_popis["ErrSql"] ? ' | '.$msg_popis["ErrSql"] : '') , 'createBinding', $msg_popis["Kod"]);
  //$vysledek = $response_OperaceStatus;
  ZapisLog($log); 
  $result = array(
    'Soubor' => $file,
    'OperaceStatus' => $response_OperaceStatus
  );


  return $result;
}


