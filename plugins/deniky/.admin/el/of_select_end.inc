<?php

class of_select_deniky extends of_select_db {
  // Constructor
  function of_select_deniky($a) {
    $this->setup_element($a);
    $this->options = array();
    if ($a["insertnull"]) $this->options[] = array('value' => "", 'label' => " ");

    if ($a['short']) 
      $this->options[] = array('value' => "1", 'label' => "ČJ");
    else
      $this->options[] = array('value' => "1", 'label' => "Hlavní evidence");

    if ($a['selectfull']) $sql = 'select * from posta_cis_deniky order by id asc';
    else $sql = 'select * from posta_cis_deniky where aktivni=1 order by id asc';

    if ($a['short']) $column = 'ZKRATKA'; else $column = 'NAZEV';
    $q = new DB_POSTA;
    $q->query($sql);
    while ($q->Next_Record()) {
      $this->options[] = array('value' => $q->Record['ID'], 'label' => $q->Record[$column]);
    }
  }
}


