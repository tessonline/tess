<?php

/**
 * DELETE vnitrnich adresatu.
 * @param integer $skupinaId - Id skupiny.
 */
function deleteAll($skupinaId) {
  
  $db = new DB_POSTA;
  
  $sql = 'DELETE FROM posta_nastaveni_vnitrni_adresati WHERE skupina_id = ' . $skupinaId;
  $db->query($sql);
}

/**
 * DELETE vnitrnich adresatu.
 * @param integer $skupinaId - Id skupiny.
 */
function deleteWithout($skupinaId, $vnitrniAdresati) { 
  
  $db = new DB_POSTA;  
  $adresatiIds = '';
  
  foreach ($vnitrniAdresati as $id => $adresat) {
  
    $adresatiIds .= $id . ', ';
  }
  
  $adresatiIds .= ' 0';
  
  $sql = 'DELETE FROM posta_nastaveni_vnitrni_adresati'
          . ' WHERE skupina_id = ' . $skupinaId
          . ' AND id NOT IN (' . $adresatiIds . ')';
  $db->query($sql);
}

/**
 * DELETE vnitrnich adresatu.
 * @param array $vnitrniAdresati - Pole vnitrnich adresatu.
 */
function delete($vnitrniAdresati) {
  
  $db = new DB_POSTA;
  
  foreach ($vnitrniAdresati as $id => $adresat) {
  
    $sql = 'DELETE FROM posta_nastaveni_vnitrni_adresati WHERE id = ' . $id;
    $db->query($sql);
  }
}

/**
 * INSERT vnitrnich adresatu.
 * @param integer $skupinaId - Id skupiny.
 * @param array $vnitrniAdresati - Pole vnitrnich adresatu.
 */
function insert($skupinaId, $vnitrniAdresati) {
  
  $db = new DB_POSTA;  
  
  foreach ($vnitrniAdresati as $adresat) {
  
    $sql = 'INSERT INTO posta_nastaveni_vnitrni_adresati (skupina_id, organizacni_vybor, zpracovatel)
              VALUES (' . $skupinaId . ', ' . $adresat['ov'] . ', ' . $adresat['zp'] . ');';
    $db->query($sql);
  }  
}

/**
 * UPDATE vnitrnich adresatu.
 * @param array $vnitrniAdresati - Pole vnitrnich adresatu.
 */
function update($vnitrniAdresati) {
  
  $db = new DB_POSTA;  
  
  foreach ($vnitrniAdresati as $id => $adresat) {
  
    $sql = 'UPDATE posta_nastaveni_vnitrni_adresati SET'
              . ' organizacni_vybor = ' . $adresat['ov'] . ', '
              . ' zpracovatel = ' . $adresat['zp']
              . ' WHERE id = ' . $id;
    $db->query($sql);
  }  
}


/**
 * SELECT vnitrnich adresatu.
 * @param integer $skupinaId - Id skupiny.
 * @return array $vnitrniAdresati - Pole vnitrnich adresatu.
 */
function getVnitrniAdresaty($skupinaId) {
  
  $db = new DB_POSTA;  
  $sql = 'SELECT * FROM posta_nastaveni_vnitrni_adresati WHERE skupina_id = ' . $skupinaId;
  $db->query($sql);
  $vnitrniAdresati = array();
  
  while ($db->next_record()) {
  
    $adresat = array();
    $adresat['ov'] = $db->Record['ORGANIZACNI_VYBOR'];
    $adresat['zp'] = $db->Record['ZPRACOVATEL'];
    
    $vnitrniAdresati[$db->Record['ID']] = $adresat;
  }
  
  return $vnitrniAdresati;
}

/**
 * Projde pole formularovych prvku a vyfiltruje z neho vnitrni adresaty.
 * Roztridi je na nove a jiz existujici.
 * @param array $formFields - Pole prvku, ktere byly odeslany prostrednictvim formulare.
 * @return array - Pole vnitrnich adresatu.
 */
function getVnitrniAdresatiFromForm($formFields) {
  
  $vnitrniAdresati = array();
  
  foreach ($formFields as $key => $value) {
  
    // Polozky formulare, ktere jsou souvisi s vnitrnimi adresaty
    if (strstr($key, 'ORGANIZACNI_VYBOR-') || strstr($key, 'ZPRACOVATEL-')) {
    
      $temp = explode('-', $key);
      $age = $temp[2] ? 'new' : 'old';
      $id = intval($temp[1]);
      
      switch ($temp[0]) {
        
        case 'ORGANIZACNI_VYBOR':
        
          $vnitrniAdresati[$age][$id]['ov'] = $value ? intval($value) : 'NULL'; // ov - organizacni vybor
          break;
          
        case 'ZPRACOVATEL':
        
          $vnitrniAdresati[$age][$id]['zp'] = $value ? intval($value) : 'NULL'; // zp - zpracovatel
          break;
      }
    }
  }
  
  return $vnitrniAdresati;
}

function deleteVnitrniAdresati($skupinaId) {

  deleteAll(intval($skupinaId));
}

function insertVnitrniAdresati($skupinaId, $vnitrniAdresati) {

  insert(intval($skupinaId), $vnitrniAdresati['new']);
}

function editvnitrniAdresati($skupinaId, $vnitrniAdresati) {
  
  $skupinaId = intval($skupinaId);
  
  deleteWithout($skupinaId, $vnitrniAdresati['old']);
  update($vnitrniAdresati['old']);
  insert($skupinaId , $vnitrniAdresati['new']);
}
