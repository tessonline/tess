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
$ref = array(67582774,72580611,11931210,44551575,71271425,84223835,91793363,27813603,61319711,47023867,76787484,88508310,93563923,96755955,10350748,69586755,82570537,18987896,76318247,12748257,67727993,90322616,21731247,43099198,77914767,62316703,74206874,95606852,79253940);
$q=new DB_POSTA;
$a=new DB_POSTA;
$sqla="select * from posta where referent in (select id from security_user where login_name in ('" . implode("','", $ref)."'))";
$q->query($sqla);
while ($q->Next_Record())
{

  $id=$q->Record["ID"];
  $ref = $q->Record['REFERENT'];
  $odbor_puv = $q->Record['ODBOR'];

  $user = LoadClass('EedUser', $ref);
  $uzel = $user->VratSpisUzelZOdboru($user->odbor_id);
  $uzel_id = $uzel['ID'];
  if ($uzel_id<>$odbor_puv) {
     $update="odbor=$uzel_id";
     $sqlb="UPDATE posta SET $update,last_date='$LAST_DATE',last_time='$LAST_TIME',last_user_id=$LAST_USER_ID WHERE id=".$id."";
     $a->query($sqlb);
     echo "puvodni $odbor_puv a nove je $uzel_id - $sqlb<br/>";
  }
}
