<?php

include_once('WsseAuthHeader.inc');

if (!extension_loaded('soap')) {
  dl('soap.so');
}

class DRKlient {
  
  // Instance SOAP klienta
  private $soapClient;
  
  /**
   * Vytvari instanci teto tridy.
   * @param string $wsdlUrl - URL WSDL sluzby.
   * @param string $httpsLogin - Username pro HTTTP komunikaci.
   * @param string $httpsPassword - Heslo pro HTTTP komunikaci.
   */
  public function __construct($sluzba_id = 0) {
    if (!$sluzba_id || $sluzba_id == 0) return false;
    $this->db = new DB_POSTA;
    $this->db->query('select * from posta_plugins_dr_app where id=' . $sluzba_id);
    $this->db->Next_Record();
    $this->wsdlUrl = $this->db->Record['KLIENT_URL'];
    $this->login = $this->db->Record['KLIENT_USERNAME'];
    $this->password = $this->db->Record['KLIENT_PASSWD'];

    $this->basic_auten = $this->db->Record['KLIENT_AUTHEN'];

    $this->HASHID_LOG = Date('d.m.Y H:i:s u');

    if ($this->basic_auten == 0) {
      try {
        $this->soapClient = new SoapClient(
          $this->wsdlUrl,
          array("trace" => 1, "exception" => 0)
        );
        $wsse_header = new WsseAuthHeader($this->login, $this->password);
        $this->soapClient->__setSoapHeaders(array($wsse_header));
      }
      catch (Exception $e) {
        $this->throwConnectorError($e, __METHOD__, __LINE__);
      }
    }
    else {
      //basic auten
      try {
        $this->soapClient = new SoapClient(
          $this->wsdlUrl,
          array(
            "trace" => 1,
            "exception" => 0,
            'login' => $this->login,
            'password' => $this->password,
          )
        );
      }
      catch (Exception $e) {
        $this->throwConnectorError($e, __METHOD__, __LINE__);
      }

    }
  }
  
  
  /**
   */
  public function vlozPrilohu($dokument) {
    try {

      $response = $this->soapClient->vlozPrilohu(array(
        'Dokument'  => $dokument,
      ));

//      WriteHTTPlog($this->HASHID_LOG,($this->soapClient->__getLastRequest()), ($this->soapClient->__getLastResponse()), 'DR' );
//      echo "REQUEST:\n" . htmlentities($this->soapClient->__getLastRequest()) . "\n";
//      echo "RESPONSE:\n" . htmlentities($this->soapClient->__getLastResponse()) . "\n";
      $ret = $response->SpslStatus;
    }
    catch (Exception $e) {
        echo "<h1>Chyba v komunikaci: Nepřišla odpověď z AIS - kontaktujte správce AIS</h1>";
//      echo "REQUEST:\n" . htmlentities($this->soapClient->__getLastRequest()) . "\n";
//      WriteHTTPlog($this->HASHID_LOG,($this->soapClient->__getLastRequest()), ($this->soapClient->__getLastResponse()), 'DR' );
      $this->throwConnectorError($e, __METHOD__, __LINE__);
    }
    return $ret;
  }


  public function vlozDokument($dokument) {
    try {

      $response = $this->soapClient->vlozDokument(array(
        'Dokument'  => $dokument,
      ));

//      WriteHTTPlog($this->HASHID_LOG,($this->soapClient->__getLastRequest()), ($this->soapClient->__getLastResponse()), 'DR' );
//      echo "REQUEST:\n" . htmlentities($this->soapClient->__getLastRequest()) . "\n";
//      echo "RESPONSE:\n" . htmlentities($this->soapClient->__getLastResponse()) . "\n";
      $ret = $response->SpslStatus;
    }
    catch (Exception $e) {
//      echo "REQUEST:\n" . htmlentities($this->soapClient->__getLastRequest()) . "\n";
        echo "<h1>Chyba v komunikaci: Nepřišla odpověď z AIS - kontaktujte správce AIS</h1>";
//      WriteHTTPlog($this->HASHID_LOG,($this->soapClient->__getLastRequest()), ($this->soapClient->__getLastResponse()), 'DR' );
//      $this->throwConnectorError($e, __METHOD__, __LINE__);
    }
    return $ret;
  }

  /**
   * Funkce vyhodi vyjimku.
   * @param Exception $e
   * @param string Nazev metody, ktera vyhodila vyjimku.
   * @param integer Cislo radku, na kterem byla vyhozena vyjimka.
   */
  private function throwConnectorError(Exception $e, $method, $line) {
    $codeInfo = ' (' . $method . ' at line ' . $line . ')';
    throw new Exception('Dr konektor (#' . $e->getCode() . '): ' . $e->getMessage() . $codeInfo);
  }
  
}
