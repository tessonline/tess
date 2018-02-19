<?php
include_once($GLOBALS['TMAPY_LIB'].'/of_select_db.inc');
class of_select_odes_typ extends of_select {

  function of_select_odes_typ($a) {
    $this->setup_element($a);
    if($a['insertnull']) $this->options[] = array('value'=>'', 'label'=>'');
		$this->options[] = array('value' => 'P', 'label' => 'Právnická osoba');
		$this->options[] = array('value' => 'U', 'label' => 'Orgán veřejné moci');
		$this->options[] = array('value' => 'F', 'label' => 'Podnikající fyzická osoba');
		$this->options[] = array('value' => 'O', 'label' => 'Fyzická osoba');
		$this->options[] = array('value' => 'N', 'label' => 'Notář');
		$this->options[] = array('value' => 'B', 'label' => 'Advokát');
		$this->options[] = array('value' => 'E', 'label' => 'Exekutor');
		$this->options[] = array('value' => 'T', 'label' => 'Patentový zástupce');
		$this->options[] = array('value' => 'D', 'label' => 'Daňový poradce');
		$this->options[] = array('value' => 'A', 'label' => 'Anonym');
		$this->options[] = array('value' => 'V', 'label' => 'Veřejnost');
		$this->options[] = array('value' => 'Z', 'label' => 'Vlastní záznam');
		$this->options[] = array('value' => 'M', 'label' => 'E-mail');
  }
}

class of_select_platna_typ extends of_select {
  function of_select_platna_typ($a) {
    $this->setup_element($a);
    if($a['insertnull']) $this->options[] = array('value'=>'', 'label'=>'');
		$this->options[] = array('value' => 'A', 'label' => 'Neplatná');
		$this->options[] = array('value' => 'N', 'label' => 'Platná');
		$this->options[] = array('value' => 'D', 'label' => 'Smazaná');
  }
}

class of_select_typ_view extends of_select {
  function of_select_typ_view($a) {
    $this->setup_element($a);
    $this->options[] = array('value'=>'1', 'label'=>'souhrnný přehled');
		$this->options[] = array('value' => '2', 'label' => 'Jen ručně zadaní adresáti');
//		$this->options[] = array('value' => '3', 'label' => 'Jen adresáti z EED');
  }
}

/*
class of_select_nazev extends of_select {

  function of_select_nazev($a) {
    $this->setup_element($a);
    if($a['insertnull']) $this->options[] = array('value'=>'', 'label'=>'');
    $this->options[] = array('value'=>1, 'label'=>'');
    $this->options[] = array('value'=>2, 'label'=>'');
  }
}

class of_select_nazev2 extends of_select_db {
  // Constructor
  function of_select_nazev2($a) {
    $this->setup_element($a);
    $this->DB_Sql = new DB_DEFAULT;
    $this->DB_Sql->query('SELECT sl1, sl2 FROM tabulka ORDER BY sl3');
    $this->init_db();
  }
}  
*/
