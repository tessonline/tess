<?php
include_once($GLOBALS["TMAPY_LIB"]."/of_select_db.inc");
include_once($GLOBALS["TMAPY_LIB"]."/of_select_db_add.inc");
include_once($GLOBALS["TMAPY_LIB"]."/of_select_db_other.inc");

class of_select_typ_pam_katalog extends of_select {
  // Constructor
  function of_select_typ_pam_katalog($a) {
    $this->setup_element($a);
    $this->options = array();
    if ($a["insertnull"]) $this->options[] = array("value"=>"", "label"=>"");
    while (list($key, $val) = each($GLOBALS['PK_CIS'])) {
      $this->options[] = array("value"=>$key, "label"=>$val['text']);

    }
    if ($a['only_prirazeni']) {
      $this->options = array();
      $this->options[] = array("value"=>"", "label"=>"");
      $this->options[] = array("value"=>0, "label"=>$GLOBALS['PK_CIS'][0]['text']);
    }
  }
}


