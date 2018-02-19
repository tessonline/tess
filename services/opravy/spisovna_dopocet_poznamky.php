<?php
require("tmapy_config.inc");
include(FileUp2(".admin/brow_.inc"));
include_once(FileUp2(".admin/db/db_monumnis.inc"));
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
$from=new DB_MONUMNIS;
$a=new DB_POSTA;
$b=new DB_POSTA;

$sqla="select * from Migrace1_Spis_1 where ZalozPozn is not null order by IdSpis asc";
$sqla="select * from Migrace1_Spis_2 where ZalozPozn is not null order by IdSpis asc";
$from->query($sqla);
$celkovy_pocet=$from->Num_Rows();
echo '<div id="upl_wait_message" class="text" style="display:block">Hotovo záznamů: 0/'.$celkovy_pocet.'</div>';
echo '<div id="upl_wait_message2" class="text" style="display:block"><img src="'.FileUpUrl('images/progress.gif').'" title="pracuji ..." alt="pracuji ..."></div>';
Flush();
$i=0;
//for ($c=26; $c<=32; $c++) $protokol[]=$c;
while ($from->Next_Record())
{
  $digitalnich=0;
  $spis_id=$from->Record['IDSPIS'];
  $poznamka = $from->Record['ZALOZPOZN'];

  $sqla='select * from posta_spisovna where dokument_id='.$spis_id;
  $a->query($sqla);
  $pocet = $a->Num_Rows();
  if ($pocet==1) {
    $poznamka = str_replace("'","",$poznamka);
    $a->Next_Record();
    $pozn = $a->Record['POZNAMKA'];
    if (ereg($poznamka, $pozn)) {
       echo "U id $spis_id poznamka je doplnena ($poznamka, ale je $pozn)<br/>";
    }
    else {
      $sql = "update posta_spisovna set poznamka='".$poznamka."',last_date='$LAST_DATE',last_time='$LAST_TIME',last_user_id=$LAST_USER_ID where dokument_id=".$spis_id." and poznamka is null";
  //    $a->query($sql);
      echo $sql."<br/>";
    }
  }
  else
  {
    echo "<font color=red>Dokument $spis_id NENI ve spisovne!</font><br/>";
  }
  
}
echo "<script>document.getElementById('upl_wait_message2').style.display = 'none'</script>";
echo "<span class=text>HOTOVO.</span>";

?>
