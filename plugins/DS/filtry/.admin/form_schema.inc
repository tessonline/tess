<?php

include_once(FileUp2('.admin/javascript.inc'));

// $isFilter = In_Array($form_params['formtype'], array($f_filter, $f_filter_all));
// $isUpdate = In_Array($form_params['formtype'], array($f_insert, $f_edit));
// $isEdit = In_Array($form_params['formtype'], array($f_edit));
// $isInsert = In_Array($form_params['formtype'], array($f_insert));
// $isInfo = In_Array($form_params['formtype'], array($f_info));

//$FORM_CONFIG['schema'][] = '&nbsp;';

global $config;

$FORM_CONFIG['schema'][] = array( 
  'label' => ' ',
);

$FORM_CONFIG['schema'][] = array( 
  'elements' => array(
    array( 
      'type' => 'text_number', 
      'name' => 'PRIORITY',
    )
  ),
  'label' => 'Priorita filtru:',
);

$FORM_CONFIG['schema'][] = array( 
  'label' => 'Položka datové zprávy',
);

$FORM_CONFIG['schema'][] = array( 
  'elements' => array(
    array( 
      'type' => 'select_dm_item', 
      'name' => 'DM_ITEM'
    ),
  ),
  'label' => 'Položka:',
);

$FORM_CONFIG['schema'][] = array( 
  'elements' => array(
    array( 
      'type' => 'text', 
      'name' => 'DM_ITEM_COMPARED_VALUES',
      'size' => 50,
      //'maxlength' => 1024
    )
  ),
  'label' => 'Obsahuje hodnoty<br/>(více hodnot oddělit pomocí | znaku):',
);

$FORM_CONFIG['schema'][] = array( 
  'label' => 'Položky el. dokumentu',
);

$FORM_CONFIG['schema'][] = array( 
  'elements' => array(
    array( 
      'type' => 'select_superodbor', 
      'name' => 'ED_ITEM_SUPERODBOR',
      'add' => 'id="SUPERODBOR" onChange=UkazOdbor(this,\'ED_ITEM_ODBOR\');',
      'insertnull' => TRUE
    ),
  ),
  'label' => '<b>' . $GLOBALS["CONFIG"]["NAZEV_SUPERODBOR"] . '</b> se nastaví na hodnotu:',
);

$FORM_CONFIG['schema'][] = array( 
  'elements' => array(
    array( 
      'type' => 'select_odbor', 
      'name' => 'ED_ITEM_ODBOR',
      'add' => 'id="ODBOR" onChange=UkazPracovnika(this,\'ED_ITEM_REFERENT\');',
      'insertnull' => TRUE
    ),
  ),
  'label' => '<b>Odbor</b> se nastaví na hodnotu:',
);

$FORM_CONFIG['schema'][] = array( 
  'elements' => array(
    array( 
      'type' => 'select_referent', 
      'name' => 'ED_ITEM_REFERENT',
      'add' => 'id="REFERENT"',
      'insertnull' => TRUE
    ),
  ),
  'label' => '<b>Zpracovatel</b> se nastaví na hodnotu:',
);

$FORM_CONFIG["schema"][] = array(
  "elements"=>array(
    array( 
      "type"=>"select_vita", 
      "name"=>"ED_STAV",
      "fullselect"=>false
    ),
  ),
  "label"=>"Kde se vyřizuje:"
  
    );
