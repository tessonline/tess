<?php

require('tmapy_config.inc');
require(FileUp2('.admin/edit_.inc'));
require(FileUp2('html_header_title.inc'));
  
Form_(array(
  'caption' => 'Posun souřadnic objektů',
  'showaccess' => TRUE,
  'myform_schema' => '.admin/form_schema_change_obj_pos.inc',
  'action' => 'objekty/run.php',
  'formvars' => array('change_objects_position' => 1)
));

require(FileUp2('html_footer.inc'));
