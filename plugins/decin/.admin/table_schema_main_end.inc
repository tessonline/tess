<?php
include_once(FileUpUrl('plugins/decin/.admin/table_func_decin.inc'));

//DECIN ma sve nastaveni sloupcu
$TABLE_CONFIG = array();

$TABLE_CONFIG['schema'][] = array(
  field => 'UkazDecin(ODESLANA_POSTA)',
  width => '10',
  label => 'směr',
  'class' => '',
  ident => 'smer',
  settings => 'default'
);

$TABLE_CONFIG['schema'][] = array(
  field => "'<i><font size = 1>'...tableBarcode(ID)...'</font></i>'",
  label => 'JID',
  width => '4%',
  order_by => 'ID',
  ident => 'CK',
  settings => 'default'
);

$TABLE_CONFIG['schema'][] = array(
  field => 'tableFormatCJednaci(ID, 1)',
  label => 'Číslo jednací',
  order_by => 'cislo_spisu2 asc, cislo_spisu1 asc, podcislo_spisu asc',
  width => '4%',
  add => 'NOWRAP',
  ident => 'SIS',
  settings => 'default'
);


$TABLE_CONFIG['schema'][] = array(
  field => "DatumPrijeti(DATUM_PODATELNA_PRIJETI)...'<br/>'...DatumVyrizeni(LHUTA_VYRIZENI)",
  label => 'Datum&nbsp;přijetí,<br/>K&nbsp;vyřízení&nbsp;do',
  order_by => '(DATUM_PODATELNA_PRIJETI, \\\'FMDD.FMMM.YYYY\\\') asc ',
  width => '4%',
  add => 'NOWRAP',
  ident => 'PRIJETI',
  settings => 'default'
);

$TABLE_CONFIG['schema'][] = array(
  field => "tableSpisUzel(ID)...'<br/>'...tableZpracovatel(ID)...tableVraceni(ID)...'<br/><i>'...ShowStatus(STATUS)...'</i>'",
  label => 'Vyřizuje',
  //add => "'align = left style = 'padding:0 0.3em' NOWRAP'",
  order_by => 'u.group_id asc,u.lname asc, u.fname asc, p.id',
  width => '10%',
  ident => 'ODBREF'
);


$TABLE_CONFIG['schema'][] = array(
  field => "Ukaz2(ODES_TYP, ZPUSOB_PODANI, VLASTNICH_RUKOU)...'&nbsp;'...UkazJmeno()...'<br/> '...JEJICH_CJ...'<br/>'...\$q->dbdate2str(JEJICH_CJ_DNE)",
  label => 'Odesílatel, Adresát',
  order_by => 'odesl_prijmeni asc, odesl_jmeno asc',
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
  ident => 'SPZNACKA',
  settings => 'default'
);

if (($GLOBALS['omez_stav'] == 2) or ($GLOBALS['STATUS'] == 2))
$TABLE_CONFIG["schema"][] = array(
  field=>"GetDocs_UPLOAD(ID)",
  label=>"Soubory",
  "add"=>"align=left",
  "order_by"=>"",
  width=>"10%",
  "add"=>"NOWRAP"
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

if ($GLOBALS[CONFIG][TWIST_UPLOAD]) {
  $TABLE_CONFIG['schema'][] = array(
    field => 'ShowUploadPosta(ID)',
    label => '&nbsp;',
    add => 'align = center',
    'width' => '1%',
    'class' => 'image',
    ident => 'upload',
    settings => 'default'
  );
}

$TABLE_CONFIG['ident_array'] = array(

    0 => array('Vyberte'),
    1 => array('standardní','smer','SIS','PRIJETI','JMENO','VEC','ODBREF','VYRIZENO','SPZNACKA','SPISOVNA','UKLZNACKA',
               'STATUS','SPISFORMA','upload'),
    2 => array('dle vyhláąky', 'smer','CK','SIS','PRIJETI','JMENO','JEJICH_CJ','VEC','ODBOR','REFERENT','VYRIZENO',
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

$TABLE_CONFIG['syscolumns'] = array(
 'upload' => array ('theme'=>array('dropdown'=>true, 'column'=>true)),
 'edit' => array ('theme'=>array('dropdown'=>true, 'column'=>true))
);



echo "
<script type=\"text/javascript\">
  function EditShowAtt(e,id,target){
    var script = '/ost/posta/ug_file.php?upload_modul=table&_set_sess_cache_limit_=1';
    if (e.ctrlKey){
      script = script + '&edit&show_typ=1&EDIT_ID='+id;
      var param = 'height=430,width=580,'
      target = 'FileAtt';
    }else{
      script = script + '&FILE_ID='+id;
      var param = 'menubar,status,titlebar,toolbar,';
    }
    var d = new Date();
    newwindow = window.open(script+'&cacheid='+d.getTime(),target,param+'left=100,top=50,scrollbars,resizable');
    newwindow.focus();
    e.cancelBubble=true;
    return false;
  }
</script>

";
echo '<iframe id="ifrm_doc" name="ifrm_doc" style="position:absolute;z-index:0;left:10;top:10;visibility:hidden"></iframe>';