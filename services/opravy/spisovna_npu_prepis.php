<?php
require("tmapy_config.inc");
include(FileUp2(".admin/brow_.inc"));
include(FileUp2(".admin/security_obj.inc"));
include("spisovna_fce.inc");
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
//$sqla="select * from posta where status=2 or status is null and id=157198";
$pole_ids = array(919949558,1000039793,1000070102,1000076948,920308542,1000064154,919957070);
$celkovy_pocet=count($pole_ids);
echo '<div id="upl_wait_message" class="text" style="display:block">Hotovo záznamů: 0/'.$celkovy_pocet.'</div>';
echo '<div id="upl_wait_message2" class="text" style="display:block"><img src="'.FileUpUrl('images/progress.gif').'" title="pracuji ..." alt="pracuji ..."></div>';
Flush();
$i=0;
while (list($key,$doc_id)=each($pole_ids))
{
  
  $digitalnich=0;
  $pole = NactiDataProSpisovnu($doc_id);
  $pole2 = NaciUdajeZHistoriePosty($doc_id, $pole);
  $sql = CreaSQLFromData(1,$doc_id,$pole2);
  echo $sql;
  echo "<hr/>";
}
echo "<script>document.getElementById('upl_wait_message2').style.display = 'none'</script>";
echo "<span class=text>Celkem je problem s $i .HOTOVO.</span>";

?>
