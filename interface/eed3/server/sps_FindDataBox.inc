<?php
//Funkce zprostĹedkuje pro IS RĹ˝P dotaz na existenci datovĂŠ schrĂĄnky... 
function FindDataBox($dbOwnerInfo, $Autorizace=array()) {
  //nastaveni parametru
  global $server, $soap;
  $server->responseMethodname = $server->methodname;
  $dbOwnerInfo = $server->methodparams["dbOwnerInfo"];
  //print_r($Udalosti);
  
  if ($GLOBALS[CONFIG_POSTA][DS][ds_cert_id]) $certifikat=VratCestukCertifikatu(0,$GLOBALS[CONFIG_POSTA][DS][ds_cert_id],1); else $certifikat='';

  $schranka=new ISDSbox($GLOBALS[CONFIG_POSTA][DS][ds_user],$GLOBALS[CONFIG_POSTA][DS][ds_passwd],$certifikat);

  $hodnoty=$schranka->FindDataBox($dbOwnerInfo);
  if ($schranka->StatusCode<>'0000')  {  
    $msg_popis["Kod"] = $schranka->StatusCode;
    $msg_popis["Popis"] = $schranka->StatusMessage;
  }
  else {
    $msg_popis["Kod"] = '0000';
    $msg_popis["Popis"] = "OK";  

  }
  
  Response_OperaceStatus($response_OperaceStatus, $msg_popis["Kod"], $msg_popis["Popis"]);
//print_r($response_OperaceStatus);

  $vysledek = array(
    'dbResults'=>new soapval('dbResults', false, $hodnoty), //tns:tVlastniDokument
    'OperaceStatus'=>new soapval('OperaceStatus', false, $response_OperaceStatus),  //'tns:tOperaceStatus'
  );  
    
  return VratVysledek($vysledek);  

}
