<?php
$TABLE_CONFIG['schema'][] = array(
  'field' => 'ukazTyp(ID_TYP)',
  'label' => 'Druh dokumentu',
  'width' => '20%',
  'add' => 'align=left',
  'ishtml' => true,
);

$TABLE_CONFIG['schema'][] = array(
  'field' => 'ukazWorkflow(ID_WORKFLOW)',
  'label' => 'Workflow',
  'width' => '25%',
  'add' => 'align=left',
  'ishtml' => true,
);

$TABLE_CONFIG['schema'][] = array(
  'field' => 'ukazDokument(DOKUMENT)',
  'label' => 'Dokument',
  'width' => '16%',
  'add' => 'align=left',
  'ishtml' => true,
);

/*$TABLE_CONFIG['schema'][] = array(
  'field' => 'ukazOdesilatele(ODES_TYP)',
  'label' => 'Typ odesilatele',
  'width' => '16%',
  'add' => 'align=left',
  'ishtml' => true,
);*/


if ($GLOBALS['rename_columns']==3) {
  $TABLE_CONFIG['schema'][] = array(
    'field' => 'PROMENNA',
    'label' => 'Název pole',
    'width' => '25%',
    'add' => 'align=left',
    'ishtml' => true,
  );
  
  $TABLE_CONFIG['schema'][] = array(
    'field' => 'ukazDatovyTyp(HODNOTA)',
    'label' => 'Datový typ',
    'width' => '25%',
    'add' => 'align=left',
    'ishtml' => true,
  );
  
} 

elseif ($GLOBALS['rename_columns']==2) {
  $TABLE_CONFIG['schema'][] = array(
    'field' => 'ukazZadamO(PROMENNA)',
    'label' => 'Žádám o',
    'width' => '25%',
    'add' => 'align=left',
    'ishtml' => true,
  );
   
  $TABLE_CONFIG['schema'][] = array(
    'field' => 'ukazJmeno(HODNOTA)',
    'label' => 'Jméno',
    'width' => '25%',
    'add' => 'align=left',
    'ishtml' => true,
  );
  
} else 
{
  $TABLE_CONFIG['schema'][] = array(
    'field' => 'ukazPromenna(PROMENNA)',
    'label' => 'Proměnná',
    'width' => '25%',
    'add' => 'align=left',
    'ishtml' => true,
  );
  
  /*if (array_key_exists($GLOBALS["PROMENNA"],$select_var)) {
    
    $TABLE_CONFIG['schema'][] = array(
      'field' => 'ukazSelectHodnotu(HODNOTA,PROMENNA)',
      'label' => 'Hodnota',
      'width' => '25%',
      'add' => 'align=left',
      'ishtml' => true,
    );
    
  } else*/
  
  $TABLE_CONFIG['schema'][] = array(
    'field' => 'HODNOTA',
    'label' => 'Hodnota',
    'width' => '25%',
    'add' => 'align=left',
    'ishtml' => true,
  );
}


$TABLE_CONFIG['syscolumns'] = array(
  'upload' => array ('theme'=>array('dropdown'=>true, 'column'=>false)),
  'info' => array ('theme'=>array('dropdown'=>true, 'column'=>false)),
  'edit' => array ('theme'=>array('dropdown'=>true, 'column'=>false)),
  'delete' => array ('theme'=>array('dropdown'=>true, 'column'=>false)),
);

