<?php
include_once('EedUser.inc');
include_once('EedDokument.inc');

class EedSql extends Eed_db_object {

  var $status = 7;
  var $vec = 'přidělení čj.';

  /**
  * Constructor
  * @author onma
  * @description SQL prikazy pro EED    
  */
  function EedSql(){
    parent::Eed_db_object();
    $this->user = new EedUser();
  }

  function WhereOdborPodrizene($odbor_id = 0) {
    if (!$odbor_id || $odbor_id == 0) $odbor_id = $this->user->GetUnit();  
    $odbory = $this->user->VratNadrizeneUnity($unit_id);
  }

  function WhereOdborAndPrac($uzel_id = 0, $unit_id = 0) {
    $odbory = array();
    if ($uzel_id > 0) $ret = $this->user->VratUzlyAOdborPrac($uzel_id);
    if ($unit_id > 0) $ret = $this->user->VratUzlyAOdborPracZUnity($unit_id);
    $zpracovatele = array();
    if (!is_array($ret)) return false;
    foreach($ret['odborprac'] as $odbor => $prac) {
      $zpracovatele = array_merge($zpracovatele, $prac);
    }
    $where = " 1=0 ";
    if (count($ret['uzel']) > 0) $where .= " OR ODBOR in (" . implode(', ', $ret['uzel']) . ")";
    if (count($zpracovatele) > 0) $where .= " OR REFERENT in (" . implode(', ', $zpracovatele) . ")";
    return $where;
  }

  //vytor novy dokument s novym cj. Nove cj prideli sam trigger, pokud neni vyplnen soupec CISLO_JEDNACI1
  function createDocBezCJ($referent = 0, $text_cj) {
//echo "zalozime novy doc <br/>";
    $usr = new EedUser($referent);
    if (!$usr->zarizeni_id) $usr->zarizeni_id = 0;
    if (!$usr->odbor_id) $usr->odbor_id = 0;
    if (!$usr->id_user) $usr->id_user = 0;
    $sql = "insert into posta (EV_CISLO,CISLO_SPISU1,CISLO_JEDNACI1,CISLO_SPISU2,CISLO_JEDNACI2,ROK,VEC,ODES_TYP,SUPERODBOR,ODBOR,REFERENT,STATUS,DATUM_PREDANI,POCET_LISTU,TEXT_CJ)
    VALUES (0,0,-1,0,0," . Date('Y') . ",'" . $this->vec . "','Z',
           " . $usr->zarizeni_id. "," . $usr->odbor_id. "," . $usr->id_user. ", " . $this->status. ", '" . Date('d.m.Y H:i:s') . "', 0,'" . $text_cj . "')";
    $this->db->query($sql);
    return $this->db->GetLastId('posta', 'id');

  }

  //vytor novy dokument s novym cj. Nove cj prideli sam trigger, pokud neni vyplnen soupec CISLO_JEDNACI1
  function createCJ($referent = 0) {
//echo "zalozime novy doc <br/>";
    $usr = new EedUser($referent);
    if (!$usr->zarizeni_id) $usr->zarizeni_id = 0;
    if (!$usr->odbor_id) $usr->odbor_id = 0;
    if (!$usr->id_user) $usr->id_user = 0;
    $sql = "insert into posta (EV_CISLO,ROK,VEC,ODES_TYP,SUPERODBOR,ODBOR,REFERENT,STATUS,DATUM_PREDANI,POCET_LISTU,LAST_DATE,LAST_USER_ID,OWNER_ID) VALUES (0," . Date('Y') . ",'" . $this->vec . "','Z',
           " . $usr->zarizeni_id. "," . $usr->odbor_id. "," . $usr->id_user. ", " . $this->status. ", '" . Date('d.m.Y H:i:s') . "', 0,'" . Date('Y-m-d') . "',".$usr->id_user.",".$usr->id_user.")";
    $this->db->query($sql);
    return $this->db->GetLastId('posta', 'id');

  }

  //vytor novy dokument s novym cj. Nove cj prideli sam trigger, pokud neni vyplnen soupec CISLO_JEDNACI1
  //zaroven ulozime Externi ID (z jine agendy)
  function createCJwithExternalID($referent = 0, $external_id) {
    $id = $this->createDocBezCJ($referent);
    $sql = "update posta set odeslana_posta='t', dalsi_id_agenda='" . $external_id . "' where id=" . $id;
    $this->db->query($sql);
    return $id;

  }

  //vytvori dokument s existujicim cj a pripadne spisem
  function createDocWithCJ($doc_id) {
    if (!$doc_id) $doc_id = 0;
//echo "zalozime novy doc s cj $doc_id<br/>";
    $doc = new EedDokument($doc_id);
    $usr = new EedUser($doc->referent_id);
    if (!$doc->zarizeni) $doc->zarizeni = 0;
    if (!$usr->odbor_id) $usr->odbor_id = 0;
    if (!$usr->id_user) $usr->id_user = 0;

    if (!$doc->cj1) $doc->cj1 = 0;
    if (!$doc->cj2) $doc->cj2 = 0;
    $sql = "insert into posta (EV_CISLO,ROK,VEC,ODES_TYP,SUPERODBOR,ODBOR,REFERENT,STATUS,CISLO_JEDNACI1,CISLO_JEDNACI2,CISLO_SPISU1,CISLO_SPISU2,ID_PUVODNI,DATUM_PREDANI,POCET_LISTU,LAST_DATE,LAST_USER_ID,OWNER_ID) VALUES (0," . Date('Y') . ",'" . $this->vec . "','Z',
          " . $doc->zarizeni. "," . $usr->odbor_id. "," . $usr->id_user. ", " . $this->status. "," . $doc->cj1 . "," . $doc->cj2 . "," . $doc->cj1 . "," . $doc->cj2 . ", " . $doc_id . ", '" . Date('d.m.Y H:i:s') . "', 0,'" . Date('Y-m-d') . "',".$usr->id_user.",".$usr->id_user.")";
    $this->db->query($sql);
    $id = $this->db->GetLastId('posta','id');
    EedTools::PriradPodcislo($id);
    return $id;
            
  }



}
