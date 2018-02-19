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
set_time_limit(0);
$sqla="select id from posta where referent in (677) and id in (select spis_id from cis_posta_spisy where dalsi_spis_id=0 or dalsi_spis_id=spis_id) and spis_vyrizen is NULL and status=9";
$q->query($sqla);
while ($q->Next_Record()) {
   $id = $q->Record['ID'];
   $cj = LoadClass('EedCj', $id);
   $docs = $cj->GetDocsInCj($id);

   if (count($docs)>0) {
     $update="spis_vyrizen='" . Date('Y-m-d') . "', status=1 ";
     $sqlb="UPDATE posta SET $update,last_date='$LAST_DATE',last_time='$LAST_TIME',last_user_id=$LAST_USER_ID WHERE id in (".implode(',', $docs).")";
     $a->query($sqlb);
     echo $sqlb."<br/>";

    $cj_info = $cj->GetCjInfo($id);

    $text = $cj_info['CELY_NAZEV'] . ' byl uzavřen.';
    //echo $text;
    EedTransakce::ZapisLog($id, $text, 'SPIS');

   }
}
?>
