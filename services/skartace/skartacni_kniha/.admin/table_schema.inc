<?php
//include_once(FileUp2('.admin/security_name.inc'));
include_once(FileUp2('.admin/table_funkce.inc'));
include_once(FileUp2('.admin/table_func_skartace.inc'));
include_once(FileUp2('.admin/table_funkce_denik.inc'));
//include_once(FileUp2('.admin/oth_funkce.inc'));
include_once(FileUp2('services/spisovka/uzavreni_spisu/funkce.inc'));

if ($GLOBALS['PREDANI']) {
?>
<script language="JavaScript" type="text/javascript">
  function NewWindowMobWriteRuian(script) {
    if (window.name == 'WriteRuian') {
      window.location.href = script;
    } else {
      newwindow = window.open(script, 'WriteRuian','height=700,width=1000,left=10,top=10,menubar=1,scrollbars=1,resizable=1');
      newwindow.focus();
    }
  }

  function WriteRuian(param){
    NewWindowMobWriteRuian('<?php
    echo FileUpUrl('empty.php');
    ?>');
    var frm = document.frm_;
    if (typeof(frm['SELECT_ID_USE_FILTER']) == 'undefined') {}
    else frm.SELECT_ID_USE_FILTER.value = '1';
  	var tar = frm.target;
    var act = frm.action;
    frm.target = 'WriteRuian';
    frm.action = '<?php echo GetAgendaPath('POSTA_SKARTACE') ?>/write_krabice.php?cache=';
    frm.submit();
    frm.target = tar;
    frm.action = act;
    if (typeof(frm['SELECT_ID_USE_FILTER']) == 'undefined') {}
    else frm.SELECT_ID_USE_FILTER.value = '0';
  }
</script>


<?php
$TABLE_TOP_MENU['style'] = 'button';
// $TABLE_TOP_MENU['schema'][] = array(
//   'label' => 'Vložit do boxu',
//   'url' => 'javascript:WriteRuian()',
//   'title' => 'Vloľit do boxu',
//   'image' => FileUpImage('images/import'),
//   'showonempty' => false,
//   'theme_config' => array(
//     'square' => array(
//       'theme' => array(
//         'dropdown' => false,
//         'button' => true
//       )
//     )
//   )
// );
//
// $TABLE_TOP_MENU['schema'][] = array(
//   'label' => 'Seznam arch. boxů',
//   'url' => 'brow.php?SHOW_BOX=1',
//   'title' => 'Seznam arch. boxů',
//   'image' => FileUpImage('images/import'),
//   'showonempty' => false,
//   'theme_config' => array(
//     'square' => array(
//       'theme' => array(
//         'dropdown' => false,
//         'button' => true
//       )
//     )
//   )
// );

/*
  //echo $sql;
  $temp = array();
  while($qqqq->Next_Record()){
    $temp[] = $qqqq->Record['DOKUMENT_ID'];
  }
  $_SESSION['PROTOKOL_ID_TABLE'] = $temp;
*/

  $TABLE_CONFIG["schema"][] =  array( "field"=>"DATUM_PODATELNA_PRIJETI", "label"=>"Datum", "width"=>"4%");

  $TABLE_CONFIG["schema"][] =  array( "field"=>"BOX(ID)", "label"=>"Box", "width"=>"4%");

  $TABLE_CONFIG['schema'][] = array(
    field => 'showProtokol(ID)',
    label => $GLOBALS['CONFIG']['CISLO_SPISU'],
    order_by => 'cislo_spisu2 asc, cislo_spisu1 asc',
    width => '4%',
    add => 'NOWRAP',
    ident => 'SIS',
    settings => 'default'
  );

    //$TABLE_CONFIG["schema"][] =  array( "field"=>"UKAZJMENO(ODESL_JMENO,ODESL_PRIJMENI,ODESL_TITUL,ODESL_ULICE,ODESL_CP,ODESL_POSTA,ODESL_PSC)", "label"=>"Adresát", "width"=>"30%");
  $TABLE_CONFIG['schema'][] = array(
    field => 'tableSpisVec(ID)',
    label => 'Věc',
    order_by => 'vec',
    width => '30%',
    ident => 'VEC',
    settings => 'default'
  );


  $TABLE_CONFIG['schema'][] = array(
    field => "tableSpisUzel(ID)...'<br/>'...tableZpracovatel(ID)",
    label => 'Vyřizuje',
    //add => "'align = left style = 'padding:0 0.3em' NOWRAP'",
    order_by => 'u.group_id asc,u.lname asc, u.fname asc, p.id',
    width => '10%',
    ident => 'ODBREF'
  );

  $TABLE_CONFIG['schema'][] = array(
    field => 'Vyrizeno(VYRIZENO, SPIS_VYRIZEN, SPIS_VYRIZEN)',
    label => 'Vyřízeno',
    add => 'align = center',
    'width' => '1%',
    ident => 'VYRIZENO',
    settings => 'default'
  );

  $TABLE_CONFIG["schema"][] =  array( "field"=>"Listu(CISLO_SPISU1,CISLO_SPISU2,ID)", "label"=>"Listů","add"=>"NOWRAP", "width"=>"1%");
  $TABLE_CONFIG["schema"][] =  array( "field"=>"Digitalne(CISLO_SPISU1,CISLO_SPISU2)", "label"=>"Dig.","add"=>"NOWRAP", "width"=>"1%");
  $TABLE_CONFIG["schema"][] =  array( "field"=>"'<b>'...SkartacniZnakDoc(SKARTACE,'kod', ID, 0)...'</b>'", "label"=>"Sp.znak","add"=>"align=center");
   $TABLE_CONFIG["schema"][] =  array( "field"=>"SkartacniZnakDoc(SKARTACE,'znak',ID, 0)", "label"=>"Sk.zn.","add"=>"align=center");
  $TABLE_CONFIG["schema"][] =  array( "field"=>"SkartacniZnakDoc(SKARTACE,'doba',ID,0)", "label"=>"Lhůta","add"=>"align=center");
//  $TABLE_CONFIG["schema"][] =  array( "field"=>"RokSkartace(CISLO_SPISU1,CISLO_SPISU2)", "label"=>"Rok skartace","add"=>"align=center");
  $TABLE_CONFIG["schema"][] =  array( "field"=>"UkazInfo(ID)", "label"=>"&nbsp;","class"=>"image","add"=>"align=left", "width"=>"1%");
  $TABLE_CONFIG["schema"][] =  array( "field"=>"UkazEdit(ID)", "label"=>"&nbsp;","class"=>"image","add"=>"align=left", "width"=>"1%");
  //$TABLE_CONFIG["schema"][] =  array( "field"=>"Skartace(ID)", "label"=>"","add"=>"align=center");
//

}
elseif (!$GLOBALS['SHOW_BOX']) {
  if (!$GLOBALS['SKARTACNI_RIZENI_ID'])
  $TABLE_TOP_MENU["schema"] = array(
      array("label"=>"Export dat do XML",  "url"=>"javascript:RunScript_Tisk('/ost/posta/services/skartace/skartacni_kniha/exportXML.php','')", "Xtarget"=>"_blank", "title"=>"Export dat do XML"),
  );

  $TABLE_CONFIG["schema"][] =  array( "field"=>"UkazKdoSpisovna(DATUM_PREDANI,PREVZAL_ID,PROTOKOL_ID)", "label"=>"Předání do spisovny", "width"=>"15%","add"=>"NOWRAP",order_by => 'ID');
  //$TABLE_CONFIG["schema"][] =  array( "field"=>"FormatSpis(PROTOKOL_ID)", "label"=>"Protokol", "width"=>"5%");

//  $TABLE_CONFIG["schema"][] =  array( "field"=>"BOX(DOKUMENT_ID)", "label"=>"Box", "width"=>"4%");

  $TABLE_CONFIG['schema'][] = array(
//    field => 'tableFormatCJednaci(DOKUMENT_ID, 1)',
    field => 'ShowCJSpisovna(DOKUMENT_ID,CISLO_SPISU1,CISLO_SPISU2)',
    label => $GLOBALS['CONFIG']['CISLO_SPISU'],
    order_by => 'cislo_spisu2 asc, cislo_spisu1 asc',
    width => '4%',
    add => 'NOWRAP',
    ident => 'SIS',
    settings => 'default'
  );
  $TABLE_CONFIG['schema'][] = array(
    field => "UkazOdbor(ODBOR, 1)",
    label => $GLOBALS['CONFIG']['NAZEV_ODBOR'],
    //add => "'align = left style = 'padding:0 0.3em' NOWRAP'",
    order_by => 'odbor',
    width => '10%',
  );



  //$TABLE_CONFIG["schema"][] =  array( "field"=>"UKAZJMENO(ODESL_JMENO,ODESL_PRIJMENI,ODESL_TITUL,ODESL_ULICE,ODESL_CP,ODESL_POSTA,ODESL_PSC)", "label"=>"Adresát", "width"=>"30%");
//  $TABLE_CONFIG["schema"][] =  array( "field"=>"tableVec(DOKUMENT_ID)", "label"=>"Věc", "width"=>"30%");
  $TABLE_CONFIG["schema"][] =  array( "field"=>"VEC", "label"=>"Věc", "width"=>"30%");
  $TABLE_CONFIG["schema"][] =  array( "field"=>"ROK_PREDANI", "label"=>"Rok uzavření spisu","add"=>"NOWRAP align=center", "width"=>"10%", order_by => 'rok_predani');
  $TABLE_CONFIG["schema"][] =  array( "field"=>"'<b>'...LISTU...'</b><br/>'...PRILOHY", "label"=>"Listy/Přílohy","add"=>"NOWRAP", "width"=>"10%","is_html"=>true);
  $TABLE_CONFIG["schema"][] =  array( "field"=>"'<b>'...DIGITALNI...'</b>'", "label"=>"Dig.","add"=>"NOWRAP", "width"=>"5%");
  $TABLE_CONFIG["schema"][] =  array( "field"=>"'<b>'...SkartacniZnak(SKARTACE_ID,'SPIS_CISLO', ID)...'</b>'", "label"=>"Sp.znak","add"=>"align=center");
//  $TABLE_CONFIG["schema"][] =  array( "field"=>"SKAR_ZNAK", "label"=>"Sk. znak","add"=>"align=center", "width"=>"5%");
  $TABLE_CONFIG["schema"][] =  array( "field"=>"ShowSkartacniZnak(SKAR_ZNAK, SKAR_ZNAK_ALT)", "label"=>"Sk. znak","add"=>"align=center", "width"=>"5%");
  $TABLE_CONFIG["schema"][] =  array( "field"=>"LHUTA", "label"=>"Lhůta","add"=>"align=center", "width"=>"5%");
  $TABLE_CONFIG["schema"][] =  array( "field"=>"ROK_SKARTACE", "label"=>"Rok skartace","add"=>"align=center", "width"=>"5%", order_by => 'rok_skartace');
  $TABLE_CONFIG["schema"][] =  array( "field"=>"EedTools::GetLokace(LOKACE_ID)", "label"=>"Lokace","add"=>"align=center");
reset ($GLOBALS["CONFIG_POSTA"]["PLUGINS"]);
foreach($GLOBALS["CONFIG_POSTA"]["PLUGINS"] as $plug_name => $plug) {
  if ($plug['enabled']){
    $file = FileUp2('plugins/'.$plug['dir'].'/services/skartace/skartacni_kniha/.admin/table_schema_end.inc');
		if (File_Exists($file)) include($file);
  }
}


  $TABLE_CONFIG["schema"][]= array( field=>"ShowUploadPostaX(ID, REGISTRATURA)", label=>"","add"=>"align=left", "order_by"=>"", width=>"10%","class"=>"image");
}

if (!$GLOBALS['SPISOVNA_ID'] && $GLOBALS['SHOW_BOX'] && !$GLOBALS['HISTORY_ID'] && !$GLOBALS['SKARTACNI_RIZENI_ID']) {
  $TABLE_CONFIG["schema"][] =  array( "field"=>"EV_CISLO...'/'...ROK", "label"=>"Ev. číslo", "width"=>"30%");
  $TABLE_CONFIG["schema"][] =  array( "field"=>"NAZEV", "label"=>"Název", "width"=>"50%");
  $TABLE_CONFIG["schema"][] =  array( "field"=>"SKAR_ZNAK", "label"=>"sk.&nbsp;znak", "width"=>"10%");
  $TABLE_CONFIG["schema"][] =  array( "field"=>"SKAR_LHUTA", "label"=>"sk.&nbsp;lhůta", "width"=>"10%");

}


?>
<iframe id="ifrm_get_value" name="ifrm_get_value" style="position:absolute;z-index:0;left:0;top:0;visibility:hidden"></iframe>
<script>

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

  function RunScript_Tisk_OLD(name_script, tablename,cislo)
  {
    var frm = document.forms['frm_'+tablename];
    frm.method='POST';
    window.open(name_script,'tisk','height=260,width=470,left=50,top=50,scrollbars,resizable');
    var act = frm.action;
    var tar = frm.target;

    if (!frm.SHOW_CJ)
    {
      var input = document.createElement('INPUT');
      input.setAttribute('type', 'hidden');
      input.setAttribute('name', 'SHOW_CJ');
      input.value = cislo;
      frm.appendChild(input);
    }
    else
    {
      frm.SHOW_CJ.value=cislo;
    }
    frm.action = name_script;
//    frm.target = '_top';
    frm.submit();
    frm.action = act;
    frm.target = tar;
    //if(frm.SELECT_ID_USE_FILTER) frm.SELECT_ID_USE_FILTER.value='0';
  }
  function save(znak, doc_id) {
    window.open('saveAlt.php?doc_id='+doc_id+'&znak='+znak.value,'ifrm_get_value');
  }

function NewWindowUpload(script) {
  $.fancybox({
    'type':        'iframe',
    'href':        script,
    'openEffect':  'elastic',
    'closeEffect': 'elastic',
    'autoSize':    true,
    'width':920,
'minHeight':400,
    'tpl': {
      iframe: '<iframe id="fancybox-frame{rnd}" name="upload" class="fancybox-iframe" frameborder="0" vspace="0" hspace="0"></iframe>',
      closeBtn: '<a class="fancybox-item fancybox-close btn" title="Zavřít"></a>'
    },
    'afterShow': function (curr, prev) {
      for(var ii = 0; ii < frames.length; ii++) {
        if(frames[ii].$) {
          (function(idx) {
            setTimeout(function(){
               frames[idx].$('#fixedsticky').fixedsticky();
            }, 200);
          })(ii);
        }
      }
    }
  });
}
function upload_ (id) {
  NewWindowUpload('/ost/posta/services/skartace/skartacni_kniha/ug_file.php?FULLTEXT_UPLOAD=&RECORD_ID='+id);
}
</script>
