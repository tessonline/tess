<?php
require_once(FileUp2('.admin/config.inc'));
Include_once(FileUp2('.admin/form_func.inc'));
Include_once(FileUp2('.admin/table_funkce_denik.inc'));
Include_once(FileUp2('.admin/table_funkce_obj.inc'));
Include_once(FileUp2('.admin/oth_funkce.inc'));
Include_once(FileUp2('.admin/security_name.inc'));

If ($GLOBALS['CONFIG']['UPLOAD_NAS']) {
 Include_once(FileUp2('.admin/table_func_upload.inc'));
}

$TABLE_CONFIG['callback'] = 'ChangeClassBarva';

$TABLE_CONFIG['schema'][] = array( 
  field => 'Ukaz(ODESLANA_POSTA)',
  width => '1%',
  label => 'směr',
  'class' => $GLOBALS['barva_sipky'],
  ident => 'smer',
  settings => 'default'
);
If ($GLOBALS['CONFIG']['SHOW_TABLE_EV_CISLO']) {
  $TABLE_CONFIG['schema'][] = array( 
    field => "'<i><font size = 1>'...tableBarcode(ID)...'</font></i>'",
    label => 'ID',
    width => '4%',
    order_by => 'EV_CISLO',
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
  order_by => 'cislo_spisu2 asc, cislo_spisu1 asc, podcislo_spisu asc',
  width => '4%',
  add => 'NOWRAP',
  ident => 'SIS',
  settings => 'default'
);


If ($GLOBALS[CONFIG][DB] == 'psql') {
  $TABLE_CONFIG['schema'][] = array( 
    field => 'DatumPrijeti(DATUM_PODATELNA_PRIJETI)',
    label => 'Datum',
    order_by => '(DATUM_PODATELNA_PRIJETI, \'FMDD.FMMM.YYYY\') asc ',
    width => '4%',
    add => 'NOWRAP',
    ident => 'PRIJETI',
    settings => 'default'
  );
}
If ($GLOBALS[CONFIG][DB] == 'mssql') {
  $TABLE_CONFIG['schema'][] = array( 
    field => 'DatumPrijeti(DATUM_PODATELNA_PRIJETI)',
    label => 'Datum',
    order_by => 'CONVERT(datetime, datum_podatelna_prijeti, 104) asc ', 
    width => '4%',
    ident => 'PRIJETI',
    settings => 'default'
  );
}

$TABLE_CONFIG['schema'][] = array( 
  field => 'DatumVyrizeni(LHUTA_VYRIZENI)',
  label => 'K vyřízení do',
  order_by => 'LHUTA_VYRIZENI asc ',
  width => '4%',
  add => 'NOWRAP',
  ident => 'VYRIZENI'
);

$TABLE_CONFIG['schema'][] = array( 
  field => "Ukaz2(ODES_TYP, ZPUSOB_PODANI, VLASTNICH_RUKOU)...'&nbsp;'...UkazJmeno()",
  label => 'Odesílatel/Adresát',
  order_by => 'odesl_prijmeni asc, odesl_jmeno asc',
  width => '35%',
  ident => 'JMENO',
  settings => 'default'
);

$TABLE_CONFIG['schema'][] = array( 
  field => "JEJICH_CJ...'<br/>'...JEJICH_CJ_DNE",
  label => 'Vaše čj/ze dne',
  order_by => 'jejich_cj asc',
  width => '10%',
  ident => 'JEJICH_CJ',
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
  'field' => 'ShowTypPosty(TYP_POSTY)',
  label => 'Věcná klasifikace',
  add => 'align = center',
  'width' => '10%',
  ident => 'TYPPOSTY'
);

$TABLE_CONFIG['schema'][] = array( 
  'field' => 'ShowJine(JINE)',
  label => 'Věcná fáze',
  add => 'align = center',
  'width' => '10%',
  ident => 'JINE'
);

$TABLE_CONFIG['schema'][] = array( 
  field => 'tableSpisUzel(ID)',
  label => $GLOBALS['CONFIG']['NAZEV_TABLE_ODBOR'],
  add => 'align = center',
  order_by => 'u.group_id asc,u.lname asc, u.fname asc, p.id',
  width => '4%',
  ident => 'ODBOR',
  settings => 'default');

$TABLE_CONFIG['schema'][] = array( 
  field => 'tableZpracovatel(ID)',
  label => $GLOBALS['CONFIG']['NAZEV_TABLE_REFERENT'],
  add => "align = left style = 'padding:0 0.3em' NOWRAP'",
  order_by => 'u.lname asc, u.fname asc, p.id',
  width => '10%',
  ident => 'REFERENT',
  settings => 'default'
);

$TABLE_CONFIG['schema'][] = array( 
  field => "tableSpisUzel(ID)...'<br/>'...tableZpracovatel(ID)",
  label => 'Vyřizuje',
  add => "'align = left style = 'padding:0 0.3em' NOWRAP'",
  order_by => 'u.group_id asc,u.lname asc, u.fname asc, p.id',
  width => '10%',
  ident => 'ODBREF'
);

$TABLE_CONFIG['schema'][] = array( 
  field => 'Vyrizeno(VYRIZENO, SPIS_VYRIZEN)',
  label => 'Vyřízeno',
  add => 'align = center',
  'width' => '10%',
  ident => 'VYRIZENO',
  settings => 'default'
);
  
$TABLE_CONFIG['schema'][] = array( 
  field => 'SpisovaZnacka(ID)',
  label => 'Spisový znak',
  add => 'align = center',
  'width' => '10%',
  ident => 'SPZNACKA',
  settings => 'default'
);
  
$TABLE_CONFIG['schema'][] = array( 
  field => 'UlozenoVeSpisovne(ID)',
  label => 'Uloženo ve spisovně',
  add => 'align = center',
  'width' => '10%',
  ident => 'SPISOVNA'
);
  
$TABLE_CONFIG['schema'][] = array( 
  field => 'spisForma(ID)',
  label => 'Uložení',
  add => 'align = center',
  'width' => '1%',
  ident => 'SPISFORMA',
  settings => 'default'
);

$TABLE_CONFIG['schema'][] = array( 
  field => 'spisListuADigitalnich(ID)',
  label => 'Listů/Dig.',
  add => 'align = center',
  'width' => '1%',
  ident => 'SPISLISTU',
  settings => 'default'
);

$TABLE_CONFIG['schema'][] = array(
  field => 'spisVyber(ID)',
  label => 'Výběr<br/>Vyřazení',
  add => 'align = center',
  'width' => '1%',
  ident => 'SPISVYBER',
  settings => 'default'
);

$TABLE_CONFIG['schema'][] = array( 
  field => 'UklZnacka(ID)',
  label => 'Ukládací značka',
  add => 'align = center',
  'width' => '10%',
  ident => 'UKLZNACKA'
);
  
$TABLE_CONFIG['schema'][] = array( 
  field => 'ShowStatus(STATUS)',
  label => 'Stav',
  add => 'align = center',
  'width' => '10%',
  ident => 'STATUS',
  settings => 'default'
);


If (($GLOBALS['CONFIG']['UPLOAD_NAS']) && $GLOBALS['ukaz_ovladaci_prvky']) {
  $TABLE_CONFIG['schema'][] = array(
    field => "upload_files(ID, '0', '0', '0')",
    label => '&nbsp;',
    'class' => 'image',
    'width' => '1px',
    ident => 'OVL1'
  );
}
If ($GLOBALS['CONFIG']['ZAPNOUT_VLASTNI_UPLOAD'] && $GLOBALS['ukaz_ovladaci_prvky']) {
  $TABLE_CONFIG['schema'][] = array(
    field => 'ExistujeSoubor(ID, CISLO_JEDNACI1, CISLO_JEDNACI2)',
    label => '&nbsp;',
    'class' => 'image',
    'width' => '1px',
    ident => 'OVL2'
  );
}
if ($GLOBALS[CONFIG][TWIST_UPLOAD]) {
  $TABLE_CONFIG['schema'][] = array( 
    field => 'ShowUploadPosta(ID)',
    label => 'Přílohy',
    add => 'align = center',
    'width' => '1%',
    'class' => 'image',
    ident => 'upload',
    settings => 'default'
  );
}

$TABLE_TOP_MENU['style'] = 'html'; //anchor
$TABLE_TOP_MENU['schema'] = array(
  array(
    'html' => '&nbsp;&nbsp;&nbsp;<input type = \'button\' id = \'various5\' href = \'set.php\' value = \'Nastavení\' class = \'button\'>'
  ),
);

$TABLE_CONFIG['ident_array'] = array(

    0 => array('Vyberte'),
    1 => array('standardní','smer','SIS','PRIJETI','JMENO','VEC','ODBREF','VYRIZENO','SPZNACKA','SPISOVNA','UKLZNACKA',
               'STATUS','SPISFORMA','upload'),
    2 => array('dle vyhlášky', 'smer','CK','SIS','PRIJETI','JMENO','JEJICH_CJ','VEC','ODBOR','REFERENT','VYRIZENO',
               'SPZNACKA','SPISFORMA','SPISLISTU','SPISVYBER','upload'),
    3 => array('podatelna', 'smer','SIS','PRIJETI','JMENO','JEJICH_CJ','VEC','ODBOR','REFERENT','VYRIZENO','STATUS',
               'SPISFORMA','upload'),
    4 => array('klasifikace', 'smer','SIS','PRIJETI','VEC','TYPPOSTY','JINE','ODBOR','REFERENT'),
    5 => array('vyřizování','smer','SIS','PRIJETI','VYRIZENI','JMENO','VEC','ODBREF','VYRIZENO','SPZNACKA','UKLZNACKA',
               'STATUS','SPISFORMA','upload'),
    6 => array('ukládání','smer','SIS','PRIJETI','VEC','ODBREF','VYRIZENO','UKLZNACKA','STATUS','SPISFORMA','SPISLISTU',
               'upload'),
    7 => array('spisovna','smer','SIS','PRIJETI','VEC','ODBREF','SPZNACKA','UKLZNACKA','STATUS','SPISFORMA','SPISLISTU',
               'upload'),
    8 => array('skartace','CK','SIS','PRIJETI','VEC','ODBOR','REFERENT','SPZNACKA','STATUS','SPISFORMA','SPISLISTU',
               'SPISVYBER','upload'),
);


?>
<iframe id = 'ifrm_get_value' name = 'ifrm_get_value' style = 'position:absolute;z-index:0;left:0;top:0;visibility:hidden' src = 'cis.php'></iframe>
