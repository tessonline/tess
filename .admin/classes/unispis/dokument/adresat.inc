<?php

/**
 * trida pro identifikaci adresata 
 *
 * @author onma
 */
class adresat {
  /** subjekt adresata */
  var $subjekt;
  
  /**
  * konstruktor 
  *
  * @param array $adresat pole pro naplneni 
  */ 
  public function __construct($adresat) {  
    $this->Subjekt = new subjekt($adresat['Subjekt']);
  }
}
