<?php

class of_select_filtry extends of_select_db {
  // Constructor
  function of_select_filtry($a) {
    $this->setup_element($a);
    $this->options = array();
    if ($a["insertnull"]) $this->options[] = array('value' => "", 'label' => " ");

    $USER_INFO = $GLOBALS["POSTA_SECURITY"]->GetUserInfo();
    $sql = 'select * from posta_user_filtry where owner_id=' . $USER_INFO['ID'];

    $q = new DB_POSTA;
    $q->query($sql);
    while ($q->Next_Record()) {
      $this->options[] = array('value' => $q->Record['ID'], 'label' => $q->Record[NAZEV]);
    }
  }
}


