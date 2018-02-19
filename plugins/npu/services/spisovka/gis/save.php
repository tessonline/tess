<?php
require("tmapy_config.inc");
include(FileUp2(".admin/security_obj.inc"));
session_start();
print_r($_SESSION);

if (!$_SESSION['gis_spis_id']) Die('Neni gis spis id');

if ($GLOBALS['PRIR_CIS']<>'') {
  $type = 'PRIR';
  $ids = explode(',', $GLOBALS['PRIR_CIS']);
}
if ($GLOBALS['PAGIS']<>'') {
  $type = 'PAGIS';
  $ids = explode(',', $GLOBALS['PAGIS']);
}

$USER_INFO = $GLOBALS["POSTA_SECURITY"]->GetUserInfo();
$id_user=$USER_INFO["ID"];
$jmeno=$USER_INFO["FNAME"]." ".$USER_INFO["LNAME"];
$LAST_USER_ID=$id_user;
$OWNER_ID=$id_user;
$LAST_TIME=Date('H:m:i');
$LAST_DATE=Date('Y-m-d');
$dnes=Date('d.m.Y');

$q=new DB_POSTA;
foreach ($ids as $id) {
  $sql = "INSERT INTO posta_vazba_gis (DOKUMENT_ID, GIS_ID, TYP, LAST_USER_ID, OWNER_ID, LAST_DATE, LAST_TIME)
  VALUES (".$_SESSION['gis_spis_id'].", $id, '$type', $LAST_USER_ID, $OWNER_ID, '$LAST_DATE', '$LAST_TIME')";
	$q->query ($sql);
  echo $sql . '<br/>';
}
require(FileUp2("html_header_full.inc"));
echo '<script>
  window.parent.document.location.reload();
  //window.close();
</script>
';
require(FileUp2("html_footer.inc"));

