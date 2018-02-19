<?php

if (isset($GLOBALS['ID_TYP'])) {
  $button = "<input type=\"submit\" class=\"btn button\" value=\"Vytvořit workflow\" onClick=\"javascript:NewWindowEdit('".GetAgendaPath("POSTA", 0, 1)."/plugins/workflow/edit.php?insert&ID_TYP=".$GLOBALS['ID_TYP']."&cacheid=');return false;\">\n";
  

if (isset($GLOBALS['ID_TYP'])) {
  $id_typ = (is_array($GLOBALS['ID_TYP'])) ? implode(',',$GLOBALS['ID_TYP']) : $GLOBALS['ID_TYP'];
  $where = ' WHERE ID_TYP IN ('.$id_typ.') ';
} else {
  $where = ' WHERE 1=1 ';
}

$q = new DB_POSTA;
$sql = "SELECT count(*) as pocet FROM POSTA_WORKFLOW ".$where." AND id_workflow=1";
$q->query($sql);
$q->Next_Record();
$count1 = $q->Record['POCET'];


  
  if ($count1>0)
  Table(array(
    'agenda'=>'POSTA_WORKFLOW',
    'showaccess'=>true,
    'showedit'=>true,
    'showinfo'=>true,
    'showdelete'=>true,
    'appendwhere'=>'AND id_workflow=1',
  ));
  
  $GLOBALS['rename_columns'] = 2;

  $sql = "SELECT count(*) as pocet FROM POSTA_WORKFLOW ".$where." AND id_workflow=2";
  $q->query($sql);
  $q->Next_Record();
  $count2 = $q->Record['POCET'];
  
  if ($count2>0)
  Table(array(
    'agenda'=>'POSTA_WORKFLOW',
    'showaccess'=>true,
    'showedit'=>true,
    'showinfo'=>true,
    'showdelete'=>true,
    'appendwhere'=>'AND id_workflow=2',
  ));
  
  $GLOBALS['rename_columns'] = 3;
  

  $sql = "SELECT count(*) as pocet FROM POSTA_WORKFLOW ".$where." AND id_workflow=3";
  $q->query($sql);
  $q->Next_Record();
  $count3 = $q->Record['POCET'];
  
  if ($count3>0||($count1==0&&$count2==0))
  Table(array(
    'agenda'=>'POSTA_WORKFLOW',
    'showaccess'=>true,
    'showedit'=>true,
    'showinfo'=>true,
    'showdelete'=>true,
    'appendwhere'=>'AND id_workflow=3',
  ));
  
  
}
