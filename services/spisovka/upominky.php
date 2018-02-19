<?php
require("tmapy_config.inc");
include(FileUp2(".admin/brow_.inc"));


Function ReferentMail($id)
{
  $w=new DB_POSTA;
  $sql="SELECT EMAIL FROM security_user WHERE id=".$id;
  $w->query ($sql);
  $w->Next_Record();
  $odbor=$w->Record["EMAIL"];
  return $odbor;
}


$where= " odeslana_posta='f' AND p.datum_referent_prijeti  IS NOT NULL AND datum_vyrizeni IS NULL AND  (p.DATUM_PODATELNA_PRIJETI,)+LHUTA < CURRENT_DATE";

$q=new DB_POSTA;

$sql="SELECT * FROM posta p WHERE ".$where." ORDER BY EV_CISLO";
//echo $sql;
$q->query($sql);
while($q->next_record())
{
  $email=ReferentMail($q->Record["REFERENT"]);
  $text="
Vazeny referente,

upozornujeme Vas, ze pisemnost s podacim cislem ".$q->Record["EV_CISLO"]."/".$q->Record["ROK"]." jste nevyridil v dane lhute k vyrizeni. 

Prosim, postarejte se o napravu.

Generovano dne ".Date('d.m.Y H:m');


$hlavicky = "From: spisovka@meu.nmnm.cz\nX-Mailer: Ev.pisemnosti's web\n";
$hlavicky .= "Return-Path: <zbynek.grepl@meu.nmnm.cz>\n";

mail($email,'Upozorneni',$text,$hlavicky);
  
}


?>
