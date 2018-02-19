<?php

$dropdownListApp = array();
$dropdownListFunc = array();


$dropdownListApp[] = $GLOBALS['POSTA_DS'];
//$dropdownListApp[] = $GLOBALS['CONFIG_KOMPAS']['KOMPAS_IDENT'] .

$dropdownListFunc[] = array(
  'name' => $GLOBALS['RESOURCE_STRING_KOMPAS']['Export tabulek do SHP souboru'],
  'href' => 'javascript:top.frames[0].NewWindowKompasTools(\'' . GetAgendaPath($GLOBALS['CONFIG_KOMPAS']['KOMPAS_IDENT'], 0, 1) . '/tools/shp_export.php' . '\')'
  //'target' => '_top'
);

if ($GLOBALS['CONFIG_KOMPAS']['ALERT']['ENABLE']) {
  if ($GLOBALS['CONFIG_KOMPAS']['ALERT']['EMAIL']) {
    $dropdownListFunc[] = array(
      'name' => $GLOBALS['RESOURCE_STRING_KOMPAS']['Odeslat upozornujici email pro zaruku'],
      'href' => 'javascript:top.frames[0].NewWindowKompasSets(\'' . GetAgendaPath($GLOBALS['CONFIG_KOMPAS']['KOMPAS_IDENT'] . '_EMAIL_ZARUKA', 0, 1) . '/email_send.php' . '\')'
      //'target' => '_top'
    );
  }
}

// MENU_THEME
$PROPERTIES['MENU_THEME'] = array(
  'applications' => array(
    'dropdownList' => $dropdownListApp
  ),
  'functions' => array(
    'caption' => 'Moynosti',
    'icon' => '',
    'dropdownList' => $dropdownListFunc
  )
);
