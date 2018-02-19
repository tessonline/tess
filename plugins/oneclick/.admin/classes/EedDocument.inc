<?php

@include_once(FileUp2('.config/config.inc'));

class EedDocument {
  
  private $id;
  private $evidencniCislo;
  private $cisloJednaci;
  private $typ;
  private $datum;
  private $vec;
  private $typAdresy;
  private $prijmeni;
  private $jmeno;
  private $organizace;
  private $oddeleni;
  private $osoba;
  private $ulice;
  private $cisloPopisne;
  private $cisloOrientacni;
  private $mesto;
  private $psc;
  private $ds;
  private $adresatCj;
  private $odbor;
  private $zpracovatelId;
  private $skartaceId;
  private $zmocneniZakon;
  private $zmocneniRok;
  private $zmocneniParagraf;
  private $zmocneniOdstavec;
  private $zmocneniPismeno;
  private $cisloSpisu;
  private $nazevSpisu;
  private $poznamka; 
  private $files;  
  
  public function __construct() {
  }
  
  // Settery
  public function __set($name, $value) {
    $this->$name = $value;
  } 

  // Gettery
  public function __get($name) {
    return $this->$name;
  }
  
  /**
   * Funkce zjisti, jestli je k danemu dokumentu vytvoren nejaky ukol ve sluzbe 1click.
   * @global array[mixed] $CONFIG Application config.
   * @param integer $eedDocumentId Id EED dokumentu.
   * @return bool Pokud existuji ukoly: true, jinak: false. 
   */
  public static function hasTask($eedDocumentId) {
    
    global $CONFIG;
    
    $table = $CONFIG['POSTA_INTERFACE_ONE_CLICK']['AGENDA_TABLE'];
    $q = new $CONFIG['POSTA_INTERFACE_ONE_CLICK']['DB_NAME'];
    $q->query('SELECT task_id FROM ' . $table . ' WHERE document_id = ' . $eedDocumentId);
    $q->next_record();
            
    return !empty($q->Record);
  }
  
  /**
   * Funkce vrati id ukolu, pod kterym je ulozen ve sluzbe 1click.
   * @return integer Pokud ukol existuje: id 1click ukolu, jinak: 0.
   */
  public function getTaskId() {
    
    global $PROPERTIES;
    
    $table = $PROPERTIES['AGENDA_TABLE'];
    $q = new $PROPERTIES['DB_NAME'];
    $q->query('SELECT task_id FROM ' . $table . ' WHERE document_id = ' . $this->id);
    $q->next_record();
            
    return $q->Record['TASK_ID'];
  }
  
  /**
   * Funkce vrati instanci EedDocumentu vytvorenou z pole.
   * @param array $array Pole hodnot, ze kterych je vytvoren EedDocument.
   * @return EedDocument
   */
  public static function factory($array) {
    $document = new EedDocument();
    
    $document->id = $array['DOKUMENT_ID'];
    $document->evidencniCislo = $array['EV_CISLO'];
    $document->cisloJednaci = $array['CISLO_JEDNACI'];
    $document->typ = $array['TYP_DOC'];
    $document->datum = $array['DATUM'];
    $document->vec = $array['VEC'];
    $document->typAdresy = $array['TYP_ADR'];
    $document->prijmeni = $array['PRIJMENI'];
    $document->jmeno = $array['JMENO'];
    $document->organizace = $array['ORGANIZACE'];
    $document->oddeleni = $array['ODDELENI'];
    $document->osoba = $array['OSOBA'];
    $document->ulice = $array['ULICE'];
    $document->cisloPopisne = $array['CP'];
    $document->cisloOrientacni = $array['COR'];
    $document->mesto = $array['MESTO'];
    $document->psc = $array['PSC'];
    $document->ds = $array['DS'];
    $document->adresatCj = $array['ADRESAT_CJ'];
    $document->odbor = $array['ODBOR'];
    $document->zpracovatelId = $array['ZPRACOVATEL'];
    $document->skartaceId = $array['SKARTACE_ID'];
    $document->zmocneniZakon = $array['ZMOCNENI_ZAKON'];
    $document->zmocneniRok = $array['ZMOCNENI_ROK'];
    $document->zmocneniParagraf = $array['ZMOCNENI_PAR'];
    $document->zmocneniOdstavec = $array['ZMOCNENI_ODST'];
    $document->zmocneniPismeno = $array['ZMOCNENI_PISMENO'];
    $document->cisloSpisu = $array['SPIS_CISLO'];
    $document->nazevSpisu = $array['SPIS_NAZEV'];
    $document->poznamka = $array['POZNAMKA'];
    $document->files = array();
    
    return $document;
  }
}
