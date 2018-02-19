<?php
require("tmapy_config.inc");
include(FileUp2(".admin/brow_.inc"));
include_once(FileUp2(".admin/status.inc"));
include(FileUp2(".admin/security_obj.inc"));

require_once(GetAgendaPath('POSTA',false,false).'/.admin/classes/EedSchvalovani.inc');
$user_obj = new EedUser;

$USER_INFO = $GLOBALS["POSTA_SECURITY"]->GetUserInfo();

$id_user=$USER_INFO["ID"];

$jmeno =$user_obj->GetUserName();
$LAST_USER_ID=$id_user;
$OWNER_ID=$id_user;
$LAST_TIME=Date('H:m:i');
$LAST_DATE=Date('Y-m-d');
$dnes=Date('d.m.Y');
//$sql="update posta set spis_vyrizen=NULL,last_date='$LAST_DATE',last_time='$LAST_TIME',last_user_id=$LAST_USER_ID   where cislo_spisu1=".$spis1." and cislo_spisu2=".$spis2."";
$text='Dne <b>'.$dnes.'</b> v <b>'.$LAST_TIME.'</b> uživatel <b>'.$jmeno.'</b> stornoval tento záznam. Důvod: <b>'.$duvod.'</b>';
//echo $text;
//Die();
$q=new DB_POSTA;
$sql="UPDATE posta_schvalovani SET STORNOVANO='$text',last_date='$LAST_DATE',last_time='$LAST_TIME',last_user_id=$LAST_USER_ID WHERE id=".$ID;
//echo $sql;
$q->query($sql);
$sql="SELECT posta_id from posta_schvalovani  WHERE id=".$ID;
//echo $sql;
$q->query($sql);
$q->Next_Record();
NastavStatus($q->Record['POSTA_ID'], $id_user);

?>
<script language="JavaScript" type="text/javascript">
<!--
  window.parent.location.reload();
  window.close();
//-->
</script>






