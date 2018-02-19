<?php
require("tmapy_config.inc");
include(FileUp2(".admin/brow_.inc"));
include(FileUp2(".admin/status.inc"));
include_once(FileUp2(".admin/security_obj.inc")); 
include_once(FileUp2("posta/.admin/properties.inc")); 
include_once(FileUp2(".admin/security_name.inc")); 
$USER_INFO = $GLOBALS["POSTA_SECURITY"]->GetUserInfo();
$id_user=$USER_INFO["ID"];
$datum=date('d.m.Y H:m');
include_once(FileUp2("html_header_full.inc")); 

if (is_array($_POST['SELECT_ID'])) {
  if (count($_POST['SELECT_ID'])>0)
    $_POST['sql'] = str_replace(' ORDER BY ', 'and s.id in (' . implode(',',$_POST['SELECT_ID']). ') ORDER BY ', $_POST['sql']);
}


$sql=$_POST['sql'];
$spisovna_id=$_POST['spisovna_id']?$_POST['spisovna_id']:1;
$komu=$_POST['komu']?$_POST['komu']:0;
if ($komu<1) Die('Chyba');
//print_r($_POST);
$skartace=array();
$q=new DB_POSTA;
$a=new DB_POSTA;
$q->query($sql);

$komu_array = LoadClass('EedUser', $komu);
$zapujceno_komu = $komu_array->jmeno.' ' . $komu_array->prijmeni;

//echo $sql;
$spis_pole=array();
while ($q->Next_Record()) {
  $data=$q->Record;
  if ($data['DOKUMENT_ID']<0) {
    echo '<font color="red">ČJ <b>'.$data['CISLO_SPISU1'].'/'.$data['CISLO_SPISU2'].'</b> bylo ručně založeno do spisovny. Toto čj. není možné dát na výpujčku. Pro vypůjčení tohoto čj. vytvořte ruční zápujčku.</font><br/>';
    continue;
  }
  if ($data['DOKUMENT_ID']>0 && $data['VYHRAZENO'] == 'y') {
    $sql = 'select * from posta where id=' . $data['DOKUMENT_ID'];
    $a->query($sql);
    $a->Next_Record();
    $referent = $a->Record['REFERENT'];
    if ($referent <> $komu) {
      echo '<font color="red">Čj./spis <b>'.$data['CISLO_SPISU1'].'/'.$data['CISLO_SPISU2'].'</b> je označeno jako důverné a je není možné ho půjčit tomuto zpracovateli.</font><br/>';
      continue;
    }
  }

  $upl_obj = LoadClass('EedUploadPdf', $data['DOKUMENT_ID']);
  $upl_obj->unregisterPDF();
  echo "Vytvářím zápujčku pro ".$data['DOKUMENT_ID']." - ".$data['CISLO_SPISU1'].'/'.$data['CISLO_SPISU2']."<br/>";
  $skartace[]=$data['DOKUMENT_ID'];
} 
$skartace=array_unique($skartace);

$sql="insert into posta_spisovna_zapujcky (vytvoreno,vytvoreno_kym,pujceno_komu,spisovna_id,superodbor) values ('".Date('Y-m-d')."',$id_user,$komu,$spisovna_id,".VratSuperOdbor().")";
$q->query($sql);
$zapujcka_id=$q->GetLastId('posta_spisovna_zapujcky','id');
if (!$zapujcka_id || $zapujcka_id<1) Die('Nepovedlo se vytvořit zápůjčku');
while (list($key,$val)=each($skartace)) {
  if ($val>0) {
    $sql="update posta SET spisovna_id=0,last_date='".Date('Y-m-d')."',last_time='".Date('H:i:s')."',last_user_id=".$id_user." where id=".$val;
    $q->query($sql);
    $EedCj = LoadClass('EedCj', $val);
    $docs = $EedCj->GetDocsInCJ($val);
    print_r($docs);
    $docs[] = $val;
    while (list($key2, $val2) = each($docs)) {
      $sql="update posta SET status=1,spisovna_id=0,last_date='".Date('Y-m-d')."',last_time='".Date('H:i:s')."',last_user_id=".$id_user." where id=".$val2;
      $q->query($sql);
      $text = 'dokument byl dán na zápujčku uživateli <b>' . $zapujceno_komu . '</b>';
      EedTransakce::ZapisLog($val2, $text, 'DOC', $id_user);
      $sql="insert into posta_spisovna_zapujcky_id (zapujcka_id,posta_id) values ($zapujcka_id,$val2)";
      $q->query($sql);
    }
//    $q->query($sql);
  }
}

reset($skartace);
// a zapiseme zapujcky do spisovny
while (list($key,$val)=each($skartace)) {
  $sql="update posta_spisovna set zapujcka_id=".$zapujcka_id." where dokument_id=" . $val;
  $q->query($sql);
}
//Die();

echo "<br/><br/><span class='caption'>Hotovo, dokumenty byly zapůjčeny</span><br/>";
echo "
<input type='button' onclick='document.location.href=\"brow.php\";' value='Vrátit se' class='btn'>";
include_once(FileUp2("html_footer.inc")); 
