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
$sqla="select * from posta p WHERE (stav<>2 or stav is null) AND (stornovano is null or stornovano like '') and (skartovano is null or skartovano like '') ";
if ($GLOBALS["CONFIG"]["DB"]=="psql")
{
$where_cervene=" AND odeslana_posta='f' AND (datum_vyrizeni IS NULL or datum_vyrizeni='') AND (p.DATUM_PODATELNA_PRIJETI,)+CAST( LHUTA || ' days' AS interval ) < CURRENT_DATE";
$where_zlute=" AND odeslana_posta='f' AND datum_vyrizeni IS NULL AND  (p.DATUM_PODATELNA_PRIJETI,)+CAST( LHUTA-5 || ' days' AS interval ) < CURRENT_DATE  AND  (p.DATUM_PODATELNA_PRIJETI,)+CAST( LHUTA || ' days' AS interval ) >= CURRENT_DATE";
}
if ($GLOBALS["CONFIG"]["DB"]=="mssql")
{
  $where_cervene= " AND odeslana_posta='f' AND datum_vyrizeni IS NULL AND CONVERT(datetime,DATUM_PODATELNA_PRIJETI,104)+LHUTA < GETDATE()";
  $where_zlute= " AND odeslana_posta='f' AND datum_vyrizeni IS NULL AND CONVERT(datetime,DATUM_PODATELNA_PRIJETI,104)+(LHUTA-5) < GETDATE()  AND  CONVERT(datetime,DATUM_PODATELNA_PRIJETI,104)+LHUTA > GETDATE()";

}
$q->query($sqla.$where_zlute);
$celkovy_pocet=$q->Num_Rows();
echo '<div id="upl_wait_message" class="text" style="display:block">Hotovo záznamů: 0/'.$celkovy_pocet.'</div>';
echo '<div id="upl_wait_message2" class="text" style="display:block"><img src="'.FileUpUrl('images/progress.gif').'" title="pracuji ..." alt="pracuji ..."></div>';
Flush();
$i=0;
while ($q->Next_Record())
{
  $i++;
  if ($i%100==0) 
  {
    echo "<script>document.getElementById('upl_wait_message').innerHTML = 'Hotovo záznamů: ".$i."/".$celkovy_pocet."'</script>";
    Flush();
  }
  $id=$q->Record["ID"];
  $status=5;
  $sql="UPDATE posta SET status=$status,last_date='$LAST_DATE',last_time='$LAST_TIME',last_user_id=$LAST_USER_ID WHERE id=".$id;
  $a->query($sql);
}
$q->query($sqla.$where_cervene);
//echo $sqla.$where_cervene;
$celkovy_pocet=$q->Num_Rows();
Flush();
$i=0;
while ($q->Next_Record())
{
  $i++;
  if ($i%100==0) 
  {
    echo "<script>document.getElementById('upl_wait_message').innerHTML = 'Hotovo záznamů: ".$i."/".$celkovy_pocet."'</script>";
    Flush();
  }
  $id=$q->Record["ID"];
  $status=6;
  $sql="UPDATE posta SET status=$status,last_date='$LAST_DATE',last_time='$LAST_TIME',last_user_id=$LAST_USER_ID WHERE id=".$id;
  $a->query($sql);
}


echo "<script>document.getElementById('upl_wait_message2').style.display = 'none'</script>";
echo "<span class=text>HOTOVO.</span>";

?>
