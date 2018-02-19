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
//echo $sql;
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


//skartace
$EedSql = LoadClass('EedSql');
$idArchivalie = $EedSql->createCJ($id_user);

$sql = "update posta set vec='seznam dokumentů určených ke skartaci',odeslana_posta='t',datum_predani_ven=datum_predani where id=".$idArchivalie;
$q->query($sql);
NastavStatus($idArchivalie, $id_user);


$docArchivalie = LoadClass('EedDokument', $idArchivalie);

$sql = "insert into cis_posta_spisy (PUVODNI_SPIS,NOVY_SPIS,SPIS_ID,DALSI_SPIS_ID,LAST_DATE,LAST_TIME,LAST_USER_ID,OWNER_ID) VALUES ";
$sql .= "('".$docMain->cislo_jednaci."','".$docArchivalie->cislo_jednaci."',$spis_id, $idArchivalie, '$last_date','$last_time',$id_user,$id_user)";
$q->query($sql);


$_POST['pismeno'] = 'S';
$text = 'Finální seznam dokumentů určených ke skartaci';
$stream = GenerujSkartacniProtokol($_POST, $text);

$nameS = $GLOBALS[CONFIG_POSTA][HLAVNI][tmp_adresar].'protokol_skartace.pdf';
if (file_exists($nameS)) unlink($nameS);
$protokolS = $stream->Output($nameS, 'F');

$uplobj=Upload(array('create_only_objects'=>true,'agenda'=>'POSTA','noshowheader'=>true));
$ret = $uplobj['table']->SaveFileToAgendaRecord($nameS, $idArchivalie);
if ($ret[err_msg]<>'') echo 'Chyba pri ulozeni souboru '.$nameS.': '.$ret[err_msg];


//archivace
$idArchivalie = $EedSql->createCJ($id_user);

$sql = "update posta set vec='seznam dokumentů určených k archivaci',odeslana_posta='t' where id=".$idArchivalie;
$q->query($sql);


$docArchivalie = LoadClass('EedDokument', $idArchivalie);

$sql = "insert into cis_posta_spisy (PUVODNI_SPIS,NOVY_SPIS,SPIS_ID,DALSI_SPIS_ID,LAST_DATE,LAST_TIME,LAST_USER_ID,OWNER_ID) VALUES ";
$sql .= "('".$docMain->cislo_jednaci."','".$docArchivalie->cislo_jednaci."',$spis_id, $idArchivalie, '$last_date','$last_time',$id_user,$id_user)";
$q->query($sql);

$_POST['pismeno'] = 'A';
$text = 'Finální seznam dokumentů určených k archivaci';
$stream = GenerujSkartacniProtokol($_POST, $text);

$nameA = $GLOBALS[CONFIG_POSTA][HLAVNI][tmp_adresar].'protokol_archivace.pdf';
if (file_exists($nameA)) unlink($nameA);
$protokolS = $stream->Output($nameA, 'F');


$uplobj=Upload(array('create_only_objects'=>true,'agenda'=>'POSTA','noshowheader'=>true));
$ret = $uplobj['table']->SaveFileToAgendaRecord($nameA, $idArchivalie);
if ($ret[err_msg]<>'') echo 'Chyba pri ulozeni souboru '.$nameA.': '.$ret[err_msg];


//Die($idMain);
//$1000311551

$sql = "update posta_skartace set DATUM_SKARTACE='".Date('Y-m-d')."' where id=".$_POST['skartacni_rizeni_id'];
$q->query($sql);



echo '<h1>Finální seznamy byly založeny</h1>';
echo "
<input type='button' onclick='document.location.href=\"brow.php?SKARTACNI_RIZENI_ID=".$_POST['skartacni_rizeni_id']."\";' value='Pokračovat' class='btn'>";
include_once(FileUp2("html_footer.inc"));

$protokol=false;