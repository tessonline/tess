<?php

/**
 * DELETE vnitrnich adresatu.
 * @param integer $postaId - Id spisu.
 */
function deleteAll($postaId) {
  
  $db = new DB_POSTA;
  
  $sql = 'DELETE FROM posta_vnitrni_adresati WHERE posta_id = ' . $postaId;
  $db->query($sql);
}

/**
 * DELETE vnitrnich adresatu.
 * @param integer $postaId - Id spisu.
 */
function deleteWithout($postaId, $vnitrniAdresati) { 
  
  $db = new DB_POSTA;  
  $adresatiIds = '';
  
  if (is_array($vnitrniAdresati))
  foreach ($vnitrniAdresati as $id => $adresat) {
  
    $adresatiIds .= $id . ', ';
  }
  
  $adresatiIds .= ' 0';
  
  $sql = 'DELETE FROM posta_vnitrni_adresati'
          . ' WHERE posta_id = ' . $postaId
          . ' AND id NOT IN (' . $adresatiIds . ')';
  $db->query($sql);
}

/**
 * DELETE vnitrnich adresatu.
 * @param array $vnitrniAdresati - Pole vnitrnich adresatu.
 */
function delete($vnitrniAdresati) {
  
  $db = new DB_POSTA;
  
  if (is_array($vnitrniAdresati))
  foreach ($vnitrniAdresati as $id => $adresat) {
  
    $sql = 'DELETE FROM posta_vnitrni_adresati WHERE id = ' . $id;
    $db->query($sql);
  }
}

/**
 * INSERT vnitrnich adresatu.
 * @param integer $postaId - Id spisu.
 * @param array $vnitrniAdresati - Pole vnitrnich adresatu.
 */
function insert($postaId, $vnitrniAdresati) {
  
  $db = new DB_POSTA;  
  
  if (is_array($vnitrniAdresati))
  foreach ($vnitrniAdresati as $adresat) {
    
    $adresat['zp'] = $adresat['zp'] ? $adresat['zp'] : 0;
    $sql = 'INSERT INTO posta_vnitrni_adresati (posta_id, organizacni_vybor, zpracovatel)
              VALUES (' . $postaId . ', ' . $adresat['ov'] . ', ' . $adresat['zp'] . ');';
    $db->query($sql);
  }
}

/**
 * UPDATE vnitrnich adresatu.
 * @param array $vnitrniAdresati - Pole vnitrnich adresatu.
 */
function update($vnitrniAdresati) {
  
  $db = new DB_POSTA;  
  
  if (is_array($vnitrniAdresati))
  foreach ($vnitrniAdresati as $id => $adresat) {
    if (!$adresat['ov']) $adresat['ov'] = 'NULL';
    if (!$adresat['zp']) $adresat['zp'] = 'NULL';
    $sql = 'UPDATE posta_vnitrni_adresati SET'
              . ' organizacni_vybor = ' . $adresat['ov'] . ', '
              . ' zpracovatel = ' . $adresat['zp']
              . ' WHERE id = ' . $id;
    $db->query($sql);
  }  
}


/**
 * SELECT vnitrnich adresatu.
 * @param integer $postaId - Id spisu.
 * @return array $vnitrniAdresati - Pole vnitrnich adresatu.
 */
function getVnitrniAdresaty($postaId) {
  
  $db = new DB_POSTA;  
  $sql = 'SELECT * FROM posta_vnitrni_adresati WHERE posta_id = ' . $postaId;
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
  
  if (is_array($formFields))
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

function deleteVnitrniAdresati($postaId) {

  deleteAll(intval($postaId));
}

function insertVnitrniAdresati($postaId, $vnitrniAdresati) {
  insert(intval($postaId), $vnitrniAdresati['new']);
}

function editvnitrniAdresati($postaId, $vnitrniAdresati) {
  
  $posatId = intval($postaId);
  
  deleteWithout($posatId, $vnitrniAdresati['old']);
  update($vnitrniAdresati['old']);
  insert($posatId , $vnitrniAdresati['new']);
}
