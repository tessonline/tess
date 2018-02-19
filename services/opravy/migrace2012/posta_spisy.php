<?php
require("tmapy_config.inc");
include(FileUp2(".admin/brow_.inc"));
require_once(FileUp2(".admin/config.inc"));
require_once(FileUp2(".admin/db/db_posta.inc"));
require_once(FileUp2("html_header_full.inc"));
require(FileUp2("interface/.admin/soap_funkce.inc"));
//require(FileUp2(".admin/security_.inc"));
$q=new DB_POSTA;
$c=new DB_POSTA;
$a=new DB_POSTA;

$q->query('SET LOCAL synchronous_commit TO OFF');
$c->query('SET LOCAL synchronous_commit TO OFF');
$a->query('SET LOCAL synchronous_commit TO OFF');

set_time_limit(0);

$USER_INFO = $GLOBALS["TMAPY_SECURITY"]->GetUserInfo();
$id_user=$USER_INFO["ID"];
$jmeno_uzivatele=$USER_INFO["FNAME"]." ".$USER_INFO["LNAME"];
$LAST_USER_ID=$id_user;
$LAST_TIME=Date('H:i:s');
$LAST_DATE=Date('Y-m-d');



echo'<div id="upl_wait_message" class="text" style="display:block"></div>';
echo"<script>document.getElementById('upl_wait_message').innerHTML = ''</script>";Flush();

$add_info="last_date='$LAST_DATE',last_time='$LAST_TIME',last_user_id=".$LAST_USER_ID;

$sql="select * from posta_view_spisy where cislo_spisu1>0 and cislo_spisu2=2012";
//$sql="select * from posta_view_spisy where cislo_spisu1=3741 and cislo_spisu2=2015";
//  // echo"$sql<br/>";
$q->query($sql);
$pocet_zprav=$q->Num_Rows();

while ($q->Next_Record()) {

  $pocitadlo++;
  $id = $q->Record['ID'];

  $cj1 = $q->Record['CISLO_JEDNACI1'];
  $cj2 = $q->Record['CISLO_JEDNACI2'];
  
  $owner_id = $q->Record['OWNER_ID'] ? $q->Record['OWNER_ID'] : 0;
  $last_date = $q->Record['LAST_DATE'];
  $last_time = substr($q->Record['LAST_TIME'],0,10);
  
  $puvodni_spis = $cj1.'/'.$cj2;
  $novy_spis = $cj1.'/'.$cj2;
  
  $cs1 = $q->Record['CISLO_SPISU1'];
  $cs2 = $q->Record['CISLO_SPISU2'];
  $csod = $q->Record['ODBOR_SPISU'];

  $append = '';
  if (strlen($csod)>1) $append = "and odbor_spisu like '$csod'";
  $nazev_spisu = $cs1.'/'.$cs2;
  if ($q->Record['NAZEV_SPISU']<>'') $nazev_spisu .= '-'.$q->Record['NAZEV_SPISU'];
  
  $spis_id = 0;
  
  if ($cj1==$cs1 && $cj2==$cs2) {
    //MAIN DOC
    $spis_id = $id;
    $dalsi_spis_id = 0;
  } 
  else {
    $sql="select id,cislo_jednaci1,cislo_jednaci2 from posta_view_spisy where cislo_spisu1=$cs1 and cislo_spisu2=$cs2 $append and cislo_jednaci1=cislo_spisu1 and cislo_jednaci2=cislo_spisu2";
  // echo"$sql<br/>";
    $a->query($sql);
    $a->Next_Record();
    $dalsi_spis_id = $id;
    $spis_id = $a->Record['ID'] ? $a->Record['ID'] : -1;  
    $puvodni_spis = $a->Record['CISLO_JEDNACI1'].'/'.$a->Record['CISLO_JEDNACI2'];

  }
  // echo$cj1.'/'.$cj2.' - '.$cs1.'/'.$cs2.' - spis_id='.$spis_id.' - dalsi_spis_id='.$dalsi_spis_id;

  if ($spis_id > 0) {
    $sql = 'select id from cis_posta_spisy where spis_id='.$spis_id.' and dalsi_spis_id='.$dalsi_spis_id;
  // echo"$sql<br/>";
    $a->query($sql); $a->Next_Record();
    if (!$a->Record['ID'] || $a->Record['ID']<0) {
      $sql = "insert into cis_posta_spisy (spis_id,dalsi_spis_id,nazev_spisu,owner_id,last_date,last_time,puvodni_spis,novy_spis) VALUES "
           ." ($spis_id,$dalsi_spis_id,'$nazev_spisu',$owner_id,'$last_date','$last_time','$puvodni_spis','$novy_spis')";
  // echo"$sql<br/>";

      $a->query($sql);
      // echo' - ulozeno<br/>';
    } 
      //else
      // echo' - duplicita, neukladam, jiz je ulozeno<br/>';

        
  }
  
//  // echo"<br/>";

  if ($pocitadlo%100000 == 0) echo"<script>document.getElementById('upl_wait_message').innerHTML = 'Zpracovávám zprávu ".$id." - ".$pocitadlo."/".$pocet_zprav."'</script>";Flush();

}

echo"<script>document.getElementById('upl_wait_message').innerHTML = 'Hotovo'</script>";Flush();



require(FileUp2("html_footer.inc"));
