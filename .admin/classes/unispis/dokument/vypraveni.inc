<?php

/**
 * trida pro informace o vypraveni dokumentu 
 *
 * @author onma
 */
class vypraveni {
  /** trida adresat, Popis subjetku, komu je zasilka urcena */
  var $adresat;
  /** info o zasilce */
  var $zasilkaInfo;
  
  /**
  * konstruktor 
  *
  * @param array $vypraveni pole pro naplneni 
  */ 
  public function __construct($vypraveni) {  
    $this->Adresat = new adresat($vypraveni['Adresat']);
    $this->ZasilkaInfo = new zasilkaInfo($vypraveni['ZasilkaInfo']);
  }
}
