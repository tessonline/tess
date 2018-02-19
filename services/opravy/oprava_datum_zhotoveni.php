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
$sqla="select * from posta where DATUM_VYRIZENI is NULL and cislo_spisu1<1";
$q->query($sqla);
while ($q->Next_Record())
{

$count++;
   $id=$q->Record["ID"];
   $dat_vyr=$q->Record["DATUM_VYRIZENI"];
   $stav=$q->Record["STAV"];
//    $sql2="select datum_vyrizeni from posta_h where id=".$q->Record["ID"]." and  
//    ((DATUM_VYRIZENI) >= ('8.4.2008')
//    or2008-04-09
//    ((DATUM_VYRIZENI,'YYYY-FMMM-FMDD') >= ('8.4.2008')
//    datum_vyrizeni like '%.%' order by id desc limit 1";
$sql2="select datum_vyrizeni from posta_h where id=".$q->Record["ID"]." and
and char_length(DATUM_VYRIZENI)>8  
   order by id desc limit 1";
 //  $pocet=$a->Num_Rows();
 $a->query($sql2);
 $a->Next_Record();
  $datum="";
  $datum=$a->Record["DATUM_VYRIZENI"];
  if ($datum=="") 
  {
    $update="datum_vyrizeni=NULL";
  }
  else
  {
    $update="datum_vyrizeni = '".$datum."'";
  }
   $sqlb="$stav - $dat_vyr -  UPDATE posta SET $update,last_date='$LAST_DATE',last_time='$LAST_TIME',last_user_id=$LAST_USER_ID WHERE id=".$id."";
   //$a->query($sqlb);
   echo $sqlb."<br/>";
}
echo "Celkem $count";
?>
