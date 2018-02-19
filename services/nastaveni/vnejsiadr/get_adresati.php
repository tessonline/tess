<?php

require('tmapy_config.inc');
include_once(FileUp2('.admin/brow_.inc'));
include_once(FileUp2('lib/json/json.inc'));
include_once('.admin/adresati_func.inc');

access();

if (!hasSubRole('read')) {
  die();
}

$adresati = getAdresati(intval($_GET['SKUPINA']));

header('Content-Type: application/json; charset=UTF-8');

if (version_compare(PHP_VERSION, '5.2', '>=')) {
  $json = json_encode($adresati);
}
else {
  $jsonService = new Services_JSON();
  $json = $jsonService->encode($adresati);
}

echo $json;
