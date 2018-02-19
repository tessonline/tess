<?php
require_once ('db.inc');

/**
* trida EED_doc, pro praci s uzivateli
*@author onma  
*/
class EedAdresa extends EED_db_object {
  var $typ;
  var $kodAdresy;
  var $titul;
  var $oddeleni;
  var $prijmeni;
  var $jmeno;
  var $osoba;
  var $rc; // rodne cislo
  var $ulice;
  var $cp; // cislo popisne
  var $cor; // cislo orientacni
  var $psc;
  var $ico;
  var $posta;
  var $email;
  var $datovaSchranka;
  var $datumNarozeni;
  
  /**
  * Constructor
  * @author onma
  * @description inicializuje objekt Eed_doc (potomek z DB atd.)    
  * @param id - identifikátor adresy  
  */
  function EedAdresa($id=0){
    parent::Eed_db_object();
    $sql = 'SELECT * FROM posta_adresati WHERE id=' . $id; 
    //echo $sql;
    $this->_sql_query($sql);
    while ($this->db->Next_Record()) {
      $this->typ            = $this->db->Record['ODES_TYP'];
      $this->kodAdresy      = $this->db->Record['ODESL_ADRKOD'];
      $this->titul          = $this->db->Record['ODESL_TITUL'];     
      $this->oddeleni       = $this->db->Record['ODESL_ODD'];
      $this->prijmeni       = $this->db->Record['ODESL_PRIJMENI'];
      $this->jmeno          = $this->db->Record['ODESL_JMENO'];
      $this->osoba          = $this->db->Record['ODESL_OSOBA'];
      $this->rc             = $this->db->Record['ODESL_RC'];
      $this->ulice          = $this->db->Record['ODESL_ULICE'];
      $this->cp             = $this->db->Record['ODESL_CP'];
      $this->cor            = $this->db->Record['ODESL_COR'];
      $this->psc            = $this->db->Record['ODESL_PSC'];
      $this->ico            = $this->db->Record['ODESL_ICO'];
      $this->posta          = $this->db->Record['ODESL_POSTA'];
      $this->email          = $this->db->Record['ODESL_EMAIL'];
      $this->datovaSchranka = $this->db->Record['ODESL_DATSCHRANKA'];
      $this->datumNarozeni  = $this->db->Record['ODESL_DATNAR'];
    }
  }


}
