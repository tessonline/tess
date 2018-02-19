<?php
require_once ('EedDokument.inc');

class EedSchvalovani extends EedDokument{

  /**
  * Constructor
  * @author onma
  */
  function EedSchvalovani($doc_id=0) {
    parent::EedDokument($doc_id);
  }

  function JeVeSchvaleni($doc_id,$prac=0) {
    $sql='select doc_id from posta_schvalovani where doc_id='.$doc_id.'';
    return $this->JeZaznamVDB($sql);
  } 

  function JeVeSchProcesu($doc_id) {
    $sql='select doc_id from posta_schvalovani where doc_id='.$doc_id.'';
    return $this->JeZaznamVDB($sql);
  } 
  
  function MamNeschvalene($doc_id,$prac_id=0) {
    if ($prac_id>0) $add=' and schvalujici_id='.$prac_id;
    $sql='select doc_id from posta_schvalovani where doc_id='.$doc_id.' '.$add.' and schvaleno=0';
    return $this->JeZaznamVDB($sql);
  }


  function VraSeznamKdoMaSchvalit($prac_id=0) {
    $unit_id = $this->GetUnit($prac_id);
    $pole_prac_id = array();
    $nadrizene_unity = $this->VratNadrizeneUnity($unit_id);
    while (list($key,$val)=each($nadrizene_unity)) {
      $prac_id = $this->NajdiVedoucihoVUnite($key);
      if ($prac_id>0)
        $pole_prac_id[] = $prac_id;
    }
    $this->ShowDebug($pole_prac_id);
    return $pole_prac_id;
  }


  function getPostupSchvalovani($doc_id) {
    $sql='select postup from posta_schvalovani where posta_id='.$doc_id.' ';
    $this->_sql_query($sql);
    $this->db->Next_Record();
    $data = $this->db->Record;
    return $data['POSTUP'];
  }

}


