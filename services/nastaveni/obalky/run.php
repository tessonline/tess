<?php

require('tmapy_config.inc');
require(FileUp2('.admin/run2_.inc'));
require_once(Fileup2('html_header_title.inc'));

if ($_GET['create_objects']) {

  // Vytvoreni kopie oblaky
  $new_envelope_id = Run_(array(
    'showaccess' => true,
    'outputtype' => 3,
  ));
  unset($GLOBALS['ID']);
  
  // Vytvoreni kopii objektu k dane obalce
  $old_envelope_id = intval($_GET['envelope_id']);

  $db = $PROPERTIES['DB_NAME'] ? $PROPERTIES['DB_NAME'] : 'DB_DEFAULT';
  $q = new $db;  
  $sql = "SELECT * FROM posta_cis_obalky_objekty WHERE obalka_id = $old_envelope_id";
  $q->query($sql);
  
  $GLOBALS['OBALKA_ID'] = $new_envelope_id;
  
  while ($q->next_record()) {
    
    $GLOBALS['VELIKOST_FONTU'] = $q->Record['VELIKOST_FONTU'];
    $GLOBALS['SOURX'] = $q->Record['SOURX'];
    $GLOBALS['SOURY'] = $q->Record['SOURY'];
    $GLOBALS['VELIKOST'] = $q->Record['VELIKOST'];
    $GLOBALS['RADKOVANI'] = $q->Record['RADKOVANI'];
    $GLOBALS['OBJEKT'] = $q->Record['OBJEKT'];
    $GLOBALS['FONT'] = $q->Record['FONT'];
    $GLOBALS['TEXT'] = $q->Record['TEXT'];
    
    Run_(array(
      'outputtype' => 3,
      'agenda' => 'POSTA_OBALKY_OBJEKTY'
    ));
    unset($GLOBALS['ID']);
  }  
}

else if ($GLOBALS['DELETE_ID']) {

  Run_(array(
    'showaccess' => true,
    'outputtype' => 2
  ));
  
  $db = $PROPERTIES['DB_NAME'] ? $PROPERTIES['DB_NAME'] : 'DB_DEFAULT';
  $q = new $db;  
  $sql = "SELECT id FROM posta_cis_obalky_objekty WHERE obalka_id = $DELETE_ID";
  $q->query($sql);
  
  while ($q->next_record()) {
    
    $GLOBALS['DELETE_ID'] = $q->Record['ID'];
    
    Run_(array(
      'outputtype' => 3,
      'agenda' => 'POSTA_OBALKY_OBJEKTY'
    ));
  } 
}
else {

  Run_(array(
    'showaccess' => true,
    'outputtype' => 3
  ));
  
}

require_once(Fileup2('html_footer.inc'));  

