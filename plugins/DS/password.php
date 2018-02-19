<?php
require("tmapy_config.inc");
require_once(FileUp2(".admin/brow_.inc"));
require_once(FileUp2("html_header_full.inc"));
require_once(FileUp2(".admin/nastaveni.inc"));
require_once(FileUp2("security/.admin/security_func.inc"));
require_once(FileUp2(".admin/funkce.inc"));
require_once(FileUp2(".admin/isds_.inc"));
require_once(FileUp2("interface/.admin/soap_funkce.inc"));
require_once(FileUp2("interface/.admin/certifikat_funkce.inc"));
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

echo "<script>document.getElementById('upl_wait_message').innerHTML = 'Načítám údaje o DS...'</script>";Flush();
$OwnerInfo=$schranka->GetOwnerInfoFromLogin(); 
if ($schranka->StatusCode<>'0000') {
  echo "Odpověd z ISDS: <b>".TxtEncodingFromSoap($schranka->StatusMessage)."</b>";
  require(FileUp2("html_footer.inc"));
  Die();
}

echo "<script>document.getElementById('upl_wait_message').innerHTML = 'Načítám údaje o uživateli...'</script>";Flush();
$UserInfo=$schranka->GetUserInfoFromLogin(); 
if ($schranka->StatusCode<>'0000') {
  echo "Odpověd z ISDS: <b>".TxtEncodingFromSoap($schranka->StatusMessage)."</b>";
  require(FileUp2("html_footer.inc"));
  Die();
}

echo "<script>document.getElementById('upl_wait_message').innerHTML = 'Načítám údaje o heslu...'</script>";Flush();
$PasswordInfo=$schranka->GetPasswordInfo(); 
if ($schranka->StatusCode<>'0000') {
  echo "Odpověd z ISDS: <b>".TxtEncodingFromSoap($schranka->StatusMessage)."</b>";
  require(FileUp2("html_footer.inc"));
  Die();
}

$odes_typ=$GLOBALS[TypDS][$OwnerInfo[dbType]];
//Die($odes_typ);

if ($odes_typ=='U' || $odes_typ=='P')
  $prijmeni=$OwnerInfo[firmName];
else
  $prijmeni=$OwnerInfo[pnLastName];
if ($OwnerInfo[dbType]=='OVM_NOTAR' || $OwnerInfo[dbType]=='OVM_EXEKUT') $prijmeni=$OwnerInfo[firmName];

$PasswordInfo=$schranka->GetPasswordInfo();

if (!$PasswordInfo) $PasswordInfo='bez expirace';
else
  $PasswordInfo=ConvertDatumToString($PasswordInfo);


//dbID] => fw8ahtk [dbType] => OVM [ic] => 73067199 [pnFirstName] => [pnMiddleName] => [pnLastName] => [pnLastNameAtBirth] => [firmName] => lioend [biDate] => [biCity] => [biCounty] => [biState] => [adCity] => Hradec KrĂĄlovĂprint_r($OwnerInfo);
echo "<h1>Údaje o datové schránce</h1><span class='text'>
<ul><table>
<tr><td>ID schránky:</td><td><b>".$OwnerInfo['dbID']."</b></td></tr>
<tr><td>Typ schránky:</td><td><b>".$OwnerInfo['dbType']."</b></td></tr>
<tr><td>Jméno majitele:</td><td><b>".TxtEncodingFromSoap($prijmeni)."</b></td></tr>
<tr><td>IČ majitele:</td><td><b>".$OwnerInfo['ic']."</b></td></tr>
</table>
</ul></span><br/>";


echo "<h1>Údaje o přihlášeném uživateli</h1><span class='text'>
<ul><table>
<tr><td>Uživatel:</td><td><b>".TxtEncodingFromSoap($UserInfo['pnFirstName']." ".$UserInfo['pnLastName'])."</b></td></tr>
<tr><td>Typ uživatele:</td><td><b>".$UserInfo['userType']."</b></td></tr>
<tr><td>Práva uživatele:</td><td><b>".$UserInfo['userPrivils']."</b></td></tr>
<tr><td>Expirace hesla:</td><td><b>".$PasswordInfo."</b></td></tr>
</table>
</ul></span><br/>";

echo "<h1>Nové heslo pro přihlášeného uživatele</h1><span class='text'>
<ul>Pravidla pro vytvoření nového hesla:<br/>&nbsp;
<li>Heslo do datové schránky musí být minimálně 8 a maximálně 32 znaků dlouhé.</li>
<li>Heslo musí obsahovat minimálně jedno velké písmeno, jedno malé písmeno a jedno číslo. Povolené znaky jsou písmena (a-z, A-Z), číslice (0-9) a speciální znaky (! # $ % & ( ) * + , - . : = ? @ [ ] _ { | } ~).</li>
<li>Není povoleno heslo shodné s jedním z posledních použitých 255 hesel.</li>
<li>Nesmí obsahovat id (login) uživatele, jemuž se heslo mění.</li>
<li>V hesle se nesmí opakovat za sebou 3 a více stejných znaků.</li>
<li>Heslo nesmí začínat na qwert, asdgf, 12345.</li>
<br/>
<b>Upozornění: při změně hesla je možné přihlášení novým heslem v důsledku replikací v infrastrukuře možné nejprve za cca 15 sekund.</b>
<br/>
<div class='form darkest-color'> <div class='form-body'> <div class='form-row'>

<form method='get' action='set_password.php' onsubmit='return frm_edit_Validator(this)'>
<table>
<tr><td align=right>Zadejte nové heslo:</td><td><input type='password' name='password' value='' size=15 maxlength=32 class='required'></td></tr>
<tr><td align=right>Zadejte heslo znovu:</td><td><input type='password' name='password_kontrola' value='' size=15 maxlength=32 class='required'></td></tr>
<tr><td align=right></td><td><input type='submit' name='sumbit' value='Změnit heslo' class='btn'></td></tr>

</table>
</div></div></div>
</ul>";

echo "<script>document.getElementById('upl_wait_message').innerHTML = ''</script>";Flush();
require(FileUp2("html_footer.inc"));

echo '
<script language="javascript" type="text/javascript">
<!--
function frm_edit_Validator(f) {
  if (f.password.value.length < 8) {
    alert("Heslo musí mít minimálně 8 a maximálně 32 znaků!");
    f.password.focus();
    return(false);
  }
  if (f.password.value.length != f.password_kontrola.value.length) {
    alert("Hesla jsou rozdílná!");
    f.password_kontrola.focus();
    return(false);
  }


//if (document.frm_edit.__) document.frm_edit.__.disabled = true;
}
//-->
</script>
';
