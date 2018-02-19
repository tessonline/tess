<?php
require("tmapy_config.inc");
include(FileUp2(".admin/brow_.inc"));
include(FileUp2(".admin/run2_.inc"));
include_once(FileUp2(".admin/status.inc"));
include_once(FileUp2(".admin/security_name.inc"));
include_once(FileUp2('services/spisovka/uzavreni_spisu/funkce.inc'));
include_once(FileUp2(".admin/security_obj.inc"));
include_once(FileUp2(".admin/upload_.inc"));

include(FileUp2(".admin/oth_funkce.inc"));
include_once(FileUp2(".admin/security_name.inc"));

$USER_INFO = $GLOBALS["POSTA_SECURITY"]->GetUserInfo();
$id_user=$USER_INFO["ID"];
$last_date=Date('Y-m-d');
$last_time=Date('H:i:s');
$datum=date('d.m.Y H:m');
include_once(FileUp2("html_header_full.inc")); 

$sql_zaklad=$_POST['sql'];
$spisovna_id=$_POST['spisovna'];

$uloz=false;


$q = new DB_POSTA;
$a = new DB_POSTA;

include(FileUp2("../../output/pdf/skartaceInc.php"));


$docMain = LoadClass('EedDokument', $idMain);

$sql = 'select * from posta_skartace where id='.$_POST['skartacni_rizeni_id'];
$q->query($sql);
$q->Next_Record();

$spis_id = $q->Record['SPIS_ID'];

$docMain = LoadClass('EedDokument', $spis_id);


$EedSql = LoadClass('EedSql');
$idArchivalie = $EedSql->createCJ($id_user);

$sql = "update posta set vec='žádost o provedení výběru archiválií ve skartačním řízení',odeslana_posta='t',datum_predani_ven=datum_predani where id=".$idArchivalie;
$q->query($sql);
NastavStatus($idArchivalie, $id_user);


$docArchivalie = LoadClass('EedDokument', $idArchivalie);

$sql = "insert into cis_posta_spisy (PUVODNI_SPIS,NOVY_SPIS,SPIS_ID,DALSI_SPIS_ID,LAST_DATE,LAST_TIME,LAST_USER_ID,OWNER_ID) VALUES ";
$sql .= "('".$docMain->cislo_jednaci."','".$docArchivalie->cislo_jednaci."',$spis_id, $idArchivalie, '$last_date','$last_time',$id_user,$id_user)";
$q->query($sql);


$_POST['pismeno'] = 'S';
$stream = GenerujSkartacniProtokol($_POST);
$nameS = $GLOBALS[CONFIG_POSTA][HLAVNI][tmp_adresar].'protokol_skartace.pdf';
if (file_exists($nameS)) unlink($nameS);
$protokolS = $stream->Output($nameS, 'F');

$_POST['pismeno'] = 'A';
$stream = GenerujSkartacniProtokol($_POST);
$nameA = $GLOBALS[CONFIG_POSTA][HLAVNI][tmp_adresar].'protokol_archivace.pdf';
if (file_exists($nameA)) unlink($nameA);
$protokolS = $stream->Output($nameA, 'F');

$_POST['pismeno'] = 'V';
$stream = GenerujSkartacniProtokol($_POST);
$nameV = $GLOBALS[CONFIG_POSTA][HLAVNI][tmp_adresar].'protokol_vyber.pdf';
if (file_exists($nameV)) unlink($nameV);
$protokolS = $stream->Output($nameV, 'F');


$uplobj=Upload(array('create_only_objects'=>true,'agenda'=>'POSTA','noshowheader'=>true));
$ret = $uplobj['table']->SaveFileToAgendaRecord($nameA, $idArchivalie);
if ($ret[err_msg]<>'') echo 'Chyba pri ulozeni souboru '.$nameA.': '.$ret[err_msg];
$ret = $uplobj['table']->SaveFileToAgendaRecord($nameS, $idArchivalie);
if ($ret[err_msg]<>'') echo 'Chyba pri ulozeni souboru '.$nameS.': '.$ret[err_msg];
$ret = $uplobj['table']->SaveFileToAgendaRecord($nameV, $idArchivalie);
if ($ret[err_msg]<>'') echo 'Chyba pri ulozeni souboru '.$nameV.': '.$ret[err_msg];


//Die($idMain);
//$1000311551

$sql = "update posta_skartace set DATUM_ODESLANI='".Date('Y-m-d')."' where id=".$_POST['skartacni_rizeni_id'];
$q->query($sql);



echo '<h1>Žádost byla založena</h1>';
echo "
<input type='button' onclick='document.location.href=\"brow.php?SKARTACNI_RIZENI_ID=".$_POST['skartacni_rizeni_id']."\";' value='Pokračovat' class='btn'>";
include_once(FileUp2("html_footer.inc"));

$protokol=false;