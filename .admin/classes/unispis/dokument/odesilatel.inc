<?php

/**
 * trida pro identifikaci odesilatele 
 *
 * @author onma
 */
class odesilatel {
  /** trida subjekt pro indentifikaci odesilatele */
  var $Subjekt;
  
  /**
  * konstruktor 
  *
  * @param array $odesilatel pole pro naplneni 
  */ 
  public function __construct($odesilatel) {  
    $this->Subjekt = new subjekt($odesilatel['Subjekt']);
  }
}
