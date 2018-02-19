<?php
require("tmapy_config.inc");
include(FileUp2(".admin/brow_.inc"));
include(FileUp2(".admin/security_obj.inc"));
$USER_INFO = $GLOBALS["POSTA_SECURITY"]->GetUserInfo();
$id_user=$USER_INFO["ID"];
$jmeno=$USER_INFO["FNAME"]." ".$USER_INFO["LNAME"];
$LAST_USER_ID=$id_user;
$OWNER_ID=$id_user;
$LAST_TIME=Date('H:i:s');
$LAST_DATE=Date('Y-m-d');
$dnes=Date('d.m.Y');

$oprava = array('ODBOR','ODDELENI','REFERENT','STATUS','VYRIZENO','STAV'); 
$q=new DB_POSTA;
$a=new DB_POSTA;
$sqla="select id,last_date,last_time,last_user_id from posta where referent=3129 and rok=2016 and last_date='2016-08-03' and last_time like '09:39:%' order by last_time";
$q->query($sqla);
while ($q->Next_Record()) {
  $id = $q->Record["ID"];
  $sql2="select * from posta_h where id=".$q->Record["ID"]." and referent<>3129 order by id_h desc limit 1";
//  echo $sql2;
  $a->query($sql2);
  $pocet=$a->Num_Rows();
  $a->Next_Record();
  if ($pocet>0)   {
    $count++;
    $update=array();
    foreach($oprava as $sloupec)
      $update[] = $sloupec."=".($a->Record[$sloupec]?"'".$a->Record[$sloupec]."'":'NULL');
    
    $sqlb="UPDATE posta SET ".implode(',',$update).",last_date='$LAST_DATE',last_time='$LAST_TIME',last_user_id=$LAST_USER_ID WHERE id=".$id."";
    echo $sqlb."<br/>";
//    $a->query($sqlb);
}  }
 
echo "Celkem $count";
?>
