<?php
require_once ('EedUser.inc');

class EedVnitrniPosta extends EedUser{

  var $adresati = array();

  /**
  * Constructor
  * @author onma
  * @description inicializuje objekt EedVNitrniPosta (potomek z DB atd.), konsturktor vrati primo seznam adresatu vnitrni posty     
  * @param id - identifikátor dokumentu  
  */
  function EedVnitrniPosta($doc_id = 0){
    parent::EedUser();
    $sql = 'select * from posta_vnitrni_adresati where posta_id=' . $doc_id;
    $this->_sql_query($sql);
//    $this->db->query($sql);
    while ($this->db->Next_Record()) {
      $this->adresati[$this->db->Record['ID']] = array(
        'UNIT_ID' => $this->db->Record['ORGANIZACNI_VYBOR'],
        'ZPRACOVATEL_ID' => $this->db->Record['ZPRACOVATEL'],
      );
    } 
  }
  
  function VratSeznamVnitrnichAdresatu($adresati = array()) {
    $adresat_cele = array();
    foreach($adresati as $key => $adresat) {
      $zarizeni_id = $this->NajdiZarizeniId($adresat['UNIT_ID']);
      $uzel = $this->VratSpisUzelZOdboru($adresat['UNIT_ID']);
      $uzel_id = $uzel['ID'];
      $adresat_cele[$key] = array(          
        'UNIT_ID' => $adresat['UNIT_ID'],
        'UNIT_NAME' => $this->GetUnitName($adresat['UNIT_ID']),
        'ZARIZENI_ID' => $zarizeni_id,
        'ZARIZENI_NAME' => $this->GetUnitName($zarizeni_id),
        'ZPRACOVATEL_ID' => $adresat['ZPRACOVATEL_ID'],
        'ZPRACOVATEL_NAME' => $this->GetUserName($adresat['ZPRACOVATEL_ID']),
        'UZEL_ID' => $uzel_id,
      );
    }
    return $adresat_cele;
  }

}
