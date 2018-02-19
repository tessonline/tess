<?php
if (!$_SERVER['HTTPS'] == 'on') Die();
require("tmapy_config.inc");
include(FileUp2(".admin/brow_.inc"));
@include(FileUp2(".admin/run2_.inc"));
require_once(FileUp2(".admin/config.inc"));
require_once(FileUp2(".admin/db/db_posta.inc"));
require_once(FileUp2(".admin/oth_funkce.inc"));
//require_once(FileUp2("html_header_full.inc"));
require_once(FileUp2("interface/.admin/soap_funkce.inc"));
require_once(FileUp2("interface/.admin/certifikat_funkce.inc"));
require(FileUp2(".admin/funkce.inc"));
require(FileUp2(".admin/nastaveni.inc"));
require(FileUp2(".admin/status.inc"));
require(FileUp2(".admin/isds_.inc"));
require_once(Fileup2("html_header_title.inc"));
$q=new DB_POSTA;

$schranka=new ISDSbox($GLOBALS[CONFIG_POSTA][DS][ds_user],$GLOBALS[CONFIG_POSTA][DS][ds_passwd],'');

$USER_INFO = $GLOBALS["TMAPY_SECURITY"]->GetUserInfo();
$id_user=$USER_INFO["ID"];
$jmeno_uzivatele=$USER_INFO["FNAME"]." ".$USER_INFO["LNAME"];
$so = $USER_INFO['PRACOVISTE'];
$LAST_USER_ID=$id_user;
$LAST_TIME=Date('H:i:s');
$LAST_DATE=Date('Y-m-d');

//inicializace NuSOAP
require_once($GLOBALS["TMAPY_LIB"]."/lib/nusoap/lib/nusoap.php"); 
$eed_konektor=$GLOBALS["KONEKTOR"]["SOAP_SERVER"];

// if (strpos($eed_konektor,'?')) $eed_konektor.='&LAST_USER_ID='.$USER_INFO["ID"];
// else $eed_konektor.='?LAST_USER_ID='.$USER_INFO["ID"];

$client = new TW_SoapClient($eed_konektor, false);
$client->soap_defencoding='UTF-8';
$client->decodeUTF8(false);
$err = $client->getError();
if ($err) {
    echo "<script>document.getElementById('upl_wait_message').style.display = 'none'</script>";
    echo $button_back;
    Die('Konektor EED není dostupný');
}
$result = $client->call('login', array(
    'software_id'=>'DS',
    'username'=>'AUTORIZOVANY_PRISTUP',
    'userpasswd'=>'11'
  )
);
$session_id=$result['session_id'];
if ($result['return']['RESULT']<>'OK') Die('neni konexe na soap');
$session_id=$result['session_id'];
echo "Otvírám datovou schránku...<br/>"; Flush();


//print_r($_POST);
if ($ID_DOSLE)
  $pole[]=$ID_DOSLE;
else
{
  if (count($_POST)>0)
    $pole=$_POST["SELECT_ID"];
}
$pole=array_unique ($pole);
if (count($pole)==0)
{
  require_once(FileUp2("html_footer.inc"));
  Die('<span class="caption">Nebyla vybrána žádná datová zpráva pro načtení</span>');
}

//print_r($pole);
//Die();

$expirationTime = 60 * 2; // 2 minuty
deleteExpiredDmTimestamps($expirationTime);
$existSavedDms = FALSE; // existuji datove zpravy, ktere jiz byly ulozeny drive

while (list($aaa, $bbb) = each($pole))
{
  if (isDmSaved($bbb)) {
    $existSavedDms = TRUE;
    echo "<p style=\"color: red\">
            Datovou zprávu č. $bbb není možné uložit do EED (v EED se již nachází).
          </p>";
  }
  else {
    createDmTimestamp($bbb);
    UlozDZ($bbb, 1, $session_id, 0, $multiselect, $so);
  }
}

if ($existSavedDms) {
  echo '<p style="color: red; font-weight: bold">
          Pokud si přejete uložit některé datové zprávy znovu,
          budete tak moci učinit nejdříve za ' . $expirationTime / 60  . ' min.
        </p>';
}
//print_r($uid_email);


$result = $client->call('logout', array(
    'session_id'=>$session_id,
  )
);

echo "<a href='prichozi.php'>Návrat zpět</a>";

require_once(FileUp2("html_footer.inc"));


