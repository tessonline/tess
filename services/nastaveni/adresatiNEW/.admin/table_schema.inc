<?php
  $TABLE_CONFIG['schema'][] =	array( 
    'field' => "ODESL_PRIJMENI...' '...ODESL_JMENO...' '...ODESL_TITUL", 
    'label' => 'Příjmení a jméno'
  );
  $TABLE_CONFIG['schema'][] =	array( 
    'field' => 'Adresa(ODESL_ULICE,ODESL_CP,ODESL_COR)',
    'label' => 'Adresa'  
  );   	   
  $TABLE_CONFIG['schema'][] =	array( 
    'field' => "ODESL_ICO",
    'label' => 'ICO'
  );
  $TABLE_CONFIG['schema'][] =	array( 
    'field' => "ODESL_PSC",
    'label' => 'PSČ'
  );
  $TABLE_CONFIG['schema'][] =	array( 
    'field' => "ODESL_POSTA",
    'label' => 'Pošta'
  );
  $TABLE_CONFIG['schema'][] =	array( 
    'field' => "ODESL_DATSCHRANKA",
    'label' => 'Datová schránka'
  );
//   $TABLE_CONFIG['schema'][] =	array(
// 	'field' => 'Frozen(ID,FROZEN)',
//     'label' => 'Platnost adresy'
//   );

$TABLE_CONFIG['syscolumns'] = array(
 'edit' => array ('theme'=>array('dropdown'=>true, 'column'=>true)),
 'delete' => array ('theme'=>array('dropdown'=>true, 'column'=>true)),
);

