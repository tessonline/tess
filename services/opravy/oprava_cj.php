<?php
require("tmapy_config.inc");
include(FileUp2(".admin/brow_.inc"));
include(FileUp2(".admin/security_obj.inc"));
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
$sqla='select * from posta where cislo_jednaci1 is null';
$q->query($sql);
while ($q->Next_Record())
{
  $id=$q->Record["ID"];
  $ev_cislo=$q->Record["EV_CISLO"];
  $rok=$q->Record["ROK"];
  $sqlb="UPDATE posta SET cislo_jednaci1=$ev_cislo,cislo_jednaci2=$rok,last_date='$LAST_DATE',last_time='$LAST_TIME',last_user_id=$LAST_USER_ID WHERE id=".$id;
//  $a->query($sqlb);
  echo $sqlb;
}
?>
