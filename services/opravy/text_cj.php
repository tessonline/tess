<?php
require("tmapy_config.inc");
include(FileUp2(".admin/brow_.inc"));
include(FileUp2(".admin/security_obj.inc"));
include(FileUp2(".admin/oth_funkce.inc"));
set_time_limit(0);
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

$sqla = "alter table posta disable trigger posta_history;";
$q->query($sqla);


$sqla="select * from posta where text_cj is null order by id desc";
$q->query($sqla);
echo $sqla; Flush();
$celkovy_pocet=$q->Num_Rows();
echo '<div id="upl_wait_message" class="text" style="display:block">Hotovo záznamů: 0/'.$celkovy_pocet.'</div>';Flush();
echo '<div id="upl_wait_message2" class="text" style="display:block"><img src="'.FileUpUrl('images/progress.gif').'" title="pracuji ..." alt="pracuji ..."></div>';
Flush();
$i=0;
while ($q->Next_Record())
{
  $i++;
  if ($i%100==0) 
  {
    echo "<script>document.getElementById('upl_wait_message').innerHTML = 'Hotovo záznamů: ".$i."/".$celkovy_pocet."'</script>";
    Flush();
  }
  $doc = LoadSingleton('EedDokument', $q->Record[ID]);
  $cislo_jednaci = $doc->cislo_jednaci;

  $sql="update posta set text_cj='".$cislo_jednaci."' where id=".$q->Record[ID];
  //echo $sql.'<br/>';
  $a->query($sql);
}

$sqla = "alter table posta enable trigger posta_history;";
$q->query($sqla);



echo "<script>document.getElementById('upl_wait_message2').style.display = 'none'</script>";
echo "<span class=text>HOTOVO.</span>";

?>
