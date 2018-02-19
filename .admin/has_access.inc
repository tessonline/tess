<?php
//$user_obj = new EedUser;

require_once(GetAgendaPath('POSTA',false,false).'/.admin/classes/EedSchvalovani.inc');
$user_access_obj = new EedUser;
//$user_access_obj->show_debug_sql = true;

$odbor_org=$user_access_obj->GetUnit();
$user_obj = LoadClass('EedUser', 0);
$odbor = VratOdbor();
$odbory = array();

if (HasRole('editace_uzel')) {
  $odbory[] = $odbor;
  $unita = $user_obj->VratOdborZSpisUzlu($odbor);
  $podrizene_unity = $user_obj->VratPodrizeneUnity($unita);
  foreach($podrizene_unity as $unita => $val) {
    $temp = $user_obj->VratSpisUzelZOdboru($unita);
    if ($temp['ID']>0) $odbory[] = $temp['ID'];

  }
}

$nadrizene_odbory = array();
$nadrizene_odbory[] = $odbor;
$unita = $user_obj->VratOdborZSpisUzlu($odbor);
$nadrizene_unity = $user_obj->VratNadrizeneUnity($unity);
foreach($nadrizene_unity as $unita => $val) {
  $temp = $user_obj->VratSpisUzelZOdboru($unita);
  if ($temp['ID']>0) $nadrizene_odbory[] = $temp['ID'];
}
$so = $user_obj->VratSpisUzelZOdboru($user_obj->zarizeni_id);
$nadrizene_odbory[] = $so['ID'];

$pracovnici_pode_mnou = array();
$ret = $user_obj->VratUzlyAOdborPrac($odbor);
foreach($ret['odborprac'] as $odbor => $prac) {
  $pracovnici_pode_mnou = array_merge($pracovnici_pode_mnou, $prac);
}

$GLOBALS['pracovnici_pode_mnou'] = $pracovnici_pode_mnou;
$GLOBALS['spisove_uzly_pode_mnou'] = $odbory;
$GLOBALS['USER_INFO'] = $GLOBALS["POSTA_SECURITY"]->GetUserInfo();
$GLOBALS['db_sec'] = new DB_POSTA;
$GLOBALS['nadrizene_odbory'] = $nadrizene_odbory;


function MaPristupKDokumentu_old($IDP) {
  global $pracovnici_pode_mnou,$spisove_uzly_pode_mnou, $USER_INFO, $db_sec, $nadrizene_odbory,$CONFIG_POSTA,$CONFIG;
  $pristupy=array();
  $pristup = false;
  //zjistime zastupy
//   $sql='select zastoupena from posta_zastupy where zpracovatel in ('.$USER_INFO["ID"].')';
//   $db_sec->query($sql);
//   while ($db_sec->Next_Record()) $pristupy[]=$db_sec->Record["ZASTOUPENA"];

//  include(FileUp2('.admin/access_.inc'));
//  Access(array('agenda'=>'POSTA'));
  $id=$GLOBALS['EDIT_ID']?$GLOBALS['EDIT_ID']:$GLOBALS['ID'];
  IF ($IDP>0) $id = $IDP;
  if (@in_array($id, $GLOBALS['CONFIG_POSTA']['NEMAM_PRISTUP'])) return false; //uz bylo testovano, tak smula
  if (@in_array($id, $GLOBALS['CONFIG_POSTA']['MAM_PRISTUP'])) return true; //uz bylo testovano, a je to v pohode

  if (isset($GLOBALS['POSTA_OPT']['POSTA'][$id])) {
    $db_sec->Record = $GLOBALS['POSTA_OPT']['POSTA'][$id];
  }
  else {
    $sql='select * from posta where id='.$id;
    $db_sec->query($sql); $db_sec->Next_Record();
  }
   
    
  if (HasRole('editace_zpracovatel')) {
    if ($USER_INFO['ID']==$db_sec->Record['REFERENT']) $pristup=true;
  }
  if (HasRole('editace_uzel')) {
    if (VratOdbor()==$db_sec->Record['ODBOR']) $pristup=true;
    if (in_array($db_sec->Record['REFERENT'],$pracovnici_pode_mnou)) $pristup=true;
    if (in_array($db_sec->Record['ODBOR'],$spisove_uzly_pode_mnou)) $pristup=true;
    if ($db_sec->Record['ODESLANA_POSTA'] == 'f' && $db_sec->Record['DATUM_PREDANI'] == '') $pristup = false;
  }
  
  if (HasRole('dz-uk')||HasRole('dz-odbor')||HasRole('dz-soucast')||HasRole('dz-zpracovatel')) {
    if ($db_sec->Record['VLASTNICH_RUKOU'] == '9') $pristup = true;
  }
  
  if (HasRole('editace_vse_pracoviste')) {
    if ($db_sec->Record['SUPERODBOR']==EedTools::VratSuperOdbor()) $pristup=true;
  }
  if (HasRole('editace_admin')) {
    $pristup=true;
  }
  if ($pristup) {
    $GLOBALS['CONFIG_POSTA']['MAM_PRISTUP'][] = $id;
    return true;
  }

  if (HasRole('editace_vse_pracoviste')) {
    $sql='select * from posta where id='.$id .'  and id in (select h.id from (select distinct on (id) id,superodbor from posta_h where superodbor>0 order by id, id_h) as h LEFT JOIN posta p ON p.id=h.id where p.superodbor>0 and p.superodbor<>h.superodbor) ';
    $db_sec->query($sql);
    if ($db_sec->Num_Rows() > 0) {
      $GLOBALS['CONFIG_POSTA']['MAM_PRISTUP'][] = $id;
      return true;
    }
  }

  $cj_temp_access = LoadClass('EedCj', $id);
  $doc_in_cj = $cj_temp_access->GetDocsInCj($id);
  $doc_in_cj[] = $id;
  unset($cj_temp_access);
  $sql='select * from posta_pristupy where (posta_id='.$id.' and spis=0 and access in (\'edit\',\'delete\')) or (posta_id in ('.implode(',',$doc_in_cj).') and spis=1 and access in (\'edit\',\'delete\'))';
  $db_sec->query($sql);
  while ($db_sec->Next_Record()) {
    if ($USER_INFO['ID']==$db_sec->Record['REFERENT']) $pristup=true;
    if (in_array($db_sec->Record['ODBOR'], $nadrizene_odbory)) $pristup=true;
//    if (in_array($db_sec->Record['REFERENT'],$pracovnici_pode_mnou)) $pristup=true;
  }

  if (!$pristup) $GLOBALS['CONFIG_POSTA']['NEMAM_PRISTUP'][] = $id;
  if ($pristup) $GLOBALS['CONFIG_POSTA']['MAM_PRISTUP'][] = $id;
  return $pristup;
}

function MaPristupKDokumentu_table() {
  global $pracovnici_pode_mnou,$spisove_uzly_pode_mnou, $USER_INFO, $db_sec, $nadrizene_odbory,$CONFIG_POSTA;

  $pristup=false;
  $pristupy=array();
  
  $pristupy[]=$USER_INFO["ID"];
  If (!in_array($GLOBALS["REFERENT"],$pristupy))
    $pristup=false;
  else
    $pristup=true;
//  return $pristup;
//  include(FileUp2('.admin/access_.inc'));
//  Access(array('agenda'=>'POSTA'));
  $id=$GLOBALS['EDIT_ID']?$GLOBALS['EDIT_ID']:$GLOBALS['ID'];
  if (@in_array($id, $GLOBALS['CONFIG_POSTA']['NEMAM_PRISTUP'])) return false; //uz bylo testovano, tak smula
  if (@in_array($id, $GLOBALS['CONFIG_POSTA']['MAM_PRISTUP'])) return true; //uz bylo testovano, a je to v pohode

  $sql='select * from posta where id='.$id;

  $db_sec->query($sql); $db_sec->Next_Record();
  if (HasRole('editace_zpracovatel')) {
    if ($USER_INFO['ID']==$db_sec->Record['REFERENT']) $pristup=true;
  }
  if (HasRole('editace_uzel')) {
    if (VratOdbor()==$db_sec->Record['ODBOR']) $pristup=true;
    if (in_array($db_sec->Record['REFERENT'],$pracovnici_pode_mnou)) $pristup=true;
    if (in_array($db_sec->Record['ODBOR'],$spisove_uzly_pode_mnou)) $pristup=true;
    if ($db_sec->Record['ODESLANA_POSTA'] == 'f' && $db_sec->Record['DATUM_PREDANI'] == '') $pristup = false;
  }
  if (HasRole('dz-uk')||HasRole('dz-odbor')||HasRole('dz-soucast')||HasRole('dz-zpracovatel')) {
    if ($db_sec->Record['VLASTNICH_RUKOU'] == '9') $pristup = true;
  }
  if (HasRole('editace_vse_pracoviste')) {
    if ($db_sec->Record['SUPERODBOR']==EedTools::VratSuperOdbor()) $pristup=true;
  }
  if (HasRole('editace_admin')) {
    $pristup=true;
  }
  if ($pristup) {
    $GLOBALS['CONFIG_POSTA']['MAM_PRISTUP'][] = $id;
    return true;
  }

  if (HasRole('editace_vse_pracoviste')) {
    $sql='select * from posta where id='.$id .'  and id in (select h.id from (select distinct on (id) id,superodbor from posta_h where superodbor>0 order by id, id_h) as h LEFT JOIN posta p ON p.id=h.id where p.superodbor>0 and p.superodbor<>h.superodbor) ';
    $db_sec->query($sql);
    if ($db_sec->Num_Rows() > 0) {
      $GLOBALS['CONFIG_POSTA']['MAM_PRISTUP'][] = $id;
      return true;
    }
  }


  $cj_temp_access = LoadClass('EedCj', $id);
  $doc_in_cj = $cj_temp_access->GetDocsInCj($id);
  $doc_in_cj[] = $id;
  unset($cj_temp_access);
  $sql='select * from posta_pristupy where (posta_id='.$id.' and spis=0 and access in (\'edit\',\'delete\')) or (posta_id in ('.implode(',',$doc_in_cj).') and spis=1 and access in (\'edit\',\'delete\'))';
  $db_sec->query($sql);
  while ($db_sec->Next_Record()) {
    if ($USER_INFO['ID']==$db_sec->Record['REFERENT']) $pristup=true;
    if (in_array($db_sec->Record['ODBOR'], $nadrizene_odbory)) $pristup=true;
//    if (in_array($db_sec->Record['REFERENT'],$pracovnici_pode_mnou)) $pristup=true;
  }

  if (!$pristup) $GLOBALS['CONFIG_POSTA']['NEMAM_PRISTUP'][] = $id;
  if ($pristup) $GLOBALS['CONFIG_POSTA']['MAM_PRISTUP'][] = $id;

  return $pristup;
}

function MaPristupKSmazaniDokumentu($IDP) {
  global $pracovnici_pode_mnou,$spisove_uzly_pode_mnou, $USER_INFO, $db_sec, $nadrizene_odbory;
  $pristupy=array();
  //zjistime zastupy
//   $sql='select zastoupena from posta_zastupy where zpracovatel in ('.$USER_INFO["ID"].')';
//   $db_sec->query($sql);
//   while ($db_sec->Next_Record()) $pristupy[]=$db_sec->Record["ZASTOUPENA"];

//  include(FileUp2('.admin/access_.inc'));
//  Access(array('agenda'=>'POSTA'));
  $id=$GLOBALS['EDIT_ID']?$GLOBALS['EDIT_ID']:$GLOBALS['ID'];
  IF ($IDP>0) $id = $IDP;
  $sql='select * from posta where id='.$id;
  $db_sec->query($sql); $db_sec->Next_Record();
  $odchozi = ($db_sec->Record['ODESLANA_POSTA']=="f") ? false : true;
  $sp = HasRole('storno_prichozi_zpracovatel');
  $so = HasRole('storno_odchozi_zpracovatel');
  //  if (HasRole('storno_zpracovatel')) {
  if ((HasRole('storno_prichozi_zpracovatel')&&!$odchozi)||(HasRole('storno_odchozi_zpracovatel')&&$odchozi)) {
    if ($USER_INFO['ID']==$db_sec->Record['REFERENT']) $pristup=true;
  }
  //if (HasRole('storno_uzel')) {
  if ((HasRole('storno_prichozi_uzel')&&!$odchozi)||(HasRole('storno_odchozi_uzel')&&$odchozi)) {
    if (VratOdbor()==$db_sec->Record['ODBOR']) $pristup=true;
    if (in_array($db_sec->Record['REFERENT'],$pracovnici_pode_mnou)) $pristup=true;
    if (in_array($db_sec->Record['ODBOR'],$spisove_uzly_pode_mnou)) $pristup=true;
    if ($db_sec->Record['ODESLANA_POSTA'] == 'f' && $db_sec->Record['DATUM_PREDANI'] == '') $pristup = false;
  }
  if ((HasRole('storno_prichozi_vse_pracoviste')&&!$odchozi)||(HasRole('storno_odchozi_vse_pracoviste')&&$odchozi)) {
  //  if (HasRole('storno_prichozi_vse_pracoviste')) {
    if ($db_sec->Record['SUPERODBOR']==EedTools::VratSuperOdbor()) $pristup=true;
  }
  //if (HasRole('storno_admin')) {
   if ((HasRole('storno_prichozi_admin')&&!$odchozi)||(HasRole('storno_odchozi_admin')&&$odchozi)) {
      $pristup=true;
  }
  if ($pristup) return true;

  $cj_temp_access = LoadClass('EedCj', $id);
  $doc_in_cj = $cj_temp_access->GetDocsInCj($id);
  $doc_in_cj[] = $id;
  unset($cj_temp_access);
  $sql='select * from posta_pristupy where (posta_id='.$id.' and spis=0 and access=\'delete\') or (posta_id in ('.implode(',',$doc_in_cj).') and spis=1 and access=\'delete\')';
  $db_sec->query($sql);
  while ($db_sec->Next_Record()) {
    if ($USER_INFO['ID']==$db_sec->Record['REFERENT']) $pristup=true;
    if (in_array($db_sec->Record['ODBOR'], $nadrizene_odbory)) $pristup=true;
//    if (in_array($db_sec->Record['REFERENT'],$pracovnici_pode_mnou)) $pristup=true;
  }
  return $pristup;
}


function MaPristupKCteniDokumentu($IDP) {
  global $pracovnici_pode_mnou,$spisove_uzly_pode_mnou, $USER_INFO, $db_sec, $nadrizene_odbory;
  $pristupy=array();

  $id=$GLOBALS['EDIT_ID']?$GLOBALS['EDIT_ID']:$GLOBALS['ID'];
  IF ($IDP>0) $id = $IDP;
  $sql='select * from posta where id='.$id;
  $db_sec->query($sql); $db_sec->Next_Record();
  if (HasRole('cteni_zpracovatel')) {
    if ($USER_INFO['ID']==$db_sec->Record['REFERENT']) $pristup=true;
  }
  if (HasRole('cteni_uzel')) {
    if (VratOdbor()==$db_sec->Record['ODBOR']) $pristup=true;
    if (in_array($db_sec->Record['REFERENT'],$pracovnici_pode_mnou)) $pristup=true;
    if (in_array($db_sec->Record['ODBOR'],$spisove_uzly_pode_mnou)) $pristup=true;
//    if ($db_sec->Record['ODESLANA_POSTA'] == 'f' && $db_sec->Record['DATUM_PREDANI'] == '') $pristup = false;

  }
  if (HasRole('cteni_vse_pracoviste')) {
    if ($db_sec->Record['SUPERODBOR']==EedTools::VratSuperOdbor()) $pristup=true;
  }
  if (HasRole('cteni_admin')) {
    $pristup=true;
  }
  if ($pristup) return true;

  if (HasRole('cteni_vse_pracoviste')) {
    $sql='select * from posta where id='.$id .'  and id in (select h.id from (select distinct on (id) id,superodbor from posta_h where superodbor>0 order by id, id_h) as h LEFT JOIN posta p ON p.id=h.id where p.superodbor>0 and p.superodbor<>h.superodbor) ';
    $db_sec->query($sql);
    if ($db_sec->Num_Rows() > 0) {
      $GLOBALS['CONFIG_POSTA']['MAM_PRISTUP'][] = $id;
      return true;
    }
  }


  $cj_temp_access = LoadClass('EedCj', $id);
  $doc_in_cj = $cj_temp_access->GetDocsInCj($id);
  $doc_in_cj[] = $id;
  unset($cj_temp_access);
  $sql='select * from posta_pristupy where (posta_id='.$id.' and spis=0) or (posta_id in ('.implode(',',$doc_in_cj).') and spis=1)';
  $db_sec->query($sql);
  while ($db_sec->Next_Record()) {
    if ($USER_INFO['ID']==$db_sec->Record['REFERENT']) $pristup=true;
    if (in_array($db_sec->Record['ODBOR'], $nadrizene_odbory)) $pristup=true;
    if (VratOdbor() == $db_sec->Record['ODBOR']) $pristup=true;

//    if (in_array($db_sec->Record['REFERENT'],$pracovnici_pode_mnou)) $pristup=true;
  }


//  if (in_array($db_sec->Record['ODBOR'],$spisove_uzly_pode_mnou)) $pristup=true;
//    if ($db_sec->Record['ODESLANA_POSTA'] == 'f' && $db_sec->Record['DATUM_PREDANI'] == '') $pristup = false;


  return $pristup;
}


