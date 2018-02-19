<?php
include_once('Dokument.php');

/*
 * @author luma
 */
class Txt extends Dokument {
  
  //public $globals = array();
  
  /*
   * Precte z dokumentu specifikovaného
   */
  public function process() {
    $f = fopen($this->doc_path, "r");
    $this->setGlobals();
  }
  
  
  
}