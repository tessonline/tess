<?php
// $_SERVER['SERVER_NAME'] = 'kr-ustecky.matej6.tmapserver.cz'; //proze checkGlobalAccess jinak kouka na jiny ldap
// $GLOBALS["PROPERTIES_DEBUG"]["USER_NAME"] = 'tomnovo'; // jako debug je to ok
// $GLOBALS['Debug']['sql'] = true;
error_reporting(E_ALL);

$path = __DIR__ . '/../../../../'; //relativni cesta k test adresari, protoze jeste neumi "FileUp2"
if(!is_dir($path . DIRECTORY_SEPARATOR . 'ost')){
  echo sprintf('There is no ./ost directory in path %1$s. Please correct include path in bootstrap.inc.', $path);
  die('problem path');
}

require_once $path . '/tmapy/lib/twist-mock/twist-mock.inc';

// set_include_path(get_include_path() . PATH_SEPARATOR . $path);
// require('.config/tmapy_config.inc');

//$this->connection->getDatabasePlatform()->getName()
