<?php

/**
 * trida zmocneni (uziva se obcas pri posilani datovou schrankou), definice, na zaklade
 * jakeho zakona se dana vec vyrizuje 
 *
 * @author onma
 */
class zmocneni {
  /** číslo zákona */
  var $LegalTitleLaw;
  /** rok vydání */
  var $LegalTitleYear;
  /** paragraf v zákoně< */
  var $LegalTitleSect;
  /** odstavec v paragrafu */
  var $LegalTitlePar;
  /** písmeno v odstavci */
  var $LegalTitlePoint;
  
  /**
  * konstruktor 
  *
  * @param array $zmocneni pole pro naplneni 
  */ 
  public function __construct($zmocneni) {  
    $this->LegalTitleLaw = ($zmocneni['LegalTitleLaw']);
    $this->LegalTitleYear = ($zmocneni['LegalTitleYear']);
    $this->LegalTitleSect = ($zmocneni['LegalTitleSect']);
    $this->LegalTitlePar = ($zmocneni['LegalTitlePar']);
    $this->LegalTitlePoint = ($zmocneni['LegalTitlePoint']);
  }

}
