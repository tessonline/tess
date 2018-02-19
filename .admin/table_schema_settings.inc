<?php
reset ($GLOBALS["CONFIG_POSTA"]["PLUGINS"]);
foreach($GLOBALS["CONFIG_POSTA"]["PLUGINS"] as $plug_name => $plug) {
  if ($plug['enabled']){
    $file = FileUp2('plugins/'.$plug['dir'].'/.admin/table_schema_settings_start.inc');
		if (File_Exists($file)) include($file);
  }
}
$TABLE_CONFIG['schema'][] = array(
  field => 'Ukaz(ODESLANA_POSTA)',
  width => '1%',
  label => 'Směr',
  'class' => '',
  ident => 'smer',
  settings => 'default'
);


$TABLE_CONFIG['schema'][] = array(
//    field => "'<i><font size = 1>'...tableBarcode(ID)...'</font></i>'",
  field => "tableBarcode(ID)",
  label => 'JID',
  width => '4%',
  order_by => 'ID',
  ident => 'CK',
  settings => 'default'
);

$TABLE_CONFIG['schema'][] = array(
//    field => "'<i><font size = 1>'...tableBarcode(ID)...'</font></i>'",
  field => "EV_CISLO...'/'...ROK",
  label => 'Ev.číslo',
  width => '4%',
  order_by => 'rok asc, ev_cislo asc',
  ident => 'EV_CISLO',
);


$TABLE_CONFIG['schema'][] = array( 
  field => 'tableFormatCJednaci(ID, 1)',
  label => $GLOBALS['CONFIG']['CISLO_SPISU'] .', evidenční, spis',
  order_by => 'cislo_spisu2 asc, cislo_spisu1 asc, main_doc asc',
  width => '4%',
  add => 'NOWRAP',
  ident => 'SIS',
  settings => 'default'
);

$TABLE_CONFIG['schema'][] = array(
  field => 'tableFormatJenCJ(ID, 1)',
  label => $GLOBALS['CONFIG']['CISLO_SPISU'],
  order_by => 'cislo_spisu2 asc, cislo_spisu1 asc, main_doc asc',
  width => '4%',
  add => 'NOWRAP',
  ident => 'SIS1',
);

$TABLE_CONFIG['schema'][] = array(
  field => 'tableFormatJenSpis(ID, 1)',
  label => 'Spis',
  order_by => 'cislo_spisu2 asc, cislo_spisu1 asc, main_doc asc',
  width => '4%',
  add => 'NOWRAP',
  ident => 'SIS2',
);


$TABLE_CONFIG['schema'][] = array( 
  field => "DatumPrijeti(DATUM_PODATELNA_PRIJETI)...'<br/>'...DatumVyrizeni(LHUTA_VYRIZENI)",
  label => 'Datum&nbsp;přijetí,<br/>K&nbsp;vyřízení&nbsp;do',
  order_by => 'datum_podatelna_prijeti',
  width => '4%',
  add => 'NOWRAP',
  ident => 'PRIJETI',
  settings => 'default'
);

$TABLE_CONFIG['schema'][] = array( 
  field => "Ukaz2(ODES_TYP, ZPUSOB_PODANI, VLASTNICH_RUKOU)...'&nbsp;'...UkazJmeno()",
  label => 'Odesílatel, Adresát',
  order_by => 'odesl_prijmeni asc, odesl_jmeno asc',
  order_by => 'odesl_prijmeni asc, odesl_jmeno asc, odesl_ulice asc, odesl_posta asc, odesl_osoba asc',
  width => '35%',
  ident => 'JMENO',
  settings => 'default'
);

$TABLE_CONFIG['schema'][] = array( 
  field => "JEJICH_CJ...'<br/>'...JEJICH_CJ_DNE",
  label => $GLOBALS['CONFIG']['NAZEV_JEJICH_CJ_VYBER'].', ze dne',
  order_by => 'jejich_cj asc',
  width => '10%',
  ident => 'JEJICH_CJ',
  settings => 'default'
);

$TABLE_CONFIG['schema'][] = array( 
  field => 'tableVec(ID)',
  label => 'Věc',
  order_by => 'vec asc',
  width => '30%',
  ident => 'VEC',
  settings => 'default'
);

$TABLE_CONFIG['schema'][] = array(
  'field' => 'ShowTypPosty(TYP_POSTY)',
  label => $GLOBALS['CONFIG']['NAZEV_TYP_POSTY'],
  add => 'align = center',
  'width' => '10%',
  ident => 'TYPPOSTY'
);

$TABLE_CONFIG['schema'][] = array(
  field => 'tableSpisUzel(ID)',
  label => $GLOBALS['CONFIG']['NAZEV_TABLE_ODBOR'],
  add => 'align = center',
  order_by => 'o.zkratka asc',
  width => '4%',
  ident => 'ODBOR',
  settings => 'default');

$TABLE_CONFIG['schema'][] = array(
  field => 'tableZpracovatel(ID)',
  label => $GLOBALS['CONFIG']['NAZEV_TABLE_REFERENT'],
  add => "align = left style = 'padding:0 0.3em' NOWRAP'",
  order_by => 'lname asc,fname asc',
  width => '10%',
  ident => 'REFERENT',
  settings => 'default'
);
//
$TABLE_CONFIG['schema'][] = array( 
  field => "tableSpisUzel(ID, '1')...'<br/>'...tableZpracovatel(ID, '1')...tableVraceni(ID)",
  label => 'Vyřizuje',
  //add => "'align = left style = 'padding:0 0.3em' NOWRAP'",
//  order_by => 'u.group_id asc,u.lname asc, u.fname asc, p.id',
  order_by => 'o.zkratka asc,lname asc,fname asc',
  width => '10%',
  ident => 'ODBREF'
);

$TABLE_CONFIG['schema'][] = array(
  field => "DATUM_VYPRAVENI...'<br/>'...DATUM_DORUCENI",
  label => 'Dodáno/Doručeno',
  add => 'align = left',
  'width' => '1%',
  ident => 'VYPRAVDORUC',
  settings => 'default'
);

$TABLE_CONFIG['schema'][] = array(
  field => "tableDatovaZprava(ID)",
  label => 'ID DZ',
  add => 'align = left',
  'width' => '1%',
  ident => 'IDDZ',
  settings => 'default'
);

$TABLE_CONFIG['schema'][] = array(
  field => 'Vyrizeno(VYRIZENO, DATUM_VYRIZENI, SPIS_VYRIZEN)',
  label => 'Vyřízeno',
  add => 'align = center',
  'width' => '1%',
  ident => 'VYRIZENO',
  settings => 'default'
);

$TABLE_CONFIG['schema'][] = array(
  field => 'SpisovaZnacka(ID)',
  label => 'Spisový znak',
  add => 'align = center',
  'width' => '10%',
  'order_by' => 'vs.priorita asc',
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
  label => 'Skartační znak',
  add => 'align = center',
  'order_by' => 'vs.skar_znak asc',
  'width' => '1%',
  ident => 'SPISVYBER',
  settings => 'default'
);

$TABLE_CONFIG['schema'][] = array(
  field => 'ShowStatus(STATUS)',
  label => 'Stav',
  add => 'align = center',
  'width' => '10%',
  ident => 'STATUS',
  'order_by' => 'status_text',
  settings => 'default'
);

if (HasRole('muze-kopii-podcislo')) {
  $TABLE_CONFIG['schema'][] = array(
    field => 'KopieDokumentu2(ID)',
    label => ' ',
    add => 'align = center',
    'width' => '1%',
    'class' => 'image',
    ident => 'kopie',
    'add' => 'NOWRAP',
    settings => 'function',
    'theme' => array(
      'dropdown'=>true,
      'column'=>true
    ),
  );

}
$TABLE_CONFIG['schema'][] = array(
  field => 'KopieDokumentu(ID)',
  label => ' ',
  add => 'align = center',
  'width' => '1%',
  'class' => 'image',
  ident => 'kopie',
  'add' => 'NOWRAP',
  settings => 'function',
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
  settings => 'function',
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
    settings => 'function',
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
  settings => 'function',
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
  settings => 'function',
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
  settings => 'function',
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
  settings => 'function',
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
  settings => 'function',
  'theme' => array(
    'dropdown'=>true,
    'column'=>true
  ),
);

if ($GLOBALS["CONFIG"]["VNITRNI_POSTA"] || $GLOBALS["CONFIG"]["PREDANI_KOLEGOVI"])
$TABLE_CONFIG['schema'][] = array(
  field => 'UkazVnitrniPostu(ID)',
  label => ' ',
  add => 'align = center',
  'width' => '1%',
  'class' => 'image',
  ident => 'odpovedi',
  'add' => 'NOWRAP',
  settings => 'function',
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
  settings => 'function',
  'theme' => array(
    'dropdown'=>true,
    'column'=>true
  ),
);


/*
$TABLE_CONFIG['schema'][] = array(
  field => 'UkazSchvalovani(ID)',
  label => ' ',
  add => 'align = center',
  'width' => '1%',
  'class' => 'image',
  ident => 'schvalovani',
  'add' => 'NOWRAP',
  settings => 'function',
  'theme' => array(
    'dropdown'=>true,
    'column'=>true
  ),
);

$TABLE_CONFIG['schema'][] = array(
  field => 'PamKatalog(ID, DALSI_ID_AGENDA)',
  width => '1%',
  label => '',
  'class' => 'image',
  ident => 'PK',
  settings => 'function',
);

*/
reset ($GLOBALS["CONFIG_POSTA"]["PLUGINS"]);
foreach($GLOBALS["CONFIG_POSTA"]["PLUGINS"] as $plug_name => $plug) {
  if ($plug['enabled']){
    $file = FileUp2('plugins/'.$plug['dir'].'/.admin/table_schema_settings_end.inc');
		if (File_Exists($file)) include($file);
  }
}
 

if (HasRole('spravce')) {
  $TABLE_TOP_MENU["schema"][] = array(
    "label"=>"Export dat do XML",
    "url"=>"javascript:RunScript_Tisk('/ost/posta/exportXML.php','".$table_params['tablename']."')",
    "Xtarget"=>"_blank",
    "title"=>"Export dat do XML"
    
  );
  /*$TABLE_TOP_MENU["schema"][] = array(
      array("label"=>"Export dat do XML",  "url"=>"javascript:RunScript_Tisk('/ost/posta/exportXML.php','".$table_params['tablename']."')", "Xtarget"=>"_blank", "title"=>"Export dat do XML"),
  );*/

  echo "
  <script type=\"text/javascript\">
    function RunScript_Tisk(name_script, tablename){;
      var frm = document.forms['frm_'+tablename];
      frm.method='POST';
      window.open(name_script,'tisk','height=260,width=470,left=50,top=50,scrollbars,resizable');
      var act = frm.action;
      var tar = frm.target;
      //if(frm.SELECT_ID_USE_FILTER) frm.SELECT_ID_USE_FILTER.value='1';
      frm.action = name_script;
      frm.target = 'tisk';
      frm.submit();
      frm.action = act;
      frm.target = tar;
      //if(frm.SELECT_ID_USE_FILTER) frm.SELECT_ID_USE_FILTER.value='0';
    }
  </script>
  ";

}

