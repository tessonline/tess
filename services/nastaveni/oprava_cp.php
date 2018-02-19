<?php
require("tmapy_config.inc");
include(FileUp2(".admin/brow_.inc"));
include(FileUp2(".admin/security_obj.inc"));

echo '<h1 align=center>';
echo '
OPRAVA CISLA PODACIHO!
';
echo "</h1>";

//nastaveni parametru
$rok=2005;
$cislo_od=49509;
$novy_rok=2006;
//konec nastaveni

$USER_INFO = $GLOBALS["POSTA_SECURITY"]->GetUserInfo();
$id_user=$USER_INFO["ID"];
$jmeno=$USER_INFO["FNAME"]." ".$USER_INFO["LNAME"];
$LAST_USER_ID=$id_user;
$OWNER_ID=$id_user;
$LAST_TIME=Date('H:m:i');
$LAST_DATE=Date('Y-m-d');
$dnes=Date('d.m.Y');
$q=new DB_DEFAULT;
$a=new DB_DEFAULT;
$sqla='select id from posta where ev_cislo>='.$cislo_od.' and rok='.$rok.'';
$q->query($sqla);
while ($q->Next_Record())
{
  $id=$q->Record["ID"];
  $sqlb='select max(ev_cislo) as maxevcislo from posta where rok='.$novy_rok;
  $a->query($sqlb); $a->Next_Record();
  $new_ev_cislo=$a->Record["MAXEVCISLO"];
  $new_ev_cislo++;
  $sqlb="UPDATE posta SET ev_cislo=$new_ev_cislo,rok=$novy_rok,last_date='$LAST_DATE',last_time='$LAST_TIME',last_user_id=$LAST_USER_ID WHERE id=".$id;
//  $a->query($sqlb);
  echo $sqlb."<br/>";Flush();
}
echo "<h1>hotovo.</h1>";
?>
