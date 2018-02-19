<?php 
require_once(FileUp2('.admin/el/of_select_.inc'));

function ShowRange($spis_id) {
  if ($spis_id == 1) 
    $range_id = "C";
  else 
    $range_id = "V";
  $range = getSelectDataEed(new of_select_nastaveni_pristupy_rozsah(array()));
  $ret = $range[$range_id];
  if (!$ret) $ret = $range_id;
  return $ret;
}

function ShowPIDs($edit_id) {
  $res = "";
  $q = new DB_POSTA;  
 // $sql = "select posta_id from posta_pristupy where spis_id=".$spis_id;
  $sql = "select posta_id from posta_pristupy where spis_id=(SELECT spis_id from posta_pristupy where id=".$edit_id.") and referent = (SELECT referent from posta_pristupy where id=".$edit_id.") and odbor = (SELECT odbor from posta_pristupy where id=".$edit_id.")";
  
  
 /* if ($odbor>0)
    $sql.="and odbor=".$odbor;
  if ($referent>0)
    $sql.= "and referent=".$referent;*/  
  $q->query($sql);
  while ($q->Next_Record()) {
    $cj_obj2 = LoadClass('EedCj',$q->Record['POSTA_ID']);
    $res.= $cj_obj2->cislo_jednaci."<br />";
  }
  return $res;
}