<?php

$thisDir = getcwd();
chdir(GetAgendaPath('POSTA', FALSE, FALSE));
include_once(FileUp2('.admin/properties.inc'));
include_once(FileUp2('.admin/el/of_select_.inc'));
chdir($thisDir); 

include_once(FileUp2('.admin/db/db_posta.inc'));

class of_select_dm_item extends of_select {
  function of_select_dm_item($a) {    
    $this->setup_element($a);
    
    if ($a['insertnull']) $this->options[] = array('value'=>'', 'label'=>'');
    
    global $config;
    
    foreach ($config['POSTA_DS_FILTRY']['DM_ITEMS'] as $key => $value) {      
      $this->options[] = array('value' => $key, 'label' => $value['label']);
    }
  }
}

/*
class of_select_nazev2 extends of_select_db {
  function of_select_nazev2($a) {
    $this->setup_element($a);
    $this->DB_Sql = new $GLOBALS['PROPERTIES']['DB_NAME'];
    $this->DB_Sql->query('SELECT sl1, sl2 FROM tabulka ORDER BY sl3');
    $this->init_db();
  }
}  
*/
