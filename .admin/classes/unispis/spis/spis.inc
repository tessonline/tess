<?php
require_once(FileUpUrl('classes/tools/spisTools.inc'));
require_once('vlozeneDokumenty.inc');
require_once('vlozenyDokument.inc');

/**
 * trida spisu
 *
 * @author onma
 */
class spis {

  /** identifikator spisu */
  var $Id;
  /** Krátká věc vystihující obsah spisu */
  var $Nazev;
  /** Podrobný popis obsahu spisu */
  var $Popis;
  /** textove pole cisla jednaciho */
  var $CisloJednaci;
  /** označení spisu */
  var $SpisovaZnacka;
  /** datum a cas vytvoreni dokumentu */
  var $DatumCasVytvoreni;
  /** Popis typu dokumentu */
  var $TypDokumentu = 'SPIS';
  /** Stručný popis/označení spisového a skartačního plánu */
  var $SpisovyPlan; 
  /** Označení ukládacího znaku (330.0) nebo popis znaku spisového a  skartačního plánu */
  var $SpisovyZnak; 
  /** Znak pro oznaceni skartace - A-archivace, S-skartace, V-vytřídění na základě skartačního řízení */
  var $SkartacniZnak; 
  /** Skartační nebo archivační lhůta v letech */
  var $SkartacniLhuta;  
  /** Poznámka */
  var $Poznamka; 
  /** třída elementů dokumentů vložených do spisu */
  var $DokumentyVlozene = array();
  
  // Settery
  public function __set($name, $value) {
    $this->$name = $value;
  } 

  // Gettery
  public function __get($name) {
    return $this->$name;
  }

  /** konstruktor
   *
   * @author onma
   * @param array $spis vstupni pole pro konstruktor
   */            
  public function __construct($spis = array()) {  
    $this->Id = ($spis['Id']);
    $this->Nazev = ($spis['Nazev']);
    $this->Popis = ($spis['Popis']);
    $this->CisloJednaci = ($spis['CisloJednaci']);
    $this->SpisovaZnacka = ($spis['SpisovaZnacka']);
    $this->PodaciDenikPoradi = ($spis['PodaciDenikPoradi']);
    $this->PodaciDenikRok = ($spis['PodaciDenikRok']);
    $this->PodaciDenik = ($spis['PodaciDenik']);
    $this->DatumCasVytvoreni = ($spis['DatumCasVytvoreni']);
    $this->SpisovyPlan = ($spis['SpisovyPlan']);
    $this->SpisovyZnak = ($spis['SpisovyZnak']);
    $this->SkartacniZnak = ($spis['SkartacniZnak']);
    $this->SkartacniLhuta = ($spis['SkartacniLhuta']);
    $this->Poznamka = ($spis['Poznamka']);
  }

  public function addDokumentDoSpisu(&$dokument) {
    $this->DokumentyVlozene[] = new VlozenyDokument(&$dokument);
  }

  public function getFirstDokument() {
    return $this->DokumentyVlozene[0]->DokumentUplnyVlozeny;
  }

}

