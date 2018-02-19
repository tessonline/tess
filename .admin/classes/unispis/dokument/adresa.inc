<?php
require_once('adresaPostovni.inc');
require_once('adresaDS.inc');
require_once('adresaElektronicka.inc');

/**
 * trida pro identifikaci adresy 
 *
 * @author onma
 */
class adresa {
  /** trida postovni adresy, muze byt uvedeno 0..N adres */
  var $AdresaPostovni = array();
  /**  trida adresy datove schranky, vedeno jen 0..1 elementů */
  var $AdresaDS;
  /**  trida elektronicke adresy, muze byt uvedeno 0..N adres */
  var $AdresaElektronicka = array();
  
  /**
  * konstruktor 
  *
  * @param array $adresa pole pro naplneni 
  */ 
  public function __construct($adresa) {  
    $this->AdresaPostovni[] = new adresaPostovni($adresa['AdresaPostovni']);
    $this->AdresaDS = new adresaDS($adresa['AdresaDS']);
    $this->AdresaElektronicka[] = new adresaElektronicka($adresa['AdresaElektronicka']);
  }
}
