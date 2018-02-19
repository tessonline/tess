<?php
require('tmapy_config.inc');
include(FileUp2('.admin/brow_.inc'));
include(FileUp2('.admin/security_obj.inc'));
set_time_limit(0);

//skript slouzi k uzavreni vsech cj ve spisu - pokud bylo uzavreno jenom inicializacni cj a nebyly uzavreny ostatni cj.

$USER_INFO = $GLOBALS['POSTA_SECURITY']->GetUserInfo();
$id_user = $USER_INFO['ID'];
$jmeno = $USER_INFO['FNAME'].' '.$USER_INFO['LNAME'];
$LAST_USER_ID = $id_user;
$OWNER_ID = $id_user;
$LAST_TIME = Date('H:m:i');
$LAST_DATE = Date('Y-m-d');
$dnes = Date('d.m.Y');
$q = new DB_POSTA;
$a = new DB_POSTA;
$b = new DB_POSTA;
$c = new DB_POSTA;

//$sqla = 'select * from cis_posta_spisy where spis_id = 01000004058';
//$sqla = 'select * from posta where cislo_spisu2<2012 and referent>0 order by id desc limit 500';
$sqla = 'select * from posta where cislo_spisu2<2012 and referent>0 and superodbor=2 and status>0 order by referent desc limit 10000';

$b->query($sqla);
$celkovy_pocet=$q->Num_Rows();
echo '<div id="upl_wait_message" class="text" style="display:block">Hotovo záznamů: 0/'.$celkovy_pocet.'</div>';
echo '<div id="upl_wait_message2" class="text" style="display:block"><img src="'.FileUpUrl('images/progress.gif').'" title="pracuji ..." alt="pracuji ..."></div>';
Flush();
$i=0;
$usrObj = LoadClass('EedUser', $id_user);

while ($b->Next_Record()) {
  $id = $b->Record['ID'];
  $referent = $b->Record['REFERENT'];
  $odbor = $b->Record['ODBOR'];
//  echo $id.'-'.$referent.'<br/>';
  $odbor_prac = $usrObj->VratSpisovyUzelPracovnika($referent);
  
  if ($odbor <> $odbor_prac && $odbor_prac>0) {
    echo 'Problem s id '.$id.' (referent '.$referent.') odbor puvodni = '.$odbor.' ma byt '.$odbor_prac.' - ';
    $sql="update posta set odbor=".$odbor_prac.",last_date='$LAST_DATE',last_time='$LAST_TIME',last_user_id=$LAST_USER_ID where id=".$id;
    $q->query($sql);
   // echo $sql."<br/>";
      echo "<br/>";
  }
  else {
    if ($odbor_prac == 0) {
     // echo '<font color=red>id '.$id.' odbor puvodni = '.$odbor.' ma byt '.$odbor_prac.'</font>';
      //echo "<br/>";
    }
    
  }
}
echo "<script>document.getElementById('upl_wait_message2').style.display = 'none'</script>";
echo "<span class=text>HOTOVO.</span>";

?>
