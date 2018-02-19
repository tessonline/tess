<?php

//Funkce vrati nove cislo jednaci k dane zadosti... 
function SouborZadostRequest($app) {
  //nastaveni parametru
  global $server, $soap;
  $server->responseMethodname = str_replace("Request", "", $server->methodname).'Response';
  $server->methodURI = $soap["methodURI"];
  
  //print_r($server->methodparams);
//  $app = $server->methodparams["App"];
//  $VlastniDokument = $server->methodparams["Ess"];
  $Autorizace = $server->methodparams["Autorizace"];


  if (VratReferenta($Autorizace)==0)
    return VratChybu($log,'Nepovedlo se identifikovat uzivatele v parametru ProvedlKdo');

  $id = getPostaIdFromUpload($app);
  $id = (integer) $id;
  if ($id<1)
    $msg_popis = NastavPopis('getFileContent','1000');
  else {
    $file = fce_getFileCOntent($app, $id);
    $msg_popis = NastavPopis('getFileContent','0000');

  //print_r($file);
  }
//print_r($msg_popis);
//print_r($ess);

  //print_r($UdalostiPredchazejici);
  //print_r($VlastniDokument);
  //print_r($Autorizace);


 //response
  Response_OperaceStatus($response_OperaceStatus, $msg_popis["Kod"], $msg_popis["Popis"]);

  NastavLog($log, $msg_popis["Kod"].': '.$msg_popis["Popis"].($msg_popis["ErrSql"] ? ' | '.$msg_popis["ErrSql"] : '') , 'createBinding', $msg_popis["Kod"]);

  $vysledek = array(
//    'Soubory'=>$file,  //'tns:tOperaceStatus'
    'Soubor'=>new soapval('Soubory', false, $file),  //'tns:tOperaceStatus'
    'OperaceStatus'=>new soapval('OperaceStatus', false, $response_OperaceStatus),  //'tns:tOperaceStatus'
  );

  //$vysledek = $response_OperaceStatus;
  ZapisLog($log); 

  return VratVysledek($vysledek);
}
