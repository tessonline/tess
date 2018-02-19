<?php

$GLOBALS['CONFIG_NPU']['PK_SERVICE'] = array(
  'url' => 'http://dtesbtest01.npudt.local:8080/katalogtest/FulltextSearchService',
  'url' => 'http://192.168.204.24:8080/katalogtest/FulltextSearchService',

  'url_StavInfo' => 'http://192.168.204.24:8080/katalogtest/PravniStavService',
  'url_AktInfo' => 'http://192.168.204.24:8080/katalogtest/PravniAktService',
  'url_PrvekInfo' => 'http://192.168.204.24:8080/katalogtest/PrvekService',
  'url_UdalostInfo' => 'http://192.168.204.24:8080/katalogtest/UdalostService',

  'url_StavBind' => 'http://192.168.204.24:8080/katalogtest/PravniStavApplicationBindingService',
  'url_AktBind' => 'http://192.168.204.24:8080/katalogtest/PravniAktApplicationBindingService',
  'url_PrvekBind' => 'http://192.168.204.24:8080/katalogtest/PrvekApplicationBindingService',
  'url_UdalostBind' => 'http://192.168.204.24:8080/katalogtest/UdalostApplicationBindingService',
  'url_KDBind' => 'http://192.168.204.24:8080/katalogtest/KDApplicationBindingService',

  'login' => $GLOBALS['SERVER_CONFIG']['SECURITY']['AUTH_SOAP_LOGIN'],
  'passwd' => $GLOBALS['SERVER_CONFIG']['SECURITY']['AUTH_SOAP_PASSWD']
);
/*
$GLOBALS['CONFIG_NPU']['PK_SERVICE'] = array(
  'url' => 'http://dtesbtest01.npudt.local:8080/katalogtest/FulltextSearchService',

  'url_StavInfo' => 'http://dtesbtest01.npudt.local:8080/katalogtest/PravniStavService',
  'url_AktInfo' => 'http://dtesbtest01.npudt.local:8080/katalogtest/PravniAktService',
  'url_PrvekInfo' => 'http://dtesbtest01.npudt.local:8080/katalogtest/PrvekService',
  'url_UdalostInfo' => 'http://dtesbtest01.npudt.local:8080/katalogtest/UdalostService',

  'url_StavBind' => 'http://dtesbtest01.npudt.local:8080/katalogtest/PravniStavApplicationBindingService',
  'url_AktBind' => 'http://dtesbtest01.npudt.local:8080/katalogtest/PravniAktApplicationBindingService',
  'url_PrvekBind' => 'http://dtesbtest01.npudt.local:8080/katalogtest/PrvekApplicationBindingService',
  'url_UdalostBind' => 'http://dtesbtest01.npudt.local:8080/katalogtest/UdalostApplicationBindingService',
  'url_KDBind' => 'http://dtesbtest01.npudt.local:8080/katalogtest/KDApplicationBindingService',

  'login' => $GLOBALS['SERVER_CONFIG']['SECURITY']['AUTH_SOAP_LOGIN'],
  'passwd' => $GLOBALS['SERVER_CONFIG']['SECURITY']['AUTH_SOAP_PASSWD']
);
*/


$GLOBALS['CONFIG_NPU']['APP_ID'] = 12; //id ESS v PK

//$GLOBALS['CONFIG_NPU']['PK_PRVEK_BINDING'] = $GLOBALS['CONFIG_NPU']['PK_SERVICE'];
//$GLOBALS['CONFIG_NPU']['PK_PRVEK_BINDING']['url'] = 'http://dtesbtest01.npudt.local:8080/katalogtest/pkprvekapplicationbinding';

//$GLOBALS['CONFIG_NPU']['URL_PAM_KAT'] = 'http://iispptest.npu.cz/katalog_ext?presenter=ElementsResults&action=element&element=';

$GLOBALS['PK_CIS'] = array(
  '5' => array('kod' => 'PK_5', 'text' => 'objekt soupisu', 'info' => 'PagisServicePrvekInfo', 'bind' => 'PagisServicePrvekBind'),
  '8' => array('kod' => 'PK_8', 'text' => 'záznam ústředního seznamu', 'info' => 'PagisServiceStavInfo', 'bind' => 'PagisServiceStavBind'),
  '10' => array('kod' => 'PK_10', 'text' => 'památková péče', 'info' => 'PagisServiceUdalostInfo', 'bind' => 'PagisServiceUdalostBind'),
  '11' => array('kod' => 'PK_11', 'text' => 'záznam o právním aktu', 'info' => 'PagisServiceAktInfo', 'bind' => 'PagisServiceAktBind'),
  '0' => array('kod' => 'PK', 'text' => 'bez rozlišení', 'bind' => 'PkKDApplicationBinding'),
);


