<?php
//priklad na konektor EED
require("tmapy_config.inc");
include(FileUp2(".admin/run2_.inc"));

//fce na dekodovani textu z utf8
function TxtEncoding4Soap($txt){
  $to = $GLOBALS["POSTA_SECURITY"]->Security->configuration['charset'];
  return iconv('UTF-8',$to, $txt);
}


//inicializace NuSOAP
require_once($GLOBALS["TMAPY_LIB"]."/lib/nusoap/lib/nusoap.php"); 

//kde bezi SOAP server
$ns="http://demo2003.matej3.tmapserver.cz/ost/posta/interface/konektor/server/soap.php";

//nadefinujeme klienta
$client = new soapclient($ns, false);
$client->soap_defencoding='UTF-8';
$client->decodeUTF8(false);
$err = $client->getError();
if ($err) {
    Die('SOAP server není dostupný');
}

/*
a jdeme pracovat

Budeme potrebovat 4 fce:
login
get_cj - dostanu cj.
send_doc - odeslu dokument
logout

get_cj a send_doc muzu provest nekolikrat... login plati po dobu 30 minut, pak automaticky vyhodi.
*/


//fce LOGIN 
//musite znat tri parametry software_id, username, password - vse vam musi dat spisovka, podle software_id si pak EED nacte odpovidajici konfiguraci
if (!$result = $client->call('login',array( 
    'software_id'=>'TWIST_PLATAKY',
    'username'=>'onma',
    'password'=>'test',
  ),
  false,$ns)
) Die('Chyba v login fci SOAP serveru'); //kua, chyba v definici SOAP

if ($result[faultstring]) Die(TxtEncoding4Soap($result[faultstring])); //Nejaka chybka uzivatele, neproslo prihlaseni 
else 
  $session_id=$result["session_id"];
//mame session_id, jsme prihlaseny


//zjistime si CJ pro novy dokument
//fce GET_CJ 
if (!$result = $client->call('get_cj',array( 
    'session_id'=>$session_id,
    'zpracovatel_id'=>66,
  ),
  false,$ns)
) Die('Chyba v get_cj fci SOAP serveru'); //kua, chyba v definici SOAP

if ($result[faultstring]) Die(TxtEncoding4Soap($result[faultstring])); //Nejaka chybka uzivatele, neproslo vytvoreni cj
$dokument_id=$result["dokument_id"];
$cislo_jednaci=$result["cislo_jednaci"];
echo "Dokument_id: ".$dokument_id."<br/>";
echo "Cislo jednaci: ".$cislo_jednaci."<br/>";



//tady si zpracujeme texty
//to uz je na dane aplikaci



//a odesleme dopis, pozor, data musi byt v UTF8 !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
$data=array(
      'TYP_DOC'=>1, 
      'DATUM_ODESLANI'=>'25.9.2007 13:00',
      'VEC'=>'test',
      'TYP_ADR'=>'F',
      'PRIJMENI'=>$prijmeni,
      'JMENO'=>$jmeno,
      'ORGANIZACE'=>'',
      'ODDELENI'=>'',
      'OSOBA'=>'',
       'ULICE'=>'test',
       'CP'=>155,
       'COR'=>0,
       'MESTO'=>'test',
       'PSC'=>'50012',
       'OBALKA'=>0,
       'ODESLANI'=>0, //rem, bude prirazeno z konfigurace - test
);

if (!$result = $client->call('send_doc',array( 
    'session_id'=>$session_id,
    'dokument_id'=>$dokument_id,
    'dokument_data'=>new soapval('dokument_data','tns:dokument',$data),
  ),
  false,$ns)
) Die('Chyba v send_doc fci SOAP serveru'); //kua, chyba v definici SOAP

if ($result[faultstring]) Die(TxtEncoding4Soap($result[faultstring])); //Nejaka chybka uzivatele, neproslo logout 
//Dokument odeslan

//fce LOGOUT 
if (!$result = $client->call('logout',array( 
    'session_id'=>$session_id,
  ),
  false,$ns)
) Die('Chyba v logout fci SOAP serveru'); //kua, chyba v definici SOAP

if ($result[faultstring]) Die(TxtEncoding4Soap($result[faultstring])); //Nejaka chybka uzivatele, neproslo logout 
else
  echo 'Logout OK<br/>';
  
  
  
  
/*
DEBUG PRO SOAP FUNKCE, vypisuje kompletni komunikaci, kdyz ladite soap fce, tak at vite, co to dela 
echo '<h2>Request</h2>';
echo '<pre>' . htmlspecialchars($client->request, ENT_QUOTES) . '</pre>';
echo '<h2>Response</h2>';
echo '<pre>' . htmlspecialchars($client->response, ENT_QUOTES) . '</pre>';
// Display the debug messages
echo '<h2>Debug</h2>';
echo '<pre>' . htmlspecialchars($client->debug_str, ENT_QUOTES) . '</pre>';
*/
?>
