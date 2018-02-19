<?php
if (!IsFileIncluded(__FILE__."user")):

include_once($GLOBALS["TMAPY_LIB"]."/of_select_db.inc");

class of_select_log_sw extends of_select_db {
  function of_select_log_sw($a) {
    $this->setup_element($a);
    $this->DB_Sql = new DB_POSTA;
    $this->DB_Sql->query("SELECT DISTINCT sw,sw FROM posta_interface_log ORDER BY sw");
    $this->init_db();

  }
}

endif;
?>
