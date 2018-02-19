<?php
require("tmapy_config.inc");
require_once(FileUp2(".admin/brow_.inc"));
require_once(FileUp2("html_header_full.inc"));
require_once(FileUp2(".admin/nastaveni.inc"));
require_once(FileUp2(".admin/security_func.inc"));
require_once(FileUp2(".admin/funkce.inc"));
require_once(FileUp2(".admin/isds_.inc"));
require_once(FileUp2(".admin/soap_funkce.inc"));
require_once(FileUp2(".admin/certifikat_funkce.inc"));
echo '<div id="upl_wait_message2" class="text" style="display:block"></div>';
echo '<div id="upl_wait_message" class="text" style="display:block"></div>';
echo "<script>document.getElementById('upl_wait_message').innerHTML = 'Kontaktuji datovou schránku...'</script>";Flush();
if ($GLOBALS[CONFIG_POSTA][DS][ds_cert_id]) $certifikat=VratCestukCertifikatu(0,$GLOBALS[CONFIG_POSTA][DS][ds_cert_id],1); else 
$certifikat='';
$schranka=new ISDSbox($GLOBALS[CONFIG_POSTA][DS][ds_user],$GLOBALS[CONFIG_POSTA][DS][ds_passwd],$certifikat);
if (!$schranka->ValidLogin)
{
	echo ("<span class='caption'>Nepodařilo se připojit k ISDS.</span><br/><span class='text'>Zkontrolujte uživatelské jméno a heslo.<br/>".$schranka->ErrorInfo."</span>");
  echo "<script>document.getElementById('upl_wait_message').style.display = 'none'</script>";
  require(FileUp2("html_footer.inc"));
	exit();
}

echo "<script>document.getElementById('upl_wait_message').innerHTML = 'Měním heslo...'</script>";Flush();


$OldPassword=$GLOBALS[CONFIG_POSTA][DS][ds_passwd];
$NewPassword=$_GET['password'];

//echo "$OldPassword,$NewPassword";
//Die();


$res=$schranka->ChangeISDSPassword($OldPassword,$NewPassword); 
if ($schranka->StatusCode<>'0000') {
  echo "<script>document.getElementById('upl_wait_message').innerHTML = 'Nepovedlo se změnit heslo!'</script>";Flush();
  echo "Odpověd z ISDS: <font color=red><b>".TxtEncodingFromSoap($schranka->StatusMessage)."</b></font><br/>";
  echo "<input type='button' onclick='document.location.href=\"password.php\";' value='Zpět' class='button btn'>";
  require(FileUp2("html_footer.inc"));
  Die();
}


echo "<script>document.getElementById('upl_wait_message2').innerHTML = 'Heslo změněno...'</script>";Flush();

For ($a=15; $a>1; $a--)
{
  echo "<script>document.getElementById('upl_wait_message').innerHTML = 'Čekám ".$a."s...'</script>";Flush();
  sleep(1);
}

$q=new DB_POSTA;
$sql="update posta_konfigurace set hodnota='".$NewPassword."' where parametr like 'ds_passwd'";
//echo $sql;
$q->query($sql);
echo "<script>document.getElementById('upl_wait_message').innerHTML = 'Nové heslo zapsáno do Nastavení DS.';
parent.document.location.href='index.php?frame';
</script>";Flush();
