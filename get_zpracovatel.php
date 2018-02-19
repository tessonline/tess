<?php

require('tmapy_config.inc');
include_once(FileUp2('.admin/brow_.inc'));
include_once($GLOBALS['TMAPY_LIB'] . '/oohforms.inc');
include_once(FileUp2('.admin/el/of_select_.inc'));
include_once(FileUp2('lib/json/json.inc'));

access();

if (!hasSubRole('read')) {
  die();
}

$params = array(
  'odbor'       => intval($_GET['ORGANIZACNI_VYBOR']),
  'insertnull'  => true
);


include_once(FileUp2("security/.admin/security_func.inc"));
$ODBOR = $params['odbor'];
$prac = VratPracovniky($ODBOR,1);
$referenti = array();

while (list($key,$val)=each($prac)) {
    $referent = array();
    $referent['value'] = $key;
    $referent['label'] = $val;
    $referenti[] = $referent;
}

header('Content-Type: application/json; charset=UTF-8');

if (version_compare(PHP_VERSION, '5.2', '>=')) {
  $json = json_encode($referenti);
}
else {
  $jsonService = new Services_JSON();
  $json = $jsonService->encode($referenti);
}

echo $json;
