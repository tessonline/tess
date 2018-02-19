<?php
require('tmapy_config.inc');
include(FileUp2('.admin/run2_.inc'));
require(FileUp2('.admin/soap_funkce.inc'));
require(FileUp2('.admin/fce.inc'));

require(FileUp2('.admin/isds_.inc'));
require_once(FileUp2('.admin/upload_.inc'));
require(FileUp2('.admin/upload_funkce.inc'));

/*  SOAP server pro EED firmy T-MAPY
 *  ================================
 *  obslouzene funkce
 *
 *  Synchroni fce()
 *  ---------------    
 *  DorucenyDokumentZalozeni
 *  VlastniDokumentZalozeni 
 *  SpisZalozeni 
 *  -- FindDataBox
 *
 *  ASynchroni fce()
 *  ----------------
 *  UdalostiRequest
 *  ermsAsyn 
 */

//inicializace NuSOAP
require_once(FileUp2('.config/config_rzp.inc'));
require_once($GLOBALS['TMAPY_LIB'].'/lib/nusoap/lib/nusoap.php'); 
require_once(FileUp2('.admin/db/db_posta.inc'));
require_once(FileUp2('.admin/oth_funkce.inc'));

$soap['defencoding'] = 'UTF-8';
$soap['error'] = '';
$soap['wsdlstyle'] = 'rpc'; //rpc|document
$soap['wsdluse'] = 'literal'; //encoded|literal
$soap['servicename'] = 'eed_konektor';
$soap['methodURI'] = "http://nsess.public.cz/erms/v_01_00 xmlns:ess='http://mvcr.cz/ess/v_1.0.0.0";
//$soap['namespace_ess'] = 'ess:';

$usedNamespaces = array(
  'erms' => 'http://nsess.public.cz/erms/v_01_00',
  'ess' => 'http://mvcr.cz/ess/v_1.0.0.0',
);


$server = new soap_server();
//$server->methodreturnisliteralxml = true;
$server->configureWSDL($soap['servicename'], 'tns:'.$soap['servicename'], false, $soap['wsdlstyle']);
//$server->wsdl->schemaTargetNamespace = 'tns:'.$soap['servicename'];
//$server->wsdl->namespaces['erms'] = 'http://nsess.public.cz/erms/v_01_00';
//$server->wsdl->namespaces['ess'] = 'http://mvcr.cz/ess/v_1.0.0.0';

//$server->wsdl->usedNamespaces = $usedNamespaces;

$server->soap_defencoding = $soap['defencoding'];
$server->decode_utf8 = false;
$server->debug_flag = false;

/***** MAP **********************************************/

require('type_dbTypes.inc');
require('type_dmBaseTypes.inc');
require('type_ermsTypes.inc');
require('type_ess_ns.inc');
require('type_ermsAsynU.inc');
require('type_ermsIFSyn.inc');
require('type_ermsIFAsyn.inc');
require('type_ermsIF.inc');

//print_r($server->wsdl);

/***** REGISTER FCE *************************************/

//Synchroni zpracovani funkce
/*
$server->register(
  'DorucenyDokumentZalozeniRequest',
  array(
    'UdalostiPredchazejici'=>'tns:tUdalostiSyn', 
    'DorucenyDokument'=>'tns:tDorucenyDokument', 
    'Autorizace'=>'tns:tAutorizace'
  ),
  array(
    'DorucenyDokument'=>'tns:tDorucenyDokument', 
    'OperaceStatus'=>'tns:tOperaceStatus'
  ),
  'tns',                                       // namespace
  false,                // soapaction
  $soap['wsdlstyle'],                 // style
  $soap['wsdluse'],                   // use
  "DorucenyDokumentZalozeni\n".       // documentation
  "Parametry: ".
  "Vstup: \n".
  "Odpoved: "
);

//Synchroni zpracovani funkce
$server->register(
  'VlastniDokumentZalozeniRequest',
  array(
    'UdalostiPredchazejici'=>'tns:tUdalostiSyn', 
    'VlastniDokument'=>'tns:tVlastniDokument', 
    'Autorizace'=>'tns:tAutorizace'
  ),
  array(
    'VlastniDokument'=>'tns:tVlastniDokument', 
    'OperaceStatus'=>'tns:tOperaceStatus'
  ),
  'tns',                                       // namespace
  false,                // soapaction
  $soap['wsdlstyle'],                 // style
  $soap['wsdluse'],                   // use
  "VlastniDokumentZalozeni\n".        // documentation
  "Parametry: ".
  "Vstup: \n".
  "Odpoved: "
);
*/
//Synchroni zpracovani funkce
$server->register(
  'DokumentZalozeniRequest',
  array(
    'UdalostiPredchazejici'=>'tns:tUdalostiSyn',
    'ProfilDokumentu'=>'tns:tProfilDokumentu',
    'Autorizace'=>'tns:tAutorizace'
  ),
  array(
    'ProfilDokumentu'=>'tns:tProfilDokumentu',
    'OperaceStatus'=>'tns:tOperaceStatus'
  ),
  'tns',                                       // namespace
  false,                // soapaction
  $soap['wsdlstyle'],                 // style
  $soap['wsdluse'],                   // use
  "DokumentZalozeni\n".        // documentation
  "Parametry: ".
  "Vstup: \n".
  "Odpoved: "
);


//Synchroni zpracovani funkce
$server->register(
  'ProfilDokumentuZadostRequest',
  array(
    'IdDokument'=>'tIdDokument', 
    'Autorizace'=>'tns:tAutorizace'
  ),
  array(
    'ProfilDokumentu'=>'tns:tProfilDokumentu',
    'OperaceStatus'=>'tns:tOperaceStatus'
  ),
  'tns',                                       // namespace
  false,                // soapaction
  $soap['wsdlstyle'],                 // style
  $soap['wsdluse'],                   // use
  "SpisZalozeni\n".                   // documentation
  "Parametry: ".
  "Vstup: \n".
  "Odpoved: "
);

//Synchroni zpracovani funkce
$server->register(
  'SpisZalozeniRequest',
  array(
    'UdalostiPredchazejici'=>'tns:tUdalostiSyn', 
    'ProfilSpisu'=>'tns:tProfilSpisu', 
    'DokumentyVlozene'=>'tns:ttDokumentyVlozene_request', 
    'Autorizace'=>'tns:tAutorizace'
  ),
  array(
    'ProfilSpisu'=>'tns:tProfilSpisu', 
    'DokumentyVlozene'=>'tns:ttDokumentyVlozene_response', 
    'OperaceStatus'=>'tns:tOperaceStatus'
  ),
  'tns',                                       // namespace
  false,                // soapaction
  $soap['wsdlstyle'],                 // style
  $soap['wsdluse'],                   // use
  "SpisZalozeni\n".                   // documentation
  "Parametry: ".
  "Vstup: \n".
  "Odpoved: "
);

/*
//Synchroni zpracovani funkce
$server->register(
  'FindDataBox',
  array(
    'dbOwnerInfo'=>'tns:tDbOwnerInfo', 
    'Autorizace'=>'tns:tAutorizace'
  ),
  array( 
    'dbResults'=>'tns:tDbOwnersArray', 
    'OperaceStatus'=>'tns:tOperaceStatus'
  ),
  //array( 'OperaceStatus'=>'tns:tOperaceStatus'),
  'tns',                                       // namespace
  false,                // soapaction
  $soap['wsdlstyle'],                 // style
  $soap['wsdluse'],                   // use
  "FindDataBox\n".                   // documentation
  "Parametry: ".
  "Vstup: \n".
  "Odpoved: "
);
*/
/*
//Synchroni zpracovani funkce
$server->register(
  'SpisZalozeni',
  array('UdalostiPredchazejici'=>'tns:tUdalostiSyn', 'ProfilSpisu'=>'tns:tProfilSpisu', 'DokumentyVlozene'=>'tns:DokumentyVlozene', 'Autorizace'=>'tns:tAutorizace'),
  array('ProfilSpisu'=>'tns:tProfilSpisu', 'DokumentyVlozene'=>'tns:DokumentyVlozene', 'OperaceStatus'=>'tns:tOperaceStatus'),
   'tns',                                       // namespace
   'tns:'.$soap["servicename"],                // soapaction
   $soap['wsdlstyle'],                 // style
   $soap['wsdluse'],                   // use
   "SpisZalozeni\n".                   // documentation
   "Parametry: ".
   "Vstup: \n".
   "Odpoved: "
);
*/

//Synchroni zpracovani asynchroni funkce
$server->register(
  'UdalostiRequest',
  array(
    'Udalosti'=>'tns:tUdalostiSyn'
  ),
  array(
    'Zpravy'=>'tns:tZpravy',
    'OperaceStatus'=>'tns:tOperaceStatus'
  ),
  'tns',                                       // namespace
  false,                // soapaction
  $soap['wsdlstyle'],                         // style
  $soap['wsdluse'],                           // use
  "Synchroni zpracovani asynchroni funkce\n".       // documentation
  "Parametry: ".
  "Vstup: \n".
  "Odpoved: "
);

//Asynchroni zpracovani asynchronich funkci
$server->register(
  'ermsAsyn',
  array(
    'Udalosti'=>'tns:Udalosti'
  ),
  array(
    'Udalosti'=>'tns:tUdalosti',
    'Zpravy'=>'tns:tZpravy'
  ),
  'tns',                                       // namespace
  false,                // soapaction
  $soap['wsdlstyle'],                         // style
  $soap['wsdluse'],                           // use
  "Asynchroni zpracovani asynchronich funkci\n".       // documentation
  "Parametry: ".
  "Vstup: \n".
  "Odpoved: "
);

$server->register(
  'WsTestRequest',
  array(
    'WsTestId'=>'xsd:string',
    'Autorizace'=>'tns:tAutorizace'
  ),
  array(
    'WsTestId'=>'xsd:string',
    'OperaceStatus'=>'tns:tOperaceStatus'
  ),
  'tns',                                       // namespace
  false,                // soapaction
  $soap['wsdlstyle'],                         // style
  $soap['wsdluse'],                           // use
  "Asynchroni zpracovani asynchronich funkci\n".       // documentation
  "Parametry: ".
  "Vstup: \n".
  "Odpoved: "
);

/***** LOAD FCE *****************************************/

//Synchroni funkce a zpracovani 
//require('sps_DorucenyDokumentZalozeni.inc');
//require('sps_VlastniDokumentZalozeni.inc');
require('sps_DokumentZalozeni.inc');
require('sps_ProfilDokumentuZadost.inc');
require('sps_SpisZalozeni.inc');
//require('sps_FindDataBox.inc');
require('sps_Udalosti.inc');


//Asynchroni funkce a zpracovani 
require('sps_Asyn_func.inc');
require('sps_ErmsAsyn.inc');

require('sps_wstest.inc');

//Response
include('sps_Response.inc');

//Message
require('sps_Message.inc');

/**** SERVICE *******************************************/

$HTTP_RAW_POST_DATA = isset($HTTP_RAW_POST_DATA) ? $HTTP_RAW_POST_DATA : '';

$HASHID_LOG = Date('d.m.Y H:i:s u');
$buffer = '';
@$server->service($HTTP_RAW_POST_DATA);
$out = $server->responseSOAP;
WriteHTTPlog($HASHID_LOG,$HTTP_RAW_POST_DATA,$out);

