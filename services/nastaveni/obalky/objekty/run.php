<?php

require('tmapy_config.inc');
require(FileUp2('.admin/run2_.inc'));
require_once(Fileup2('html_header_title.inc'));

if ($_GET['change_objects_position']) {
  // Posun souradnic u objektu dane obalky
  
  $envelope_id = intval($_GET['EDIT_ID']);
  
  $x_shift = $GLOBALS['X_SHIFT'] ? $GLOBALS['X_SHIFT'] : 0;
  $y_shift = $GLOBALS['Y_SHIFT'] ? $GLOBALS['Y_SHIFT'] : 0;  

  $db = $PROPERTIES['DB_NAME'] ? $PROPERTIES['DB_NAME'] : 'DB_DEFAULT';
  $q = new $db;  
  $sql = "SELECT id, sourx, soury FROM posta_cis_obalky_objekty WHERE obalka_id = $envelope_id";
  $q->query($sql);
  
  while ($q->next_record()) {
    
    $GLOBALS['EDIT_ID'] = $q->Record['ID'];
    $GLOBALS['SOURX'] = $q->Record['SOURX'] + $x_shift;
    $GLOBALS['SOURY'] = $q->Record['SOURY'] + $y_shift;
    
    Run_(array(
      'outputtype' => 3,
    ));
  }
  
  ?>

  <script type="text/javascript">
    window.close();
  </script>

  <?php
  
}
else {

  Run_(array(
    'showaccess' => true,
    'outputtype'=>3
  ));
  
}

require_once(Fileup2('html_footer.inc'));  

?>

