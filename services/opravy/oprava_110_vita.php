<?php
require("tmapy_config.inc");
include(FileUp2(".admin/brow_.inc"));
include(FileUp2(".admin/oth_funkce.inc"));
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
$sqla="select * from posta where (vyrizeno is null or vyrizeno='') and odbor in (14) and odeslana_posta<>'t' and referent is not null";
$q->query($sqla);
while ($q->Next_Record())
{
  $id=$q->Record["ID"];
  $cislo_jednaci1=$q->Record["CISLO_JEDNACI1"];
  $cislo_jednaci2=$q->Record["CISLO_JEDNACI2"];
  $cislo_spisu1=$q->Record["CISLO_SPISU1"];
  $cislo_spisu2=$q->Record["CISLO_SPISU2"];
  if ($cislo_spisu1>0)
    $text="vyřízeno spisem ".strip_tags(FormatSpis($q->Record["CISLO_SPISU1"],$q->Record["CISLO_SPISU2"],$q->Record["REFERENT"],$q->Record["ODBOR"],$q->Record["NAZEV_SPISU"]));
  else
    $text="vyřízeno číslem jednacím ".strip_tags(FormatCJednaci($q->Record["CISLO_JEDNACI1"],$q->Record["CISLO_JEDNACI2"],$q->Record["REFERENT"],$q->Record["ODBOR"]));
   
    
  $sqlb="UPDATE posta SET vyrizeno='$text',last_date='$LAST_DATE',last_time='$LAST_TIME',last_user_id=$LAST_USER_ID WHERE id=".$id;
  $a->query($sqlb);
  echo $q->Record["EV_CISLO"]."/".$q->Record["ROK"]." - ".$sqlb."<br/>";
}
?>
