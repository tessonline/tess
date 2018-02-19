<?php 

/*$GLOBALS['odbor'] = getSelectDataEed(new select_vsechny_spisuzly(array()));

function ukazSpisUzel($odbor_id) {

  $eedu = LoadClass('EedUser',0);
  $ret = $eedu->VratSpisUzly(10194);

  /*$ret = $GLOBALS['odbor'][$odbor_id];
   if (!$ret) $ret = $odbor_id;
  return $ret[0];
}*/

function changeCellClassTP($t) {
  $neaktivni = $GLOBALS['NEAKTIVNI'];
  $color = 'red';
  if ($neaktivni=='t')
    $t->classname = "brow_red";
    else
      $t->classname = "brow_gray";        
}


function ShowSkartace($skartace_id) {
  if ($skartace_id>0) {
    $q=new DB_POSTA;
    $sql='select kod from cis_posta_skartace where id='.$skartace_id;
    $q->query($sql);
    $q->Next_Record();
    return $q->Record[KOD];
  }
  else
    return '&nbsp;';
}

function UkazOdbory($id) {
if ($id>0) {
  $q=new DB_POSTA;
  // sg.name nebo sg.description
  $sql='select sg.name from cis_posta_typ_odbor cpt  left join cis_posta_odbory cpo on cpt.id_odbor = cpo.id left join security_group sg on cpo.id_odbor=sg.id where cpt.id_posta_typ ='.$id;
  $q->query($sql);
  
  while ($q->Next_Record())
    $res[] = $q->Record['NAME'];
    return implode(", ",$res);
}
else
  return '&nbsp;';
}