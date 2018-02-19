<?php
if (!IsFileIncluded(__FILE__."user")):

include_once($GLOBALS["TMAPY_LIB"]."/of_select_db.inc");
require_once(FileUp2(".admin/security_obj.inc"));



class of_select_odbor extends of_select_db {
  // Constructor
  function of_select_odbor($a) {
    $this->setup_element($a);
    $this->DB_Sql = new DB_POSTA;
    $this->DB_Sql->query("SELECT DISTINCT id,name FROM security_group WHERE (type_group=1) AND id not in (SELECT id_odbor from cis_posta_odbory) ORDER BY name");
//    $this->DB_Sql->query("SELECT DISTINCT id,name FROM security_group WHERE (type=1)  ORDER BY name");
    $this->init_db();
  }
}



endif;
?>
