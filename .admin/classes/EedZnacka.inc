<?php
require_once ('EedDokument.inc');

//class EedZnacka extends EedDokument{
class EedZnacka extends EedDokument{

  /**
  * Constructor
  * @author tohu
  * @param string $wsdl - URL wsdl  
  * @param string $auth_token - auth token ze sluzby ContextRegistryService->register
  */
  function EedZnacka($id){
    parent::EedDokument($id);
    $this->db_znacka = new DB_UKLADACIZNACKA;
  }

  function GetNameForZnackaId($znacka_id = 0) {
    //nacita se z cizi DB 
    $ret = array();
    if (!$znacka_id) return false;
    $sql = "select * from SpisUklZnac where idznacka=" . $znacka_id;
    $this->db_znacka->query($sql);
    $this->db_znacka->Next_Record();
    $ret = $this->db_znacka->Record['TXTZNACKA'];
    return $ret;
/*    $ret = array();
    $sql = "select * from npu_spisuklznac where idznacka=" . $znacka_id;
    $this->_sql_query($sql);
    $this->db->Next_Record();
    $ret = $this->db->Record[TXTZNACKA];
    return $ret;
*/
  }

  function GetZnackaIdProCJ($spis_id = 0) {
    $ret = array();
    $sql = "select * from posta_uklznacka where spis_id=" . $spis_id;
    $this->_sql_query($sql);
    while ($this->db->Next_Record())
      $ret[] = $this->db->Record['ZNACKA_ID'];
    return $ret;
  }

  function GetZnackaNameProCJ($spis_id = 0) {
    $ret = array();
    $sql = "select * from posta_uklznacka where spis_id=" . $spis_id;
    $this->_sql_query($sql);
    while ($this->db->Next_Record())
      $ret[] = $this->GetNameForZnackaId($this->db->Record['ZNACKA_ID']);
    return $ret;
  }

  function _GetZnackaIdProNazev($znacka_text = '') {
    //nacita se z cizi DB 
    $ret = array();
    $sql = "select idznacka from SpisUklZnac where txthled like '%" . $znacka_text . "%'";
    $this->db_znacka->query($sql);
    while ($this->db_znacka->Next_Record())
      $ret[] = $this->db_znacka->Record['IDZNACKA'];
    return $ret;
  }

  function _GetSpisIDProIDZnacka($znacka_id = 0) {
    $ret = array();
    $sql = "select spis_id from posta_uklznacka where znacka_id=" . $znacka_id;
    $this->_sql_query($sql);
    while ($this->db->Next_Record()) {
      if ($this->db->Record[SPIS_ID]>0)
        $ret[] = $this->db->Record[SPIS_ID];
    }
    return $ret;
  }

  function VyhledejSpisIDPodleUkladaciZnacky($znacka_text = '') {
    $ret = array();
    $id_znacek = array();
    $id_znacek = $this->_GetZnackaIdProNazev($znacka_text);
    if (count($id_znacek)>0)
      while (list($key,$val) = each($id_znacek))  {
        $spis_id = $this->_GetSpisIDProIDZnacka($val);
        if ($spis_id>0) $ret[] = $spis_id;
      }
      else
        $ret = false;
    return $ret;
  }
}
