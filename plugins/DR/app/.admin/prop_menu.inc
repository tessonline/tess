<?php
$PROPERTIES["MENU2L"]["filter"] = false;
$PROPERTIES["MENU2L"]["filterall"] = false;

$dropdownListFunc[] = array(
  'name' => 'Nastavení',
  'href' => 'browSEZNAM.php',
);

// MENU_THEME
$PROPERTIES['MENU_THEME'] = array(
  'applications' => array(
    'dropdownList' => $dropdownListApp
  ),
  'functions' => array(
    'caption' => 'nadpis',
    'icon' => '',
    'dropdownList' => $dropdownListFunc
  )
);
