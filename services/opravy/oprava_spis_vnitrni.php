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
$sqla="select * from posta where cislo_spisu1>0 and skartace is null and odes_typ='X'";
$q->query($sqla);
while ($q->Next_Record())
{

  $id=$q->Record["ID"];
  $sql2="select skartace from posta where cislo_spisu1=".$q->Record["CISLO_SPISU1"]." and cislo_spisu2=".$q->Record["CISLO_SPISU2"]." order by id asc limit 1";
  $a->query($sql2);
  $a->Next_Record();
  $skartace=$a->Record["SKARTACE"];
  if ($skartace>0)
  {
    $sqlb="UPDATE posta SET skartace=$skartace,last_date='$LAST_DATE',last_time='$LAST_TIME',last_user_id=$LAST_USER_ID WHERE id=".$id;
    $a->query($sqlb);
//    echo $sqlb;
  }
}
?>
