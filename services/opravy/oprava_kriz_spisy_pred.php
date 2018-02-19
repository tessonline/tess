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
$sqla="select s.id, s.puvodni_spis from posta_krizovy_spis s LEFT JOIN posta p ON s.puvodni_spis=p.id WHERE p.main_doc=0 and p.stornovano is null";



$q->query($sqla);
while ($q->Next_Record())
{

  $id=$q->Record["ID"];
  $spis=$q->Record["PUVODNI_SPIS"];

//echo "ONMA".$spis;
  $cj_obj = LoadClass('EedCj',$spis);
  $doc = $cj_obj->GetCjInfo($spis);
  $spis_id = $doc['SPIS_ID'];
  echo " ".$spis." - ".$spis_id."<br/>";
  if ($spis<>$spis_id) 
  {
    $update="update posta_krizovy_spis set puvodni_spis=".$spis_id." where id=".$id;
   $a->query($update);
//    $update="cislo_spisu1 =$cs1 ,cislo_spisu2=$cs2,nazev_spisu='".$nazev."'";
  }
//   $a->query($sqlb);
   echo $sqlb."<br/>";
}
?>
