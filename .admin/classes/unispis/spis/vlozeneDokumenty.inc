<?php

/**
 * trida pro informace o vlozenych dokumentech 
 *
 * @author onma
 */
class DokumentyVlozene {
  /** trida VlozenyDokument, definovana pomoci tridy dokument */
  var $VlozenyDokument;
  
  /**
  * konstruktor 
  *
  * @param array $dokument pole pro naplneni 
  */ 
  public function __construct($dokument) {  
    $this->VlozenyDokument = new vlozenyDokument($dokument);
  }
}
