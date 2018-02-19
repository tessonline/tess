<?php

/**
 * Funkce vraci seznam prednastavenych adresatu dane skupiny.
 * @param integer $skupinaId Id skupiny prednastavenych adresatu
 * @return array Prednastaveni adresati array(1 => array($organizacniVyborId, $zpracovatelId), 2 => ...)
 */
function getAdresati($skupinaId) {
  
  $skupinaId = intval($skupinaId); 
  $adresati = array();
  
  $dbConnector = new $GLOBALS['PROPERTIES']['DB_NAME'];
  $sql = 'SELECT * FROM posta_nastaveni_vnitrni_adresati WHERE skupina_id = ' . $skupinaId;
  $dbConnector->query($sql);
  
  while ($dbConnector->next_record()) {
    
    $adresat = array();
    
    $adresat['organizacniVybor'] = $dbConnector->Record['ORGANIZACNI_VYBOR'];
    $adresat['zpracovatel'] = $dbConnector->Record['ZPRACOVATEL'];
    
    $adresati[] = $adresat;
  }
  
  return $adresati;
}