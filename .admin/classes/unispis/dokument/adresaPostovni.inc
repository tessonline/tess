<?php

/**
 * trida pro identifikaci postovni adresy 
 * 
 * @author onma
 */
class adresaPostovni {
  /** Název obce */
  var $Obec;
  /** Název části obce */
  var $CastObce;
  /** Název městské části */
  var $MestskaCast;
  /** Název ulice */
  var $Ulice;
  /** Evidenční číslo */
  var $EvidencniCislo;
  /** Orientační číslo */
  var $OrientacniCislo;
  /** Popisné číslo */
  var $PopisneCislo;
  /** Poštovní směrovací číslo */
  var $Psc;
  /** Kód zkratky státu dle číselníku ČSÚ */
  var $Zeme;
  /** identifikátor z Registru územní identifikace */
  var $RuianVazba;
  /** Poznámka */
  var $Poznamka;
  /** POBOX hodnota */
  var $POBOX;
  /** Typ poštovní adresy a to ve vztahu k subjektu 
   *  - Neurceno|Dorucovaci|TrvaleBydliste|PrechodneBydliste|SidloFirmy|PobockaFirmy     */
  var $TypAdresy;
  /** Název dodací pošty */
  var $DodaciPosta;
  /** Název okresu */
  var $Okres;
  
  /**
  * konstruktor 
  *
  * @param array $adresaPostovni pole pro naplneni 
  */ 
  public function __construct($adresaPostovni) {  
    $this->Obec = ($adresaPostovni['Obec']);
    $this->CastObce = ($adresaPostovni['CastObce']);
    $this->MestskaCast = ($adresaPostovni['MestskaCast']);
    $this->Ulice = ($adresaPostovni['Ulice']);
    $this->EvidencniCislo = ($adresaPostovni['EvidencniCislo']);
    $this->OrientacniCislo = ($adresaPostovni['OrientacniCislo']);
    $this->PopisneCislo = ($adresaPostovni['PopisneCislo']);
    $this->Psc = ($adresaPostovni['Psc']);
    $this->Zeme = ($adresaPostovni['Zeme']);
    $this->RuianVazba = ($adresaPostovni['RuianVazba']);
    $this->Poznamka = ($adresaPostovni['Poznamka']);
    $this->POBOX = ($adresaPostovni['POBOX']);
    $this->TypAdresy = ($adresaPostovni['TypAdresy']);
    $this->DodaciPosta = ($adresaPostovni['DodaciPosta']);
    $this->Okres = ($adresaPostovni['Okres']);
  }

}
