<?php
include_once __DIR__ . '/bootstrap.inc';

//http://doctrine-orm.readthedocs.io/projects/doctrine-dbal/en/latest/reference/configuration.html

// $GLOBALS['TMAPY_LIB'] = './../../../../tmapy';

include_once(__DIR__ . '/../../../../.admin/db/db_default.inc');
//include_once(__DIR__ . '/../../../../.admin/db/db_posta.inc');
/*
 * protoze se jedna o testovaci vytvareni tabulek, ktere pak maji 
 * korespondovat s aktualni db strukturou majetku
 */
// include_once('./../../../../.admin/db/db_default.inc');

// ini_set('mssql.charset', 'cp1250');
// ini_set('default_charset', 'cp1250');
// ini_set('mssql.charset', "UTF-8");
// ini_set('default_charset', "utf-8");

// var_dump(ini_get('mssql.charset'));
// var_dump(ini_get('default_charset'));
// die;

//$db = new DB_POSTA();
 $db = new DB_DEFAULT();

// $config = array(
//         'dbname'   => $db->Database,
//         'user'     => $db->User,
//         'password' => $db->Password,
//         'host'     => $db->Host,
//         'driver'   => 'sqlsrv',
// //         'driver'   => 'pdo_sqlsrv',
// );


//http://docs.doctrine-project.org/projects/doctrine-dbal/en/latest/reference/configuration.html
$config = array(
//   'driverClass' => 'Lsw\DoctrinePdoDblib\Doctrine\DBAL\Driver\PDODblib\Driver',
  'driver' => 'pdo_pgsql',
//   'charset' => 'UTF-8',
//   'charset' => 'UTF-8',
//   'charset' => 'Windows-1250',
//   'charset' => 'cp1250',
//   'charset' => 'utf8',
  'dbname'   => $db->Database,
  'user'     => $db->User,
  'password' => $db->Password,
  'host'     => $db->Host,
//   'host' => 'wendy12-utf8',
//  'mapping_types' => array('timestamp' => 'string'),
//         'driver'   => 'sqlsrv',
//         'driver'   => 'pdo_sqlsrv',
);

return $config;

