<?php
require_once('subjekt.inc');

/**
 * trida pro informace o doruceni dokumentu 
 *
 * @author onma
 */
class doruceni {
  /** trida Odesilatel - Popis subjetku, který odeslal = vypravil zásilku */
  var $Odesilatel;
  /** trida pro informace o samotne obalce (zasilce) */
  var $ZasilkaInfo;
  
  /**
  * konstruktor 
  *
  * @param array $doruceni pole pro naplneni 
  */ 
  public function __construct($doruceni) {  
    $this->Odesilatel = new odesilatel($doruceni['Odesilatel']);
    $this->ZasilkaInfo = new zasilkaInfo($doruceni['ZasilkaInfo']);
  }
}
