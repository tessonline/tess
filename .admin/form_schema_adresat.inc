<?php

include_once(FileUp2('.admin/oth_funkce.inc'));

if ($GLOBALS['ODESLANA_POSTA']=='t')
  $label_adresat='Adresát:';
else
  $label_adresat='Odesílatel:'; 
  
$FORM_CONFIG['schema'][] = array('elements'=>array(
  array(
    'type' => 'select_odes_typ',
    'name' => 'ODES_TYP',
    'width'=>10,
    "multiple"=>$false,
    'insertnull' => $is_filter_all,
    'required' => !$is_filter_all,
    'add' => 'onChange=\'DruhAdresata(this.value)\';onFocus=\'DruhAdresata(this.value)\'')
  ),
  'visible'=>$is_edit or $is_info or $is_insert or $is_new or $is_filter_all,
  'label'=>$label_adresat
);

if ($GLOBALS['ODESL_OTOCIT']<>1) {
  $GLOBALS['ODESL_OTOCIT']=0;
}

if ($is_filter_all) $GLOBALS['ODESIL_TYP'] = 'X';

if ($GLOBALS['ODES_TYP']=='S') {
  $GLOBALS['ODESL_ODBOR']=$GLOBALS['ODESL_ULICE'];
  $GLOBALS['ODESL_URAD']=$GLOBALS['ODESL_TITUL'];
}
  				

$FORM_CONFIG['schema'][] = array('elements'=>array(
    array( 'type' => 'text', 'name' => 'ODESL_PRIJMENI_FIRMA','size' => '57', 'label' => 'Název firmy'),
    array( 'type' => 'button', 'name' => 'Adresar', 'value' => '?', 'onclick' => 'Jmeno2()', 'label' => 'Adresář', 'tooltip' => 'Jmeno'),
    array( 'type' => 'checkbox', 'name' => 'ODESL_OTOCIT', 'value' => '1', 'label' => 'Otočit jméno firmy a osobu'),
  ),

  'visible'=>$is_edit || $is_insert || $is_new || $is_info || $is_filter_all,
  'label' => 'Firma:',
);


$FORM_CONFIG['schema'][] = array('elements'=>array(
    array( 'type' => 'select_osloveni', 'name' => 'ODESL_OSLOVENI', 'size' => '1', 'insertnull'=>true,'label' => 'Osloveni'),
  ),

  'visible'=>$is_edit || $is_insert || $is_new || $is_info || $is_filter_all,
  'label' => 'Člověk:',
);

$FORM_CONFIG['schema'][] = array('elements'=>array(
    array( 'type' => 'text', 'name' => 'ODESL_TITUL', 'size' => '4', 'label' => 'Titul před'),
	array( 'type' => 'text', 'name' => 'ODESL_PRIJMENI', 'size' => '20', 'label' => 'Příjmení'),
    array( 'type' => 'button', 'name' => 'Adresar', 'value' => '?', 'onclick' => 'Jmeno2()', 'label' => 'Adresář', 'tooltip' => 'test'),

//<a  class=\'btn btn-loading\' href=\'%\' onclick='Jmeno()'>

    array( 'type' => 'text', 'name' => 'ODESL_JMENO', 'size' => '20', 'label' => 'Jméno'),
    array( 'type' => 'text', 'name' => 'ODESL_TITUL_ZA', 'size' => '4', 'label' => 'Titul za'),
    array( 'type' => 'date_db', 'name' => 'ODESL_DATNAR', 'label' => 'Datum narození', 'insertdatebutton'=>true,'insertcalendar'=>true),
  ),

  'visible'=>$is_edit || $is_insert || $is_new || $is_info || $is_filter_all,
  'label' => 'Člověk:',
);

$FORM_CONFIG['schema'][] = array('elements'=>array(
    array( 'type' => 'text', 'name' => 'ODESL_EMAIL', 'label' => 'Emailová adresa', 'size'=>80),
  ),
  'visible'=>$is_edit || $is_insert || $is_new || $is_info || $is_filter_all,
  'label' => 'Email:',
);


$FORM_CONFIG['schema'][] = array('elements'=>array(
    array( 'type' => 'text', 'name' => 'ODESL_SUBJ', 'label' => 'Subjekt emailu', 'size'=>80),
  ),

  'visible'=>$is_edit || $is_insert || $is_new || $is_info || $is_filter_all,
  'label' => 'Email:',
);

$FORM_CONFIG['schema'][] = array('elements'=>array(
  array( 'type' => 'textarea', 'name' => 'ODESL_BODY', 'rows' => '4', 'cols' => '60', 'label' => 'Tělo emailu'),
),

  'visible'=>$is_edit || $is_insert || $is_new || $is_info || $is_filter_all,
  'label' => 'Email:',
);

if ($is_new && $GLOBALS['ODES_TYP'] == 'S') $GLOBALS['ODESL_PRAC2'] = $GLOBALS['ODESL_OSOBA']; //nastavime puvodniho zpracovatele


$doc = LoadClass('EedDokument', $GLOBALS['EDIT_ID']);
if (isset($GLOBALS['insertfrom']) && $GLOBALS['ODESLANA_POSTA'] == 't') {
  $GLOBALS['ODESL_ODBOR'] = $GLOBALS['ODESL_ULICE'];
  $GLOBALS['ODESL_PRAC2'] = $GLOBALS['ODESL_OSOBA'];
}

$FORM_CONFIG['schema'][] = array('elements'=>array(
//  array( 'type' => 'select_interni_spisuzly', 'name' => 'ODESL_ODBOR', 'label' => 'Spisový uzel', 'selectfull' => true, 'add' => "onChange=\"UkazPracovnika(this,'ODESL_PRAC2');\""),
  array( 'type' => 'select_interni_spisuzly2', 'abbr' => true, 'name' => 'ODESL_ODBOR','multiple'=>true, 'label' => 'Spisový uzel', 'selectfull' => true, 'extrahtml' => "onChange=\"UkazPracovnika(this,'ODESL_PRAC2');\""),
  array( 'type' => 'select_referent', 'name' => 'ODESL_PRAC2', 'label' => 'Zpracovatel', 'set_odbor'=> $GLOBALS['ODESL_ODBOR'], 'insertnull' => true),
  array( 'type' => 'text_number', 'name' => 'LHUTA', 'label' => 'Lhůta'),
  ),

  'visible'=>($is_edit || $is_insert || $is_new || $is_info || $is_filter_all) && $GLOBALS['ODESLANA_POSTA']=='t',
  'label' => 'Spisový uzel:',
);

$disabled = ($GLOBALS['ODES_TYP'] == 'S'?"disabled":"");


$FORM_CONFIG['schema'][] = array('elements'=>array(
  array( 'type' => 'select_interni_spisuzly', 'name' => 'ODESL_ODBOR', 'label' => 'Spisový uzel', 'add' => "onChange=\"UkazPracovnika(this,'ODESL_PRAC2');\"", "add"=>$disabled),
  //array( 'type' => 'select_interni_spisuzly', 'name' => 'ODESL_ODBOR', 'label' => 'Spisový uzel', 'add' => "onChange=\"UkazPracovnika(this,'ODESL_PRAC2');\"","frozen"=>($GLOBALS['ODES_TYP'] == 'S'?true:false)),
  //array( 'type' => 'select_referent', 'name' => 'ODESL_PRAC2',"value"=>$GLOBALS['ODESL_OSOBA'], 'label' => 'Zpracovatel',"fullselect"=>true,"frozen"=>($GLOBALS['ODES_TYP'] == 'S'?true:false)),
  array( 'type' => 'select_referent', 'name' => 'ODESL_PRAC2',"value"=>$GLOBALS['ODESL_OSOBA'], 'label' => 'Zpracovatel',"fullselect"=>true,"add"=>$disabled),
),

  'visible'=>($is_edit || $is_insert || $is_new || $is_info || $is_filter_all) && $GLOBALS['ODESLANA_POSTA']=='f',
  'label' => 'Spisový uzel:',
);




$FORM_CONFIG['schema'][] = array('elements'=>array(
    array( 'type' => 'text', 'name' => 'ODESL_ICO', 'size' => '15', 'maxlength'=>10,'label' => 'IČ'),
    array( 'type' => 'button', 'name' => 'Ares', 'value' => '?', 'onclick' => 'ARES()', 'label' => 'ARES', 'tooltip' => 'test'),
    array( 'type' => 'text', 'name' => 'ODESL_ODD', 'size' => ($is_filter_all?'30':'30'), 'label' => 'Oddělení'),
    array( 'type' => 'text', 'name' => 'ODESL_OSOBA', 'size' => '28', 'label' => 'Osoba'),
  ),

  'visible'=>$is_edit || $is_insert || $is_new || $is_info || $is_filter_all,
  'label' => 'IČO:',
);



$FORM_CONFIG['schema'][] = array('elements'=>array(
    array( 'type' => 'text', 'name' => 'ODESL_ULICE', 'size' => ($is_filter_all?'48':'48'), 'label' => 'Ulice'),
    array( 'type' => 'text', 'name' => 'ODESL_CP', 'label' => 'č.p.'),
    array( 'type' => 'text', 'name' => 'ODESL_COR', 'label' => 'č.orient.'),
  ),

  'visible'=>$is_edit || $is_insert || $is_new || $is_info || $is_filter_all,
  'label' => 'Adresa:',
);

$FORM_CONFIG['schema'][] = array('elements'=>array(
    array( 'type' => 'text', 'name' => 'ODESL_PSC', 'label' => 'PSČ'),
    array( 'type' => 'button', 'name' => 'PSČ', 'value' => '?', 'onclick' => 'PSC()', 'label' => 'PSČ'),
    array( 'type' => 'text', 'name' => 'ODESL_POSTA', 'size' => ($is_filter_all?'47':'48'), 'label'=>$GLOBALS['CONFIG']['NAZEV_ADRESAT_POSTA']),
    array( 'type' => 'text', 'name' => 'ODESL_DATSCHRANKA', 'size' => '10', 'label' => 'Datová schránka'),
    array( 'type' => 'button', 'name' => 'DS', 'value' => '?', 'onclick' => 'Datovka()', 'label' => 'DS'),
  ),

  'visible'=>$is_edit || $is_insert || $is_new || $is_info || $is_filter_all,
  'label' => 'Adresa:',
);

$FORM_CONFIG['schema'][] = array('elements'=>array(
		array( 'type' => 'text', 'name' => 'ODESL_STAT', 'label' => 'Stát', 'size' => 42),
		array( 'type' => 'text', 'name' => 'ODESL_JINE', 'label' => 'Jiné', 'size' => 42,'tooltip' => 'Zapište například zahraniční PSČ, oblast státu, aj.'),
),

		'visible'=>$is_edit || $is_insert || $is_new || $is_info || $is_filter_all,
		'label' => 'Stát:',
);



$FORM_CONFIG['schema'][] = array('elements'=>array(
    array( 'type' => 'text', 'name' => 'ODESL_REKOMANDO', 'size' => '20', 'label' => 'Rekomando'),
    array( 'type' => 'text', 'name' => 'ODESL_POSTAODESL', 'size' => '15', 'label' => 'Odesílací pošta'),
  ),

  'visible'=>($GLOBALS['ODESLANA_POSTA']=='f' || $is_insert),
  'label' => 'Adresa:',
);

$FORM_CONFIG['schema'][] = array('elements'=>array(
    array( 'type' => 'button', 'name' => 'Adresar', 'value' => 'Adresář', 'onclick' => 'JMENO()', 'label' => 'Adresář', 'tooltip' => 'test'),
    array( 'type' => 'button', 'name' => 'Ares', 'value' => 'ARES', 'onclick' => 'ARES()', 'label' => 'ARES', 'tooltip' => 'test'),
//    array( 'type' => 'button', 'name' => 'Jmeno', 'value' => 'ISZR', 'onclick' => 'Iszr()', 'label' => 'ISZR'),
    array( 'type' => 'button', 'name' => 'PSČ', 'value' => 'PSČ', 'onclick' => 'PSC()', 'label' => 'PSČ'),
    array( 'type' => 'button', 'name' => 'DS', 'value' => 'ISDS', 'onclick' => 'Datovka()', 'label' => 'ISDS'),
    array( 'type' => 'button', 'name' => 'Vyčistit', 'value' => 'Vyčistit', 'onclick' => 'Smazat()', 'label' => 'Smazat'),
  ),
  'visible'=>$is_edit || $is_insert || $is_new,
  'label' => 'Adresa:',
);


/*
if ($is_info) {
  
  $text= UkazAdresu($GLOBALS[ID],'<br/>');
  $text.=($GLOBALS[ODESL_DATSCHRANKA])?'<br/>Dat. schránka: '.$GLOBALS[ODESL_DATSCHRANKA]:'';

  $FORM_CONFIG['schema'][] = array('elements'=>array(
              array( 'type' => 'text', 'name' => 'ADRESA', 'value' => $text),
            ),
            'label' => 'Adresa:');

  $FORM_CONFIG['schema'][] = array('elements'=>array(
            array( 'type' => 'text', 'name' => 'ODESL_REKOMANDO', 'size' => '20', 'label' => 'Rekomando'),   
            array( 'type' => 'text', 'name' => 'ODESL_POSTAODESL', 'size' => '15', 'label' => 'Odesílací pošta')),
            'format'=>"ODESL_REKOMANDO...'&nbsp;&nbsp;&nbsp;Odesílací pošta&nbsp;'...ODESL_POSTAODESL",
      );
}



*/