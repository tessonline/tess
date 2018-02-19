<script language="JavaScript" type="text/javascript">
<!--
function Prevod_zpet(script){
  frm=document.frm_posta;
  var act = frm.action;
  var tar = frm.target;
  frm.SELECT_ID_USE_FILTERposta.value=1;
  frm.action=script;
  //frm.target='_blank';
  //frm.target=NewWindowObecne(script+'?cacheid=','Prevod_zpet',300,350);
  frm.submit();
  frm.action=act;
  frm.target=tar;
  frm.SELECT_ID_USE_FILTERposta.value=0;
}
//-->
</script>
<?php
$path_historie = GetAgendaPath('KOL_STAVBA', false, true);
      $TABLE_TOP_MENU["schema"]["show_urovne"] = array(
        "label"=>"Z historie",
        "url"=>"javascript:Prevod_zpet('prevod_zpet.php');",
        //"url"=>"javascript:NewWindowObecne('".$path_historie."/prevod_zpet.php?KROK=1&ID_STAVBA=".$id_most."&cacheid=','Parcela1',600,800);",
        "title"=>"Převod vybraných záznamů zpět z historie",
      );

require_once(FileUp2('.admin/config.inc'));
Include_once(FileUp2('.admin/form_func.inc'));
//Include_once(FileUp2('.admin/table_funkce_obj.inc'));
Include_once(FileUp2('.admin/table_funkce_denik.inc'));
Include_once(FileUp2('.admin/oth_funkce.inc'));
Include_once(FileUp2('.admin/security_name.inc'));

$TABLE_CONFIG["callback"] = 'ChangeClassPosta';

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
  order_by => '(DATUM_PODATELNA_PRIJETI, \'FMDD.FMMM.YYYY\') asc ',
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
  field => 'VEC',
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



$TABLE_CONFIG['syscolumns'] = array(
 'upload' => array ('theme'=>array('dropdown'=>true, 'column'=>true)),
 'edit' => array ('theme'=>array('dropdown'=>true, 'column'=>true)),
 'delete' => array ('theme'=>array('dropdown'=>true, 'column'=>true)),
);


/*
$TABLE_TOP_MENU['style'] = 'html'; //anchor
$TABLE_TOP_MENU['schema'] = array(
  array(
    'html' => '&nbsp;&nbsp;&nbsp;<input type = \'button\' id = \'various5\' href = \'set.php\' value = \'Nastavení\' class = \'button\'>'
  ),
);

*/