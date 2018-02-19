<?php
/*[16.9.2013 13:55:09] Lucie Leistnerová: tak se posila command=getdiff
a bud se vysledek ulozi do promennych 
$GLOBALS['ISZR_DIFF_OBJ'] a $GLOBALS['ISZR_DATA_OBJ'] nebo si jeste parametry muzes rict, jak se maji jmenovat
[16.9.2013 13:57:48] Lucie Leistnerová: pouziti:
*/
require('tmapy_config.inc'); 
require_once(FileUp2('.admin/agenda_func.inc'));
require_once($GLOBALS['TMAPY_LIB'].'/iszr/lib/IszrConfig.inc');
require_once($GLOBALS['TMAPY_LIB'].'/iszr/lib/IszrInterface.inc');

$icos = array(
//  '00838420',
  '00830381',
//  '00829447',

//  '00828963',
//  '00836265',

//  '00830682',
);


$PROPERTIES = loadProperties(null, GetAgendaPath('POSTA', 0, 0) . '/.admin/properties.inc');

$GLOBALS['ODESL_ICO'] = $icos[0];
$_REQUEST['AGENDA'] = 'A1023';
$_REQUEST['ROLE'] = 'CR5823';
$_REQUEST['UCEL'] = 'test aplikace';

//$GLOBALS['EDIT_ID'] = 4541945;

//$GLOBALS['ISZR_APP_ID'] = $GLOBALS['EDIT_ID'];
$conf = IszrConfig::getModulInstance('IszrDirect');
$appConf = $conf->getAppAll();
//print_r($appConf);
//Die();
$iszr = new IszrInterface(
  $PROPERTIES,
  $appConf,
  array(
  'ISZR_APP_ID' => $GLOBALS['EDIT_ID'],
  'command' => 'getdiff',
  'AGENDA' => $_REQUEST['AGENDA'],
  'ROLE' => $_REQUEST['ROLE'],
  'UCEL' => $_REQUEST['UCEL'],
));
//Die(print_r($iszr));
$iszr->process();

print_r($GLOBALS['ISZR_DATA_OBJ']);
