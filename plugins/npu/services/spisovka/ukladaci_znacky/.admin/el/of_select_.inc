<?php
if (!IsFileIncluded(__FILE__."user")):


include_once($GLOBALS["TMAPY_LIB"]."/of_select_db.inc");
include_once($GLOBALS["TMAPY_LIB"]."/of_select_db_add.inc");
include_once($GLOBALS["TMAPY_LIB"]."/of_select_db_other.inc");

class of_select_typ_ukladaciznacka extends of_select {
  // Constructor
  function of_select_typ_ukladaciznacka($a) {
    $this->setup_element($a);
    $this->options = array();
    if ($a["insertnull"]) $this->options[] = array("value"=>"", "label"=>"bez rozlišení");
//    $this->options[] = array("value"=>"X", "label"=>"Město ".$GLOBALS["CONFIG"]["MESTO"]);
	 	 
    $this->options[] = array("value"=>"L", "label"=>"lokační: misto, ves");
    $this->options[] = array("value"=>"M", "label"=>"lokační: Praha, Plzeň, Brno, Ostrava");
    $this->options[] = array("value"=>"P", "label"=>"jednotlivá památka 	památka");
    $this->options[] = array("value"=>"S", "label"=>"jiná jednotlivá stavba");
    $this->options[] = array("value"=>"V", "label"=>"ostatní");

//    					  "options_sep"=>"&nbsp;",    
  }
}

class of_select_text_ukladaciznacka extends of_select_db {
  // Constructor
  function of_select_text_ukladaciznacka($a) {
    $this->setup_element($a);
    $this->options = array();
    $this->setup_element($a);
    $this->DB_Sql = new DB_POSTA;
    $this->DB_Sql->query("SELECT idznacka, txthled FROM npu_spisuklznac ORDER BY txthled");
    $this->init_db();

//    					  "options_sep"=>"&nbsp;",    
  }
}




endif;
