<?php
require("tmapy_config.inc");
include(FileUp2(".admin/brow_.inc"));
include_once(FileUp2(".admin/status.inc"));
include(FileUp2(".admin/security_obj.inc"));
require(FileUp2("html_header_full.inc"));
$USER_INFO = $GLOBALS["POSTA_SECURITY"]->GetUserInfo();
$id_user=$USER_INFO["ID"];
$LAST_USER_ID=$id_user;
$OWNER_ID=$id_user;
$LAST_TIME=Date('H:m:i');
$LAST_DATE=Date('Y-m-d');
//$sql="update posta set spis_vyrizen=NULL,last_date='$LAST_DATE',last_time='$LAST_TIME',last_user_id=$LAST_USER_ID   where cislo_spisu1=".$spis1." and cislo_spisu2=".$spis2."";
echo "Vracím dokument...";


EedTools::MaPristupKDokumentu($ID, 'vraceni na spisovy uzel');

//tak uzivatel kliknul, aby se pisemnost vratila zpatky na spis uzel....
$q=new DB_POSTA;
$sql="UPDATE posta SET datum_predani_ven=NULL,last_date='$LAST_DATE',
last_time='$LAST_TIME',last_user_id=$LAST_USER_ID WHERE id=".$ID;
$q->query($sql);
NastavStatus($ID);
$text = 'Uživatel vrátil dokument zpět na spisový uzel.';
EedTransakce::ZapisLog($ID, $text, 'DOC', $id_user);

require(FileUp2("html_footer.inc"));
//echo $sql;
?>
<script language="JavaScript" type="text/javascript">
<!--
  window.parent.location.reload();
  window.close();
//-->
</script>






