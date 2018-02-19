<?php

$TABLE_CONFIG["schema"][] =  array( "field"=>"NAZEV", "label"=>"Název");
$TABLE_CONFIG["schema"][] =  array( "field"=>"showAktivni(AKTIVNI)", "label"=>"Aktivní");

$TABLE_TOP_MENU['style'] = 'button'; //anchor

NewWindow(array("fname" => "Sort", "name" => "Agenda", "header" => true, "cache" => false, "window" => "edit"));

$TABLE_TOP_MENU["schema"][] = array(
  'label' => 'Setřídit',
  'url' => 'javascript:NewWindowSort(\'sort.php?id=' . $t->name . '\');',
  'target' => '_self',
  'theme_config' => array(
    'square' => array(
      'theme' => array(
        'dropdown' => false,
        'button' => true
      )
    )
  )
);

$TABLE_CONFIG['syscolumns'] = array(
 'edit' => array ('theme'=>array('dropdown'=>true, 'column'=>true))
);


