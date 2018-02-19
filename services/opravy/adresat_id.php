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
//$sqla="select * from posta where status=2 or status is null and id=157198";
$sqla="select * from posta where adresat_id>0 and odesl_prijmeni is null and odesl_posta is null and odes_typ in ('P','U','F','N','E','T');";
$q->query($sqla);
$celkovy_pocet=$q->Num_Rows();
echo '<div id="upl_wait_message" class="text" style="display:block">Hotovo záznamů: 0/'.$celkovy_pocet.'</div>';
echo '<div id="upl_wait_message2" class="text" style="display:block"><img src="'.FileUpUrl('images/progress.gif').'" title="pracuji ..." alt="pracuji ..."></div>';
Flush();
$i=0;
while ($q->Next_Record())
{
  $i++;
  if ($i%1000==0) 
  {
    echo "<script>document.getElementById('upl_wait_message').innerHTML = 'Hotovo záznamů: ".$i."/".$celkovy_pocet."'</script>";
    Flush();
  }
  $id=$q->Record["ID"];
  $adrObj = LoadClass('EedAdresa', $q->Record['ADRESAT_ID']);
  //print_r($adrObj);

  $sql = "update posta set ";
  $sql .= " odes_typ = '".$adrObj->typ."', ";
  $sql .= " odesl_titul = '".$adrObj->titul."', ";
  $sql .= " odesl_odd = '".$adrObj->oddeleni  ."', ";
  $sql .= " odesl_prijmeni = '".$adrObj->prijmeni."', ";
  $sql .= " odesl_jmeno = '".$adrObj->jmeno."', ";
  $sql .= " odesl_osoba = '".$adrObj->osoba."', ";
  $sql .= " odesl_rc = '".$adrObj->rc."', ";
  $sql .= " odesl_ulice = '".$adrObj->ulice."', ";
  $sql .= " odesl_cp = '".$adrObj->cp."', ";
  $sql .= " odesl_cor = '".$adrObj->cor."', ";
  $sql .= " odesl_psc = '".$adrObj->psc."', ";
  $sql .= " odesl_ico = '".$adrObj->ico."', ";
  $sql .= " odesl_posta = '".$adrObj->posta."', ";
  $sql .= " odesl_email = '".$adrObj->email."', ";
  $sql .= " odesl_datschranka = '".$adrObj->datovaSchranka."' ";
  //$sql .= " odesl_datnar = '".$adrObj->datumNarozeni."' ";
  $sql .= " where id = ". $id;
  
  $a->query($sql);
  
}
echo "<script>document.getElementById('upl_wait_message2').style.display = 'none'</script>";
echo "<span class=text>HOTOVO.</span>";

?>
