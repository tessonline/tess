<?php

class Task {
  
  private $id;
  private $resitel;
  private $predmet;
  private $zadavatel;
  private $zadani;
  private $prilohy;
  
  public function __construct($id, $resitel, $predmet, $zadani, $prilohy, $zadavatel) {
    $this->id = $id;
    $this->resitel = $resitel;
    $this->predmet = $predmet;
    $this->zadavatel = $zadavatel;
    $this->zadani = $zadani;
    $this->prilohy = $prilohy;
  }
  
  // Settery
  public function __set($name, $value) {
    $this->$name = $value;
  } 

  // Gettery
  public function __get($name) {
    return $this->$name;
  }
  
  /**
   * Funkce zalozi ukol (vcetne priloh) do sluzby 1click.
   * Funkce take ulozi zaznam o zalozeni ukolu do DB.
   * @param OneClickConnector Konektor pro pripojeni ke sluzbe 1click.
   * @param integer Id EED dokumentu, ke kteremu se vztahuje ukladany ukol.
   * @return bool Pokud se vse poved pa true, jinak false. 
   */
  public function save(OneClickConnector $connector, $eedDocumentId) {
    
    foreach ($this->prilohy as $priloha) {
      $priloha->oneClickId = $connector->uploadDocument($priloha->name, $priloha->data);
    }
    
    $this->id = $connector->createTask($this);
    return $this->saveToDatabase($eedDocumentId);
  }
  
  /**
   * Funkce vrati URL ukolu smerujici do weboveho rozhrani sluzby 1click.
   * @global array[mixed] $CONFIG Application config.
   * @return string URL ukolu.
   */
  public static function getUrl($id) {
    
    global $CONFIG;
    
    return $CONFIG['POSTA_INTERFACE_ONE_CLICK']['ONE_CLICK']['WEB_URL'] . '/?task=' . $id;
  }
  
  /**
   * Funkce uklada do databaze zaznam o tom, ze byl tento ukol pridelen k danemu EED dokumentu.
   * @global array[mixed] $PROPERTIES Application properties.
   * @param integer $eedDocumentId Id EED dokumentu.
   * @return bool Pokud se povedlo vlozit zaznam do DB pak true, jinak false. 
   */
  private function saveToDatabase($eedDocumentId) {
    
    global $PROPERTIES;
    $dbConnector = new $PROPERTIES['DB_NAME'];
    
    $table = $PROPERTIES['AGENDA_TABLE'];
    $result = $dbConnector->query('INSERT INTO ' . $table . ' (document_id, task_id)
                                     VALUES (' . $eedDocumentId . ', ' . $this->id . ')');
    return (bool) $result;
  }
  
  /**
   * Funkce vraci pole idecek priloh, pod kterymi byly ulozeny ve sluzbe 1click.
   * @return array[integer] Seznam 1click files ids.
   */
  public function getOneClickIdsOfPrilohy() {
      
    $oneClickIds = array();
    
    foreach ($this->prilohy as $priloha) {
      $oneClickIds[] = $priloha->oneClickId;
    }
    
    return $oneClickIds;
  }
}
