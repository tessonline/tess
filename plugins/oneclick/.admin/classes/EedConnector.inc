<?php

include_once(FileUp2('.config/config.inc'));
require_once('.admin/classes/EedDocument.inc');
require_once('.admin/classes/File.inc');

if (!extension_loaded('soap')) {
  dl('soap.so');
}

/**
 * @version 2:
 *  older version: \\matej5\www-data\mu-nmnm-spis.tmapserver.cz\ost\posta\interface\mawis\
 *  newer version: is not
 */

class EedConnector {
  
  // URL WSDL sluzby
  private $wsdl;
  // Instance SOAP clienta
  private $soapClient;
  // Id pro persistentni komunikaci
  private $sessionId;
  // Identifikator uzivatele, ktery komunikuje se SOAP serverem
  private $userId;
  // Pozadovane vystupni kodovani
  private $outCharset;
  
  const IN_CHARSET = 'UTF-8';
  
  /**
   * Vytvoreni instance EedConnectoru
   * @param string $wsdlUrl - URL WSDL sluzby.
   * @param integer $userId - Identifikator uzivatele, ktery komunikuje se SOAP serverem.
   */
  public function __construct($wsdlUrl, $userId, $outCharset = 'UTF-8') {    
    try {
      
      $this->wsdl = $wsdlUrl;
      $wsdlUrl .= '&LAST_USER_ID=' . $userId;
      $this->soapClient = new SoapClient($wsdlUrl, array('trace' => TRUE));
      $this->userId = $userId;
      $this->outCharset = $outCharset;
      
    }
    catch (Exception $e) {
      $this->throwConnectorError($e, __METHOD__, __LINE__);
    }
  }
  
  /**
   * Prihlaseni do EED.
   * @param string $softwareId[optional] - Prihlasovaci udaje (viz WSDL specifikace).
   * @param string $username[optional] - Prihlasovaci udaje (viz WSDL specifikace).
   * @param string $password[optional] - Prihlasovaci udaje (viz WSDL specifikace).
   * Pokud neni nejaka hodnota vyplnena vezme se nastaveni z konfigu.
   * @return bool - If logged true, otherwise false.
   */
  public function login($softwareId = '', $username = '', $password = '') {
    try {
      
      global $CONFIG;
      
      $softwareId = $softwareId ? $softwareId : $CONFIG['POSTA_INTERFACE_ONE_CLICK']['EED']['SOFTWARE_ID'];
      $username = $username ? $username : $CONFIG['POSTA_INTERFACE_ONE_CLICK']['EED']['USERNAME'];
      $password = $password ? $password : $CONFIG['POSTA_INTERFACE_ONE_CLICK']['EED']['PASSWORD'];
      
      $response = $this->soapClient->login($softwareId, $username, $password);
      $this->sessionId = $response['session_id'];
      
    }
    catch (Exception $e) {
      $this->throwConnectorError($e, __METHOD__, __LINE__);
    }
    return $this->isSuccess($response);
  }
  
  /**
   * Odhlaseni z EED.
   * @return bool - If logged out true, otherwise false.
   */
  public function logout() {
    try {
      
      $response = $this->soapClient->logout($this->sessionId);
      
    }
    catch (Exception $e) {
      $this->throwConnectorError($e, __METHOD__, __LINE__);
    }
    return $this->isSuccess($response);
  }
  
  /**
   * Zalozeni spisu v EED.
   * @return array - Id a cislo jednaci spisu (v poli).
   */
  public function createNewDocument() {
    $newDocument = array();
    try {
      
      $response = $this->soapClient->get_cj($this->sessionId, $this->userId);

      $newDocument['documentId'] = $response['dokument_id'];
      $newDocument['cisloJednaci'] = $response['cislo_jednaci'];
      
    }
    catch (Exception $e) {
      $this->throwConnectorError($e, __METHOD__, __LINE__);
    }
    return $newDocument;
  }
  
  /**
   * Odeslani dokumentu do EED neboli prirazeni dat k danemu spisu.
   * @param integer $documentId - Id spisu.
   * @param array $document - Pole hodnot spisu.
   * @return bool - If sent true, otherwise false.
   */
  public function sendDocument($documentId, array $document) {
    try {
      
      $response = $this->soapClient->send_doc($this->sessionId, $documentId, $document);      
    }
    catch (Exception $e) {
      $this->throwConnectorError($e, __METHOD__, __LINE__);
    }
    return $this->isSuccess($response);
  }  
  
  /**
   * Odeslani souboru (priloh) souvisejicich s danym spisem.
   * @param integer $documentId - Id spisu.
   * @param array $files - Pole souboru (viz WSDL specifikace).
   * @return bool - If sent true, otherwise false.
   */
  public function sendFiles($documentId, array $files) {
    try {
      
      foreach ($files as $key => $file) {
        $files[$key] = new SoapVar($file, SOAP_ENC_OBJECT, 'soubor', 'tns');
      }
      $response = $this->soapClient->send_files(
        $this->sessionId,
        $documentId,
        new SoapVar($files, SOAP_ENC_ARRAY, 'soubory', 'tns')
      );
    }
    catch (Exception $e) {
      $this->throwConnectorError($e, __METHOD__, __LINE__);
    }
    return $this->isSuccess($response);
  }
  
  /**
   * Ziskani EED dokumentu.
   * @param integer $documentId - Id EED dokumentu.
   * @return EedDocument.
   */
  public function getDocument($documentId) {
    $document = NULL;
    try {
      
      $response = $this->soapClient->get_doc($this->sessionId, $documentId);
      $result = get_object_vars($response['dokumenty'][0]);
      
      if (is_array($result)) {
      
        foreach ($result as $key => $property) {
          $result[$key] = iconv(self::IN_CHARSET, $this->outCharset, $property);
        }

        $document = EedDocument::factory($result);
      }
    }
    catch (Exception $e) {
      $this->throwConnectorError($e, __METHOD__, __LINE__);
    }
    return $document;
  }
  
  /**
   * Ziskani souboru nalezici danemu EED dokumentu.
   * @param integer $documentId - Id EED dokumentu.
   * @return array[Files] - Pole souboru.
   */
  public function getFiles($documentId) {
    $files = array();
    try {
      
      $response = $this->soapClient->get_files($this->sessionId, $documentId);
      $result = $response['soubory'];
      
      if (is_array($result)) {
      
        foreach ($result as $responseFile) {
          
          $file = new File();
          
          $file->eedId = iconv(self::IN_CHARSET, $this->outCharset, $responseFile->FILE_ID);
          $file->name = iconv(self::IN_CHARSET, $this->outCharset, $responseFile->FILE_NAME);
          $file->description = iconv(self::IN_CHARSET, $this->outCharset, $responseFile->FILE_DESC);
          $file->size = iconv(self::IN_CHARSET, $this->outCharset, $responseFile->FILE_SIZE);
          $file->bindType = iconv(self::IN_CHARSET, $this->outCharset, $responseFile->BIND_TYPE);
          $file->data = $responseFile->FILE_DATA;
          $file->oneClickId = 0;
          
          $files[] = $file;
        }
      }
    }
    catch (Exception $e) {
      $this->throwConnectorError($e, __METHOD__, __LINE__);
    }
    return $files;
  }
  
  /**
   * Zpracuje odpoved SOAP serveru EED a vyhodnoti, jestli probehl pozadavek v poradku.
   * @param array/stdClass $response - Odpoved SOAP serveru EED.
   * @return bool - If response ok true, otherwise false.
   */
  private function isSuccess($response) {
    if (is_array($response)) {
      $response = $response['return'];
    }
    return $response->RESULT === 'OK' ? TRUE : FALSE;
  }  
  
  /**
   * Funkce vyhodi vyjimku.
   * @param Exception $e
   * @param string Nazev metody, ktera vyhodila vyjimku.
   * @param integer Cislo radku, na kterem byla vyhozena vyjimka.
   */
  private function throwConnectorError(Exception $e, $method, $line) {
    $codeInfo = ' (' . $method . ' at line ' . $line . ')';
    throw new Exception('EED konektor (#' . $e->getCode() . '): ' . $e->getMessage() . $codeInfo);
  }
  
}
