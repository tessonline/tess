<?php
//přepíšeme label z JID na PID

foreach($FORM_CONFIG['schema'] as $key => $schema) {
   if (is_array($schema['elements'])) {
     foreach($schema['elements'] as $key1 => $elem) {
       if ($elem['name'] == 'ID_X') {
          $FORM_CONFIG['schema'][$key]['elements'][$key1]['label'] = 'PID';
       };

     }
   }
}
