<?php

/**
 * trida pro informace o vyrizeni dokumentu 
 *
 * @author lule
 */
class vyrizeni {
  /** datum vyrizeni */
  var $Datum;
  /** poznamka */
  var $Poznamka;
  /** spisovy znak */
  var $SpisovyZnak;
  /** skartacni znak */
  var $SkartacniZnak;
  /** skartacni lhuta */
  var $SkartacniLhuta;
  
  /**
  * konstruktor 
  *
  * @param array $vyrizeni pole pro naplneni 
  */ 
  public function __construct($vypraveni) {  
    $this->Datum = $vypraveni['Datum'];
    $this->SpisovyZnak = $vypraveni['SpisovyZnak'];
    $this->SkartacniZnak = $vypraveni['SkartacniZnak'];
    $this->SkartacniLhuta = $vypraveni['SkartacniLhuta'];
    $this->Poznamka = $vypraveni['Poznamka'];
  }
}
