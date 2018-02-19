<?php
include_once(FileUp2(".admin/config.inc"));

$is_filter = In_Array($form_params["formtype"], array($f_filter, $f_filter_all));
$is_filter_all = In_Array($form_params["formtype"], array($f_filter_all));
$is_filter_simple = In_Array($form_params["formtype"], array($f_filter));
$is_insert = In_Array($form_params["formtype"], array($f_insert));
$is_update = In_Array($form_params["formtype"], array($f_insert, $f_edit));
$is_edit = In_Array($form_params["formtype"], array($f_edit));
$is_info = In_Array($form_params["formtype"], array($f_info));
$is_history = In_Array($form_params["formtype"], array($f_history));
$is_new = In_Array($form_params["formtype"], array($f_insertfrom)); 


$FORM_CONFIG['schema'][] = array(
  'elements' => array(
     array(
       'type' => 'text',
       'name' => 'CISLO',
       'required' => true,
       'label' => 'Číslo verze'
    ),
  ),
  'visible' => $is_edit or $is_info or $is_insert or $is_new,
);


$FORM_CONFIG['schema'][] = array(
  'elements' => array(
     array(
       'type' => 'datetime_db',
       'name' => 'DATUM',
       'insertdatebutton' => true,
       'required' => true,
       'label' => 'Datum'
    ),
  ),
  'visible' => $is_edit or $is_info or $is_insert or $is_new,										 
);

$FORM_CONFIG['schema'][] = array(
  'elements' => array(
    array(
      'type' => 'select_plugin',
      'name' => 'PLUGIN',
      'required' => false,
      'label' => 'Plugin'
    ),
  ),
  'visible' => $is_edit or $is_info or $is_insert or $is_new,
);		

$FORM_CONFIG['schema'][] = array(
  'elements' => array(
     array(
       'type' => 'textarea',
       'name' => 'POPIS',
       'required' => false,
       'label' => 'Nové věci',
       'rows' => 15,
       'cols' => 80,
    ),
  ),
  'visible' => $is_edit or $is_info or $is_insert or $is_new,
);

$FORM_CONFIG['schema'][] = array(
  'elements' => array(
     array(
       'type' => 'textarea',
       'name' => 'OPRAVY',
       'required' => false,
       'label' => 'Opravy',
       'rows' => 15,
       'cols' => 80,
    ),
  ),
  'visible' => $is_edit or $is_info or $is_insert or $is_new,
);

