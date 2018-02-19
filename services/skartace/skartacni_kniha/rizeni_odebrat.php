<?php
require("tmapy_config.inc");
include(FileUp2(".admin/brow_.inc"));
include_once(FileUp2(".admin/status.inc"));
include_once(FileUp2(".admin/security_name.inc"));
include_once(FileUp2('services/spisovka/uzavreni_spisu/funkce.inc'));
include_once(FileUp2(".admin/security_obj.inc")); 
$USER_INFO = $GLOBALS["POSTA_SECURITY"]->GetUserInfo();
$id_user=$USER_INFO["ID"];
$last_date=Date('Y-m-d');
$last_time=Date('H:i:s');
$datum=date('d.m.Y H:m');
include_once(FileUp2("html_header_full.inc")); 

if (is_array($_POST['SELECT_ID']) && !$_POST['box']) {
  if (count($_POST['SELECT_ID'])>0)
    $_POST['sql'] = str_replace(' ORDER BY ', ' and s.id in (' . implode(',',$_POST['SELECT_ID']). ') ORDER BY ', $_POST['sql']);
}

$sql_zaklad=$_POST['sql'];
//echo $sql;
$spisovna_id=$_POST['spisovna'];

$uloz=false;

$q = new DB_POSTA;
$a = new DB_POSTA;

if ($_POST['skartacni_rizeni_id']) {
  $lastId = $_POST['skartacni_rizeni_id'];
  $sql = 'select jid from posta_skartace where id=' . $lastId;
  $q->query($sql); $q->Next_Record();
  $jid = $q->Record['JID'];
}

$sql=$_POST['sql'];

$q->query($sql);
While($q->Next_Record()) {
  $doc_id = $q->Record['ID'];
  $dokument_id = $q->Record['DOKUMENT_ID'];
  $docObj = LoadClass('EedCj', $dokument_id);
  $cj = $docObj->cislo_jednaci_zaklad;
  $text = 'Spis/čj. <b>' . $cj. '</b> byl odebrán ze skartačního řízení <b>' . $jid . '</b>';
  EedTransakce::ZapisLog($dokument_id, $text, 'SPIS', $id_user);

  $sql_temp = 'DELETE FROM POSTA_SKARTACE_ID where SPISOVNA_ID= '.$doc_id;
  $a->query($sql_temp);
}

echo "
<h1>Dokument(y) byl(y) odebrán(y)</h1>
<input type='button' onclick='document.location.href=\"brow.php?SKARTACNI_RIZENI_ID=".$lastId."\";' value='Pokračovat' class='btn'>";
include_once(FileUp2("html_footer.inc"));

$protokol=false;