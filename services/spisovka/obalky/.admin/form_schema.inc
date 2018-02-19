<iframe id="ifrm_get_value" name="ifrm_get_value" style="position:absolute;z-index:0;left:10;top:10;visibility:hidden"></iframe>
<iframe id="ifrm_get_value2" name="ifrm_get_value2" style="position:absolute;z-index:0;left:0;top:0;visibility:hidden"></iframe>

<?php
$frozen_ref=!(HasRole('spravce')||HasRole('vedouci-odbor')||HasRole('podatelna-odbor')||HasRole('lokalni-spravce'));

$USER_INFO = $GLOBALS['POSTA_SECURITY']->GetUserInfo(); 
$REFERENT = $USER_INFO['ID']; 

/*$odbor = (HasRole('vedouci-odbord')||HasRole('podatelna-odbord')||HasRole('lokalni-spravcfe')) 
    ? $USER_INFO['PRACOVISTE']:$USER_INFO['GROUP_ID'];*/


$FORM_CONFIG['schema'][] = array(
  'label' => 'Filtr pro výběr:'
);


/*$FORM_CONFIG['schema'][] = array(
  'elements'=>array(
    array(
      'type' => 'select_referent',
      'name' => 'REFERENT',
      'label' => 'Zpracovatel'
    )
  ),
  'visible'=>!$frozen_ref,
  'label' => 'Zpracovatel:'
);
          
$FORM_CONFIG['schema'][] = array(
  'elements'=>array(
    array(
      'type' => 'select_referent',
      'name' => 'REFERENT',
      'label' => 'Zpracovatel',
      'frozen' => true,
      'value' => $REFERENT
    )
  ),
  'visible'=>$frozen_ref,
  'label' => 'Zpracovatel:'
);*/


$FORM_CONFIG['schema'][] = array(
  'elements'=>array(
    array(
      'type' => 'select_referent',
      'name' => 'REFERENT',
      'label' => 'Zpracovatel',
      'frozen' => $frozen_ref,
      'value' => $REFERENT
    )
  ),
  'label' => 'Zpracovatel:'
);

if (HasRole('spravce')) unset($FORM_CONFIG['schema']['elements']['odbor']);


$FORM_CONFIG["schema"][] = array("elements"=>array(
  array(
    "type"=>"select_agenda_dokumentu",
    "name"=>"AGENDA_DOKUMENTU",
    //"superodbor" => $GLOBALS['ID_SUPERODBOR'],
    "insertnull"=>true,
    "add"=>"onChange=\"UkazTypPosty(this,'TYP_POSTY','','',1);\"","label"=>"Agenda"),
),
);

//if ($GLOBALS['AGENDA_DOKUMENTU']==null) $default_agenda = true;

$FORM_CONFIG["schema"][] = array("elements"=>array(
  array(
    "type"=>"select_typ_posty",
    "name"=>"TYP_POSTY",
    //"default_agenda" => true,
    //"agenda_id" => $GLOBALS['AGENDA_DOKUMENTU'],
    "add"=>"onChange=\"getAgenda(this,'AGENDA_DOKUMENTU');\" onfocus=\"this.selectedIndex = -1;\"",
    "insertnull"=>true,
    "label"=>"Druh dokumentu",
  ),
),
);

$FORM_CONFIG['schema'][] = array(
  'elements'=>array(
    array(
      'type' => 'select_status',
      'name' => 'STATUS',
      'label' => 'Stav',
      "insertnull"=>true,     
    )
  ),
);


$FORM_CONFIG['schema'][] = array(
  'elements'=>array(
    array(
      'type' => 'select_typ_odeslani',
      'name' => 'DOPORUCENE',
      'insertnull' => true,
      'required' => false
    )
  ),
  'label' => 'Dokumenty označené jako:'
);

$FORM_CONFIG['schema'][] = array(
  'elements'=>array(
    array(
      'type' => 'date_db',
      'name' => 'DATUM_OD',
      'required' => true,
      'insertdatebutton' => true,
      'label' => 'Datum od:'
    ),
    array(
      'type' => 'date_db',
      'name' => 'DATUM_DO',
      'required' => true,
      'insertdatebutton' => true,
      'label' => 'do:'
    )
  ),
);

$FORM_CONFIG['schema'][] = array(
  'label' => 'Šablona obálek:'
);


$FORM_CONFIG['schema'][] = array(
  'elements'=>array(
    array(
      'type' => 'select_typ_obalky',
      'name' => 'OBALKA',
      'required' => true
    )
  ),
  'label' => 'Druh obálky:'
);

$FORM_CONFIG['schema'][] = array(
  'label' => 'Tisk na štítky:'
);


$FORM_CONFIG['schema'][] = array(
  'elements'=>array(
    array(
      'type' => 'select_stitek',
      'name' => 'STITKY',
      'required' => false,
      'insertnull' => true
    )
  ),
  'label' => 'Předloha štítků:'
);

$FORM_CONFIG['schema'][] = array(
  'elements'=>array(
    array(
      'type' => 'text_number',
      'name' => 'POZICE',
     'label' => 'Pozice prvního štítku:',
     'tooltip' => 'Zadejte pozici prvního volného štítku na papíru, počítáno po řádcích'
    ),
    array(
      'type' => 'text_number',
      'name' => 'POCET',
      'label' => 'Počet kopií:',
      'tooltip' => 'Zadejte počet kopií. Pokud není uvedeno, tiskne se 1x'
    ),
  ),
);
