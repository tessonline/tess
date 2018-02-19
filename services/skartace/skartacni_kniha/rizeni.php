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
include_once(FileUp2("html_header_full.inc")); 

if (is_array($_POST['SELECT_ID']) && !$_POST['box']) {
  if (count($_POST['SELECT_ID'])>0)
    $_POST['sql'] = str_replace(' ORDER BY ', 'and s.id in (' . implode(',',$_POST['SELECT_ID']). ') ORDER BY ', $_POST['sql']);
}

$sql_zaklad=$_POST['sql'];



//echo $sql;
$spisovna_id=$_POST['spisovna'];

$uloz=false;

$q = new DB_POSTA;
$a = new DB_POSTA;

if ($_POST['rizeni_id']) $lastId = $_POST['rizeni_id'];

if (!$lastId) {

  //zalozime nove skartacni rizeni

  $EedSql = LoadClass('EedSql');
  $idMain = $EedSql->createCJ($id_user);

  $sql = "update posta set vec='Skartační řízení',datum_predani_ven=datum_predani where id=".$idMain;
  $q->query($sql);
  NastavStatus($idMain, $id_user);
  $docMain = LoadClass('EedDokument', $idMain);
  $text = 'Vytvoření nového dokumentu';
  EedTransakce::ZapisLog($idMain, $text, 'DOC', $id_user);



  $sqlZaloz = "insert into posta_skartace (SUPERODBOR,DATUM_ZAHAJENI,SPIS_ID,CJ) VALUES (".VratSuperOdbor().",'".Date('Y-m-d')."',$idMain,'".$docMain->cislo_jednaci."')";
  $q->query($sqlZaloz);

  $lastId = $q->getLastId('posta_skartace', 'id');

  $jid = $GLOBALS['CONFIG']['ID_PREFIX'] . 'SR' . $lastId;
  $sql = "update posta_skartace set jid='$jid' where id=" . $lastId;
  $q->query($sql);

  $text = 'Byl založen spis pro nové skartační řízení: <b>' . $jid . '</b>';
  EedTransakce::ZapisLog($idMain, $text, 'DOC', $id_user);
  EedTransakce::ZapisLog($idMain, $text, 'SPIS', $id_user);


  $sql = "insert into cis_posta_spisy (PUVODNI_SPIS,NOVY_SPIS,SPIS_ID,DALSI_SPIS_ID,LAST_DATE,LAST_TIME,LAST_USER_ID,OWNER_ID,NAZEV_SPISU) VALUES ";
  $sql .= "('".$docMain->cislo_jednaci."','".$docMain->cislo_jednaci."',$idMain, 0, '$last_date','$last_time',$id_user,$id_user,'Skartační řízení $jid')";
  $q->query($sql);

  echo '<h1>Řízení bylo založeno</h1>';
  echo '<p><span class="text">Poznámka: Nezapomeňte do spisu ' . $docMain->cislo_jednaci . ' přiřadit číslo jednací s návrhem skartační komise.</span></p>';

}
else {
  $sql = 'select jid from posta_skartace where id=' . $lastId;
  $q->query($sql); $q->Next_Record();
  $jid = $q->Record['JID'];
  echo '<h1>Do řízení byly přidány dokumenty.</h1>';

}


$sql=$_POST['sql'];

$q->query($sql);
While($q->Next_Record()) {
  $doc_id = $q->Record['ID'];
  $dokument_id = $q->Record['DOKUMENT_ID'];
  $docObj = LoadClass('EedCj', $dokument_id);
  $cj = $docObj->cislo_jednaci_zaklad;
  $sql_temp = 'INSERT INTO POSTA_SKARTACE_ID (SKARTACE_ID,SPISOVNA_ID) VALUES ('.$lastId.','.$doc_id.')';
  $a->query($sql_temp);
  $text = 'Spis/čj. <b>' . $cj. '</b> byl vložen do skartačního řízení <b>' . $jid . '</b>';
  EedTransakce::ZapisLog($dokument_id, $text, 'SPIS', $id_user);
}

echo "
<input type='button' onclick='document.location.href=\"brow.php?SKARTACNI_RIZENI_ID=".$lastId."\";' value='Pokračovat' class='btn'>";
include_once(FileUp2("html_footer.inc"));

$protokol=false;