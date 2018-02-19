<?php

include_once(FileUp2(".admin/agenda_func.inc"));
require_once(FileUp2(".admin/security_obj.inc"));
require_once(FileUp2(".admin/soap_funkce.inc"));
require_once(FileUp2(".admin/isds_.inc"));

echo '<h1>Informace o datové schránce</h1>';
if ($GLOBALS[CONFIG_POSTA][DS][ds_cert_id]) $certifikat=VratCestukCertifikatu(0,$GLOBALS[CONFIG_POSTA][DS][ds_cert_id],1); else  $certifikat='';
$schranka=new ISDSbox($GLOBALS[CONFIG_POSTA][DS][ds_user],$GLOBALS[CONFIG_POSTA][DS][ds_passwd],$certifikat);

if (!$schranka->ValidLogin)
{
	echo ("<span class='caption'>Nepodařilo se připojit k ISDS.</span><br/><span class='text'>Zkontrolujte uživatelské jméno a heslo.<br/>".$schranka->ErrorInfo."</span>");
  echo "<script>document.getElementById('upl_wait_message').style.display = 'none'</script>";
  require(FileUp2("html_footer.inc"));
	exit();
}


$OwnerInfo=$schranka->GetOwnerInfoFromLogin();
$UserInfo=$schranka->GetUserInfoFromLogin();
//print_r($UserInfo);
$PasswordInfo=$schranka->GetPasswordInfo();

if (!$PasswordInfo) $PasswordInfo='bez expirace';
else
  $PasswordInfo=ConvertDatumToString($PasswordInfo);


