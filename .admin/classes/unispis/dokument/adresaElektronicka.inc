<?php

/**
 * trida pro identifikaci elektronicke adresy (tel, email)
 *
 * @author onma
 */
class adresaElektronicka {
  /** typ elektronickeho kontaktu tel|fax|email */
  var $Typ;
  /** Hodnota elektronické adresy, např. telefonní číslo, nebo email adresa */
  var $Kontakt;
  /** Organizační jednotka slovně */
  var $OrgUnit;
  
  /**
  * konstruktor 
  *
  * @param array $adresaElektronicka pole pro naplneni 
  */ 
  public function __construct($adresaElektronicka) {  
    $this->Typ = ($adresaElektronicka['Typ']);
    $this->Kontakt = ($adresaElektronicka['Kontakt']);
  }

}
