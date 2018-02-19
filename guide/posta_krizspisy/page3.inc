<?php
//session_start();
require("tmapy_config.inc");
require(FileUp2(".admin/brow_.inc"));
require(FileUp2("html_header_full.inc"));

  $USER_INFO = $GLOBALS["POSTA_SECURITY"]->GetUserInfo();
  $id_user=$USER_INFO["ID"];
  $jmeno=$USER_INFO["FNAME"]." ".$USER_INFO["LNAME"];
  $LAST_USER_ID=$id_user;
  $OWNER_ID=$id_user;
  $LAST_TIME=Date('H:i:s');
  $LAST_DATE=Date('Y-m-d');

$ID=$GLOBALS["SELECT_ID"];

$q = new DB_POSTA;

//echo "smer je $SMER_KRIZ, puvodni ID je $IDP_KRIZ";


if ($SMER_KRIZ==1)
{
  $NOVY_SPIS=$IDP_KRIZ;
  $PUVODNI_SPIS=$ID;
}
else
{
  $NOVY_SPIS=$ID;
  $PUVODNI_SPIS=$IDP_KRIZ;
}
  $sql="insert into posta_krizovy_spis (PUVODNI_SPIS,NOVY_SPIS,LAST_DATE,LAST_TIME,OWNER_ID,LAST_USER_ID)
  VALUES ($PUVODNI_SPIS,$NOVY_SPIS,'$LAST_DATE','$LAST_TIME',$OWNER_ID,$LAST_USER_ID)";
  //Die($sql);
$q->query($sql);
?>
<script language="JavaScript" type="text/javascript">
  window.opener.document.location.reload();
  window.close();
</script>


