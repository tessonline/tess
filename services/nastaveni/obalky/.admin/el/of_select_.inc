<?php
if (!IsFileIncluded(__FILE__."user")):

include_once($GLOBALS["TMAPY_LIB"]."/of_select_db.inc");
require_once(FileUp2(".admin/security_obj.inc"));


class of_select_superodbor extends of_select_db {
  // Constructor
  function of_select_superodbor($a) {
    $this->setup_element($a);
    $this->DB_Sql = new DB_POSTA;
    $USER_INFO = $GLOBALS["POSTA_SECURITY"]->GetUserInfo();
    $this->DB_Sql->query("SELECT DISTINCT g.id,g.name, g.poradi FROM cis_posta_odbory o LEFT JOIN security_group g ON g.id=o.id_odbor WHERE g.parent_group_id=0 or g.parent_group_id is null ORDER BY g.poradi, g.id");
    $this->init_db();
  }
}

class of_select_velikost extends of_select {
  // Constructor
  function of_select_velikost($a) {
    $this->setup_element($a);
    $this->options = array();
    if ($a["insertnull"]) $this->options[] = array("value"=>"", "label"=>" ");
    $this->options[] = array("value"=>"A3", "label"=>"A3");
    $this->options[] = array("value"=>"A4", "label"=>"A4");
    $this->options[] = array("value"=>"A5", "label"=>"A5");
    $this->options[] = array("value"=>"Letter", "label"=>"Letter");
    $this->options[] = array("value"=>"Legal", "label"=>"Legal");
  }
}

class of_select_otoceni extends of_select {
  // Constructor
  function of_select_otoceni($a) {
    $this->setup_element($a);
    $this->options = array();
    if ($a["insertnull"]) $this->options[] = array("value"=>"", "label"=>" ");
    $this->options[] = array("value"=>"P", "label"=>"svisle");
    $this->options[] = array("value"=>"L", "label"=>"vodorovně");
  }
}

class of_select_ano_ne extends of_select {
  // Constructor
  function of_select_ano_ne($a) {
    $this->setup_element($a);
    $this->options = array();
    if ($a["insertnull"]) $this->options[] = array("value"=>"", "label"=>" ");

   $this->options[] = array("value"=>"1", "label"=>"Ano");
   $this->options[] = array("value"=>"2", "label"=>"Ne");
  }
}

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
    $this->options[] = array("value"=>"20", "label"=>"Zkratka odboru a zpracovatele");
    $this->options[] = array("value"=>"10", "label"=>"Číslo spisu");
    $this->options[] = array("value"=>"13", "label"=>"Název spisu");
    $this->options[] = array("value"=>"11", "label"=>"Podací číslo");
    $this->options[] = array("value"=>"12", "label"=>"Poznámka");
    $this->options[] = array("value"=>"15", "label"=>"Dnešní datum");
    $this->options[] = array("value"=>"21", "label"=>"Vložená čj");
    $this->options[] = array("value"=>"1000", "label"=>"Čarový kód 3z9 - vodorovně");
    $this->options[] = array("value"=>"1001", "label"=>"Čarový kód 3z9 - svisle");
    $this->options[] = array("value"=>"1100", "label"=>"Čarový kód 128 - vodorovně");
    $this->options[] = array("value"=>"1101", "label"=>"Čarový kód 128 - svisle");
    $this->options[] = array("value"=>"2000", "label"=>"R kód České pošty");
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
