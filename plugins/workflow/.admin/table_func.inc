<?php

include_once($GLOBALS['TMAPY_LIB'] . '/oohforms.inc');
require_once(FileUp2('.admin/el/of_select_.inc'));
require_once(FileUp2('.admin/el/of_select_workflow.inc'));

$select_var = array(

  "ODBOR" => "select_vsechny_spisuzly",
  "ODES_TYP" => "select_odes_typ", 
  "ODESL_ODBOR" => "select_interni_spisuzly",
  "REFERENT" => "select_referent",
  "VLASTNICH_RUKOU" => "select_druh_odeslani",
  "DOPORUCENE" => "select_typ_odeslani",
  "TYP_DOKUMENTU" => "select_typ_dokumentu",
  "ODESL_PRAC2" => "select_referent",
 // "VYRIZENO" => "select_vyrizeno",
  "OBALKA_NEVRACET" => "select_ano_ne",
  "OBALKA_10DNI" => "select_ano_ne", 
);

$GLOBALS['typ'] = getSelectDataEed(new of_select_typ_posty(array('agendacount'=>1)));
$GLOBALS['workflow'] = getSelectDataEed(new of_select_workflow(array()));
$GLOBALS['promenna'] = getSelectDataEed(new of_select_promenna(array()));
$GLOBALS['odesilatel'] = getSelectDataEed(new of_select_odes_typ(array()));
$GLOBALS['dokument'] = getSelectDataEed(new of_select_dokument(array()));
$GLOBALS['odesl_odbor'] = getSelectDataEed(new of_select_vsechny_spisuzly(array('enable_disabled'=>true)));
$GLOBALS['referent'] = getSelectDataEed(new of_select_referent(array('fullselect'=>true)));
$GLOBALS['zadost_schvaleni'] = getSelectDataEed(new of_select_zadost_schvaleni(array()));
$GLOBALS['datovy_typ'] = getSelectDataEed(new of_select_datovy_typ(array()));


function ukazTyp($typ_id) {
  $ret = $GLOBALS['typ'][$typ_id];
  if (!$ret) $ret = $typ_id;
  return $ret;
}

function ukazWorkflow($workflow_id) {
  $ret = $GLOBALS['workflow'][$workflow_id];
  if (!$ret) $ret = $jine_id;
  return $ret;
}

function ukazPromenna($promenna_id) {
  $ret = $GLOBALS['promenna'][$promenna_id];
  if (!$ret) $ret = $promenna_id;
  return $ret;
}

function ukazDokument($dokument_id) {
  $ret = $GLOBALS['dokument'][$dokument_id];
  if (!$ret) $ret = $dokument_id;
  return $ret;
}

function ukazOdesilatele($odes_id) {
  $ret = $GLOBALS['odesilatel'][$odes_id];
  if (!$ret) $ret = $odes_id;
  return $ret;
}

function ukazZadamO($o_id) {
  $ret = $GLOBALS['zadost_schvaleni'][$o_id];
  if (!$ret) $ret = $o_id;
  return $ret;
}

function ukazJmeno($ref_id) {
  $ret = $GLOBALS['referent'][$ref_id];
  if (!$ret) $ret = $ref_id;
  return $ret;
}

function ukazDatovyTyp($typ_id) {
  $ret = $GLOBALS['datovy_typ'][$typ_id];
  if (!$ret) $ret = $typ_id;
  return $ret;
}




/*function ukazSelectHodnotu($hodnota,$promenna) {
  
}*/