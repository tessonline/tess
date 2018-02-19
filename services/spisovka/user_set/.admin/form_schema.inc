<?php

$GLOBALS['USER_SETTINGS'] = 1;

$FORM_CONFIG = array(
  'theme_config' => array(
    'square' => array(
      'theme' => array(
        'columns' => true
      ),
    )
  )
);


if ($GLOBALS['CAST'] == 1) {
$FORM_CONFIG['schema'][] = array(
  'label' => 'Základní nastavení',
  'visible' => true,
  'theme_config' => array(
    'square' => array(
      'theme' => array(
        'column' => 1,
      )
    )
  )
);
	$FORM_CONFIG['schema'][] = array('elements'=>array(
			array(
					'type' => 'button',
					'name' => 'NastavCjButton',
					'value' => 'Vrátit do původního nastavení',
					'onclick' => 'document.frm_edit.SET_DEFAULT.value=1;frm_edit.submit()',
					'label' => 'Vrátit do původního nastavení',
					'tooltipNOTLOAD' => 'test'),
	),
	);
	
	
	if (!$GLOBALS['CONFIG_POSTA_DEFAULT']['DEFAULT_TABLE_SCHEMA']) {
		include(FileUp2('posta/.admin/table_schema.inc'));
		$vysl_schema = array();
		foreach ($TABLE_CONFIG['schema'] as $schema) {
			$vysl_schema[] = $schema['ident'];
		}
		$GLOBALS['CONFIG_POSTA_DEFAULT']['DEFAULT_TABLE_SCHEMA'] = $vysl_schema;
	}
	
	if (!$GLOBALS['CONFIG_POSTA_DEFAULT']['DEFAULT_TABLE_SCHEMA_SPIS']) {
		include(FileUp2('posta/.admin/table_schema_spis.inc'));
		$vysl_schema = array();
		foreach ($TABLE_CONFIG['schema'] as $schema) {
			$vysl_schema[] = $schema['ident'];
		}
		$GLOBALS['CONFIG_POSTA_DEFAULT']['DEFAULT_TABLE_SCHEMA_SPIS'] = $vysl_schema;
	}
	
	
	$GLOBALS['SKRYT_STORNOVANO'] = $GLOBALS['CONFIG_POSTA_DEFAULT']['SKRYT_STORNOVANO'] ? $GLOBALS['CONFIG_POSTA_DEFAULT']['SKRYT_STORNOVANO'] : 0;
	$GLOBALS['SKRYT_VYRAZENE'] = $GLOBALS['CONFIG_POSTA_DEFAULT']['SKRYT_VYRAZENE'] ? $GLOBALS['CONFIG_POSTA_DEFAULT']['SKRYT_VYRAZENE'] : 0;
	$GLOBALS['UKAZOVAT_OBALKY'] = $GLOBALS['CONFIG_POSTA_DEFAULT']['UKAZOVAT_OBALKY'] ? $GLOBALS['CONFIG_POSTA_DEFAULT']['UKAZOVAT_OBALKY'] : 0;
	$GLOBALS['UKAZAT_FILTR_V_DETAILU'] = $GLOBALS['CONFIG_POSTA_DEFAULT']['UKAZAT_FILTR_V_DETAILU'] ? $GLOBALS['CONFIG_POSTA_DEFAULT']['UKAZAT_FILTR_V_DETAILU'] : 0;
	
	$GLOBALS['SKRYT_VE_SPISOVNE'] = $GLOBALS['CONFIG_POSTA_DEFAULT']['SKRYT_VE_SPISOVNE'] ? $GLOBALS['CONFIG_POSTA_DEFAULT']['SKRYT_VE_SPISOVNE'] : 0;

	$GLOBALS['NEZASILAT_EMAILY'] = $GLOBALS['CONFIG_POSTA_DEFAULT']['NEZASILAT_EMAILY'] ? $GLOBALS['CONFIG_POSTA_DEFAULT']['NEZASILAT_EMAILY'] : 0;
	$GLOBALS['DEFAULT_STAV'] = $GLOBALS['CONFIG_POSTA_DEFAULT']['DEFAULT_STAV'];
	
	$GLOBALS['NA_STRANKU'] = $GLOBALS['CONFIG_POSTA_DEFAULT']['NA_STRANKU'];
	
	
	$GLOBALS['UKAZAT_BAREVNY_FILTR'] = $GLOBALS['CONFIG_POSTA_DEFAULT']['UKAZAT_BAREVNY_FILTR'] ? $GLOBALS['CONFIG_POSTA_DEFAULT']['UKAZAT_BAREVNY_FILTR'] : 0;
	
	
	$FORM_CONFIG['schema'][] = array( 'elements' => array(
			array( 'type' => 'hidden', 'name' => 'SET_DEFAULT','value' => '0'),
			array( 'type' => 'checkbox', 'name' => 'SKRYT_STORNOVANO','tooltipNOTLOAD' => 'Při zaškrtnutí se nebudou v přehledového tabulce zobrazovat stornované dokumenty')),
			'label' => 'Skrýt stornované dokumenty');
	
	$FORM_CONFIG['schema'][] = array( 'elements' => array(
			array( 'type' => 'checkbox', 'name' => 'SKRYT_VYRAZENE','tooltipNOTLOAD' => 'Při zaškrtnutí se nebudou v přehledového tabulce zobrazovat vyřazené dokumenty. Jedná se zejména o dokumenty, které byly předány do archivu nebo skartovány.')),
			'label' => 'Skrýt vyřazené dokumenty');
	
	$FORM_CONFIG['schema'][] = array( 'elements' => array(
			array( 'type' => 'checkbox', 'name' => 'SKRYT_VE_SPISOVNE')),
			'label' => 'Skrýt dokumenty ve spisovně');
	
	
	$FORM_CONFIG['schema'][] = array( 'elements' => array(
			array( 'type' => 'checkbox', 'name' => 'UKAZAT_FILTR_V_DETAILU')),
			'label' => 'Zobrazovat filtr i v detailu čj.');
	
	$FORM_CONFIG['schema'][] = array( 'elements' => array(
			array(
        'type' => 'checkbox',
        'name' => 'UKAZOVAT_OBALKY',
        'add' => "onclick=\"showChecksTable(this)\";",
       )),
			'label' => 'Zobrazovat detaily čj. v přehledu');
	
	$FORM_CONFIG['schema'][] = array( 'elements' => array(
			array( 'type' => 'select_stavy_filtr', 'name' => 'DEFAULT_STAV')),
			'label' => 'Zobrazení výchozího stavu');
	
	
	$FORM_CONFIG['schema'][] = array( 'elements' => array(
			array( 'type' => 'text_number', 'name' => 'NA_STRANKU','minlength' => 1, 'maxlength' => 2, 'required'=>true)),
			'label' => 'Počet záznamů na stránce');
	
	
		$FORM_CONFIG['schema'][] = array( 'elements' => array(
				array( 'type' => 'checkbox', 'name' => 'UKAZAT_BAREVNY_FILTR')),
				'label' => 'Ukazovat rychlý filtr');

		$FORM_CONFIG['schema'][] = array( 'elements' => array(
				array( 'type' => 'checkbox', 'name' => 'NEZASILAT_EMAILY')),
				'label' => 'Vypnout e-mailové notifikace');

}


if ($GLOBALS['CAST'] == 1) {

	$FORM_CONFIG['schema'][] = array(
//	  'label' => 'Sloupce pro přehled čj.<br/><font size=-1><i>Lze vybrat jen, pokud je vypnutá volba <br/>"Zobrazovat detaily čj. v přehledu"</i></font>',
	  'label' => 'Sloupce pro přehled čj.',
	  'visible' => true,
	  'theme_config' => array(
	    'square' => array(
	      'theme' => array(
	        'column' => 1,
	      )
	    )
	  )
	);
	
	$count = count($FORM_CONFIG['schema']);
	
	$kod = '<table>';
	$TABLE_CONFIG = array();
	include(FileUp2('.admin/table_schema_settings.inc'));
	foreach ($TABLE_CONFIG['schema'] as $schema) {
	  $pocet = 1;
	
	  if ($schema['settings'] == 'function') {
	    $FORM_CONFIG['schema'][]['elements'][] = array(
	      'type' => 'hidden',
	      'name' => 'TABLE[' .$schema['ident'].']',
	      'label' => $schema['label'],
	      'value' => 1,
	    );
	  }
	  else {
	    $checked = false;
	    if (in_array($schema['ident'], $GLOBALS['CONFIG_POSTA_DEFAULT']['DEFAULT_TABLE_SCHEMA'])) $checked = true;
	    $FORM_CONFIG['schema'][]['elements'][] = array(
	      'type' => 'checkbox',
	      'name' => 'TABLE[' .$schema['ident'].']',
	      'label' => $schema['label'],
	      'value' => $checked,
	    );
	  }
	
	}
	$FORM_CONFIG['schema'][] = array(
	  'label' => 'Sloupce pro detail čj.',
	  'visible' => true,
	  'theme_config' => array(
	    'square' => array(
	      'theme' => array(
	        'column' => 2,
	      )
	    )
	  )
	);
	
	$count = count($FORM_CONFIG['schema']);
	
	$kod = '<table>';
	reset($TABLE_CONFIG['schema']);
	foreach ($TABLE_CONFIG['schema'] as $schema) {
	  $pocet = 1;
	
	  if ($schema['settings'] == 'function') {
	    $FORM_CONFIG['schema'][]['elements'][] = array(
	      'type' => 'hidden',
	      'name' => 'TABLE_SPIS[' .$schema['ident'].']',
	      'label' => $schema['label'],
	      'value' => 1,
	    );
	  }
	  else {
	    $checked = false;
	    if (in_array($schema['ident'], $GLOBALS['CONFIG_POSTA_DEFAULT']['DEFAULT_TABLE_SCHEMA_SPIS'])) $checked = true;
	    $FORM_CONFIG['schema'][]['elements'][] = array(
	      'type' => 'checkbox',
	      'name' => 'TABLE_SPIS[' .$schema['ident'].']',
	      'label' => $schema['label'],
	      'value' => $checked,
	    );
	  }
	
	}
}