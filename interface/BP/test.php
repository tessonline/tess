ďťż<?php
require("tmapy_config.inc");
require(FileUp2(".admin/brow_.inc"));
require(FileUp2("html_header_posta.inc"));
require_once(FileUp2(".admin/security_obj.inc"));
require_once(FileUp2(".admin/security_name.inc"));
require_once($GLOBALS["TMAPY_LIB"]."/lib/nusoap/lib/nusoap.php"); 

$url = "http://mu-lnl-test-spis.bilbo5.tmapserver.cz/ost/posta/interface/eed/server/soap.php";
$url = "http://tmapy-demo-zis.matej5.tmapserver.cz/ost/posta/interface/eed/test.php";

$loginname = 'unispis';
$password = 'Uni2011';
$client = new TW_SoapClient($url, false);
//$client->namespaces = 'SOAP-ENV';
$client->namespaces['tns']='http://isds.czechpoint.cz';
$client->setCredentials($loginname,$password);
$client->soap_defencoding='UTF-8';
$client->methodreturnisliteralxml=true;

$client->xml_encoding='UTF-8';
$client->decodeUTF8(false); 
$err = $client->getError();
if ($err) {
    echo('SOAP server nenĂ­ dostupnĂ˝');
}

$doc = array( 'dbOwnerInfo' => array('pnLastName'=>'MalĂ˝'));
//Die();
$client->call('SPS_FindDataBox',$doc,'','','');


echo '<h2>Request</h2>';
echo '<pre>' . htmlspecialchars(Str_replace('<',"\n<",$client->request), ENT_QUOTES) . '</pre>';
echo '<h2>Response</h2>';
echo '<pre>' . htmlspecialchars(Str_replace('<',"\n<",$client->response), ENT_QUOTES) . '</pre>';
// Display the debug messages
echo '<h2>Debug</h2>';
echo '<pre>' . htmlspecialchars($client->debug_str, ENT_QUOTES) . '</pre>';


