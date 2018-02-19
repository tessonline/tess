<?php
require("tmapy_config.inc");
include(FileUp2(".admin/brow_.inc"));
include(FileUp2(".admin/run2_.inc"));
include_once(FileUp2(".admin/status.inc"));
include_once(FileUp2(".admin/security_name.inc"));
include_once(FileUp2('services/spisovka/uzavreni_spisu/funkce.inc'));
include_once(FileUp2(".admin/security_obj.inc"));
include_once(FileUp2(".admin/upload_.inc"));



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


$sql = 'select * from posta_skartace where id='.$_POST['skartacni_rizeni_id'];
$q->query($sql);
$q->Next_Record();

$spis_id = $q->Record['SPIS_ID'];

$docMain = LoadClass('EedDokument', $spis_id);



$sql = "update posta_skartace set DATUM_UZAVRENI='".Date('Y-m-d')."' where id=".$_POST['skartacni_rizeni_id'];
$q->query($sql);



echo '<h1>Řížení bylo ukončeno</h1>';
echo "
<input type='button' onclick='document.location.href=\"../../../brow.php?frame&ID=".$spis_id."\";' value='Vrátit se' class='btn' target='_top'>";
include_once(FileUp2("html_footer.inc"));

$protokol=false;