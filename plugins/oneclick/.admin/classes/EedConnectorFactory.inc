<?php

include_once(FileUp2('.admin/classes/EedConnector.inc'));
include_once(FileUp2('.admin/security_.inc'));

/**
 * @version 2:
 *  older version: \\matej5\www-data\mu-nmnm-spis.tmapserver.cz\ost\posta\interface\mawis\
 *  newer version: is not
 */

class EedConnectorFactory {
  
  public static function getEedConnector() {
    
    $userInfo = $GLOBALS['TMAPY_SECURITY']->GetUserInfo();
    $wsdl = 'http://' . $GLOBALS['HTTP_HOST'] . '/ost/posta/interface/konektor/server/soap.php?wsdl';
    
    return new EedConnector($wsdl, $userInfo['ID']);
  }
}
