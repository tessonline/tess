<?php

if (!extension_loaded('soap')) {
  dl('soap.so');
}

class OneClickConnector {
  
  // Instance SOAP klienta
  private $soapClient;
  
  /**
   * Vytvari instanci teto tridy.
   * @param string $wsdlUrl - URL WSDL sluzby.
   * @param string $httpsLogin - Username pro HTTTP komunikaci.
   * @param string $httpsPassword - Heslo pro HTTTP komunikaci.
   */
  public function __construct($wsdlUrl, $login, $password) {    
    try {
      
      $this->soapClient = new SoapClient(
        $wsdlUrl,
        array('login' => $login, 'password' => $password)
      );
      
    }
    catch (Exception $e) {
      $this->throwConnectorError($e, __METHOD__, __LINE__);
    }
  }
  
  /**
   * Zapouzdreni SOAP sluzby getAllUsers, ktera vrati seznam uzivatelu sluzby 1click.
   * @return array[mixed] - Seznam uzivatelu sluzby 1click.
   */
  public function getAllUsers() {
    $users = array();
    try {
      
      $response = $this->soapClient->getAllUsers();
      $users = $response->return;
    }
    catch (Exception $e) {
      $this->throwConnectorError($e, __METHOD__, __LINE__);
    }
    return $users;
  }
  
  /**
   * Zapouzdreni SOAP sluzby uploadDocument, pro nahravani priloh ukolu.
   * @param string $filename - Jmeno souboru vcetne pripony.
   * @param string $data - Binarni obsah souboru.
   * @return integer - Id nahravaneho dokumentu.
   */
  public function uploadDocument($filename, $data) {
    $documentId = 0;
    try {
      
      $response = $this->soapClient->uploadDocument(array(
        'filename'  => $filename,
        'body'      => $data
      ));
      
      $documentId = $response->return;    
    }
    catch (Exception $e) {
      $this->throwConnectorError($e, __METHOD__, __LINE__);
    }
    return $documentId;
  }
  
  /**
   * Zapouzdreni SOAP sluzby createTask, ktera vytvari ukol ve sluzbe 1click.
   * @param Task $task - Ukol.
   * @return integer - Identifikator nove zalozeneho ukolu.
   */
  public function createTask(Task $task) {
    $taskId = 0;
    try {
      
      // Testovaci data
//      $response = $this->soapClient->createTask(array(
//        'assignee'    => 'u/2', // tmapy
//        'subject'     => 'Test ' . iconv('Windows-1250', 'UTF-8', 'ěčřýáíé ') . date('H:i:s'),
//        'submitter'   => 'u/2', // tmapy
//        'comment'     => date('d.m.y'),
//        'attachment'  => array(562, 563)
//      ));
      
      $response = $this->soapClient->createTask(array(
        'assignee'    => $task->resitel,
        'subject'     => $task->predmet,
        'submitter'   => $task->zadavatel,
        'comment'     => $task->zadani,
        'attachment'  => $task->getOneClickIdsOfPrilohy()
      ));
      
      $taskId = $response->return;
    }
    catch (Exception $e) {
      $this->throwConnectorError($e, __METHOD__, __LINE__);
    }
    return $taskId;
  }
  
  /**
   * Funkce vyhodi vyjimku.
   * @param Exception $e
   * @param string Nazev metody, ktera vyhodila vyjimku.
   * @param integer Cislo radku, na kterem byla vyhozena vyjimka.
   */
  private function throwConnectorError(Exception $e, $method, $line) {
    $codeInfo = ' (' . $method . ' at line ' . $line . ')';
    throw new Exception('1Click konektor (#' . $e->getCode() . '): ' . $e->getMessage() . $codeInfo);
  }
  
}
