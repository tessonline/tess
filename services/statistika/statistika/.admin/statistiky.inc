<?php
include_once($GLOBALS["TMAPY_LIB"]."/oohforms.inc");
//include_once($GLOBALS["TMAPY_LIB"]."/of_select.inc");
require_once(GetAgendaPath('POSTA',false,false)."/.admin/el/of_select_.inc");


$odbory = getSelectDataEed(new of_select_vsechny_spisuzly(array()));
$role = getSelectDataEed(new of_select_prava(array()));

$odbor_puv = $GLOBALS['ODBOR'];

$typ_doc =getSelectDataEed(new of_select_typ_posty(array()));
unset($GLOBALS['ODBOR']);
$GLOBALS['ODBOR'] = $odbor_puv;
$odes_typ = getSelectDataEed(new of_select_odes_typ(array()));
$status = getSelectDataEed(new of_select_status(array()));
$obalky = getSelectDataEed(new of_select_typ_odeslani(array()));
$odeslani = getSelectDataEed(new of_select_druh_odeslani(array()));
$prichozi_prijeti = getSelectDataEed(new of_select_druh_prijeti(array()));


//$STATISTIKA['VSE']=" ";
$STATISTIKA['BEZ_STORNA']= " AND STORNOVANO IS NULL";

$STATISTIKA['PRICHOZI']=" AND odeslana_posta<>'t'";
$STATISTIKA['ODCHOZI']=" AND odeslana_posta='t'";

foreach($odbory as $key=>$val)
  $STATISTIKA['ODBORY'][$key]=array('NAME'=>$val,'SQL'=>"AND ODBOR IN (".$key.")");

/*foreach($role as $key=>$val)
  $STATISTIKA['$role'][$key]=array('NAME'=>$val,'SQL'=>"AND ODBOR IN (".$key.")");
*/
foreach($typ_doc as $key=>$val)
  $STATISTIKA['TYP_DOC'][$key]=array('NAME'=>$val,'SQL'=>"AND TYP_POSTY IN (".$key.")");

foreach($odes_typ as $key=>$val)
  $STATISTIKA['ODES_TYP'][$key]=array('NAME'=>$val,'SQL'=>"AND ODES_TYP IN (".$key.")");

foreach($status as $key=>$val)
  $STATISTIKA['STATUS'][$key]=array('NAME'=>$val,'SQL'=>"AND STATUS IN (".$key.")");

foreach($obalky as $key=>$val)
  $STATISTIKA['OBALKY'][$key]=array('NAME'=>$val,'SQL'=>"AND DOPORUCENE IN (".$key.")");

foreach($odeslani as $key=>$val)
  $STATISTIKA['ODESLANI'][$key]=array('NAME'=>$val,'SQL'=>"AND VLASTNICH_RUKOU like ('".$key."')");

foreach($prichozi_prijeti as $key=>$val)
  $STATISTIKA['PRIJETI'][$key]=array('NAME'=>$val,'SQL'=>"AND ZPUSOB_PODANI like ('".$key."')");

$GLOBALS['STATISTIKA'] = $STATISTIKA;
//$STATISTIKA['TYP_DOKUMENTU']=array('')


function VratPocet($sql_where_add)
{
  global $sql,$sql_where,$sql_group_by,$q;
  $sql_temp=$sql.' WHERE 1=1 '.implode(' ',$sql_where).implode(' ',$sql_where_add);  
  if ($sql_group_by) $sql_temp.=" ".$sql_group_by;
  $q->query($sql_temp); $pocet = $q->Num_Rows();
  return $pocet;

//  return $sql_temp;

// return rand(0,25500);
}
