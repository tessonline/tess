<?php
require("tmapy_config.inc");
include(FileUp2(".admin/brow_.inc"));
include(FileUp2(".admin/vnitrni_adresati.inc"));
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
$sqla="select * from posta where cislo_spisu1>0 and skartace is null and odes_typ='X' and odeslana_posta='t' and DALSI_PRIJEMCI is not null";
echo $sqla;
$userObj = LoadClass('EedUser',0);
$q->query($sqla);
while ($q->Next_Record())
{

  echo $q->Record["ID"]. ' '. $q->Record['DALSI_PRIJEMCI']. '<br/>';

  $postaId = $q->Record['ID'];

  $prijemci = array();
  $prijemci = explode(',', $q->Record['DALSI_PRIJEMCI']);
  $a = 0; 
  $adresati = array();
  foreach($prijemci as $prijemce) {
    list($superodbor,$odbor,$oddeleni,$ref) = explode(':', $prijemce);
    if ($oddeleni>0) $odbor = $oddeleni;
    $adresati[$a]['ov'] = UkazOdbor($odbor,0,0,1);
    $adresati[$a]['zp'] = $ref;
    
    $a++; 
  }
//  print_r($adresati);
  deleteAll($postaId);
  insert($postaId, $adresati);

/*  $sql2="select skartace from posta where cislo_spisu1=".$q->Record["CISLO_SPISU1"]." and cislo_spisu2=".$q->Record["CISLO_SPISU2"]." order by id asc limit 1";
  $a->query($sql2);
  $a->Next_Record();
  $skartace=$a->Record["SKARTACE"];
  if ($skartace>0)
  {
    $sqlb="UPDATE posta SET skartace=$skartace,last_date='$LAST_DATE',last_time='$LAST_TIME',last_user_id=$LAST_USER_ID WHERE id=".$id;
    $a->query($sqlb);
//    echo $sqlb;
  }
*/

}
