<?php
require("tmapy_config.inc");
require(FileUp2(".admin/brow_.inc"));
require(FileUp2("html_header_full.inc"));
require(GetAgendaPath('POSTA_INTERFACE_TWIST',false,false).'/../.admin/certifikat_funkce.inc');
$q=new DB_POSTA;
$a=new DB_POSTA;
$sql="select id,osoba from posta_certifikaty where zneplatneni_datum is null or zneplatneni_datum like ''";
$q->query($sql);
while ($q->Next_Record())
{
  $id=$q->Record[ID];
  $cert=VratCertifikat($q->Record[OSOBA],$id,1);
  //openssl_pkey_export($cert[CONTENT],$text);
  $info=openssl_x509_parse($cert[CONTENT]);
  $valid_from=Date('Y-m-d',$info[validFrom_time_t]);
  $valid_to=Date('Y-m-d',$info[validTo_time_t]);
  //echo $info[validFrom_time_t]." - ".strtotime("now")." - ".$info[validTo_time_t]." x ";Flush();
  if ($info[validFrom_time_t]>strtotime("now") || $info[validTo_time_t]<strtotime("now"))
  {
    $add=",zneplatneni_datum='".Date('Y-m-d')."',zneplatneni_duvod='prošlý certifikát'";
  } 
  $sql2="update posta_certifikaty set platnost_od='".$valid_from."', platnost_do='".$valid_to."' $add where id=".$id;
  $a->query($sql2);
  print_r($valid_from." - ".$valid_to);
}
