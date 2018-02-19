<?php
require("tmapy_config.inc");
include(FileUp2(".admin/brow_.inc"));
include(FileUp2(".admin/security_obj.inc"));
set_time_limit(0);

//skript slouzi k uzavreni vsech cj ve spisu - pokud bylo uzavreno jenom inicializacni cj a nebyly uzavreny ostatni cj.

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
$c=new DB_POSTA;

//$sqla = 'select * from cis_posta_spisy where spis_id = 01000004058';
$sqla = 'select * from cis_posta_spisy';

$b->query($sqla);
$celkovy_pocet=$q->Num_Rows();
echo '<div id="upl_wait_message" class="text" style="display:block">Hotovo záznamů: 0/'.$celkovy_pocet.'</div>';
echo '<div id="upl_wait_message2" class="text" style="display:block"><img src="'.FileUpUrl('images/progress.gif').'" title="pracuji ..." alt="pracuji ..."></div>';
Flush();
$i=0;
//print_r($protokol);
//$protokol

while ($b->Next_Record())
{
  //najdeme vsechna ID inicializacnich dokumentu
  $id = $b->Record['DALSI_SPIS_ID'];
  $sqlb = 'select * from posta where id='.$b->Record['SPIS_ID'];
//  echo $sqlb."<br/>";
  $q->query($sqlb); 
  $q->Next_Record(); $status=$q->Record['STATUS']; $spis_vyrizen = $q->Record['SPIS_VYRIZEN'];

  if ($status==1)
  {
    $sqlb = 'select * from posta where id='.$id;
//    echo $sqlb."<br/>";
    $q->query($sqlb); 
    while ($q->Next_Record())
    {
      $digitalnich=0;
      $pocet_listu_celkem=0;
      $spisovna_id=$q->Record['SPISOVNA_ID'];
      $cs1=$q->Record['CISLO_SPISU1'];
      $cs2=$q->Record['CISLO_SPISU2'];
      $superodbor=$q->Record['SUPERODBOR'];
     
      $sqla='select id from posta where cislo_spisu1='.$cs1.' and cislo_spisu2='.$cs2.' and stornovano is null and superodbor in ('.$superodbor.') and status>1 order by id asc';
      //echo $sqla;
      $a->query($sqla);
    
      while ($a->Next_Record()) 
      {
        $id_dalsi=$a->Record['ID'];
        $sql="update posta set status=".$status.",spis_vyrizen='".$spis_vyrizen."',last_date='$LAST_DATE',last_time='$LAST_TIME',last_user_id=$LAST_USER_ID where id=".$id_dalsi;
       echo $sql."<br/>";
       //if (strlen($spis_vyrizen)>0)
        //$c->query($sql);
      }
    }
  }
}
echo "<script>document.getElementById('upl_wait_message2').style.display = 'none'</script>";
echo "<span class=text>HOTOVO.</span>";

?>
