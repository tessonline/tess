<?php
require("tmapy_config.inc");
include(FileUp2(".admin/run2_.inc"));
include(FileUp2("nastaveni.inc"));
include(FileUp2("redirect.inc"));
require_once(FileUp2(".admin/db/db_posta.inc"));
require_once(FileUp2(".admin/oth_funkce.inc"));
//inicializace NuSOAP
require_once($GLOBALS["TMAPY_LIB"]."/lib/nusoap/lib/nusoap.php"); 

ShowText('Čekejte prosím, kontaktuji AEC server e-podatelny ...');
//inicializace NuSOAP
require_once($GLOBALS["TMAPY_LIB"]."/lib/nusoap/lib/nusoap.php"); 
set_time_limit(0);
$debug=1;
// vypina/zapina debugovani
$fiddler=0;
// vypina/zapina monitorovani fiddlerem

$OperationsWSDL="dm_operations.wsdl";
$InfoWSDL="dm_info.wsdl";
$SearchWSDL="db_search.wsdl";
$OperationsURL="https://www.czebox.cz/DS/dz";
$InfoURL="https://www.czebox.cz/DS/dx";
$SearchURL="https://www.czebox.cz/DS/df";

$OperationsCertWSDL="dm_operations_cert.wsdl";
$InfoCertWSDL="dm_info_cert.wsdl";
$SearchCertWSDL="db_search.wsdl";
$OperationsCertURL="https://www.czebox.cz/cert/DS/dz";
$InfoCertURL="https://www.czebox.cz/cert/DS/dx";
$SearchCertURL="https://www.czebox.cz/cert/DS/df";

function QX($s)
// debugovaci funkce
{
//	global $debug;
/*
	if ($debug == 0)
	{
		return;
	}
*/
	echo($s."\r\n");
}

//echo $$adresa_ds;
//Die();



//a konec, mame cookie.
//Die();
//$client = new soapclient($adresa_ds, false,'192.168.110.34','8888','','','',2,2);
$client = new soapclient($adresa_ds, false);
$client->setCredentials($username, $password, 'basic');

$client->SetCookie($cookie[0],$cookie[1]);


//$client->SetHeaders(array('Authorization' => 'Basic '.base64_encode(str_replace(':','',$username).':'.$password)));

/*
$certRequest['cainfofile']='Organizational_CA.cer';
$certRequest["sslcertfile"] = "login.czebox.cz.cer";
$certRequest["sslkeyfile"] = "";


$client->setCredentials("", "", "certificate", $certRequest); 
*/
$client->soap_defencoding='UTF-8';
$client->decodeUTF8(false);
$err = $client->getError();
if ($err) {
    echo "<script>document.getElementById('upl_wait_message').style.display = 'none'</script>";
    echo $button_back;
    Die('AEC server e-podatelny není dostupný');
}
ShowText('Povedlo se, provedeme dummy');
/*
$result = $client->call('DummyOperation', array('DummyOperation'=>'test'),false,$adresa_ds);

echo '<h2>Request</h2>';
echo '<pre>' . htmlspecialchars($client->request, ENT_QUOTES) . '</pre>';
echo '<h2>Response</h2>';
echo '<pre>' . htmlspecialchars($client->response, ENT_QUOTES) . '</pre>';
echo '<h2>Debug</h2>';
echo '<pre>' . htmlspecialchars($client->debug_str, ENT_QUOTES) . '</pre>';
*/
/*
$client->setCredentials($username, $password, 'digest');
$result = $client->call('DummyOperation', array(),false,$adresa_ds);

echo '<h2>Request</h2>';
echo '<pre>' . htmlspecialchars($client->request, ENT_QUOTES) . '</pre>';
echo '<h2>Response</h2>';
echo '<pre>' . htmlspecialchars($client->response, ENT_QUOTES) . '</pre>';
*/
/*
$hlavicky=$client->GetCookies();
echo "<hr/>";

while (list($key,$val)=each($hlavicky))
{
  if (substr($val[name],0,3)=="IPC")
  {
    echo "Nastavime hlavicku";
    $client->SetCookie($val[name],$val[value]);
  }
}
*/
print_r($hlavicky);
//Die();
$dbOwnerInfo=array('dbType'=>'OVM','ic'=>'8181181');
$result = $client->call('FindDataBox', array('dbOwnerInfo'=>$dbOwnerInfo),false,$adresa_ds);

print_r($result);

echo '<h2>Request</h2>';
echo '<pre>' . htmlspecialchars($client->request, ENT_QUOTES) . '</pre>';
echo '<h2>Response</h2>';
echo '<pre>' . htmlspecialchars($client->response, ENT_QUOTES) . '</pre>';
// Display the debug messages
echo '<h2>Debug</h2>';
echo '<pre>' . htmlspecialchars($client->debug_str, ENT_QUOTES) . '</pre>';
