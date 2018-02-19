<?php

/**
 * trida pro dodatecna data
 *
 * @author onma
 */
class doplnujiciData {
  /** počet listů listinného dokumentu */
  var $PocetListu;
  /** počet listinných příloh */
  var $PocetPriloh;
  /** druh příloh textově */
  var $DruhPriloh;
  
  /**
  * konstruktor 
  *
  * @param array $doplnujiciData pole pro naplneni 
  */ 
  public function __construct($doplnujiciData) {  
    $this->PocetListu = $doplnujiciData['PocetListu'];
    $this->PocetPriloh = $doplnujiciData['PocetPriloh'];
    $this->DruhPriloh = ($doplnujiciData['DruhPriloh']);
  }

}
