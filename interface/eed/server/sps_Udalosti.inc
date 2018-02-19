<?php

//Funkce zpracovavajici asyn. funkci... 
function UdalostiRequest($Udalosti) {
  //nastaveni parametru
  global $server, $soap;
  $server->responseMethodname = str_replace("Request", "", $server->methodname).'Response';
  $server->methodURI = $soap["methodURI"];
  $Autorizace = $server->methodparams["Udalosti"]["Autorizace"];
  $sqlTranFce = true;
  $poradi = 0;
  
  $q=new DB_POSTA;
  $q->ShowError = false;
	$q->Error_Die = false;

//   if (VratReferenta($Autorizace)==0) {
//     return VratChybu($log,'Nepovedlo se identifikovat uzivatele v parametru ProvedlKdo');
//   }

  //Zpracovani...
  if (key($Udalosti)=='DokumentOtevreni') 
    $res = DokumentOtevreni($Udalosti['DokumentOtevreni'],$q,$sqlTranFce,$poradi,$response_Zprava,$log);
  elseif (key($Udalosti)=='DokumentPostoupeni') 
    $res = DokumentPostoupeni($Udalosti['DokumentPostoupeni'],$q,$sqlTranFce,$poradi,$response_Zprava,$log);
  elseif (key($Udalosti)=='DokumentUprava') 
    $res = DokumentUprava($Udalosti['DokumentUprava'],$q,$sqlTranFce,$poradi,$response_Zprava,$log);
  elseif (key($Udalosti)=='DokumentVlozeniDoSpisu') 
    $res = DokumentVlozeniDoSpisu($Udalosti['DokumentVlozeniDoSpisu'],$q,$sqlTranFce,$poradi,$response_Zprava,$log);
  elseif (key($Udalosti)=='DokumentVraceni') 
    $res = DokumentVraceni($Udalosti['DokumentVraceni'],$q,$sqlTranFce,$poradi,$response_Zprava,$log);
  elseif (key($Udalosti)=='DokumentVyjmutiZeSpisu') 
    $res = DokumentVyjmutiZeSpisu($Udalosti['DokumentVyjmutiZeSpisu'],$q,$sqlTranFce,$poradi,$response_Zprava,$log);
  elseif (key($Udalosti)=='DokumentZmenaZpracovatele') 
    $res = DokumentZmenaZpracovatele($Udalosti['DokumentZmenaZpracovatele'],$q,$sqlTranFce,$poradi,$response_Zprava,$log);
  elseif (key($Udalosti)=='DokumentZruseni') 
    $res = DokumentZruseni($Udalosti['DokumentZruseni'],$q,$sqlTranFce,$poradi,$response_Zprava,$log);
  elseif (key($Udalosti)=='DoruceniUprava') 
    $res = DoruceniUprava($Udalosti['DoruceniUprava'],$q,$sqlTranFce,$poradi,$response_Zprava,$log);
  elseif (key($Udalosti)=='SouborNovaVerze') 
    $res = SouborNovaVerze($Udalosti['SouborNovaVerze'],$q,$sqlTranFce,$poradi,$response_Zprava,$log);
  elseif (key($Udalosti)=='SouborVlozitKVypraveni') 
    $res = SouborVlozitKVypraveni($Udalosti['SouborVlozitKVypraveni'],$q,$sqlTranFce,$poradi,$response_Zprava,$log);
  elseif (key($Udalosti)=='SouborVyjmoutZVypraveni') 
    $res = SouborVyjmoutZVypraveni($Udalosti['SouborVyjmoutZVypraveni'],$q,$sqlTranFce,$poradi,$response_Zprava,$log);
  elseif (key($Udalosti)=='SouborZalozeni') 
    $res = SouborZalozeni($Udalosti['SouborZalozeni'],$q,$sqlTranFce,$poradi,$response_Zprava,$log);
  elseif (key($Udalosti)=='SouborZruseni') 
    $res = SouborZruseni($Udalosti['SouborZruseni'],$q,$sqlTranFce,$poradi,$response_Zprava,$log);
  elseif (key($Udalosti)=='SpisOtevreni') 
    $res = SpisOtevreni($Udalosti['SpisOtevreni'],$q,$sqlTranFce,$poradi,$response_Zprava,$log);
  elseif (key($Udalosti)=='SpisPostoupeni') 
    $res = SpisPostoupeni($Udalosti['SpisPostoupeni'],$q,$sqlTranFce,$poradi,$response_Zprava,$log);
  elseif (key($Udalosti)=='SpisVraceni') 
    $res = SpisVraceni($Udalosti['SpisVraceni'],$q,$sqlTranFce,$poradi,$response_Zprava,$log);
  elseif (key($Udalosti)=='SpisVyrizeni') 
    $res = SpisVyrizeni($Udalosti['SpisVyrizeni'],$q,$sqlTranFce,$poradi,$response_Zprava,$log);
  elseif (key($Udalosti)=='SpisZalozeni') 
    $res = SpisZalozeni($Udalosti['SpisZalozeni'],$q,$sqlTranFce,$poradi,$response_Zprava,$log);
  elseif (key($Udalosti)=='SpisZmenaZpracovatele') 
    $res = SpisZmenaZpracovatele($Udalosti['SpisZmenaZpracovatele'],$q,$sqlTranFce,$poradi,$response_Zprava,$log);
  elseif (key($Udalosti)=='SpisZruseni')
    $res = SpisZruseni($Udalosti['SpisZruseni'],$q,$sqlTranFce,$poradi,$response_Zprava,$log);
  elseif (key($Udalosti)=='SpisUprava')
    $res = SpisUprava($Udalosti['SpisUprava'],$q,$sqlTranFce,$poradi,$response_Zprava,$log);
  elseif (key($Udalosti)=='VypraveniDoruceno')
    $res = VypraveniDoruceno($Udalosti['VypraveniDoruceno'],$q,$sqlTranFce,$poradi,$response_Zprava,$log);
  elseif (key($Udalosti)=='VypraveniPredatVypravne') 
    $res = VypraveniPredatVypravne($Udalosti['VypraveniPredatVypravne'],$q,$sqlTranFce,$poradi,$response_Zprava,$log);
  elseif (key($Udalosti)=='VypraveniUprava') 
    $res = VypraveniUprava($Udalosti['VypraveniUprava'],$q,$sqlTranFce,$poradi,$response_Zprava,$log);
  elseif (key($Udalosti)=='VypraveniVypraveno') 
    $res = VypraveniVypraveno($Udalosti['VypraveniVypraveno'],$q,$sqlTranFce,$poradi,$response_Zprava,$log);
  elseif (key($Udalosti)=='VypraveniZalozeni') 
    $res = VypraveniZalozeni($Udalosti['VypraveniZalozeni'],$q,$sqlTranFce,$poradi,$response_Zprava,$log);
  elseif (key($Udalosti)=='VypraveniZruseni') 
    $res = VypraveniZruseni($Udalosti['VypraveniZruseni'],$q,$sqlTranFce,$poradi,$response_Zprava,$log);
  else {
    $res = false;
    $udalostId = $Udalosti[key($Udalosti)]['!UdalostId'];
    
    $msg_popis = NastavPopis('Udalosti','1000',key($Udalosti));
    
    //response 
    Response_Zprava($response_Zprava, $msg_popis["Kod"], $msg_popis["Popis"], $udalostId, $poradi);
    NastavLog($log, $msg_popis["Kod"].': '.$msg_popis["Popis"].($msg_popis["ErrSql"] ? ' | '.$msg_popis["ErrSql"] : '') , Date('dmYHis').' - Udalosti'.': '.$poradi.'|'.$udalostId, $msg_popis["Kod"]);
  }
  
  ZapisLog($log);
  
  $vysledek = array(
    'Zprava'=>new soapval('Zprava', false, $response_Zprava), //'tns:Zprava'
  );
  
  return VratVysledek($vysledek);
}
