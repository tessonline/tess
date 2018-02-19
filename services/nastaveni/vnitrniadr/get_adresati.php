<?php

require('tmapy_config.inc');
include_once(FileUp2('.admin/brow_.inc'));
include_once($GLOBALS['TMAPY_LIB'] . '/oohforms.inc');
include_once(GetAgendaPath('POSTA', false, false) . '/.admin/properties.inc');
include_once(FileUp2('.admin/el/of_select_.inc'));
include_once(FileUp2('lib/json/json.inc'));
include_once('.admin/adresati_func.inc');

access();

if (!hasSubRole('read')) {
  die();
}

$adresati = getAdresati(intval($_GET['SKUPINA']));
$nastaveniAdresati = array();

foreach ($adresati as $adresat) {  

  $params = array(
    'set_odbor'       => $adresat['organizacniVybor'],
    'insertnull'  => true
  );

  $referentSelect = new of_select_referent($params);
  $referenti = array();

  foreach ($referentSelect->options as $option) {

    $referent = array();
    //$referent['value'] = iconv('ISO-8859-2', 'UTF-8', $option['value']);
    //$referent['label'] = iconv('ISO-8859-2', 'UTF-8', $option['label']);
    $referent['value'] = $option['value'];
    $referent['label'] = $option['label'];
    
    $referenti[] = $referent;
  }
  
  $nastavenyAdresat = array();
  
  $nastavenyAdresat['organizacniVybor'] = $adresat['organizacniVybor'];
  $nastavenyAdresat['zpracovatel'] = $adresat['zpracovatel'];
  $nastavenyAdresat['zpracovatele'] = $referenti;
  
  $nastaveniAdresati[] = $nastavenyAdresat;
}

header('Content-Type: application/json; charset=UTF-8');

if (version_compare(PHP_VERSION, '5.2', '>=')) {
  $json = json_encode($nastaveniAdresati);
}
else {
  $jsonService = new Services_JSON();
  $json = $jsonService->encode($nastaveniAdresati);
}

echo $json;


