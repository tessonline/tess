<?php

/**
 * DELETE odbory.
 * @param integer $typPostyIdId.
 */
function deleteAll($typPostyId) {
  
  $db = new DB_POSTA;
  
  $sql = 'DELETE FROM cis_posta_typ_odbor WHERE id_posta_typ=' . $typPostyId;
  $db->query($sql);
}


/**
 * DELETE vnitrnich adresatu.
 * @param integer $postaId - Id spisu.
 */
function deleteWithout($typPostyId, $odbory) {
  
  $db = new DB_POSTA;
  $odboryIds = '';
  
  if (is_array($odbory))
    foreach ($odbory as $id => $odbor) {
      
      $odboryIds .= $id . ', ';
    }
  
  $odboryIds .= ' 0';
  
  $sql = 'DELETE FROM cis_posta_typ_odbor'
      . ' WHERE id_posta_typ = ' . $typPostyId
      . ' AND id NOT IN (' . $odboryIds . ')';
      $db->query($sql);
}


/**
 * DELETE vnitrnich adresatu.
 * @param array $vnitrniAdresati - Pole vnitrnich adresatu.
 */
function delete($odbory) {
  
  $db = new DB_POSTA;
  
  if (is_array($odbory))
  foreach ($odbory as $id => $odbor) {
  
    $sql = 'DELETE FROM cis_posta_typ_odbor WHERE id = ' . $id;
    $db->query($sql);
  }
}

/**
 * INSERT odbory.
 * @param integer $typPostyId.
 * @param array $odbory - Pole odboru.
 */
function insert($typPostyId, $odbory) {
  
  $db = new DB_POSTA;  
  var_dump($odbory);

  if (is_array($odbory))
  foreach ($odbory as $odbor) {
    if ($odbor!="NULL") {
      $sql = 'INSERT INTO cis_posta_typ_odbor (id_posta_typ, id_odbor)
              VALUES (' . $typPostyId . ', ' . $odbor . ');';
      $db->query($sql);
    }
  }
}

/**
 * UPDATE odboru.
 * @param array $odbory - Pole vnitrnich adresatu.
 */
function update($odbory) {
  
  $db = new DB_POSTA;  
  
  if (is_array($odbory))
  foreach ($odbory as $id => $odbor) {
    if (!$odbor) $odbor = 'NULL';
    $sql = 'UPDATE cis_posta_typ_odbor SET'
              . ' id_odbor = ' . $odbor 
              . ' WHERE id = ' . $id;
    $db->query($sql);
  }  
}


/**
 * SELECT vnitrnich odboru.
 * @param integer $typPostyId.
 * @return array $odbory - Pole odboru.
 */
function getOdbory($typPostyId) {
  
  $db = new DB_POSTA;  
  $sql = 'SELECT * FROM cis_posta_typ_odbor WHERE id_posta_typ = ' . $typPostyId;
  $db->query($sql);
  $odbory = array();
  
  while ($db->next_record()) {
  
/*    $odbor = array();
    $adresat['ov'] = $db->Record['ORGANIZACNI_VYBOR'];
    $adresat['zp'] = $db->Record['ZPRACOVATEL'];*/
    
    $odbor = $db->Record['ID_ODBOR'];
    
    $odbory[$db->Record['ID']] = $odbor;
  }
  
  return $odbory;
}

/**
 * Projde pole formularovych prvku a vyfiltruje z neho vnitrni adresaty.
 * Roztridi je na nove a jiz existujici.
 * @param array $formFields - Pole prvku, ktere byly odeslany prostrednictvim formulare.
 * @return array - Pole vnitrnich adresatu.
 */
function getOdboryFromForm($formFields) {
  
  $odbory = array();
  
  if (is_array($formFields))
  foreach ($formFields as $key => $value) {
    // Polozky formulare, ktere jsou souvisi s vnitrnimi adresaty
    if (strstr($key, 'ODBOR-') ) {
      $temp = explode('-', $key);
      $age = $temp[2] ? 'new' : 'old';
      $id = intval($temp[1]);
      
      switch ($temp[0]) {
        
        case 'ODBOR':
        
          $odbory[$age][$id] = $value ? intval($value) : 'NULL'; // ov - organizacni vybor
          break;
      }
    }
  }
  
  return $odbory;
}

function deleteOdbory($typPostyId) {

  deleteAll(intval($typPostyId));
}

function insertOdbory($typPostyId, $odbory) {
  insert(intval($typPostyId), $odbory['new']);
}

function editOdbory($typPostyId, $odbory) {
  
  $posatId = intval($typPostyId);
  
  deleteWithout($typPostyId, $odbory['old']);
  update($odbory['old']);
  insert($typPostyId, $odbory['new']);
}
