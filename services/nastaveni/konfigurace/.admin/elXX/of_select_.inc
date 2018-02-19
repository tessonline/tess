<?php
if (!IsFileIncluded(__FILE__."user")):

include_once($GLOBALS["TMAPY_LIB"]."/of_select_db.inc");
include_once($GLOBALS["TMAPY_LIB"]."/of_select_db_add.inc");

$is_history = In_Array($form_params["formtype"], array($f_history));
$is_info = In_Array($form_params["formtype"], array($f_info));


class of_select_kategorie extends of_select {
  // Constructor
  function of_select_kategorie($a) {
    $this->setup_element($a);
    $this->options = array();
    if ($a["insertnull"]) $this->options[] = array("value"=>"", "label"=>" ");
    $this->options[] = array("value"=>"HLAVNI", "label"=>"Hlavní nastavení");
    $this->options[] = array("value"=>"SYS", "label"=>"Bezpečnost");
    $this->options[] = array("value"=>"EPODATELNA", "label"=>"Epodatelna");
    $this->options[] = array("value"=>"DS", "label"=>"Dat. schránka");
    $this->options[] = array("value"=>"PODPIS", "label"=>"modul podepisování");
    $this->options[] = array("value"=>"SCANNER", "label"=>"modul skenování");
  }
}

class of_select_typ extends of_select {
  // Constructor
  function of_select_typ($a) {
    $this->setup_element($a);
    $this->options = array();
    if ($a["insertnull"]) $this->options[] = array("value"=>"", "label"=>" ");
    $this->options[] = array("value"=>"text", "label"=>"text");
    $this->options[] = array("value"=>"textarea", "label"=>"textarea");
    $this->options[] = array("value"=>"text_number", "label"=>"number");
    $this->options[] = array("value"=>"pole", "label"=>"pole");
  }
}


endif;
  require_once (FileUp2('posta/.admin/el/of_select_.inc'));
