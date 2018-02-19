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
$sqla=" select id,datum_podatelna_prijeti,last_date from posta where char_length(datum_podatelna_prijeti)<3 or datum_podatelna_prijeti is NULL";
$q->query($sqla);
while ($q->Next_Record()){

  $id=$q->Record["ID"];

  $sql2="select datum_podatelna_prijeti from posta_h where id=".$id." and datum_podatelna_prijeti is not null order by id desc limit 1";
  $a->query($sql2);
  $a->Next_Record();
  $datum=$a->Record["DATUM_PODATELNA_PRIJETI"];

  if ($datum>0)  {
    $sqlb="UPDATE posta SET datum_podatelna_prijeti='$datum',last_date='$LAST_DATE',last_time='$LAST_TIME',last_user_id=$LAST_USER_ID WHERE id=".$id;
//    $a->query($sqlb);
    echo $sqlb . '<br/>';
  }

}
