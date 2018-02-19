<?php
$xml='<?xml version="1.0" encoding="UTF-8"?><SOAP-ENV:Envelope SOAP-ENV:encodingStyle="http://schemas.xmlsoap.org/soap/encoding/" xmlns:SOAP-ENV="http://schemas.xmlsoap.org/soap/envelope/" xmlns:xsd="http://www.w3.org/2001/XMLSchema" xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance" xmlns:SOAP-ENC="http://schemas.xmlsoap.org/soap/encoding/"><SOAP-ENV:Header><noname xsi:type="xsd:string">Basic YWFyaXRpOlh2OU12N0NoOFE=</noname></SOAP-ENV:Header><SOAP-ENV:Body><DummyOperation></DummyOperation></SOAP-ENV:Body></SOAP-ENV:Envelope>';
  $headers = Array("Content-type: text/xml");
  $ch = curl_init();
  
  $url="https://www.czebox.cz/DS/df";
  $auth="aariti:Xv9Mv7Ch8Q";
  //$url="localhost:8080/xqw/xervlet/sps/sps_interface";
  
  curl_setopt($ch, CURLOPT_URL, $url);
  curl_setopt($ch, CURLOPT_VERBOSE, 1);
  curl_setopt($ch, CURLOPT_HEADER, 1);
  curl_setopt($ch, CURLOPT_HTTPHEADER, array("Content-Type: text/xml; charset=UTF-8"));
  curl_setopt($ch, CURLOPT_POST, 1);
  curl_setopt($ch, CURLOPT_POSTFIELDS, $xml);
  curl_setopt($ch, CURLOPT_RETURNTRANSFER, 1);
  curl_setopt($ch, CURLOPT_USERPWD,$auth);  
  $http_result = curl_exec($ch);
  $error = curl_error($ch);
  $http_code = curl_getinfo($ch ,CURLINFO_HTTP_CODE);
  
  curl_close($ch);
echo $http_result;
