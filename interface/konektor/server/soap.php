<?php
require("tmapy_config.inc");
include(FileUp2(".admin/run2_.inc"));
require(FileUp2(".admin/soap_funkce.inc"));
require(FileUp2(".admin/upload_funkce.inc"));
require(FileUp2(".admin/fce.inc"));
require(FileUp2(".admin/status.inc"));
require_once(FileUp2('.admin/upload_.inc'));


/*  SOAP server pro EED firmy T-MAPY
 *  ================================
 *  obslouzene funkce
 *
 * login
 * get_cj
 * get_doc
 * get_files
 * work_on
 * send_doc
 * send_files
 * logout
 *
 * 2009-07-23, pridany fce
 * spis_zalozeni
 * spis_vlozeni
 * spis_predani
 * spis_uzavreni
 *
 */

//inicializace NuSOAP
$GLOBALS['konektor']=$konektor;
$GLOBALS['LAST_USER_ID']=$LAST_USER_ID;
require_once($GLOBALS["TMAPY_LIB"]."/lib/nusoap/lib/nusoap.php"); 
require_once(FileUp2(".admin/db/db_posta.inc"));
require_once(FileUp2(".admin/oth_funkce.inc"));

//vytvoří objekt uploadu

$server = new soap_server();

$soap_defencoding = 'UTF-8';
$error='';
$wsdlstyle='rpc'; //rpc|document
$wsdluse='encoded';  //encoded|literal
$servicename='eed_konektor';

//$server->methodreturnisliteralxml = true;
$server->soap_defencoding = 'UTF-8';

$server->configureWSDL($servicename, 'tns:'.$servicename, false, $wsdlstyle);
$server->wsdl->schemaTargetNamespace = $ns;

//nacteme data z utf8
//a zabranime mu v konevrzi, aby ty data byly citelny (musi to tam byt!!!!§)
$server->decode_utf8 = false;
$server->debug_flag = false;
$server->xml_encoding = 'UTF-8';

$server->wsdl->addComplexType(
  'soubor','complexType','struct','all','',
  array(
    'FILE_ID'=>array('name'=>'FILE_ID','type'=>'xsd:integer'),
    'FILE_NAME'=>array('name'=>'FILE_NAME','type'=>'xsd:string'),
    'FILE_DESC'=>array('name'=>'FILE_DESC','type'=>'xsd:string','nillable'=>'true'),
    'FILE_SIZE'=>array('name'=>'FILE_SIZE','type'=>'xsd:integer','nillable'=>'true'),
    'BIND_TYPE'=>array('name'=>'BIND_TYPE','type'=>'xsd:string','nillable'=>'true'),
    'FILE_DATA'=>array('name'=>'FILE_DATA','type'=>'xsd:base64Binary')
  )
);

$server->wsdl->addComplexType(
  'soubory','complexType','array','sequence','',
  array(
    'soubor'=>array('name'=>'soubor', 'type'=>'tns:soubor', 'maxOccurs'=>'unbounded', 'minOccurs'=>'0', 'nillable'=>'true')
  ),
  array(),
  'tns:soubor'
);


//komplexni typy
$server->wsdl->addComplexType(
  'dokument','complexType','struct','all','',
  array(
    'DOKUMENT_ID'=>array('name'=>'DOKUMENT_ID','type'=>'xsd:integer'),
    'EV_CISLO'=>array('name'=>'EV_CISLO','type'=>'xsd:string'),
    'CISLO_JEDNACI'=>array('name'=>'CISLO_JEDNACI','type'=>'xsd:string'),
//    'CISLO_SPISU'=>array('name'=>'CISLO_SPISU','type'=>'xsd:string'),
//    'NAZEV_SPISU'=>array('name'=>'NAZEV_SPISU','type'=>'xsd:string'),
    'TYP_DOC'=>array('name'=>'TYP_DOC','type'=>'xsd:string'),
    'DATUM'=>array('name'=>'DATUM','type'=>'xsd:dateTime'),
    'VEC'=>array('name'=>'VEC','type'=>'xsd:string'),
    'TYP_ADR'=>array('name'=>'TYP_ADR','type'=>'xsd:string'),
    'PRIJMENI'=>array('name'=>'PRIJMENI','type'=>'xsd:string'),
    'JMENO'=>array('name'=>'JMENO','type'=>'xsd:string'),
    'ORGANIZACE'=>array('name'=>'ORGANIZACE','type'=>'xsd:string'),
    'RCIC'=>array('name'=>'RCIC','type'=>'xsd:string'),
    'ODDELENI'=>array('name'=>'ODDELENI','type'=>'xsd:string'),
    'OSOBA'=>array('name'=>'OSOBA','type'=>'xsd:string'),
    'ULICE'=>array('name'=>'ULICE','type'=>'xsd:string'),
    'CP'=>array('name'=>'CP','type'=>'xsd:integer'),
    'COR'=>array('name'=>'COR','type'=>'xsd:integer'),
    'MESTO'=>array('name'=>'MESTO','type'=>'xsd:string'),
    'PSC'=>array('name'=>'PSC','type'=>'xsd:string'),
    'DS'=>array('name'=>'DS','type'=>'xsd:string'),
    'ADRESAT_CJ'=>array('name'=>'ADRESAT_CJ','type'=>'xsd:string'),
    'ODBOR'=>array('name'=>'ODBOR','type'=>'xsd:integer'),
    'ZPRACOVATEL'=>array('name'=>'ZPRACOVATEL','type'=>'xsd:integer'),
    'OBALKA'=>array('name'=>'OBALKA','type'=>'xsd:integer'),
    'ODESLANI'=>array('name'=>'ODESLANI','type'=>'xsd:integer'),
    'SKARTACE_ID'=>array('name'=>'SKARTACE_ID','type'=>'xsd:integer'),
    'SKARTACNI_KOD'=>array('name'=>'SKARTACNI_KOD','type'=>'xsd:string'),
    'ZMOCNENI_ZAKON'=>array('name'=>'ZMOCNENI_ZAKON','type'=>'xsd:integer'),
    'ZMOCNENI_ROK'=>array('name'=>'ZMOCNENI_ROK','type'=>'xsd:integer'),
    'ZMOCNENI_PAR'=>array('name'=>'ZMOCNENI_PAR','type'=>'xsd:integer'),
    'ZMOCNENI_ODST'=>array('name'=>'ZMOCNENI_ODST','type'=>'xsd:integer'),
    'ZMOCNENI_PISMENO'=>array('name'=>'ZMOCNENI_PISMENO','type'=>'xsd:string'),
    'DATUM_VYPRAVENI'=>array('name'=>'DATUM_VYPRAVENI','type'=>'xsd:dateTime'),
    'DATUM_DORUCENI'=>array('name'=>'DATUM_DORUCENI','type'=>'xsd:dateTime'),
    'DATUM_PRECTENI'=>array('name'=>'DATUM_PRECTENI','type'=>'xsd:dateTime'),
    'DATUM_VYRIZENI'=>array('name'=>'DATUM_VYRIZENI','type'=>'xsd:dateTime'),
    'ZPUSOB_VYRIZENI'=>array('name'=>'ZPUSOB_VYRIZENI','type'=>'xsd:string'),
    'SPIS_CISLO'=>array('name'=>'SPIS_CISLO','type'=>'xsd:string','nillable'=>'true'),
    'SPIS_NAZEV'=>array('name'=>'SPIS_NAZEV','type'=>'xsd:string','nillable'=>'true'),
    'POZNAMKA'=>array('name'=>'POZNAMKA','type'=>'xsd:string','nillable'=>'true'),
  )
);
$server->wsdl->addComplexType(
  'dokumenty','complexType','array','sequence','',
  array(
    'dokument'=>array('name'=>'dokument', 'type'=>'tns:dokument', 'maxOccurs'=>'unbounded', 'minOccurs'=>'0', 'nillable'=>'true')
  ),
  array(),
  'tns:dokument'
);

$server->wsdl->addComplexType(
  'spis','complexType','struct','all','',
  array(
    'SPIS_CISLO'=>array('name'=>'SPIS_CISLO','type'=>'xsd:string'),
    'SPIS_NAZEV'=>array('name'=>'SPIS_NAZEV','type'=>'xsd:string','nillable'=>'true'),
    'SPIS_STAV'=>array('name'=>'SPIS_STAV','type'=>'xsd:string','nillable'=>'true'),
    'SPIS_DOKUMENTY'=>array('name'=>'SPIS_DOKUMENTY','type'=>'tns:dokumenty'),
  )
);


$server->wsdl->addComplexType(
  'Result','complexType','struct','all','',
  array(
    'RESULT'=>array('name'=>'RESULT','type'=>'xsd:string'),
    'DESCRIPTION'=>array('name'=>'DESCRIPTION','type'=>'xsd:string')
  )
);

// metody a jeji parametry
$server->register(
  'login',
  array('software_id' => 'xsd:string','username' => 'xsd:string', 'userpasswd' => 'xsd:string'),
  array('return' => 'tns:Result','session_id'=>'xsd:string'),
   'tns',                              // namespace
   'tns:'.$servicename,                // soapaction
   $wsdlstyle,                         // style
   $wsdluse,                           // use
   "LOGIN\n".                          // documentation
   "Parametry: ".
   "Vstup: software_id, username, userpasswd\n".
   "Odpoved: result pole"
);
$server->register(
  'get_doc',
  array('session_id' => 'xsd:string', 'dokument_id' => 'xsd:integer', 'odbor_id'=>'xsd:integer', 'zpracovatel_id' => 'xsd:integer'),
  array('return' => 'tns:Result','dokumenty'=>'tns:dokumenty'),
   'tns',                              // namespace
   'tns:'.$servicename,                // soapaction
   $wsdlstyle,                         // style
   $wsdluse,                           // use
   "LOGIN\n".                          // documentation
   "Parametry: ".
   "Vstup: software_id, username, userpasswd\n".
   "Odpoved: result pole"
);

$server->register(
  'work_on',
  array('session_id' => 'xsd:string','dokument_id' => 'xsd:integer', 'work_status' => 'xsd:integer'),
  array('return' => 'tns:Result'),
   'tns',                              // namespace
   'tns:'.$servicename,                // soapaction
   $wsdlstyle,                         // style
   $wsdluse,                           // use
   "WORK_ON\n".                          // documentation
   "Parametry: ".
   "Vstup: session_id, dokument_id, work_status\n".
   "Odpoved: result pole"
);

$server->register(
  'get_cj',
  array('session_id' => 'xsd:string','zpracovatel_id' => 'xsd:integer', 'prichozi_id' => 'xsd:integer'),
  array('return' => 'tns:Result', 'dokument_id'=>'xsd:integer', 'cislo_jednaci'=>'xsd:string'),
   'tns',                              // namespace
   'tns:'.$servicename,                // soapaction
   $wsdlstyle,                         // style
   $wsdluse,                           // use
   "GET_CJ\n".                          // documentation
   "Parametry: ".
   "Vstup: session_id, zpracovatel_id, prichozi_id\n".
   "Odpoved: result pole, dokument_id, cislo_jednaci"
);

$server->register(
  'send_doc',
  array('session_id' => 'xsd:string','dokument_id'=>'xsd:integer','dokument_data'=>'tns:dokument'),
  array('return' => 'tns:Result'),
   'tns',                              // namespace
   'tns:'.$servicename,                // soapaction
   $wsdlstyle,                         // style
   $wsdluse,                           // use
   "SEND_DOC\n".                       // documentation
   "Parametry: ".
   "Vstup: session_id, dokument_id,dokument_data\n".
   "Odpoved: result pole"
);

$server->register(
  'get_files',
  array('session_id' => 'xsd:string', 'dokument_id'=>'xsd:integer'),
  array('return' => 'tns:Result','soubory'=>'tns:soubory'),
   'tns',                              // namespace
   'tns:'.$servicename,                // soapaction
   $wsdlstyle,                         // style
   $wsdluse,                           // use
   "GET_FILES\n".                      // documentation
   "Parametry: ".
   "Vstup: session_id, dokument_id\n".
   "Odpoved: result pole"
);

$server->register(
  'get_info_file',
  array('session_id' => 'xsd:string', 'dokument_id'=>'xsd:integer', 'file_id'=>'xsd:integer'),
  array('return' => 'tns:Result','soubory'=>'tns:soubory'),
   'tns',                              // namespace
   'tns:'.$servicename,                // soapaction
   $wsdlstyle,                         // style
   $wsdluse,                           // use
   "GET_INFO_FILE\n".                      // documentation
   "Parametry: ".
   "Vstup: session_id, dokument_id, file_id\n".
   "Odpoved: result pole"
);

$server->register(
  'send_files',
  array('session_id' => 'xsd:string','dokument_id'=>'xsd:integer','soubory'=>'tns:soubory'),
  array('return' => 'tns:Result','soubory'=>'tns:soubory'),
   'tns',                              // namespace
   'tns:'.$servicename,                // soapaction
   $wsdlstyle,                         // style
   $wsdluse,                           // use
   "SEND_FILES\n".                     // documentation
   "Parametry: ".
   "Vstup: session_id, dokument_id, files\n".
   "Odpoved: result pole"
);

$server->register(
  'document',
  array('session_id' => 'xsd:string', 'dokument_id'=>'xsd:integer','dokument_data'=>'tns:dokument'),
  array('return' => 'tns:Result'),
   'tns',                              // namespace
   'tns:'.$servicename,                // soapaction
   $wsdlstyle,                         // style
   $wsdluse,                           // use
   "DOCUMENT\n".                      // documentation
   "Parametry: ".
   "Vstup: session_id, dokument_id,dokument_data\n".
   "Odpoved: result pole"
);

$server->register(
  'storno',
  array('session_id' => 'xsd:string', 'dokument_id'=>'xsd:integer','duvod'=>'xsd:string'),
  array('return' => 'tns:Result'),
   'tns',                              // namespace
   'tns:'.$servicename,                // soapaction
   $wsdlstyle,                         // style
   $wsdluse,                           // use
   "STORNO\n".                      // documentation
   "Parametry: ".
   "Vstup: session_id, dokument_id,duvod\n".
   "Odpoved: result pole"
);

$server->register(
  'spis_zalozeni',
  array('session_id' => 'xsd:string', 'dokument_id' => 'xsd:integer', 'nazev_spisu' => 'xsd:string'),
  array('return' => 'tns:Result', 'spis' => 'tns:spis'),
   'tns',                              // namespace
   'tns:'.$servicename,                // soapaction
   $wsdlstyle,                         // style
   $wsdluse,                           // use
   "SPIS_ZALOZENI\n".                  // documentation
   "Parametry: ".
   "Vstup: session_id, dokument_id, nazev_spisu\n".
   "Odpoved: result pole, element spis"
);

$server->register(
  'spis_vlozeni',
  array('session_id' => 'xsd:string', 'dokument_id' => 'xsd:integer', 'spis_id' => 'xsd:string'),
  array('return' => 'tns:Result', 'spis' => 'tns:spis'),
   'tns',                              // namespace
   'tns:'.$servicename,                // soapaction
   $wsdlstyle,                         // style
   $wsdluse,                           // use
   "SPIS_VLOZENI\n".                  // documentation
   "Parametry: ".
   "Vstup: session_id, dokument_id, spis_id\n".
   "Odpoved: result pole, element spis"
);

$server->register(
  'spis_predani',
  array('session_id' => 'xsd:string', 'spis_id' => 'xsd:string', 'zpracovatel_id' => 'xsd:integer'),
  array('return' => 'tns:Result', 'spis' => 'tns:spis'),
   'tns',                              // namespace
   'tns:'.$servicename,                // soapaction
   $wsdlstyle,                         // style
   $wsdluse,                           // use
   "SPIS_PREDANI\n".                  // documentation
   "Parametry: ".
   "Vstup: session_id, spis_id, zpracovatel_id\n".
   "Odpoved: result pole, element spis"
);

$server->register(
  'spis_stav',
  array('session_id' => 'xsd:string', 'spis_id' => 'xsd:string', 'akce' => 'xsd:string'),
  array('return' => 'tns:Result', 'spis' => 'tns:spis'),
   'tns',                              // namespace
   'tns:'.$servicename,                // soapaction
   $wsdlstyle,                         // style
   $wsdluse,                           // use
   "SPIS_STAV\n".                  // documentation
   "Parametry: ".
   "Vstup: session_id, spis_id, akce (O,Z)\n".
   "Odpoved: result pole, element spis"
);

$server->register(
  'logout',
  array('session_id' => 'xsd:string'),
  array('return' => 'tns:Result'),
   'tns',                              // namespace
   'tns:'.$servicename,                // soapaction
   $wsdlstyle,                         // style
   $wsdluse,                           // use
   "LOGOUT\n".                          // documentation
   "Parametry: ".
   "Vstup: session_id\n".
   "Odpoved: result pole"
);


/******* LOAD FCE ***************************************/
require('sps_login.inc');
require('sps_get_doc.inc');
require('sps_work_on.inc');
require('sps_get_cj.inc');
require('sps_send_doc.inc');
require('sps_get_files.inc');
require('sps_get_info_file.inc');
require('sps_send_files.inc');
require('sps_document.inc');
require('sps_storno.inc');
require('sps_logout.inc');
require('sps_spis_zalozeni.inc');
require('sps_spis_vlozeni.inc');
require('sps_spis_predani.inc');
require('sps_spis_stav.inc');

/**** SERVICE *******************************************/
$HTTP_RAW_POST_DATA = isset($HTTP_RAW_POST_DATA) ? $HTTP_RAW_POST_DATA : '';
@$server->service($HTTP_RAW_POST_DATA);

