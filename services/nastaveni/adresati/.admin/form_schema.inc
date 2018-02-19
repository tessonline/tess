<?php
//$FORM_CONFIG['schema'][] = '&nbsp;';
if ($GLOBALS['INSERT_ID']) {
  $sql = 'select * from posta where id='.$GLOBALS['INSERT_ID'];
echo $sql;
  $q->query($sql);
  $q->Next_Record();

  SetVarFromHash($q->Record, &$fields, $noglobals);
}

$is_filter = In_Array(
  $form_params["formtype"], 
  array($f_filter, $f_filter_all)
);
$is_filter_all = In_Array(
  $form_params["formtype"], 
  array($f_filter_all)
);
$is_filter_simple = In_Array(
  $form_params["formtype"], 
  array($f_filter)
);
$is_insert = In_Array(
  $form_params["formtype"], 
  array($f_insert)
);
$is_update = In_Array(
  $form_params["formtype"], 
  array($f_insert, $f_edit)
);
$is_edit = In_Array(
  $form_params["formtype"], 
  array($f_edit)
);
$is_info = In_Array(
  $form_params["formtype"], 
  array($f_info)
);
$is_history = In_Array(
  $form_params["formtype"], 
  array($f_history)
);
$is_new = In_Array(
  $form_params["formtype"], 
  array($f_insertfrom)
); 
$is_multiedit = In_Array(
  $form_params["formtype"], 
  array($f_editall)
);

/* select typ */
$FORM_CONFIG['schema'][] = array( 
  'elements' => array(
    array( 
      'type' => 'select_odes_typ', 
      'name' => 'ODES_TYP',
	  'insertnull' => true,
    )
  ),
  'label' => 'Typ:',
   'visible' => $is_insert || $is_update || $is_edit || $is_filter_all || $is_filter || $is_info,
  
);

/* select platná/neplatná */
/*
$FORM_CONFIG['schema'][] = array( 
  'elements' => array(
    array( 
      'type' => 'select_platna_typ', 
      'name' => 'FROZEN',
	  'insertnull' => true
    )
  ),
  'label' => 'Platnost adresy:',
  'visible' => $is_insert || $is_update || $is_edit || $is_filter_all || $is_info,
  
);
*/

$FORM_CONFIG['schema'][] = array( 
  'elements' => array(
    array( 
      'type' => 'text_number', 
      'name' => 'ODESL_ADRKOD',
      'size' => 4,
    )
  ),
  'label' => 'Kód RUIAN:',
   'visible' => $is_insert || $is_update || $is_edit || $is_filter_all || $is_info,
);

$FORM_CONFIG['schema'][] = array( 
  'elements' => array(
    array( 
      'type' => 'text', 
      'name' => 'ODESL_TITUL',
      'size' => 4
    )
  ),
  'visible' => $is_insert || $is_update || $is_edit || $is_filter_all || $is_info,
  'label' => 'Titul:'
);

$FORM_CONFIG['schema'][] = array( 
  'elements' => array(
    array( 
      'type' => 'text', 
      'name' => 'ODESL_JMENO',
      'size' => 20
    ),
	 array( 
      'type' => 'text', 
      'name' => 'ODESL_PRIJMENI',
      'size' => 20
    )
	
  ),
   'visible' => $is_insert || $is_update || $is_edit || $is_filter_all || $is_filter || $is_info,
   'format' => "ODESL_JMENO...'&nbsp;&nbsp;&nbsp;Příjmení/Organizace:&nbsp;'...ODESL_PRIJMENI...",
   'label' => 'Jméno:'
);



$FORM_CONFIG['schema'][] = array( 
  'elements' => array(
    array( 
      'type' => 'text', 
      'name' => 'ODESL_ODD',
      'size' => 20
    ),
	 array( 
      'type' => 'text', 
      'name' => 'ODESL_OSOBA',
      'size' => 20
    )
	
  ),
   'visible' => $is_insert || $is_update || $is_edit || $is_filter_all || $is_info,
   'format' => "ODESL_ODD...'&nbsp;&nbsp;&nbsp;Osoba:&nbsp;'...ODESL_OSOBA...",
   'label' => 'Oddělení:',
);


$FORM_CONFIG['schema'][] = array( 
  'elements' => array(
    array( 
      'type' => 'text', 
      'name' => 'ODESL_ULICE',
      'size' => 20
    ),
	array( 
      'type' => 'text_number', 
      'name' => 'ODESL_CP',
      'size' => 5
    ),
	 array( 
      'type' => 'text_number', 
      'name' => 'ODESL_COR',
      'size' => 5
    )
	
  ),
   'visible' => $is_insert || $is_update || $is_edit || $is_filter_all || $is_info,
   'format' => "ODESL_ULICE...'&nbsp;&nbsp;&nbsp;Číslo popisné :&nbsp;'...ODESL_CP...'&nbsp;&nbsp;&nbsp;Číslo orientační&nbsp;'...ODESL_COR",
   'label' => ' Ulice:'
  
  
);

$FORM_CONFIG['schema'][] = array( 
  'elements' => array(
    array( 
      'type' => 'text_number', 
      'name' => 'ODESL_ICO',
      'size' => 8
    )
  ),
   'visible' => $is_insert || $is_update || $is_edit || $is_filter_all || $is_info,
  'label' => ' IČO'
);

$FORM_CONFIG['schema'][] = array( 
  'elements' => array(
    array( 
      'type' => 'text_number', 
      'name' => 'ODESL_PSC',
      'size' => 5
    ),
	array( 
      'type' => 'text', 
      'name' => 'ODESL_POSTA',
      'size' => 20
    )
	
  ),
   'visible' => $is_insert || $is_update || $is_edit || $is_filter_all || $is_info,
   'format' => "ODESL_PSC...'&nbsp;&nbsp;&nbsp;Město:&nbsp;'...ODESL_POSTA...", 
   'label' => ' PSČ'
);

$FORM_CONFIG['schema'][] = array( 
  'elements' => array(
    array( 
      'type' => 'text', 
      'name' => 'ODESL_EMAIL',
      'size' => 20
    )
  ),
   'visible' => $is_insert || $is_update || $is_edit || $is_filter_all || $is_info,
  'label' => ' Email'
);
$FORM_CONFIG['schema'][] = array( 
  'elements' => array(
    array( 
      'type' => 'text', 
      'name' => 'ODESL_DATSCHRANKA',
      'size' => 20
    )
  ),
   'visible' => $is_insert || $is_update || $is_edit || $is_filter_all || $is_info,
  'label' => 'Datová schránka'
);

$FORM_CONFIG['schema'][] = array( 
  'elements' => array(
    array( 
      'type' => 'date_db', 
      'name' => 'ODESL_DATNAR',
      'insertdatebutton' => true
    )
  ),
   'visible' => $is_insert || $is_update || $is_edit || $is_filter_all || $is_info,
  'label' => 'Datum narození:'
);



// ODES_TYP 	ODESL_ADRKOD 	ODESL_TITUL 	ODESL_PRIJMENI 	ODESL_JMENO 	ODESL_ODD 	ODESL_OSOBA 	ODESL_ULICE 	ODESL_CP 	ODESL_COR 	ODESL_ICO 	ODESL_PSC 	ODESL_POSTA 	ODESL_RC 	ODESL_EMAIL 	ODESL_DATSCHRANKA 	ODESL_DATNAR 	FROZEN
/*
$FORM_CONFIG['schema'][] = array( 
  'elements' => array(
    array( 
      'type' => 'select_nazev', 
      'name' => 'SLOUPEC2'
    )
  ),
  'label' => 'NAZEV2:'
);
*/
