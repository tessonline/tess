<?php
require("tmapy_config.inc");
include(FileUp2(".admin/brow_.inc"));
require_once(FileUp2(".admin/config.inc"));
require_once(FileUp2(".admin/status.inc"));
require_once(FileUp2(".admin/db/db_posta.inc"));
require_once(FileUp2("html_header_full.inc"));
require(FileUp2("interface/.admin/soap_funkce.inc"));
$q=new DB_POSTA;
$c=new DB_POSTA;
$a=new DB_POSTA;

set_time_limit(0);

$USER_INFO = $GLOBALS["TMAPY_SECURITY"]->GetUserInfo();
$id_user=$USER_INFO["ID"];
$jmeno_uzivatele=$USER_INFO["FNAME"]." ".$USER_INFO["LNAME"];
$LAST_USER_ID=$id_user;
$LAST_TIME=Date('H:i:s');
$LAST_DATE=Date('Y-m-d');

$db = LoadClass('EedUser', 0);

function VratSpisovnu($odbor) {
  global $db;
  if (!$c) $c = new DB_POSTA;
  $sql = "select * from posta_cis_spisovna where spisovna like '%histor%' and odbor=".$odbor;
  // echo $sql.'<br/>';
  $c->query($sql);
  if ($c->Num_Rows()>0) {
    $c->Next_Record();
    return $c->Record['ID'];
  }
  else {
    $odbor = $db->VratOdborZSpisUzlu($odbor);
    $nadrizeny = $db->GetUnitParent($odbor);
    $odbor = $db->VratSpisUzelZOdboru($nadrizeny);
    $odbor = $odbor['ID'];
    if (!$odbor) return -1;
    $sql = "select * from posta_cis_spisovna where spisovna like '%histor%' and odbor=".$odbor;
    $c->query($sql);
    // echo $sql.'<br/>';
    $c->Next_Record();
    return $c->Record['ID'];
  }

}

echo'<div id="upl_wait_message" class="text" style="display:block"></div>';
echo"<script>document.getElementById('upl_wait_message').innerHTML = ''</script>";Flush();

$add_info="last_date='$LAST_DATE',last_time='$LAST_TIME',last_user_id=".$LAST_USER_ID;

//$sql="select * from posta_stare_zaznamy where cislo_spisu1=59266 and cislo_spisu2=2007";
$sql="select * from posta_stare_zaznamy where cislo_spisu2=2008 ";
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
  
  $odbor = $q->Record['ODDELENI'] ? $q->Record['ODDELENI'] : $q->Record['ODBOR'];

  if ($cj1==$cs1 && $cj2==$cs2) {
    //MAIN DOC
    $spis_id = $id;
    $dalsi_spis_id = 0;
  } 
  else {
    $sql="select id,cislo_jednaci1,cislo_jednaci2 from posta_stare_zaznamy where cislo_spisu1=$cs1 and cislo_spisu2=$cs2 $append and cislo_jednaci1=cislo_spisu1 and cislo_jednaci2=cislo_spisu2";
  // echo"$sql<br/>";
    $a->query($sql);
    $a->Next_Record();
    $dalsi_spis_id = $id;
    $spis_id = $a->Record['ID'] ? $a->Record['ID'] : -1;  
    $puvodni_spis = $a->Record['CISLO_JEDNACI1'].'/'.$a->Record['CISLO_JEDNACI2'];

  }
  // echo$cj1.'/'.$cj2.' - '.$cs1.'/'.$cs2.' - spis_id='.$spis_id.' - dalsi_spis_id='.$dalsi_spis_id;

  if ($spis_id > 0) {

    $spisovna_id = -1;
    $spisovna_id = VratSpisovnu($odbor);
    //echo "onma Spisovna Id je  $spisovna_id<br/>";

    $sql = 'select id from cis_posta_spisy where spis_id='.$spis_id.' and dalsi_spis_id='.$dalsi_spis_id;
   //echo"$sql<br/>";
    $a->query($sql); $a->Next_Record();
    if (!$a->Record['ID'] || $a->Record['ID']<0) {
      $sql = "insert into cis_posta_spisy (spis_id,dalsi_spis_id,nazev_spisu,owner_id,last_date,last_time,puvodni_spis,novy_spis) VALUES "
           ." ($spis_id,$dalsi_spis_id,'$nazev_spisu',$owner_id,'$last_date','$last_time','$puvodni_spis','$novy_spis')";
     //echo"$sql<br/>";

     $a->query($sql);
      // echo' - ulozeno<br/>';
    }
  }
  if ($spis_id>0) {
      //else
      // echo' - duplicita, neukladam, jiz je ulozeno<br/>';

    $sql = "select * from posta where cislo_jednaci1=$cj1 and cislo_jednaci2=$cj2";
    $a->query($sql);
    if ($a->Num_Rows() == 0) {
      $sql = "insert into posta (select * from posta_stare_zaznamy where id in ( select id from posta_stare_zaznamy where cislo_jednaci1=$cj1 and cislo_jednaci2=$cj2))";
      // echo $sql.'<br/>';
      $a->query($sql);
    }

    $sql = "update posta set main_doc=1 where id=".$spis_id;
    // echo $sql.'<br/>';
    $a->query($sql);

//  nemuzu ted prevest, protoze to pak dela bordel u dalsich dokumentu...
//    $sql = "update posta set cislo_spisu2=cislo_jednaci2,cislo_spisu1=cislo_jednaci1,status=-3 where cislo_spisu1=$cs1 and cislo_spisu2=$cs2";
//    // echo $sql.'<br/>';
//    $a->query($sql);

    $sql = "update posta set kopie=-1 where cislo_jednaci1=$cj1 and cislo_jednaci2=$cj2";
    // echo $sql.'<br/>';
    $a->query($sql);

    $sql = "update posta set odbor=oddeleni where cislo_jednaci1=$cj1 and cislo_jednaci2=$cj2 and oddeleni>0";
    // echo $sql.'<br/>';
    $a->query($sql);
  }
  if ($cj1==$cs1 && $cj2==$cs2) {

    $sql = "select * from posta_spisovna where dokument_id=".$spis_id;
    $a->query($sql);
    
    if ($a->Num_Rows() == 0) {
      $sql = "select * from posta where id=".$spis_id;
      // echo $sql.'<br/>';
      $a->query($sql);
      $a->Next_Record();
      $data = $q->Record;
      //$data = $a->Record;
      $skar_pole = Skartace_Pole($data[SKARTACE]);
      $rok_uzavreni = $data[CISLO_SPISU2]+1;
      $rok_skartace = $rok_uzavreni + $skar_pole['doba'];
      $skartace_id = $data['SKARTACE'];
      if (!$skar_pole[doba]) $skar_pole[doba] = 0;
      if (!$skartace_id) $skartace_id = 0;
      $vec = $data['VEC'];
      $vec = str_replace("'", "", $vec);
      $sql="insert into posta_spisovna (superodbor,protokol_id,dokument_id,skartace_id,spisovna_id,cislo_spisu1,cislo_spisu2,vec,listu,prilohy,digitalni,skar_znak,lhuta,rok_predani,rok_skartace,datum_predani,last_date,last_time,last_user_id,owner_id,prevzal_id)
      VALUES (0,0,$spis_id,$skartace_id,$spisovna_id,$data[CISLO_SPISU1],$data[CISLO_SPISU2],'".$vec."',0,'',0,'$skar_pole[znak]',$skar_pole[doba],$rok_uzavreni,$rok_skartace,'".Date('Y-m-d')."','".Date('Y-m-d')."','$LAST_TIME',$LAST_USER_ID,$LAST_USER_ID,$LAST_USER_ID);";
      // echo $sql.'<br/>';
      $a->query($sql);
    }


  }


  //   select id,cislo_jednaci1,cislo_jednaci2 from posta_stare_zaznamy where cislo_spisu2=$cs1 and cislo_spisu1=$cs2;




  
//  // echo"<br/>";

  if ($pocitadlo%100000 == 0) echo"<script>document.getElementById('upl_wait_message').innerHTML = 'Zpracovávám zprávu ".$id." - ".$pocitadlo."/".$pocet_zprav."'</script>";Flush();

}

// $sql = "update posta set cislo_spisu2=cislo_jednaci2,cislo_spisu1=cislo_jednaci1,status=-3 where kopie=-1";
// // echo $sql.'<br/>';
// $a->query($sql);

echo"<script>document.getElementById('upl_wait_message').innerHTML = 'Hotovo'</script>";Flush();



require(FileUp2("html_footer.inc"));
