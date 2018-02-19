<?php
require("tmapy_config.inc");
include(FileUp2(".admin/brow_.inc"));
include(FileUp2(".admin/security_obj.inc"));
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

$file = 'decin_vita.csv';
$fp = fopen($file, 'r');
$data = fread($fp, filesize($file));
fclose($fp);

$data_array = explode(chr(10), $data);

$spisy = array();

foreach($data_array as $val) {
  list($pom1, $pom2) = explode(';', $val);
  if ($pom1>0) {
    $spisy[$pom1] = $pom2;
  }

}

echo '<div id="upl_wait_message" class="text" style="display:block">Hotovo záznamů: 0/'.count($spisy).'</div>';
echo '<div id="upl_wait_message2" class="text" style="display:block"><img src="'.FileUpUrl('images/progress.gif').'" title="pracuji ..." alt="pracuji ..."></div>';
Flush();
$i=0;
foreach($spisy as $cj => $spis) {

   $a_id = $cj;
   $a_spisid = $spis;

   if ($a_id>0 && $a_spisid<>0) {

     $sql = 'select * from cis_posta_spisy where spis_id='.$a_spisid.' and dalsi_spis_id='.$a_id;
     $a->query($sql);
     if ($a->Num_Rows()>0) {
       echo "OK - nalezeno a_id= $a_id---- a_spisid= $a_spisid <br/>";

     }
     else {
       echo "NENI - nalezeno a_id= $a_id---- a_spisid= $a_spisid <br/>";

      $spis = LoadClass('EedDokument', $a_spisid);
      $doc = LoadClass('EedDokument', $a_id);
      $sqlx="insert into cis_posta_spisy (PUVODNI_SPIS,NOVY_SPIS,SPIS_ID,DALSI_SPIS_ID,LAST_DATE,LAST_TIME,OWNER_ID,LAST_USER_ID)
      VALUES ('".$spis->cislo_jednaci."','".$doc->cislo_jednaci."',".$a_spisid.",$a_id,'$LAST_DATE','$LAST_TIME',$LAST_USER_ID,$LAST_USER_ID)";

      $x = new DB_POSTA;
      //echo $sqlx.'<br/>';
      if ($_GET['proved'] == 1) $x->query($sqlx);

      $text = 'VITA: dokument (<b>'.$a_id.'</b>) '.$doc->cislo_jednaci.' byl vložen do spisu: <b>' . $spis->cislo_jednaci . '</b> - reimport dat';
      if ($_GET['proved'] == 1) EedTransakce::ZapisLog($a_spisid, $text, 'DOC', $id_user);

      $sql = 'select status from posta where id='.$a_spisid;
      $a->query($sql); $a->Next_Record();
      $status = $a->Record['STATUS'];

      $sql = 'update posta set status='.$status.',last_date=\''.$LAST_DATE.'\',last_time=\''.$LAST_TIME.'\',last_user_id='.$OWNER_ID.' where id='.$a_id;
      if ($_GET['proved'] == 1) $a->query($sql);


     }
   }
}
echo "<script>document.getElementById('upl_wait_message2').style.display = 'none'</script>";
echo "<span class=text>HOTOVO.</span>";

?>
