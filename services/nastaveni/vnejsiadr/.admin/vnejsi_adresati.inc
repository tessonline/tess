<?php
/**
 * DELETE vnejsich adresatu.
 * @param integer $skupinaId - Id skupiny.
 */
function deleteAll($skupinaId) {
  
  $db = new DB_POSTA;
  
  $sql = 'DELETE FROM posta_nastaveni_vnejsi_adresati WHERE skupina_id = ' . $skupinaId;
  $db->query($sql);
}

function deleteVnejsiAdresati($skupinaId) {

  deleteAll(intval($skupinaId));
}

/**
 * DELETE vnejsich adresatu.
 * @param integer $skupinaId - Id skupiny.
 */
function deleteWithout($skupinaId, $vnejsiAdresati) { 
  
  $db = new DB_POSTA;  
  $adresatiIds = '';
  
  foreach ($vnejsiAdresati as $key => $adresat) {
  
    $adresatiIds .= $key . ', ';
	
  }
 
  $adresatiIds .= ' 0';
  $sql = 'DELETE FROM posta_nastaveni_vnejsi_adresati'
          . ' WHERE skupina_id = ' . $skupinaId
          . ' AND adresat_id NOT IN (' . $adresatiIds . ')';
  $db->query($sql);

  }

/**
 * DELETE vnejsich adresatu.
 * @param array $vnejsiAdresati - Pole vnejsich adresatu.
 */
function delete($vnejsiAdresati) {
  
  $db = new DB_POSTA;
  
  foreach ($vnejsiAdresati as $key => $adresat) {
  
    $sql = 'DELETE FROM posta_nastaveni_vnejsi_adresati WHERE id = ' . $key;
    $db->query($sql);
  }
}

/**
 * INSERT vnejsich adresatu.
 * @param integer $skupinaId - Id skupiny.
 * @param array $vnejsiAdresati - Pole vnejsich adresatu.
 */
function insert($skupinaId, $vnejsiAdresati) {
	$db = new DB_POSTA;	
	foreach ($vnejsiAdresati as $key => $val) {
		$sql = 'INSERT INTO posta_nastaveni_vnejsi_adresati (skupina_id, adresat_id)
              VALUES (' . $skupinaId . ', ' . $key .');';
		$db->query($sql);
	}
}

function insertVnejsiAdresati($skupinaId, $vnejsiAdresati) {

  insert(intval($skupinaId), $vnejsiAdresati['NEW']);
}

function editvnejsiAdresati($skupinaId, $vnejsiAdresati) {
    
  $skupinaId = intval($skupinaId);
  
  deleteWithout($skupinaId, $vnejsiAdresati['OLD']);
  insert($skupinaId , $vnejsiAdresati['NEW']);
}

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
    if (strstr($key, 'ADRESAT-')) {
    
      $temp = explode('-', $key);
	  $id = intval($temp[1]);
          $vnejsiAdresati[$temp[2]][$id] = $value ? intval($value) : 'NULL'; // id adresata
      }
    }
  
  return $vnejsiAdresati;
}

/**
 * SELECT vnejsich adresatu.
 * @param integer $skupinaId - Id skupiny.
 * @return array $vnejsiAdresati - Pole vnejsich adresatu.
 */
function getVnejsiAdresaty($skupinaId) {
  
  $db = new DB_POSTA;  
  $sql = 'SELECT pn.*,po.ODESL_PRIJMENI,po.ID as ADRID FROM posta_nastaveni_vnejsi_adresati pn LEFT JOIN POSTA_ADRESATI po ON PN.ADRESAT_ID = PO.ID  WHERE skupina_id = ' . $skupinaId;
  $db->query($sql);
  $vnejsiAdresati = array();
  
  while ($db->next_record()) {
    $adresat = array();
    $adresat['name'] = $db->Record['ODESL_PRIJMENI'];
    $adresat['id'] = $db->Record['ADRID'];
    $vnejsiAdresati[$db->Record['ID']] = $adresat;
  }
  return $vnejsiAdresati;
}

