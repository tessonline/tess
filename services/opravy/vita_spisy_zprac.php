<?php
require("tmapy_config.inc");
include(FileUp2(".admin/brow_.inc"));
include(FileUp2(".admin/security_obj.inc"));
include(FileUp2(".admin/status.inc"));
set_time_limit(0);
$USER_INFO = $GLOBALS["POSTA_SECURITY"]->GetUserInfo();
$id_user=$USER_INFO["ID"];
$jmeno=$USER_INFO["FNAME"]." ".$USER_INFO["LNAME"];
$LAST_USER_ID=$id_user;
$OWNER_ID=$id_user;
$LAST_TIME=Date('H:m:i');
$LAST_DATE=Date('Y-m-d');
$dnes=Date('d.m.Y');
$q=new DB_POSTA;
$a=new DB_POSTA;
$b=new DB_POSTA;

function VratCislo($text, $start) {
  $res = '';
   for ($a = $start; $a<strlen($text); $a++) {
    $cislo = substr($text, $a, 1);
    if (is_numeric($cislo)) $res .= $cislo;
       else $a = strlen($text)+100;
  }
  return $res;
}

$zpusob_vyrizeni = $GLOBALS["KONEKTOR"]["VITA"]["ZPUSOB_VYRIZENI"] ? $GLOBALS["KONEKTOR"]["VITA"]["ZPUSOB_VYRIZENI"] : '';

$sqla="select id,popis from posta_interface_log where popis like '%a_id=%' and popis like '%a_spisid=%' and popis like '%a_pisvyr=%' order by id asc  ";
$q->query($sqla);
$celkovy_pocet=$q->Num_Rows();
echo '<div id="upl_wait_message" class="text" style="display:block">Hotovo záznamů: 0/'.$celkovy_pocet.'</div>';
echo '<div id="upl_wait_message2" class="text" style="display:block"><img src="'.FileUpUrl('images/progress.gif').'" title="pracuji ..." alt="pracuji ..."></div>';
Flush();
$i=0;
while ($q->Next_Record()) {

   $popis = $q->Record['POPIS'];

   $id_start = strpos($popis, 'a_id=') + 5;
   $idspis_start = strpos($popis, 'a_spisid=') + 9;

   $a_id = VratCislo($popis, $id_start);
   $a_spisid = VratCislo($popis, $idspis_start);

   if ($a_id>0 && $a_spisid<>0) {
     $sql = 'select * from posta where id=' . $a_id;
     $a->query($sql);
     $a->Next_Record();

     if ($a->Record['VYRIZENO'] == '') {
       $sql = "update posta set vyrizeno='$zpusob_vyrizeni' where id=" . $a_id;
       echo $sql.'<br/>';
       $a->query($sql);
       NastavStatus($a_id, $OWNER_ID);

     }


   }

    //zalozime
    /*
    $spis = LoadClass('EedDokument', $GLOBALS['a_spisid']);
    $doc = LoadClass('EedDokument', $GLOBALS['a_id']);
    $sqlx="insert into cis_posta_spisy (PUVODNI_SPIS,NOVY_SPIS,SPIS_ID,DALSI_SPIS_ID,LAST_DATE,LAST_TIME,OWNER_ID,LAST_USER_ID)
    VALUES ('".$spis->cislo_jednaci."','".$doc->cislo_jednaci."',".$GLOBALS['a_spisid'].",".$GLOBALS['a_id'].",'$LAST_DATE','$LAST_TIME',$LAST_USER_ID,$LAST_USER_ID)";

    $x = new DB_POSTA;
    $x->query($sqlx);

    $text = 'VITA: dokument (<b>'.$GLOBALS['a_id'].'</b>) '.$doc->cislo_jednaci.' byl vložen do spisu: <b>' . $spis->cislo_jednaci . '</b>';
    EedTransakce::ZapisLog($GLOBALS["a_spisid"], $text, 'DOC', $id_user);
    */

}
echo "<script>document.getElementById('upl_wait_message2').style.display = 'none'</script>";
echo "<span class=text>HOTOVO.</span>";

?>
