<?php

include_once(GetAgendaPath('POSTA', false, false) . '/.admin/properties.inc');
include_once(FileUp2('posta/.admin/adresati_func.inc'));

/**
 * Funkce vraci seznam prednastavenych adresatu dane skupiny.
 * @param integer $skupinaId Id skupiny prednastavenych adresatu
 * @return array Prednastaveni adresati array(1 => array($organizacniVyborId, $zpracovatelId), 2 => ...)
 */
function getAdresati($skupinaId) {
  
  $skupinaId = intval($skupinaId); 
  $adresati = array();
  
  $dbConnector = new $GLOBALS['PROPERTIES']['DB_NAME'];
  $sql = 'SELECT * FROM posta_nastaveni_vnejsi_adresati va
            LEFT JOIN posta_adresati a ON va.adresat_id = a.id
            WHERE skupina_id = ' . $skupinaId;
  $dbConnector->query($sql);
  
  while ($dbConnector->next_record()) {
    
    $adresat = array();
    
    $adresat['id'] = $dbConnector->Record['ADRESAT_ID'];    
    $adresat['preview'] = iconv('ISO-8859-2', 'UTF-8', formatPreview($dbConnector->Record));
    
    $adresati[] = $adresat;
  }
  
  return $adresati;
}