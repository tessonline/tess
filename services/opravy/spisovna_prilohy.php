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
$sqla="select * from posta_spisovna where (id<26 and id>32) or (id<126 and id>220) ";
$sqla="select * from posta_spisovna where spisovna_id=16 order by id asc ";
$q->query($sqla);
$celkovy_pocet=$q->Num_Rows();
echo '<div id="upl_wait_message" class="text" style="display:block">Hotovo záznamů: 0/'.$celkovy_pocet.'</div>';
echo '<div id="upl_wait_message2" class="text" style="display:block"><img src="'.FileUpUrl('images/progress.gif').'" title="pracuji ..." alt="pracuji ..."></div>';
Flush();
$i=0;
//for ($c=26; $c<=31; $c++) $protokol[]=$c;
for ($c=126; $c<=220; $c++) $protokol[]=$c;
for ($c=222; $c<=224; $c++) $protokol[]=$c;
for ($c=237; $c<=294; $c++) $protokol[]=$c;
for ($c=304; $c<=323; $c++) $protokol[]=$c;
for ($c=346; $c<=392; $c++) $protokol[]=$c;
//print_r($protokol);
//$protokol
while ($q->Next_Record())
{
  $digitalnich=0;
  $pocet_listu_celkem=0;
  $pocet_priloh_celkem=array();
  $spisovna_id=$q->Record['ID'];
    $sqla='select * from posta where cislo_spisu1='.$q->Record['CISLO_SPISU1'].' and cislo_spisu2='.$q->Record['CISLO_SPISU2'].' and stornovano is null and superodbor in ('.VratSuperOdbor().')order by id asc';
    //echo $sqla;
    $a->query($sqla);
  
    while ($a->Next_Record()) 
    {
      $skartace[]=$a->Record['ID'];
//    echo "ID".$a->Record['ID']."<br/>";
      $pocet_listu = $a->Record["POCET_LISTU"];
      $pocet_priloh = $a->Record["POCET_PRILOH"];
      $druh_priloh = $a->Record["DRUH_PRILOH"];
//      if ($a->Record['SKARTACE']==2398 || $a->Record['TYP_DOKUMENTU']=='D' || $a->Record['ODES_TYP']=='X') {$pocet_listu=0; $pocet_priloh=0;}//neni urceno ke skartaci
      if ($a->Record['SKARTACE']==2398 || $a->Record['TYP_DOKUMENTU']=='D') {$pocet_listu=0; $pocet_priloh=0;}//neni urceno ke skartaci
      if ($a->Record['TYP_DOKUMENTU']=='D' && $a->Record['SKARTACE']<>2398 ) {$digitalnich++;}//neni urceno ke skartaci

      $pocet_listu_celkem=$pocet_listu_celkem+$pocet_listu;
      $pocet_priloh_celkem[$druh_priloh]=$pocet_priloh_celkem[$druh_priloh]+$pocet_priloh;

      
      $sql='select listu from posta_spisobal where posta_id='.$a->Record['ID'];
//      echo $sql;
      $b->query($sql); $b->Next_Record();
      $pocet=$b->Record['LISTU']; if (!$pocet) $pocet==0; 
      if ($pocet>0 && !in_array($spisovna_id,$protokol)) $pocet_listu_celkem=$pocet_listu_celkem+$pocet; //pricteme spis obal a prehled
    }


  //tady pricist pripadne prebal
    $prilohy="";
    while (list($key,$val)=each($pocet_priloh_celkem)) if ($val>0) $prilohy.="$key: $val<br/>";
//    echo "$celkem x $pocitadlo - ";
    if (!$pocet_listu_celkem || $pocet_listu_celkem<0) $pocet_listu_celkem=0;
    if ($q->Record['PRILOHY']<>$prilohy)
    {
     echo $q->Record['ID']." - čj. ".$q->Record["CISLO_SPISU1"]." - příloh ".$q->Record['PRILOHY']." -nove ".$prilohy."<br/>";
     $sql="update posta_spisovna set prilohy='".$prilohy."' where id=".$spisovna_id;
     echo $sql;
     $b->query($sql);
    }
}
echo "<script>document.getElementById('upl_wait_message2').style.display = 'none'</script>";
echo "<span class=text>HOTOVO.</span>";

?>
