<?php 
//provedeni workflow zaloz schvalovaci proces

function zpracujWorkflow($typ_posty)
{
  $res = array();
  $q=new DB_POSTA;
  $sql="select id_workflow, promenna, hodnota, dokument from posta_workflow where id_workflow=2 and id_typ=".$typ_posty;
  $q->query($sql);
  while ($q->Next_Record()) {
    $res[] =$q->Record;
  }
  return $res;
}

function zalozSchvalovaciProces($zadam_o,$id_referent,$last_id) {
  $q=new DB_POSTA;
  //overeni zda jiz neni zalozen
  $sql = "SELECT count(posta_id) as POCET FROM posta_schvalovani WHERE posta_id=".$last_id." AND schvalujici_id=".$id_referent;
  $q->query($sql);
  $q->Next_Record();
  if ($q->Record['POCET']==0) {  
    //zalozeni
    $datum_zalozeni = Date('d.m.Y H:i:s');
    $sql = "INSERT into posta_schvalovani (posta_id,schvalujici_id,datum_zalozeni,typschvaleni) VALUES ("
        .$last_id.",".$id_referent.",'".$datum_zalozeni."',".$zadam_o.")";
    $q->query($sql);
  }
}

function ulozNovaPole($record_id) {
  $q=new DB_POSTA;
  foreach ($GLOBALS as $key => $value) {
    $find = substr( $key, 0, 9 );
    if ($find === "WORKFLOW_") {
      $sql = "SELECT count(id_posta) as pocet FROM posta_workflow_pole WHERE id_posta=".$record_id." AND promenna='".$GLOBALS['VAR_'.$key]."'";
      $q->query($sql);
      $q->Next_Record();
      if ($q->Record['POCET']==0) 
        $sql = "INSERT into posta_workflow_pole (id_posta,promenna,hodnota,datovy_typ) VALUES (".$record_id.",'".$GLOBALS['VAR_'.$key]."','".$GLOBALS[$key]."','".$GLOBALS['VAR_DT_'.$key]."')";
      else
        $sql = "UPDATE posta_workflow_pole SET hodnota ='".$GLOBALS[$key]."', datovy_typ ='".$GLOBALS['VAR_DT_'.$key]."'  WHERE promenna='".$GLOBALS['VAR_'.$key]."' AND id_posta=".$record_id;
      $q->query($sql);
    }
  }
}

//pro ug_file_end.php
if (!isset($GLOBALS['TYP_POSTY']) && $GLOBALS['RECORD_ID']) {
  $sql = "select typ_posty from posta where id=".$GLOBALS['RECORD_ID'];
  $q = new DB_POSTA;
  $q->query($sql);
  $q->Next_Record();
  $GLOBALS['TYP_POSTY'] = $q->Record['TYP_POSTY']; 
  $GLOBALS['lastid'] = $GLOBALS['RECORD_ID'];
}

if ($GLOBALS['TYP_POSTY'])
  $workflow = zpracujWorkflow($GLOBALS['TYP_POSTY']);

if (is_array($workflow))
foreach ($workflow as $w) {
  $doc_pozadovany = $w['DOKUMENT'];
  $odchozi_posta = $GLOBALS['ODCHOZI_POSTA'];
  if (($doc_pozadovany=="")|| (($doc_pozadovany=="O")&&($GLOBALS['ODCHOZI_POSTA']=="t")) || (($doc_pozadovany=="P")&&($GLOBALS['ODCHOZI_POSTA']!="t"))) {
    zalozSchvalovaciProces($w['PROMENNA'],$w['HODNOTA'],$GLOBALS['lastid']);
  }
}

ulozNovaPole($GLOBALS['RECORD_ID'] ? $GLOBALS['RECORD_ID'] : $lastid);