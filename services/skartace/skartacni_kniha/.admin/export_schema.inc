<?php
require_once(FileUp2(".admin/config.inc"));
//Include_once(FileUp2(".admin/table_func.inc"));
//Include_once(FileUp2(".admin/table_funkce_denik.inc"));

include_once(FileUp2('.admin/export_func_skartace.inc'));
include_once(FileUp2('.admin/table_funkce_denik.inc'));
//include_once(FileUp2('.admin/oth_funkce.inc'));
include_once(FileUp2('services/spisovka/uzavreni_spisu/funkce.inc'));

/*seznam moznych formatu vystupu s nastavenim*/
$EXPORT_CONFIG['format'] = array(
  'csv'    => array('label'=>'Excel (CSV)'),
  'tabbed' => array('label'=>'Excel (Tabbed)', 'default'=>true ),
  'xml'    => array('label'=>'XML'),
  'xhtml'  => array(
    'label'=>'XHTML',
    'css' => FileUpURL('xhtml.css'),
    'title'=>'Elektronická evidence dokumentů - export',
    'header'=>"''",
    'footer'=>"'<div>Tisk dne ".Date('d.m.Y H:i')."</div>'",
  ),
  
);


if (!$GLOBALS['SPISOVNA_ID'] && !$GLOBALS['HISTORY_ID'] && !$GLOBALS['SKARTACNI_RIZENI_ID']) {
/*
  //echo $sql;
  $temp = array();
  while($qqqq->Next_Record()){
    $temp[] = $qqqq->Record['DOKUMENT_ID'];
  }
  $_SESSION['PROTOKOL_ID_TABLE'] = $temp;
*/
  function showProtokol($ID) {
    $text = tableFormatCJednaci($ID, 0) . UkazPocetCJ($ID);
    $text = strip_tags($text);
    return $text;

  }

  $TABLE_CONFIG["schema"][] =  array( "field"=>"DATUM_PODATELNA_PRIJETI", "label"=>"Datum", "width"=>"4%");

  $TABLE_CONFIG['schema'][] = array(
    field => 'showProtokol(ID)',
    label => $GLOBALS['CONFIG']['CISLO_SPISU'],
    order_by => 'cislo_spisu2 asc, cislo_spisu1 asc',
    width => '4%',
    add => 'NOWRAP',
    ident => 'SIS',
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
    field => "tableSpisUzel(ID)...', '...exportZpracovatel(ID)",
    label => 'Vyřizuje',
    //add => "'align = left style = 'padding:0 0.3em' NOWRAP'",
    order_by => 'u.group_id asc,u.lname asc, u.fname asc, p.id',
    width => '10%',
    ident => 'ODBREF'
  );

  $TABLE_CONFIG['schema'][] = array(
    field => 'ExportVyrizeno(VYRIZENO, SPIS_VYRIZEN, SPIS_VYRIZEN)',
    label => 'Vyřízeno',
    add => 'align = center',
    'width' => '1%',
    ident => 'VYRIZENO',
    settings => 'default'
  );

  $TABLE_CONFIG["schema"][] =  array( "field"=>"Listu(CISLO_SPISU1,CISLO_SPISU2,ID)", "label"=>"Listů","add"=>"NOWRAP", "width"=>"1%");
  $TABLE_CONFIG["schema"][] =  array( "field"=>"Digitalne(CISLO_SPISU1,CISLO_SPISU2)", "label"=>"Dig.","add"=>"NOWRAP", "width"=>"1%");
  $TABLE_CONFIG["schema"][] =  array( "field"=>"''...SkartacniZnak(SKARTACE,'SPIS_CISLO')...''", "label"=>"Sp.znak","add"=>"align=center");
  $TABLE_CONFIG["schema"][] =  array( "field"=>"SkartacniZnak(SKARTACE,'SKAR_ZNAK',ID, 0)", "label"=>"Sk.zn.","add"=>"align=center");
  $TABLE_CONFIG["schema"][] =  array( "field"=>"SkartacniZnak(SKARTACE,'DOBA',ID, 0)", "label"=>"Lhůta","add"=>"align=center");
}
else {

  $TABLE_CONFIG["schema"][] =  array( "field"=>"ExportKdoSpisovna(DATUM_PREDANI,PREVZAL_ID,PROTOKOL_ID)", "label"=>"Předání do spisovny", "width"=>"15%","add"=>"NOWRAP");
  $TABLE_CONFIG['schema'][] = array(
    field => 'ExportShowCJSpisovna(DOKUMENT_ID,CISLO_SPISU1,CISLO_SPISU2)',
    label => $GLOBALS['CONFIG']['CISLO_SPISU'],
    order_by => 'cislo_spisu2 asc, cislo_spisu1 asc',
    width => '4%',
    add => 'NOWRAP',
    ident => 'SIS',
    settings => 'default'
  );


  $TABLE_CONFIG["schema"][] =  array( "field"=>"VEC", "label"=>"Věc", "width"=>"30%");
  $TABLE_CONFIG["schema"][] =  array( "field"=>"ROK_PREDANI", "label"=>"Rok předání","add"=>"NOWRAP align=center", "width"=>"10%");
  $TABLE_CONFIG["schema"][] =  array( "field"=>"''...LISTU...' - '...PRILOHY", "label"=>"Listy/Přílohy","add"=>"NOWRAP", "width"=>"10%","is_html"=>true);
  $TABLE_CONFIG["schema"][] =  array( "field"=>"''...DIGITALNI...''", "label"=>"Dig.","add"=>"NOWRAP", "width"=>"5%");
  $TABLE_CONFIG["schema"][] =  array( "field"=>"''...SkartacniZnak(SKARTACE_ID,'SPIS_CISLO', ID)...''", "label"=>"Sp.znak","add"=>"align=center");
  $TABLE_CONFIG["schema"][] =  array( "field"=>"ExportSkartacniZnak(SKAR_ZNAK, SKAR_ZNAK_ALT)", "label"=>"Sk. znak","add"=>"align=center", "width"=>"5%");
  $TABLE_CONFIG["schema"][] =  array( "field"=>"LHUTA", "label"=>"Lhůta","add"=>"align=center", "width"=>"5%");
  $TABLE_CONFIG["schema"][] =  array( "field"=>"ROK_SKARTACE", "label"=>"Rok skartace","add"=>"align=center", "width"=>"5%");
}


$EXPORT_CONFIG = $TABLE_CONFIG;
