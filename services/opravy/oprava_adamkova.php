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

$oprava = array('SPISOVNA_ID');
$q=new DB_POSTA;
$a=new DB_POSTA;
//$sqla="SELECT p.* from posta p WHERE p.REFERENT IN (7200073) AND p.LAST_USER_ID IN (6200001) AND p.SUPERODBOR IN (62) AND STORNOVANO IS NULL order by id desc ";
$sqla="SELECT * from posta_spisovna where dokument_id=-1";
$q->query($sqla);
while ($q->Next_Record()) {
  $id = $q->Record["ID"];
//   $sql2="select * from posta_h where id=".$q->Record["ID"]." and  (
//   (last_date='2013-08-28' and last_time like '11:%') OR
//   (last_date<'2013-08-28') )
//    order by id_h desc limit 1";
  $sql2="select * from posta_spisovna_h where id=".$q->Record["ID"]." order by id_h desc limit 1";
//  echo $sql2;
  $a->query($sql2);
  $pocet=$a->Num_Rows();
  $a->Next_Record();
  if ($pocet>0)   {
    $count++;
    $update=array();
    foreach($oprava as $sloupec)
      $update[] = $sloupec."=".($a->Record[$sloupec]?"'".$a->Record[$sloupec]."'":'NULL');
    
    $sqlb="UPDATE posta_spisovna SET ".implode(',',$update).",last_date='$LAST_DATE',last_time='$LAST_TIME',last_user_id=$LAST_USER_ID WHERE id=".$id."";
    echo $sqlb."<br/>";
//    $a->query($sqlb);
}  }
 
echo "Celkem $count";
?>
