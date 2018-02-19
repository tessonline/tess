<?php
require_once('adresa.inc');

/**
 * trida pro identifikaci subjektu
 *
 * @author onma
 */
class subjekt {
  /** vyjadřuje právní forma subjektu a případný způsob zastoupení tohoto subjektu
   *  Neurceno|Fyzicka|Osvc|Pravnicka|Zamestnanec|Utvar
   */
  var $TypSubjektu;
  /** Nazev pravnicke osoby. 
   * Beuvádí se v případě že TypSubjektu="Fyzicka"  
   */
  var $ObchodniNazev;
  /** IČO se uvádí, pokud je subjektu IČO přiděleno a je v době pořízení záznamu známé */
  var $IC;
  /** Datum narození 
   *  Element se uvádí pouze v případě že TypSubjektu="Fyzicka" nebo TypSubjektu="Osvc" a to pouze 
   *  v případě, že je nutné odlišit dvě osoby stejného jména a stejného trvalého bydliště.
   */
  var $DatumNarozeni;
  /** Místo narození, viz. jako u DatumNarozeni */
  var $MistoNarozeni;
  /** Jméno fyzické osoby
   * neuvádí se v případě TypSubjektu="Pravnicka" a value="Utvar"  
   */
  var $Jmeno;
  /** Jméno fyzické osoby
   * neuvádí se v případě TypSubjektu="Pravnicka" a value="Utvar"  
   */
  var $Prijmeni;
  /** příjmení fyzické osoby
   * neuvádí se v případě TypSubjektu="Pravnicka" a value="Utvar"  
   */
  var $Osloveni;
  /** titul fyzické osoby před jménem
   * neuvádí se v případě TypSubjektu="Pravnicka" a value="Utvar"  
   */
  var $TitulPred;
  /** titul fyzické osoby za jménem
   * neuvádí se v případě TypSubjektu="Pravnicka" a value="Utvar"  
   */
  var $TitulZa;
  /** textově název útvaru
   *  uvádí pouze v případě že TypSubjektu="Pravnicka" a value="Utvar"
   */
  var $FunkceUtvarPopis;
  /** identifikator utvaru
   *  uvádí pouze v případě že TypSubjektu="Pravnicka" a value="Utvar"
   */
  var $FunkceUtvarIdentifikator;
  /** Poznámka */
  var $Poznamka;
  /** trida s uvedenim adres subjektu */
  var $Adresa;
  
  /**
  * konstruktor 
  *
  * @param array $zmocneni pole pro naplneni 
  */ 
  public function __construct($subjekt) {  
    $this->TypSubjektu = ($subjekt['TypSubjektu']);
    $this->ObchodniNazev = ($subjekt['ObchodniNazev']);
    $this->IC = ($subjekt['IC']);
    $this->DatumNarozeni = ($subjekt['DatumNarozeni']);
    $this->MistoNarozeni = ($subjekt['MistoNarozeni']);
    $this->Jmeno = ($subjekt['Jmeno']);
    $this->Prijmeni = ($subjekt['Prijmeni']);
    $this->Osloveni = ($subjekt['Osloveni']);
    $this->TitulPred = ($subjekt['TitulPred']);
    $this->TitulZa = ($subjekt['TitulZa']);
    $this->FunkceUtvarPopis = ($subjekt['FunkceUtvarPopis']);
    $this->FunkceUtvarIdentifikator = ($subjekt['FunkceUtvarIdentifikator']);
    $this->Poznamka = ($subjekt['Poznamka']);
    $this->Adresa = new adresa($subjekt['Adresa']);
  }

}
