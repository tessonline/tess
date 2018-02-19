<?php
require("tmapy_config.inc");
include(FileUp2(".admin/run2_.inc"));
include_once(FileUp2(".admin/status.inc"));

/*  SOAP server pro CZECH POINT
 *  ================
 *
 *
 */

//inicializace NuSOAP
require_once($GLOBALS["TMAPY_LIB"]."/lib/nusoap/lib/nusoap.php"); 
include_once(FileUp2(".admin/db/db_default.inc"));
require_once(FileUp2(".admin/db/db_posta.inc"));
require_once(FileUp2(".admin/oth_funkce.inc"));
require_once(FileUp2(".admin/soap_funkce.inc"));

//$ns = "http://ws.exprit.cz/ws602"; // prostor n8yvu sluzby
$ns = "http://www.software602.cz/webservices/602xml";
$server = new soap_server();

$wsdlstyle='literal'; //encoded|literal

$wsdluse='rpc'; //rpc|document


/*$wsdlstyle='rpc'; //rpc|document
*/

$servicename = 'login';
//vracime vlastni xml
$server->methodreturnisliteralxml = true;
//$server->wsdl->schemaTargetNamespace = $ns;
$server->configureWSDL('EED', 'tns:'.$servicename, false, $wsdlstyle); // nazev webove sluzby

//nacteme data z utf8 
$server->soap_defencoding = 'UTF-8';
//a zabranime mu v konevrzi, aby ty data byly citelny (musi to tam byt!!!!Â§)
$server->decode_utf8 = false;

//nastavime, ze kdyz neni kodovani od protistrany, tak dame UTF-8
$server->my_xml_encoding = 'UTF-8';

//typy
$server->wsdl->addComplexType(
  'dokument','complexType','struct','all','',
  array(
    'identifikace' => array('type'=>'tns:identifikace'),
    'metadata'=> array('type'=>'tns:metadata'),
    'prilohy'=> array('type'=>'tns:prilohy'),
    'adresy'=> array('type'=>'tns:adresy'),
  )
);

$server->wsdl->addComplexType(
  'prilohy','complexType','struct','all','',
  array(
    'priloha' => array('type'=>'tns:priloha'),
  )
);

$server->wsdl->addComplexType(
  'adresy','complexType','struct','all','',
  array(
    'adresa' => array('type'=>'tns:adresa'),
  )
);



$server->wsdl->addComplexType(
  'identifikace','complexType','struct','all','',
  array(
    'dokument_id' => array('type'=>'xsd:int'),
  )
);

$server->wsdl->addComplexType(
  'metadata','complexType','struct','all','',
  array(
    'cislo_jednaci' => array('type'=>'xsd:string'),
    'typ_dokumentu' => array('type'=>'xsd:string'),
    'vec' => array('type'=>'xsd:string'),
    'datum_dokumentu' => array('type'=>'xsd:string'),
    'datum_doruceni' => array('type'=>'xsd:string'),
    'datum_odeslani' => array('type'=>'xsd:string'),
    'poznamka' => array('type'=>'xsd:string'),
  )
);

$server->wsdl->addComplexType(
  'priloha','complexType','struct','all','',
  array(
    'typ' => array('type'=>'xsd:string'),
    'nazev' => array('type'=>'xsd:string'),
    'format' => array('type'=>'xsd:string'),
    'filename' => array('type'=>'xsd:string'),
    'obsah' => array('type'=>'xsd:base64Binary'),
  )
);

$server->wsdl->addComplexType(
  'adresa','complexType','struct','all','',
  array(
    'typ' => array('type'=>'xsd:string'),
    'typ_doruceni' => array('type'=>'xsd:string'),
    'organizace' => array('type'=>'xsd:string'),
    'organizacni_jednotka' => array('type'=>'xsd:string'),
    'jmobyv' => array('type'=>'xsd:string'),
    'prijobyv' => array('type'=>'xsd:string'),
    'osloveni' => array('type'=>'xsd:string'),
    'titpredjm' => array('type'=>'xsd:string'),
    'titzajm' => array('type'=>'xsd:string'),
    'funkce' => array('type'=>'xsd:string'),
    'obec' => array('type'=>'xsd:string'),
    'cobce' => array('type'=>'xsd:string'),
    'mcast' => array('type'=>'xsd:string'),
    'uvp' => array('type'=>'xsd:string'),
    'cp' => array('type'=>'xsd:string'),
    'cev' => array('type'=>'xsd:string'),
    'cor' => array('type'=>'xsd:string'),
    'psc' => array('type'=>'xsd:string'),
    'k_statu' => array('type'=>'xsd:string'),
    'po_box' => array('type'=>'xsd:string'),
    'poznamka' => array('type'=>'xsd:string'),
    'tel_fax' => array('type'=>'xsd:string'),
    'email' => array('type'=>'xsd:string'),
  )
);

$server->wsdl->addComplexType(
  'Login','complexType','struct','all','',
  array(
    'Name' => array('type'=>'xsd:string'),
    'Password' => array('type'=>'xsd:string'),
  )
);

$server->wsdl->addComplexType(
  'Logout','complexType','struct','all','',
  array(
    'LogToken' => array('type'=>'xsd:string'),
  )
);

$server->wsdl->addComplexType(
  'GetReferenceNumber','complexType','struct','all','',
  array(
    'LogToken' => array('type'=>'xsd:string'),
    'Params' => array('type'=>'xsd:string'),
  )
);

$server->wsdl->addComplexType(
  'ProcessXmlData','complexType','struct','all','',
  array(
    'LogToken' => array('type'=>'xsd:string'),
    'XmlData' => array('type'=>'xsd:string'),
  )
);



// metody a jeji parametry
$server->register(
  'Login',
  array('Name'=>'xsd:string', 'Password'=>'xsd:string'),
  array('' => 'xsd:string'),
   'tns',                              // namespace
   'tns:'.$servicename,                // soapaction
   $wsdlstyle,                         // style
   $wsdluse,                           // use
   ""      // documentation
);
//    $wsdlstyle,                         // style
//    $wsdluse,                           // use

$server->register(
  'Logout',
  array('Logout' => 'xsd:string'),
  array('' => 'xsd:string'),
   'tns',                              // namespace
   'tns:'.$servicename,                // soapaction
   $wsdlstyle,                         // style
   $wsdluse,                           // use
   ""      // documentation
);

$server->register(
  'GetReferenceNumber',
  array('LogToken' => 'xsd:string','Params' => 'xsd:string'),
  array('return' => 'xsd:string'),
   'tns',                              // namespace
   'tns:'.$servicename,                // soapaction
   $wsdlstyle,                         // style
   $wsdluse,                           // use
   ""      // documentation
);

$server->register(
  'GetDocument',
  array('LogToken' => 'xsd:string','ReferenceNumber' => 'xsd:string','DocumentID'=>'xsd:string', 'DocumentType' => 'xsd: number'),
  array('return' => 'xsd:string'),
   'tns',                              // namespace
   'tns:'.$servicename,                // soapaction
   $wsdlstyle,                         // style
   $wsdluse,                           // use
   ""      // documentation
);


$server->register(
  'ProcessXmlData',
  array('LogToken' => 'xsd:string','XmlData' => 'xsd:string'),
  array('' => 'xsd:string'),
   'tns',                              // namespace
   'tns:'.$servicename,                // soapaction
   $wsdlstyle,                         // style
   $wsdluse,                           // use
   ""      // documentation
);

$server->register(
  'GetVersion',
  array(),
  array(),
   'tns',                              // namespace
   'tns:'.$servicename,                // soapaction
   $wsdlstyle,                         // style
   $wsdluse,                           // use
   ""      // documentation
);

$server->register(
  'InitializeData',
  array(),
  array(),
   'tns',                              // namespace
   'tns:'.$servicename,                // soapaction
   $wsdlstyle,                         // style
   $wsdluse,                           // use
   ""      // documentation
);



require('.admin/sps_cp_login.inc');
require('.admin/sps_cp_getreferencenumber.inc');
require('.admin/sps_cp_processform.inc');
require('.admin/sps_cp_logout.inc');
require('.admin/sps_cp_getversion.inc');
require('.admin/sps_cp_initializedata.inc');
require('.admin/sps_cp_getdocument.inc');

$server->service($HTTP_RAW_POST_DATA);

?>
