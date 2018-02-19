<?php
if (!IsFileIncluded(__FILE__."user")):

include_once($GLOBALS["TMAPY_LIB"]."/of_select_db.inc");
require_once(FileUp2(".admin/security_obj.inc"));

class of_select_rok extends of_select_db {
  function of_select_rok($a) {
    $where = $GLOBALS["PROPERTIES_ACCESS"]['condition_read_a'][1];
    $this->setup_element($a);
    $this->DB_Sql = new DB_POSTA;
    $this->DB_Sql->query("SELECT DISTINCT rok,rok FROM posta ORDER BY rok");
    $this->init_db();

  }
}

class of_select_mesic extends of_select {
  // Constructor
  function of_select_mesic($a) {
    $this->setup_element($a);
    $this->options = array();
    if ($a["insertnull"]) $this->options[] = array("value"=>"", "label"=>" ");
    $this->options[] = array("value"=>"1", "label"=>"Leden");
    $this->options[] = array("value"=>"2", "label"=>"Únor");
    $this->options[] = array("value"=>"3", "label"=>"Březen");
    $this->options[] = array("value"=>"4", "label"=>"Duben");
    $this->options[] = array("value"=>"5", "label"=>"Květen");
    $this->options[] = array("value"=>"6", "label"=>"Červen");
    $this->options[] = array("value"=>"7", "label"=>"Červenec");
    $this->options[] = array("value"=>"8", "label"=>"Srpen");
    $this->options[] = array("value"=>"9", "label"=>"Září");
    $this->options[] = array("value"=>"10", "label"=>"Říjen");
    $this->options[] = array("value"=>"11", "label"=>"Listopad");
    $this->options[] = array("value"=>"12", "label"=>"Prosinec");
//    					  "options_sep"=>"&nbsp;",    
  }
}


class of_select_odbor extends of_select_db {
  // Constructor
  function of_select_odbor($a) {
    $this->setup_element($a);
    $this->DB_Sql = new DB_POSTA;
//    $this->DB_Sql->query("SELECT DISTINCT id,name FROM security_group WHERE (type_group=1) and (name<>'T-MAPY') ORDER BY name");
    $this->DB_Sql->query("SELECT DISTINCT o.id,g.name FROM cis_posta_odbory o LEFT JOIN security_group g ON g.id=o.id_odbor ORDER BY g.name");
    $this->init_db();
  }
}


endif;
?>
