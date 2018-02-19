<?php
require("tmapy_config.inc");
require(FileUp2(".admin/run2_.inc"));
require(FileUp2(".admin/security_obj.inc"));
require_once(FileUp2(".admin/oth_funkce_2D.inc"));
require_once(Fileup2("html_header_title.inc"));

$USER_INFO = $GLOBALS["POSTA_SECURITY"]->GetUserInfo();
$id_user=$USER_INFO["ID"];
$LAST_USER_ID=$id_user;
$OWNER_ID=$id_user;
$LAST_TIME=Date('H:m:i');
$LAST_DATE=Date('Y-m-d');
$aa=new DB_POSTA;

$cj_obj = LoadClass('EedCj', $GLOBALS['SPIS_ID']);
$cj_info = $cj_obj->GetCjInfo($GLOBALS['SPIS_ID']);

$text = 'smazán '.$cj_info['CELY_NAZEV'];
EedTransakce::ZapisLog($GLOBALS['SPIS_ID'], $text, 'SPIS', $id_user);

$sql="delete from cis_posta_spisy WHERE spis_id=".$GLOBALS['SPIS_ID'];
//echo $sql;Die();
$aa->query($sql);
require_once(Fileup2("html_footer.inc"));  

?>
<script language="JavaScript" type="text/javascript">
  window.opener.document.location.reload();
  window.close();
</script>

