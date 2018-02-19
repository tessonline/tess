<?php
if (!IsFileIncluded(__FILE__."user")):

include_once($GLOBALS["TMAPY_LIB"]."/of_select_db.inc");
require_once(FileUp2(".admin/security_obj.inc"));




class of_select_objekt extends of_select {
  // Constructor
  function of_select_objekt($a) {
    $this->setup_element($a);
    $this->options = array();
    if ($a["insertnull"]) $this->options[] = array("value"=>"", "label"=>" ");
    $this->options[] = array("value"=>"1", "label"=>"Odesílatel");
    $this->options[] = array("value"=>"2", "label"=>"Adresát");
    $this->options[] = array("value"=>"22", "label"=>"Adresát (bez narození)");
    $this->options[] = array("value"=>"23", "label"=>"Adresát (bez IČ)");
    $this->options[] = array("value"=>"24", "label"=>"Adresát (jenom IČ)");
    $this->options[] = array("value"=>"3", "label"=>"text Do vlastních rukou");
    $this->options[] = array("value"=>"4", "label"=>"text Jen adresátovi");
    $this->options[] = array("value"=>"16", "label"=>"text nevracet,vložit do schránky");
    $this->options[] = array("value"=>"17", "label"=>"text jen 10 dní");
    $this->options[] = array("value"=>"18", "label"=>"označení nevracet,vložit do schránky");
    $this->options[] = array("value"=>"19", "label"=>"označení jen 10 dní");
    $this->options[] = array("value"=>"5", "label"=>"číslo jednací");
    $this->options[] = array("value"=>"14", "label"=>"Značka ČJ");
    $this->options[] = array("value"=>"6", "label"=>"Zkratka zpracovatele");
    $this->options[] = array("value"=>"7", "label"=>"Jméno zpracovatele");
    $this->options[] = array("value"=>"8", "label"=>"Zkratka odboru");
    $this->options[] = array("value"=>"9", "label"=>"Název odboru");
    $this->options[] = array("value"=>"10", "label"=>"Číslo spisu");
    $this->options[] = array("value"=>"13", "label"=>"Název spisu");
    $this->options[] = array("value"=>"11", "label"=>"Podací číslo");
    $this->options[] = array("value"=>"12", "label"=>"Poznámka");
    $this->options[] = array("value"=>"15", "label"=>"Dnešní datum");
    $this->options[] = array("value"=>"1000", "label"=>"Čarový kód 3z9 - vodorovně");
    $this->options[] = array("value"=>"1001", "label"=>"Čarový kód 3z9 - svisle");
    $this->options[] = array("value"=>"1100", "label"=>"Čarový kód 128 - vodorovně");
    $this->options[] = array("value"=>"3000", "label"=>"vlastní text");
  }
}

class of_select_tucne extends of_select {
  // Constructor
  function of_select_tucne($a) {
    $this->setup_element($a);
    $this->options = array();
    if ($a["insertnull"]) $this->options[] = array("value"=>"", "label"=>" ");
    $this->options[] = array("value"=>"B", "label"=>"normální");
//    $this->options[] = array("value"=>"B", "label"=>"tučně");
//    $this->options[] = array("value"=>"I", "label"=>"italic");
//    $this->options[] = array("value"=>"BI", "label"=>"tučně a italic");
  }
}


endif;
?>
