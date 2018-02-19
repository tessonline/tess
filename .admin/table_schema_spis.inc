<?php
require_once(FileUp2('.admin/config.inc'));
Include_once(FileUp2('.admin/form_func.inc'));
//Include_once(FileUp2('.admin/table_funkce_obj.inc'));
Include_once(FileUp2('.admin/table_funkce_denik.inc'));
Include_once(FileUp2('.admin/oth_funkce.inc'));
Include_once(FileUp2('.admin/security_name.inc'));

//$TABLE_CONFIG["callback"] = 'ChangeClassPosta';

$TABLE_CONFIG['schema'][] = array(
  field => 'Ukaz(ODESLANA_POSTA)',
  width => '1%',
  label => 'směr',
  'class' => '',
  ident => 'smer',
  settings => 'default'
);
If ($GLOBALS['CONFIG']['SHOW_TABLE_EV_CISLO']) {
  $TABLE_CONFIG['schema'][] = array( 
//    field => "'<i><font size = 1>'...tableBarcode(ID)...'</font></i>'",
    field => "tableBarcode(ID)",
    label => 'JID',
    width => '4%',
    order_by => 'ID',
    ident => 'CK',
    settings => 'default'
  );
}

If ($GLOBALS['CONFIG']['SHOW_TABLE_C_JEDNACI']) {
  $TABLE_CONFIG['schema'][] = array(
    field => 'FormatCJednaci(ID)',
    label => $GLOBALS['CONFIG']['JEDNACI_CISLO'],
    order_by => 'cislo_jednaci2 asc,  cislo_jednaci1 asc',
    width => '4%',
    add => 'NOWRAP align=center',
    ident => 'CJ',
    settings => 'default'
  );
}

$TABLE_CONFIG['schema'][] = array( 
  field => 'tableFormatCJednaci(ID, 1)',
  label => $GLOBALS['CONFIG']['CISLO_SPISU'],
  order_by => 'cislo_spisu2 asc, cislo_spisu1 asc, main_doc asc',
  width => '4%',
  add => 'NOWRAP',
  ident => 'SIS',
  settings => 'default'
);


$TABLE_CONFIG['schema'][] = array( 
  field => 'DatumPrijeti(DATUM_PODATELNA_PRIJETI)',
  label => 'Datum',
  order_by => 'datum_podatelna_prijeti',
  width => '4%',
  add => 'NOWRAP',
  ident => 'PRIJETI',
  settings => 'default'
);

$TABLE_CONFIG['schema'][] = array( 
  field => "Ukaz2(ODES_TYP, ZPUSOB_PODANI, VLASTNICH_RUKOU)...'&nbsp;'...UkazJmeno()",
  label => 'Odesílatel/Adresát',
  order_by => 'odesl_prijmeni asc, odesl_jmeno asc, odesl_ulice asc, odesl_posta asc, odesl_osoba asc',
  width => '35%',
  ident => 'JMENO',
  settings => 'default'
);

$TABLE_CONFIG['schema'][] = array( 
  field => 'tableVec(ID)',
  label => 'Věc',
  order_by => 'vec',
  width => '30%',
  ident => 'VEC',
  settings => 'default'
);

$TABLE_CONFIG['schema'][] = array( 
  field => "tableSpisUzel(ID)...'<br/>'...tableZpracovatel(ID)...tableVraceni(ID)",
  label => 'Vyřizuje',
  add => "'align = left style = 'padding:0 0.3em' NOWRAP'",
  order_by => 'u.group_id asc,u.lname asc, u.fname asc, p.odbor asc, p.id asc',
  width => '10%',
  ident => 'ODBREF'
);

$TABLE_CONFIG['schema'][] = array(
  field => 'ShowStatus(STATUS)',
  label => 'Stav',
  add => 'align = center',
  order_by => 'status',
  'width' => '10%',
  ident => 'STATUS',
  settings => 'default'
);

$TABLE_CONFIG['schema'][] = array(
  field => 'Razitko(ID)',
  label => ' ',
  add => 'align = center',
  'width' => '1%',
  'class' => 'image',
  ident => 'razitko',
  'add' => 'NOWRAP',
  settings => 'default',
  'theme' => array(
    'dropdown'=>true,
    'column'=>true
  ),
);


$TABLE_CONFIG['schema'][] = array(
  field => 'KopieDokumentu(ID)',
  label => ' ',
  add => 'align = center',
  'width' => '1%',
  'class' => 'image',
  ident => 'kopie',
  'add' => 'NOWRAP',
  settings => 'default',
  'theme' => array(
    'dropdown'=>true,
    'column'=>true
  ),
);

$TABLE_CONFIG['schema'][] = array(
  field => 'Precteno(ID, REFERENT)',
  label => ' ',
  add => 'align = center',
  'width' => '1%',
  'class' => 'image',
  ident => 'precteno',
  'add' => 'NOWRAP',
  settings => 'default',
  'theme' => array(
    'dropdown'=>true,
    'column'=>true
  ),
);

If ($GLOBALS["CONFIG"]["VRACENI_NA_PODATELNU"]) {
  $TABLE_CONFIG['schema'][] = array(
    field => 'VraceniPodatelna(ID, REFERENT)',
    label => ' ',
    add => 'align = center',
    'width' => '1%',
    'class' => 'image',
    ident => 'precteno',
    'add' => 'NOWRAP',
    settings => 'default',
    'theme' => array(
      'dropdown'=>true,
      'column'=>true
    ),
  );
}
$TABLE_CONFIG['schema'][] = array(
  field => 'Odmitnout(ID, REFERENT)',
  label => ' ',
  add => 'align = center',
  'width' => '1%',
  'class' => 'image',
  ident => 'precteno',
  'add' => 'NOWRAP',
  settings => 'default',
  'theme' => array(
    'dropdown'=>true,
    'column'=>true
  ),
);

$TABLE_CONFIG['schema'][] = array(
  field => 'Razitko(ID)',
  label => ' ',
  add => 'align = center',
  'width' => '1%',
  'class' => 'image',
  ident => 'razitko',
  'add' => 'NOWRAP',
  settings => 'default',
  'theme' => array(
    'dropdown'=>true,
    'column'=>true
  ),
);

$TABLE_CONFIG['schema'][] = array(
  field => 'Dalsi_Precteno(ID, REFERENT)',
  label => ' ',
  add => 'align = center',
  'width' => '1%',
  'class' => 'image',
  ident => 'precteno2',
  'add' => 'NOWRAP',
  settings => 'default',
  'theme' => array(
    'dropdown'=>true,
    'column'=>true
  ),
);

$TABLE_CONFIG['schema'][] = array(
  field => 'SouborPodpis(ID, REFERENT)',
  label => ' ',
  add => 'align = center',
  'width' => '1%',
  'class' => 'image',
  ident => 'precteno3',
  'add' => 'NOWRAP',
  settings => 'default',
  'theme' => array(
    'dropdown'=>true,
    'column'=>true
  ),
);
/*
$TABLE_CONFIG['schema'][] = array(
  field => 'Odeslani(ID, REFERENT)',
  label => ' ',
  add => 'align = center',
  'width' => '1%',
  'class' => 'image',
  ident => 'DSodeslani',
  'add' => 'NOWRAP',
  settings => 'default',
  'theme' => array(
    'dropdown'=>true,
    'column'=>true
  ),
);
*/
$TABLE_CONFIG['schema'][] = array(
  field => 'UkazOdpoved(ID)',
  label => ' ',
  add => 'align = center',
  'width' => '1%',
  'class' => 'image',
  ident => 'odpovedi',
  'add' => 'NOWRAP',
  settings => 'default',
  'theme' => array(
    'dropdown'=>true,
    'column'=>true
  ),
);

$TABLE_CONFIG['schema'][] = array(
  field => 'UkazVnitrniPostu(ID)',
  label => ' ',
  add => 'align = center',
  'width' => '1%',
  'class' => 'image',
  ident => 'odpovedi',
  'add' => 'NOWRAP',
  settings => 'default',
  'theme' => array(
    'dropdown'=>true,
    'column'=>true
  ),
);
/*
$TABLE_CONFIG['schema'][] = array(
  field => 'PluginsTable(ID, REFERENT)',
  label => ' ',
  add => 'align = center',
  'width' => '1%',
  'class' => 'image',
  ident => 'precteno4',
  'add' => 'NOWRAP',
  settings => 'default',
  'theme' => array(
    'dropdown'=>true,
    'column'=>true
  ),
);

*/
reset ($GLOBALS["CONFIG_POSTA"]["PLUGINS"]);
foreach($GLOBALS["CONFIG_POSTA"]["PLUGINS"] as $plug_name => $plug) {
  if ($plug['enabled']){
    $file = FileUp2('plugins/'.$plug['dir'].'/.admin/table_schema_end.inc');
		if (File_Exists($file)) include($file);
  }
}


$TABLE_CONFIG['syscolumns'] = array(
 'upload' => array ('theme'=>array('dropdown'=>true, 'column'=>true)),
 'edit' => array ('theme'=>array('dropdown'=>true, 'column'=>true)),
 'delete' => array ('theme'=>array('dropdown'=>true, 'column'=>true)),
);


//print_r($GLOBALS['CONFIG_POSTA_DEFAULT']['DEFAULT_TABLE_SCHEMA_SPIS']);
if ($GLOBALS['CONFIG_POSTA_DEFAULT']['DEFAULT_TABLE_SCHEMA_SPIS']) {
  if (!in_array('schvalovani', $GLOBALS['CONFIG_POSTA_DEFAULT']['DEFAULT_TABLE_SCHEMA_SPIS'])) $GLOBALS['CONFIG_POSTA_DEFAULT']['DEFAULT_TABLE_SCHEMA_SPIS'][] = 'schvalovani';
  if (count($GLOBALS['CONFIG_POSTA_DEFAULT']['DEFAULT_TABLE_SCHEMA_SPIS'])>0) {
  $TABLE_CONFIG['schema'] = array();
  $vysl_schema = array();
  include(FileUp2('.admin/table_schema_settings.inc'));
    foreach ($TABLE_CONFIG['schema'] as $schema) {
      if (in_array($schema['ident'], $GLOBALS['CONFIG_POSTA_DEFAULT']['DEFAULT_TABLE_SCHEMA_SPIS'])) {
        $vysl_schema[] = $schema;
      }
    }
  }
  $TABLE_CONFIG['schema'] = $vysl_schema;

}

