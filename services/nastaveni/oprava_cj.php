<?php
require("tmapy_config.inc");
include(FileUp2(".admin/brow_.inc"));
include(FileUp2(".admin/db/db_posta.inc"));
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
$sqla='select * from posta where ev_cislo>23250 and rok=2006';
//$sqla='select * from posta where ev_cislo>22540 and rok=2006';
$q->query($sqla);
while ($q->Next_Record())
{
  $id=$q->Record["ID"];
  $cislo_jednaci1=$q->Record["CISLO_JEDNACI1"];
  $cislo_jednaci1=$cislo_jednaci1+468;
//  $rok=$q->Record["ROK"];
  $sqlb="UPDATE posta SET cislo_jednaci1=$cislo_jednaci1,last_date='$LAST_DATE',last_time='$LAST_TIME',last_user_id=$LAST_USER_ID WHERE id=".$id;
//  $a->query($sqlb);
  echo $sqlb."<br/>";
}
?>
