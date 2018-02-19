<?php
if ($GLOBALS['ODES_TYP'] == 'O' && $GLOBALS['WHOIS_NUMBER']>0 && $GLOBALS['WHOIS_IDSTUDIA']>0) {
  $GLOBALS['ODES_TYP'] = 'C';
}
elseif ($GLOBALS['ODES_TYP'] == 'O' && $GLOBALS['WHOIS_NUMBER']) {
  $GLOBALS['ODES_TYP'] = 'G';
}


    $FORM_CONFIG['schema'][] = array('elements'=>array(
        array( 'type' => 'text', 'name' => 'SHOW_WHOIS_TYPOVYSPIS','add' =>'style="display:none" '),
      ),
      'label' => '',
    );
