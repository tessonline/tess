<?php
require("tmapy_config.inc");
include(FileUp2(".admin/brow_.inc"));
include(FileUp2(".admin/security_obj.inc"));
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
$b=new DB_POSTA;

//$sqla="select * from posta where status=2 or status is null and id=157198";
$sqla="select s.id, p.id as ID_doc,s.dokument_id,s.cislo_spisu1,s.cislo_spisu2,s.last_date
  from posta_view_spisy p
  left join posta_spisovna s
  on (p.cislo_spisu1=s.cislo_spisu1 and p.cislo_spisu2=s.cislo_spisu2 and p.superodbor=s.superodbor)

  where p.id<>s.dokument_id
  and s.dokument_id in (select dalsi_spis_id from cis_posta_spisy);
";
$q->query($sqla);
$celkovy_pocet=$q->Num_Rows();
echo '<div id="upl_wait_message" class="text" style="display:block">Hotovo záznamů: 0/'.$celkovy_pocet.'</div>';
echo '<div id="upl_wait_message2" class="text" style="display:block"><img src="'.FileUpUrl('images/progress.gif').'" title="pracuji ..." alt="pracuji ..."></div>';
Flush();
$i=0;
while ($q->Next_Record())
{
  $id_doc = $q->Record['ID_DOC'];
  $id = $q->Record['ID'];
  $minus_id = 0 - $id_doc;
    $sqlb="UPDATE posta_spisovna SET dokument_id=$minus_id,last_date='$LAST_DATE',last_time='$LAST_TIME',last_user_id=$LAST_USER_ID WHERE id=".$id;
  echo $sqlb.'<br/>';
  $b->query($sqlb);
    $sqlb="UPDATE posta_spisovna SET dokument_id=$id_doc,last_date='$LAST_DATE',last_time='$LAST_TIME',last_user_id=$LAST_USER_ID WHERE id=".$id;
  echo $sqlb.'<br/>';
  $b->query($sqlb);
}
echo "<script>document.getElementById('upl_wait_message2').style.display = 'none'</script>";
echo "<span class=text>HOTOVO.</span>";

?>
