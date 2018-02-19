<?php
// require_once(FileUp2('.admin/el/of_select_.inc'));
require_once(FileUp2('.config/config.inc'));

$is_filter = In_Array($form_params['formtype'], array($f_filter, $f_filter_all));
$is_filter_all = In_Array($form_params['formtype'], array($f_filter_all));
$is_filter_small = In_Array($form_params['formtype'], array($f_filter));
$is_update = In_Array($form_params['formtype'], array($f_insert, $f_edit));
$is_edit = In_Array($form_params['formtype'], array($f_edit));
$is_insert = In_Array($form_params['formtype'], array($f_insert));
$is_info = In_Array($form_params['formtype'], array($f_info));

if($GLOBALS['EDIT_ID']) {
  $q = new DB_POSTA;
  $sql = 'SELECT nazev FROM posta_spisovna_cis_lokace WHERE id='.$GLOBALS['EDIT_ID'];
  $q->query($sql);
  $q->next_record();
  $nazev = $q->Record['NAZEV'];
  $nazev = explode(" ", $nazev, 2);
}

$FORM_CONFIG['schema'][] = 
  array(
    'elements' => 
      array(
        array(
          'type' => 'hidden',
          'name' => 'ID_PARENT',
          //'value' => $GLOBALS['ID_PARENT'],
        )
      ),
  );
  
$FORM_CONFIG['schema'][] =
  array(
    'elements' =>
    array(
      array(
        'type' => 'hidden',
        'name' => 'SPISOVNA_ID',
        //'value' => $GLOBALS['ID_PARENT'],
      )
    ),
  );
  

$FORM_CONFIG['schema'][] =
  array(
    'elements' =>
      array(
        array(
          'type' => 'text',
          'name' => 'NAZEV',
        )
      ),
    'label' => 'Název',
    'visible' =>!$is_update,
  );
  
$FORM_CONFIG['schema'][] =
  array(
    'elements' =>
    array(
      array(
        'label' => 'Název',
        'type' => 'text',
        'name' => 'NAZEV_TEXT',
        'value' => $GLOBALS['RESOURCE_STRING']['lokace_uroven'][$GLOBALS['UROVEN']][1],
        'frozen' => true,
      ),
      array(
        'label' => '&nbsp;',
        'type' => 'text',
        'name' => 'NAZEV_CISLO',
      )
    ),
    'visible' =>$is_insert,
  );
  
// $FORM_CONFIG['schema'][] =
//   array(
//     'elements' =>
//     array(
      
//     ),
//     'label' => 'Název',
//     'visible' =>$is_insert,
//   );

$FORM_CONFIG['schema'][] =
  array(
    'elements' =>
    array(
      array(
        'label' => 'Název',
        'type' => 'text',
        'name' => 'NAZEV_TEXT',
        'value' => $nazev[0],
        'frozen' => true,
      ),
      array(
        'label' => '&nbsp',
        'type' => 'text',
        'name' => 'NAZEV_CISLO',
        'value' => $nazev[1]
      )
    ),
    'visible' =>$is_edit,
  );
  
//  $FORM_CONFIG['schema'][] =
//   array(
//     'elements' =>
//     array(
      
//     ),
//     'label' => 'Název',
//     'visible' =>$is_edit,
//   );

// $FORM_CONFIG['schema'][] =
//   array(
//     'elements' =>
//       array(
//         array(
//           'type' => 'select_spisovna',
//           'name' => 'SPISOVNA_ID',
//         )
//       ),
// );

$FORM_CONFIG['schema'][] = array( 
  'elements' => array(
    array(
      'type' => 'text',
      'name' => 'PLNA_CESTA',
      'size' => 46,
    )
  ),
  'visible' => $is_filter || $is_info,
  'label' => 'Úplná cesta',
);

$FORM_CONFIG['schema'][] = array(
  'elements' => array(
    array(
      'type' => 'text',
      'name' => 'PLNA_CESTA',
      'size' => 46,
      'frozen' => true,
    )
  ),
  'visible' => $is_edit,
  'label' => 'Úplná cesta',
);
  
$FORM_CONFIG['schema'][] = array(
  'elements' => array(
    array(
      'type' => 'hidden',
      'name' => 'UROVEN',
    )
  ),
  'visible' => $is_update,
);

$FORM_CONFIG['schema'][] = array(
  'elements' => array(
    array(
        'type' => 'checkbox',
        'name' => 'DALSI_LOKACE',
        'extrahtml' => (isset($GLOBALS['DALSI_LOKACE']) && $GLOBALS['DALSI_LOKACE'] == 1 ? ' checked="checked" ': ''),
    )
  ),
  'visible' => $is_update && $GLOBALS['UROVEN'] <= 2,
  'label' => 'Další lokace'
);

$FORM_CONFIG['schema'][] = array(
  'elements' => array(
    array(
      'type' => 'hidden',
      'name' => 'DALSI_LOKACE',
      'value' => 1,
    )
  ),
  'visible' => $is_update && $GLOBALS['UROVEN'] > 2,
  'label' => 'Další lokace'
);