<?php

/**
 * trida pro informace o vlozenych dokumentech 
 *
 * @author onma
 */
class vlozenyDokument {
  /** trida VlozenyDokument, definovana pomoci tridy dokument */
  var $DokumentUplnyVlozeny;
  
  /**
  * konstruktor 
  *
  * @param array $dokument pole pro naplneni 
  */ 
  public function __construct($dokument) {  
    $this->DokumentUplnyVlozeny = &$dokument;
  }
}
