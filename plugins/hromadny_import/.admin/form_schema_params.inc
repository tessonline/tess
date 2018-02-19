<?php 

$validVec = "
    if (document.forms[0].VEC.value.length>255) {
      alert('Věc nesmí být dešlí než 255 znaků.');
      document.forms[0].VEC.focus();
      return false;
    }
    return(true);    ";

$FORM_CONFIG['schema'][] = array("elements"=>array(
  array("type"=>"hidden","name"=>"dalsi_krok","value"=>1),
  array("type"=>"hidden","name"=>"restart","value"=>$restart),
  array("type"=>"hidden","name"=>"REFERENT","value"=>$GLOBALS['REFERENT']),
  array("type"=>"hidden","name"=>"LHUTA","value"=>$GLOBALS['REFERENT']),
  array("type"=>"hidden","name"=>"id", "value"=>$id)));


$FORM_CONFIG['schema'][] = array(
  'elements' => array(
    array(
      'type' => 'select_agenda_dokumentu',
      'filter' => true,
      'name' => 'AGENDA_DOKUMENTU',
      "add"=>"onChange=\"UkazTypPosty(this,'TYP_POSTY','','',1)\"",
      "insertnull" => true,
    ),
  ),
  'label' => 'Agenda:',
);

$FORM_CONFIG['schema'][] = array(
  'elements' => array(
    array(
      'type' => 'select_typ_posty',
      'name' => 'TYP_POSTY',
      'add'=>'style="width:730px;" onChange="ZmenaTypuDokumentu(this)"',
    ),
  ),
  'label' => 'Druh dokumentu:',
);

$FORM_CONFIG['schema'][] = array(
   'elements' => array(
     array(
       'type' => 'text',
       'size' => 40,
       'name' => 'VEC'
     ),
   ),
   'label' => 'Věc',
 ); 

$FORM_CONFIG['schema'][] = array(
  'elements' => array(
    array(
      'type' => 'select_odes_typ',
      'name' => 'ODES_TYP',
    ),
  ),
  'label' => 'Adresát:',
);

$FORM_CONFIG['schema'][] = array(
  'elements' => array(
    array(
      'type' => 'select_druh_odeslani',
      'name' => 'VLASTNICH_RUKOU',
      "add"=>"onChange=\"TypObalky(this,'1');\"",
    ),
  ),
  'label' => 'Způsob vypravení:',
);


$FORM_CONFIG['schema'][] = array(
  'elements' => array(
    array(
      'type' => 'select_typ_odeslani',
      'name' => 'DOPORUCENE'
    ),
  ),
  'label' => 'Obálka',
);


$FORM_CONFIG["schema"][] = array("elements"=>array(
  array( "type"=>"checkbox", "name"=>"OBALKA_NEVRACET","label"=>"nevracet"),
  array( "type"=>"checkbox", "name"=>"OBALKA_10DNI","label"=>"Jen 10 dní"),
),
  "format"=>"OBALKA_NEVRACET...'Nevracet, vložit do schránky&nbsp;&nbsp;&nbsp;'...OBALKA_10DNI...'Jen 10 dní&nbsp;'",
  "label"=>"Na obálku:",
  'theme_config' => array(
    'square' => array(
      'format' => '',
    )
  )
);

$FORM_CONFIG['schema'][] = array(
  'elements' => array(
    array(
      'type' => 'textarea',
      'name' => 'POZNAMKA',
      'rows' => 5,
      'cols' => 80,
    ),
  ),
  'label' => 'Poznámka:',
);

$FORM_CONFIG['schema'][] = array(
  'elements' => array(
    array(
      'type' => 'select_skartace',
      'name' => 'SKARTACE',
      'width'=> '730px'
    ),
  ),
  'label' => 'Spisový znak',
);



if ($GLOBALS['csv_only']!=1)
$FORM_CONFIG['schema'][] = array(
  'elements' => array(
    array(
      'type' => 'checkbox',
      'name' => 'PDF'
    ),
  ),
  'label' => 'Generovat do formátu PDF:',
);

$FORM_CONFIG['schema'][] = array(
  'elements' => array(
    array(
      'type' => 'checkbox',
      'name' => 'DS'
    ),
  ),
  'label' => 'Ověřovat DS:',
);


$FORM_CONFIG['schema'][] = array(
  'elements' => array(
    array(
      'type' => 'checkbox',
      'name' => 'DAT_VYP'
    ),
  ),
  'label' => 'Doplnit datum vypravení:',
);

$FORM_CONFIG['schema'][] = array(
  'elements' => array(
    array(
      'type' => 'checkbox',
      'name' => 'DAT_DOR'
    ),
  ),
  'label' => 'Doplnit datum doručení:',
);

$FORM_CONFIG['schema'][] = array(
  'elements' => array(
    array(
      'type' => 'checkbox',
      'name' => 'ODESL_OTOCIT'
    ),
  ),
  'label' => 'Otočit jméno firmy a osobu:',
);


$FORM_CONFIG["schema"][] = array("elements"=>array(
  array("type"=>"valid_fce",
    "name_fce"=>$validVec)),
);


