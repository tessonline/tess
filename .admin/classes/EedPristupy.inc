<?php

require_once ('db.inc');

class EedPristupy extends EED_db_object {

  var $verze;
  var $datum;
  var $historie = array();

  /**
  * Constructor
  * @author onma
  *
  * return cislo verze
  */
  function EedPristupy(){
    parent::Eed_db_object();
    return true;
  }

  /**
  * MamPristupKeSpisu
  * @author onma
  * zapise verzi z Gitu
  *
  * return cislo verze
  */
  function MamPristupKeSpisu($id) {
    $sql = "select id from posta_pristupy where posta_id in (" . $id . ") and spis=1";
    $this->_sql_query($sql);
    if ($this->db->Num_Rows() == 0)
      return false;
    else
      return true;
  }

}