<?php
require_once ('db.inc');

/**
*@author luma
*/
class EedSpisUzelKontakt extends EED_db_object {
  var $adresa;
  var $telefon;
  var $mobil;
  var $email;
  var $web;
  
  /**
  * Constructor
  * @author luma
  * @param id - identifikátor adresy (id spisového uzlu)  
  */
  function EedSpisUzelKontakt($id=0){
    parent::Eed_db_object();
    
    $q= new DB_POSTA; 
    
    $sql = 'select id_odbor from cis_posta_odbory where  id = '.$id;
    //$sql = 'SELECT adresa,telefon,mobilni_tel,email FROM security_groups_kontakty k LEFT JOIN cis_posta_odbory o on o.id_odbor = k.id_security_group WHERE o.id =' . $id;
    $q->query($sql);
    $q->Next_Record();
    
    if ($q->Record['ID_ODBOR']) {
      $not_found = true;
      $first_run = true;
      $id = $q->Record['ID_ODBOR'];
      while($not_found) {
        if (!$first_run) {
          $sql = 'select parent_group_id from security_group where id='.$id;
          $q->query($sql);
          $q->Next_Record();
          if ($q->Record['PARENT_GROUP_ID'])
            $id = $q->Record['PARENT_GROUP_ID'];
            else
              $not_found = false;
        } 
        $sql = 'SELECT adresa,telefon,mobilni_tel,email,web FROM security_groups_kontakty k where id_security_group ='.$id;
        $q->query($sql);
        $q->Next_Record();
        if ($q->Record) {
          $this->adresa       = $q->Record['ADRESA'];
          $this->telefon      = $q->Record['TELEFON'];
          $this->mobil        = $q->Record['MOBILNI_TEL'];
          $this->email        = $q->Record['EMAIL'];
          $this->web          = $q->Record['WEB'];
          $not_found = false;
        }
        $first_run = false;
      }
          
    }

  }
}
