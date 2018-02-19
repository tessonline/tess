<?php

include_once(FileUp2('.admin/classes/OneClickConnector.inc'));

class OneClickConnectorFactory {
  
  public static function getOneClickConnector() {
    
    global $CONFIG;
    
    return new OneClickConnector(
      $CONFIG['POSTA_INTERFACE_ONE_CLICK']['ONE_CLICK']['WSDL_URL'],
      $CONFIG['POSTA_INTERFACE_ONE_CLICK']['ONE_CLICK']['LOGIN'],
      $CONFIG['POSTA_INTERFACE_ONE_CLICK']['ONE_CLICK']['PASSWORD']
    );
  }
}
