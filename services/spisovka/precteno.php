<?php
require("tmapy_config.inc");
include(FileUp2(".admin/brow_.inc"));
include_once(FileUp2(".admin/status.inc"));
include(FileUp2(".admin/security_obj.inc"));
$USER_INFO = $GLOBALS["POSTA_SECURITY"]->GetUserInfo();
$id_user=$USER_INFO["ID"];
$LAST_USER_ID=$id_user;
$OWNER_ID=$id_user;
$LAST_TIME=Date('H:m:i');
$LAST_DATE=Date('Y-m-d');
//$sql="update posta set spis_vyrizen=NULL,last_date='$LAST_DATE',last_time='$LAST_TIME',last_user_id=$LAST_USER_ID   where cislo_spisu1=".$spis1." and cislo_spisu2=".$spis2."";


If ($GLOBALS["podatelna"]) {
  EedTools::MaPristupKDokumentu($ID, 'vraceni na podatelnu');

  //tak uzivatel kliknul, aby se pisemnost vratila zpatky na podatelnu....
  $q=new DB_POSTA;
  $sql="UPDATE posta SET REFERENT=NULL,ODBOR=NULL,DATUM_VYRIZENI=NULL,last_date='$LAST_DATE',
  last_time='$LAST_TIME',last_user_id=$LAST_USER_ID WHERE id=".$ID;
  $q->query($sql);
  NastavStatus($ID);
  $text = 'Uživatel vrátil dokument zpět na podatelnu.';
  EedTransakce::ZapisLog($ID, $text, 'DOC', $id_user);

}
else
{
  EedTools::MaPristupKDokumentu($ID, 'oznaceni precteni');
  //tak uzivatel kliknul, ze si chce danou pisemnost precist
  $q=new DB_POSTA;
  $sql="SELECT * FROM posta WHERE ID IN (".$ID.")";
  //echo $sql;
  $q->query($sql);
  $q->Next_Record();
  $data = $q->Record;
  $referent_zadan=$q->Record["REFERENT"];
  
  If ($referent_zadan=="")  {
    $USER_INFO = $GLOBALS["POSTA_SECURITY"]->GetUserInfo(); 
    $referent_novy=$USER_INFO["ID"];;
    $sql="UPDATE posta SET REFERENT=".$referent_novy.",last_date='$LAST_DATE',last_time='$LAST_TIME',last_user_id=$LAST_USER_ID WHERE id=".$ID;
  //  echo $sql;
    $q->query($sql);
    NastavStatus($ID);
  }
  
  $nowd =date('Y-m-d H:i:s');
  $sql="UPDATE posta SET DATUM_REFERENT_PRIJETI='".$nowd."',last_date='$LAST_DATE',last_time='$LAST_TIME',last_user_id=$LAST_USER_ID  WHERE id=".$ID;
  $q->query($sql);
  NastavStatus($ID);

  $text = 'Uživatel označil dokument jako přečtený.';
  EedTransakce::ZapisLog($ID, $text, 'DOC', $id_user);

  if ($data['ODES_TYP']=='S' && $data['ID_PUVODNI']>0 && $GLOBALS['CONFIG']["INTERNI_DORUCENKA_AZ_PO_PREVZETI"]) {
    include_once(FileUp2(".admin/config.inc"));
    include_once(FileUp2(".admin/upload_.inc"));
    include_once(FileUp2(".admin/oth_funkce.inc"));
    include_once(FileUp2("interface/.admin/upload_funkce.inc"));
    include_once(FileUp2('.admin/dorucenka.inc'));
    include(FileUp2(".admin/run2_.inc"));
    //ulozime dorucenku pri zmene stavu
    if (!ExistujeDorucenka($data['ID_PUVODNI']))
    {
       //echo $GLOBALS['ID_PUVODNI'];
       $sql="update posta set datum_doruceni='".Date('Y-m-d H:i:s')."' where id=".$data['ID_PUVODNI'];
       $q->query($sql);
  //     echo $sql;
       VytvorDorucenku($data['ID_PUVODNI']);
    }
  }
}
//echo $sql;
?>
<script language="JavaScript" type="text/javascript">
<!--
  window.parent.location.reload();
  window.close();
//-->
</script>






