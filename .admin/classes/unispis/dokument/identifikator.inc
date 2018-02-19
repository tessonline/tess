<?php

/**
 * trida pro identifikator
 *
 * @author onma
 */
class identifikator {
  /** trida postovni adresy, muze byt uvedeno 0..N adres */
  var $HodnotaID;
  /**  trida adresy datove schranky, vedeno jen 0..1 elementů */
  var $ZdrojID;
  
  /**
  * konstruktor 
  *
  * @param array $ident pole pro naplneni
  */ 
  public function __construct($ident) {
    $this->HodnotaID = $ident['HodnotaID'];
    $this->ZdrojID = $ident['ZdrojID'];
  }
}
