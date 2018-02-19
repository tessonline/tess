<?php
require_once ('EedUser.inc');

class EedArchivacniBox extends EedUser {
  
  var $box_id;
  var $nazev;
  var $umisteni;
  var $ev_cislo;
  var $skar_znak;
  var $skar_lhuta;
  var $spisovna_id;
  var $pocet;
  var $db;
  /**
  * Constructor
  * @author onma  
  */  
  function EedArchivacniBox($box_id = 0){
    parent::EedUser(0);
    $this->box_id = $box_id;
    $sql = "select * from posta_spisovna_boxy where id=" . $this->box_id . "";
    $this->_sql_query($sql);
    while ($this->db->Next_Record()) {
      $this->nazev = $this->db->Record['NAZEV'];
      $ev_cislo = $this->db->Record['EV_CISLO'];
      $odbor = $this->db->Record['ODBOR'] ? $this->db->Record['ODBOR'] : 0;
      $this->umisteni = $this->db->Record['UMISTENI'];
      $this->skar_znak = $this->db->Record['SKAR_ZNAK'];
      $this->skar_lhuta = $this->db->Record['SKAR_LHUTA'];
      $this->spisovna_id = $this->db->Record['SPISOVNA_ID'];
      $this->ck = $this->db->Record['CK'];
      $odbor = $this->db->Record['ODBOR'] ? $this->db->Record['ODBOR'] : 0;
      $rok = $this->db->Record['ROK'];
      $spis_uzel = $this->_VratSpisovyUzel($odbor);
      $this->ev_cislo = $spis_uzel['ZKRATKA'] . '/' . $ev_cislo . '/' . $rok;
    }
    $sql = 'select count(*) as pocet from posta_spisovna_boxy_ids where box_id=' . $this->box_id;
    $this->_sql_query($sql);
    while ($this->db->Next_Record()) {
      $this->pocet = $this->db->Record['POCET'];
    }

    if (!$ev_cislo && $this->box_id>0) {
      $sql = 'select max(ev_cislo) as max_ev from posta_spisovna_boxy where odbor=' . $odbor .'';
      $this->_sql_query($sql);
      $this->db->Next_Record();
      $max_ev = $this->db->Record['MAX_EV'];
      
      if (!$max_ev || $max_ev == 0) $max_ev = 1;
      else $max_ev = $max_ev + 1;
      $sql = "update posta_spisovna_boxy set ev_cislo=" . $max_ev . " where id=" . $this->box_id . "";
      $this->_sql_query($sql);
      $this->ev_cislo = $max_ev . '/' . $rok;
    }
    return true;
  }

  function PrepocitatArchivaci($box_id = 0) {
    $sql = "select * from posta_spisovna_boxy_ids where box_id=" . $this->box_id . "";
    $this->_sql_query($sql);
    $znak = '';
    $pole = '';
    $doba = '';
    $q = new DB_POSTA;
    while ($this->db->Next_Record()) {
      $sql = 'select * from posta where id=' . $this->db->Record['POSTA_ID'];
      $q->query($sql);
      $q->Next_Record();
      $poleID = EedTools::Skartace_Pole($q->Record['SKARTACE']);
      if (!$znak) {
        $znak = $poleID['znak'];
        $doba = $poleID['doba'];
      }
      if ($poleID['doba'] > $doba) {
          $skartace_id = $q->Record['SKARTACE'];
          $pole = $poleID;
          $doba = $poleID['doba'];
      }
      if ($znak == 'S' and ($poleID['znak']=='A' || $poleID['znak']=='V')) {
        $skartace_id = $q->Record['SKARTACE'];
        $znak = $poleID['znak'];
        $pole = $poleID;
      }
      if ($znak == 'V' and $poleID['znak']=='A') {
        $skartace_id = $q->Record['SKARTACE'];
        $znak = $poleID['znak'];
        $pole = $poleID;
      }
    }
    if (!$doba) $doba = -1;
    $sql = "update posta_spisovna_boxy set skar_znak='" .  $znak . "', skar_lhuta=" . $doba . " where id=" . $this->box_id . "";
    $this->_sql_query($sql);
    return true;
  }

  function GetBoxProPostaID($posta_id = 0) {
    $res = array();
    $sql = "select * from posta_spisovna_boxy_ids where posta_id=" . $posta_id . "";

    $box_db = new DB_POSTA;
    $box_db->query($sql);
    $q = new DB_POSTA;
    while ($box_db->Next_Record()) {
      $sql = 'select * from posta_spisovna_boxy where id=' . $box_db->Record['BOX_ID'];
      $q->query($sql);
      $q->Next_Record();
      $id = $q->Record['ID'];
      $res[$id]['ID'] = $q->Record['ID'];
      $res[$id][''] = $q->Record['ID'];

      $res[$id]['NAZEV'] = $q->Record['NAZEV'];
      $ev_cislo = $q->Record['EV_CISLO'];
      $odbor = $q->Record['ODBOR'] ? $q->Record['ODBOR'] : 0;
      $res[$id]['UMISTENI'] = $q->Record['UMISTENI'];
      $res[$id]['SKAR_ZNAK'] = $q->Record['SKAR_ZNAK'];
      $res[$id]['SKAR_LHUTA'] = $q->Record['SKAR_LHUTA'];
      $res[$id]['SPISOVNA_ID'] = $q->Record['SPISOVNA_ID'];
      $res[$id]['CK'] = $q->Record['CK'];
      $odbor = $q->Record['ODBOR'] ? $q->Record['ODBOR'] : 0;
      $rok = $q->Record['ROK'];
      $spis_uzel = $this->_VratSpisovyUzel($odbor);
      $res[$id]['EV_CISLO'] = $spis_uzel['ZKRATKA'] . '/' . $ev_cislo . '/' . $rok;

    }
    if (!$doba) $doba = -1;
    return $res;
  }


}

