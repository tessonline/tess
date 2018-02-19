<?php

//Funkce vrati nove cislo jednaci k dane zadosti... 
function ProfilSpisuZadostRequest($UdalostiPredchazejici, $ProfilSpisu, $DokumentyVlozene, $Autorizace) {
  //nastaveni parametru
  global $server, $soap;
  $server->responseMethodname = str_replace("Request", "", $server->methodname).'Response';
  $server->methodURI = $soap["methodURI"];
  
  //print_r($server->methodparams);
  $UdalostiPredchazejici = $server->methodparams["UdalostiPredchazejici"];
  $ProfilSpisu = $server->methodparams["IdSpisu"];
  $DokumentyVlozene = $server->methodparams["DokumentyVlozene"];
  $Autorizace = $server->methodparams["Autorizace"];
//   if (VratReferenta($Autorizace)==0) {
//     return VratChybu($log,'Nepovedlo se identifikovat uzivatele v parametru ProvedlKdo');
//   }
  //response null
  Response_ProfilSpisu($response_ProfilSpisu);
  Response_DokumentyVlozene($response_DokumentyVlozene);
  if (ExistujeSpis($id_spis,$ProfilSpisu['Identifikator']['HodnotaID'],$ProfilSpisu['Identifikator']['ZdrojID'])) {
    $msg_popis = NastavPopis('ProfilSpisuZadost','0000');
  }
  else
    $msg_popis = NastavPopis('ProfilSpisuZadost','1000');

    //Nacteni spisu
  if ($id_spis>0) {
    Response_ProfilSpisu($response_ProfilSpisu,$id_spis);
    Response_DokumentyVlozene($response_DokumentyVlozene,$id_spis);
  }
  else
    $msg_popis = NastavPopis('ProfilSpisuZadost','1000');
  
  //response 
  Response_OperaceStatus($response_OperaceStatus, $msg_popis["Kod"], $msg_popis["Popis"]);
  NastavLog($log, $msg_popis["Kod"].': '.$msg_popis["Popis"].($msg_popis["ErrSql"] ? ' | '.$msg_popis["ErrSql"] : '') , 'SpisZalozeniRequest', $msg_popis["Kod"]);
//  print_r($response_DokumentyVlozene);
  $vysledek = array(
    'ProfilSpisu'=>new soapval('ProfilSpisu', false, $response_ProfilSpisu), //tns:tProfilSpisu
    'DokumentyVlozene'=>new soapval('DokumentyVlozene', false, $response_DokumentyVlozene), //tns:ttDokumentyVlozene_response
    'OperaceStatus'=>new soapval('OperaceStatus', false, $response_OperaceStatus), //tns:tOperaceStatus
  );
  
  ZapisLog($log); 

  return VratVysledek($vysledek);
}

?>
