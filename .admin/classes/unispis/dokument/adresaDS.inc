<?php

/**
 * trida pro identifikaci adresy datove schranky
 *
 * @author onma
 * @package spis.main 
 */
 
class adresaDS {
  /** identifikator datove schranky */
  var $IdDb;
  /** Organizační jednotka hodnotou z číselníku */
  var $OrgUnitNum;
  /** Organizační jednotka slovně */
  var $OrgUnit;
  
  /**
  * konstruktor 
  *
  * @param array $adresaDS pole pro naplneni 
  */ 
  public function __construct($adresaDS) {  
    $this->IdDb = ($adresaDS['IdDb']);
    $this->OrgUnitNum = ($adresaDS['OrgUnitNum']);
    $this->OrgUnit = ($adresaDS['OrgUnit']);
  }

}
