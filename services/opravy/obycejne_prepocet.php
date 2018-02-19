<?php
require('tmapy_config.inc');
include(FileUp2('.admin/brow_.inc'));
include(FileUp2('.admin/status.inc'));
include(FileUp2('.admin/security_obj.inc'));
set_time_limit(0);

//skript slouzi k uzavreni vsech cj ve spisu - pokud bylo uzavreno jenom inicializacni cj a nebyly uzavreny ostatni cj.

$USER_INFO = $GLOBALS['POSTA_SECURITY']->GetUserInfo();
$id_user = $USER_INFO['ID'];
$jmeno = $USER_INFO['FNAME'].' '.$USER_INFO['LNAME'];
$LAST_USER_ID = $id_user;
$OWNER_ID = $id_user;
$LAST_TIME = Date('H:m:i');
$LAST_DATE = Date('Y-m-d');
$dnes = Date('d.m.Y');
$q = new DB_POSTA;
$a = new DB_POSTA;
$b = new DB_POSTA;
$c = new DB_POSTA;

$sqla = "alter table posta disable trigger posta_history;";
$q->query($sqla);

//$sqla = 'select * from cis_posta_spisy where spis_id = 01000004058';
//$sqla = 'select * from posta where cislo_spisu2<2012 and referent>0 order by id desc limit 500';
$sqla = 'select * from posta where vlastnich_rukou=\'1\' and doporucene=\'1\' and datum_vypraveni is null';

$b->query($sqla);
$celkovy_pocet=$q->Num_Rows();
echo '<div id="upl_wait_message" class="text" style="display:block">Hotovo záznamů: 0/'.$celkovy_pocet.'</div>';
echo '<div id="upl_wait_message2" class="text" style="display:block"><img src="'.FileUpUrl('images/progress.gif').'" title="pracuji ..." alt="pracuji ..."></div>';
Flush();
$i=0;
$usrObj = LoadClass('EedUser', $id_user);

while ($b->Next_Record()) {
  $id = $b->Record['ID'];
  $referent = $b->Record['REFERENT'];
  $odbor = $b->Record['ODBOR'];
  $sql="update posta set datum_vypraveni=datum_podatelna_prijeti,last_date='$LAST_DATE',last_time='$LAST_TIME',last_user_id=$LAST_USER_ID where id=".$id;
  $q->query($sql);
  NastavStatus($id, $id_user);
}

$sqla = "alter table posta enable trigger posta_history;";
$q->query($sqla);

echo "<script>document.getElementById('upl_wait_message2').style.display = 'none'</script>";
echo "<span class=text>HOTOVO.</span>";

?>
