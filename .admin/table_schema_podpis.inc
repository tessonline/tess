<?php
echo '<iframe id="ifrm_doc" name="ifrm_doc" src="'.FileUpUrl('empty.php').'" style="position:absolute;z-index:0;left:0;top:0;display:none"></iframe>';

require_once(FileUp2('.admin/config.inc'));
Include_once(FileUp2('.admin/form_func.inc'));
//Include_once(FileUp2('.admin/table_funkce_obj.inc'));
Include_once(FileUp2('.admin/table_funkce_denik.inc'));
Include_once(FileUp2('.admin/oth_funkce.inc'));
Include_once(FileUp2('.admin/security_name.inc'));

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
  order_by => 'cislo_spisu2 asc, cislo_spisu1 asc, podcislo_spisu asc',
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
  field => "tableSpisUzel(ID)...'<br/>'...tableZpracovatel(ID)",
  label => 'Vyřizuje',
  add => "'align = left style = 'padding:0 0.3em' NOWRAP'",
  order_by => 'u.group_id asc,u.lname asc, u.fname asc, p.id',
  width => '10%',
  ident => 'ODBREF'
);

$TABLE_CONFIG['schema'][] = array(
  field => 'ShowStatus(STATUS)',
  label => 'Stav',
  add => 'align = center',
  'width' => '10%',
  ident => 'STATUS',
  settings => 'default'
);


$TABLE_CONFIG["schema"][]= array( field=>"GetDocs_UPLOAD(ID)", label=>"Soubory","add"=>"align=left", "order_by"=>"", width=>"10%","add"=>"NOWRAP");


reset ($GLOBALS["CONFIG_POSTA"]["PLUGINS"]);
foreach($GLOBALS["CONFIG_POSTA"]["PLUGINS"] as $plug_name => $plug) {
  if ($plug['enabled']){
    $file = FileUp2('plugins/'.$plug['dir'].'/.admin/table_schema_end.inc');
		if (File_Exists($file)) include($file);
  }
}


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

if ($GLOBALS[CONFIG][VLASTNI_UPLOAD]) {

  $TABLE_CONFIG['schema'][] = array(
    field => 'ShowUploadPosta(ID)',
    label => '&nbsp;',
    add => 'align = center',
    'width' => '1%',
    'class' => 'image',
    ident => 'vlastni_upload',
    settings => 'function',
    'theme' => array(
      'dropdown'=>true,
      'column'=>true
    ),
  );
}


?>
<script language="JavaScript" type="text/javascript">
<!--
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
//-->
</script>
