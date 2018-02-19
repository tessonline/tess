<?php
/**
 * Projde pole formularovych prvku a vyfiltruje z neho vnejsi adresaty.
 * Roztridi je na nove a jiz existujici.
 * @param array $formFields - Pole prvku, ktere byly odeslany prostrednictvim formulare.
 * @return array - Pole vnejsich adresatu.
 */
function getVnejsiAdresatiFromForm($formFields) {
  
  $vnejsiAdresati = array();
  
  foreach ($formFields as $key => $value) {
  
    // Polozky formulare, ktere jsou souvisi s vnejsimi adresaty
    if (strstr($key, 'ADRESAT_ID_')) {
    
      $temp = explode('ADRESAT_ID_', $key);
	  $id = intval($temp[1]);
          $vnejsiAdresati[$temp[2]][$id] = $value ? intval($value) : 'NULL'; // id adresata
      }
    }
  
  return $vnejsiAdresati;
}