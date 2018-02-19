<?php

/**
 * Rozhrani pro elektronicky podepsany dokument
 * @author mier
 */
interface ISignedDocument {
  
  /**
   * Funkce overi zda elektronicky podpis dokumentu platny
   * @return bool Pokud je el. podpis platny pak true, jinak false 
   */
  public function verify();
  
  /**
   * Funkce vygeneruje protokol o zpracovani dokumentu (informace o nem a jeho podpisu)
   * @param string[PDF|TXT] $protocolType Typ vystupniho souboru
   * @return string Obsah souboru
   */
  public function createProtocolContent($protocolType);
  
}

?>
