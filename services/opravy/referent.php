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
$sqla="select * from posta where referent in (547,5)";
$q->query($sqla);
while ($q->Next_Record())
{

  $id=$q->Record["ID"];
  $sql2="select * from posta_h where id=".$q->Record["ID"]." and referent<>547 order by id desc limit 1";
//  $pocet=$a->Num_Rows();
  $a->query($sql2);
  $a->Next_Record();
  $ref=$a->Record["REFERENT"]?$a->Record["REFERENT"]:'0';
  if ($ref1<1) 
  {
    $update="referent=NULL";
//    $update="cislo_spisu1 =$cs1 ,cislo_spisu2=$cs2,nazev_spisu='".$nazev."'";
  }
  else
  {
    $update="referent=$ref";
  }
   $sqlb="UPDATE posta SET $update,last_date='$LAST_DATE',last_time='$LAST_TIME',last_user_id=$LAST_USER_ID WHERE id=".$id."";
   $a->query($sqlb);
   echo $sqlb."<br/>";
}
?>
