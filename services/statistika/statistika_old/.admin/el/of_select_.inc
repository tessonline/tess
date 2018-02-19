<?php
include_once($GLOBALS["TMAPY_LIB"]."/of_select_db.inc");
//include_once($GLOBALS["TMAPY_LIB"]."/of_select_db_add.inc");
//include_once($GLOBALS["TMAPY_LIB"]."/of_select_group.inc");

class of_select_mesic extends of_select {
  function of_select_mesic($a) {
    $this->setup_element($a);
    if ($a["insertnull"]) $this->options[] = array("value"=>"", "label"=>"");
		$this->options[] = array("value"=>"1", "label"=>"leden");
		$this->options[] = array("value"=>"2", "label"=>"únor");
		$this->options[] = array("value"=>"3", "label"=>"březen");
		$this->options[] = array("value"=>"4", "label"=>"duben");
		$this->options[] = array("value"=>"5", "label"=>"květen");
		$this->options[] = array("value"=>"6", "label"=>"červen");
		$this->options[] = array("value"=>"7", "label"=>"červenec");
		$this->options[] = array("value"=>"8", "label"=>"srpen");
		$this->options[] = array("value"=>"9", "label"=>"září");
		$this->options[] = array("value"=>"10", "label"=>"říjen");
		$this->options[] = array("value"=>"11", "label"=>"listopad");
		$this->options[] = array("value"=>"12", "label"=>"prosinec");
  }
}

class of_select_rok extends of_select_db {
  function of_select_rok($a) {
    $where = $GLOBALS["PROPERTIES_ACCESS"]['condition_read_a'][1];
    $this->setup_element($a);
    $this->DB_Sql = new DB_POSTA;
    $this->DB_Sql->query("SELECT DISTINCT rok,rok FROM posta ORDER BY rok");
    $this->init_db();

  }
}


?>
