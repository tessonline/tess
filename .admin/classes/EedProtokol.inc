<?php
require_once ('db.inc');

class EedProtokol extends EED_db_object {
  
  var $protokol_id;
  var $doc_ids = array();

  /**
  * Constructor
  * @author onma  
  */  
  function EedProtokol($protokol_id = 0){
    parent::Eed_db_object();
    $this->protokol_id = $protokol_id;
  }
 

  function ZalozNovyProtokol($typ='') {
    $sql = "insert into posta_protokoly (type,last_date,last_time,last_user_id,owner_id) VALUES ('%s','%s','%s',%s,%s)";
    if (!$USER_INFO) {
      $USER_INFO =  $GLOBALS["POSTA_SECURITY"]->GetUserInfo();
    }
    $sql = sprintf($sql,
                   $typ,
                   Date('Y-m-d'),
                   Date('H:i:s'),
                   $USER_INFO['ID'],
                   $USER_INFO['ID']
                 );
    $this->_sql_query($sql);
    $protokol_id = $this->db->getLastId('posta_protokoly', 'id');
    $this->protokol_id = $protokol_id;
    $cislo = $typ . str_pad($protokol_id, 6 , "0", STR_PAD_LEFT);
   
    $sql = "update posta_protokoly set cislo='" . $cislo . "' where id=" . $protokol_id;
    $this->_sql_query($sql);
    return $cislo;
  }

  function VlozIDSDoProtokolu($cislo, $doc_ids=array()) {
    if (count($doc_ids)>0) {
      $sql = "insert into posta_protokoly_ids (cislo, dokument_id, last_date,last_time,last_user_id,owner_id) VALUES ('%s',%s,'%s','%s',%s,%s)";
      if (!$USER_INFO) {
        $USER_INFO =  $GLOBALS["POSTA_SECURITY"]->GetUserInfo();
      }
      foreach ($doc_ids as $id) {
        $sql = sprintf($sql,
                       $cislo,
                       $id,
                       Date('Y-m-d'),
                       Date('H:i:s'),
                       $USER_INFO['ID'],
                       $USER_INFO['ID']
                     );
        $this->_sql_query($sql);
        
      }
    }
    else {
      return false;
    }
  }

  function VratIDSZProtokolu() {
    $ret = array();
    $sql = "select * from posta_protokoly_ids where cislo like '" . $this->protokol_id . "'";
    $this->_sql_query($sql);
    while ($this->db->Next_Record())
      $ret[] = $this->db->Record['DOKUMENT_ID'];
    return $ret;
  }

}

