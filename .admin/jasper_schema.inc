<?php
require_once(FileUp2('.config/config_posta.inc'));
$config = TW_AppConfig::getInstance('ders-uk-test');

/*
 * kdyz se to prepise, tak nefunguje na selfu pripadu report pro vyzvu ani pro samotny pripad 
 */
//$config['JASPER']['folders'] = array(__DIR__ . '/../.jasper/dokument');

return $config['JASPER'];
