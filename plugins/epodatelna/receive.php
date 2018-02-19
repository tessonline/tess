<?php
require("tmapy_config.inc");
include(FileUp2(".admin/run2_.inc"));
require_once(FileUp2(".admin/config.inc"));
require_once(FileUp2(".admin/db/db_posta.inc"));
require_once(FileUp2(".admin/oth_funkce.inc"));
require_once(FileUp2(".admin/oth_funkce_2D.inc"));
require_once(FileUp2("html_header_full.inc"));
require(FileUp2(".admin/nastaveni.inc"));
require(FileUp2(".admin/funkce.inc"));
require(FileUp2("interface/.admin/soap_funkce.inc"));
require(FileUp2(".admin/podpis.inc"));
require(FileUp2(".admin/status.inc"));
require(FileUp2("lib/elpodpis/function.inc"));
require_once(FileUp2(".admin/classes/e_signing/SMimeFile.php"));
require_once(FileUp2(".admin/classes/e_signing/Email.php"));

$q=new DB_POSTA;
//inicializace NuSOAP
require_once($GLOBALS["TMAPY_LIB"]."/lib/nusoap/lib/nusoap.php"); 

$USER_INFO = $GLOBALS["TMAPY_SECURITY"]->GetUserInfo();
$id_user=$USER_INFO["ID"];
$jmeno_uzivatele=$USER_INFO["FNAME"]." ".$USER_INFO["LNAME"];
$so = $USER_INFO['PRACOVISTE'];
$LAST_USER_ID=$id_user;
$LAST_TIME=Date('H:i:s');
$LAST_DATE=Date('Y-m-d');
/*
$eed_konektor=$GLOBALS["KONEKTOR"]["SOAP_SERVER"];
if (strpos($eed_konektor,'?')) $eed_konektor.='&LAST_USER_ID='.$USER_INFO["ID"];
else $eed_konektor.='?LAST_USER_ID='.$USER_INFO["ID"];

$client = new tw_soapclient($eed_konektor, false);
$client->soap_defencoding='UTF-8';
$client->decodeUTF8(false);
$err = $client->getError();
if ($err) {
    echo "<script>document.getElementById('upl_wait_message').style.display = 'none'</script>";
    echo $button_back;
    Die('Server e-podatelny není dostupný');
}
$result = $client->call('login', array(
    'software_id'=>'EPODATELNA',
    'username'=>'AUTORIZOVANY_PRISTUP',
    'userpasswd'=>'11'
  )
);
print_r($client->response);
if ($result['return']['RESULT']<>'OK') Die('neni konexe na soap');
$session_id=$result['session_id'];
*/
echo "Otevírám emailovou schránku...<br/>"; Flush();

$mbox_eed = imap_open("".$eed_folder."", $GLOBALS["CONFIG_POSTA"]["EPODATELNA"]["username"], $GLOBALS["CONFIG_POSTA"]["EPODATELNA"]["passwd"]);

unset($email);

if ($ID_DOSLE)
  $pole[] = $ID_DOSLE;
else {
  if (count($_POST["SELECT_IDepodatelna"])>0)
    if ($_POST['SELECT_IDepodatelna']>0) $pole=$_POST["SELECT_IDepodatelna"];
}
if (count($pole)==0) {
  require_once(FileUp2("html_footer.inc"));
  echo '<h1>Nebyl vybrán žádný email pro načtení</h1>';
  echo "<a href='prichozi.php' class='btn'>Návrat zpět</a>";
  require_once(FileUp2("html_footer.inc"));
  Die();
}

//print_r($pole);


include_once($GLOBALS['TMAPY_LIB'].'/upload/functions/SOAP_602_print2pdf.php');
//pod stejnzm souborem ulozi 
$a=new SOAP_602_print2pdf($SERVER_CONFIG["UPLOAD_CONFIG"]["MODULES"]["table"]["STORAGE"]["Print2PDF_SERVICE"]);

while (list($aaa,$bbb)=each($pole)) {
  UlozitMail($bbb,null, $so);
}

//print_r($uid_email);

imap_close($mbox_eed);
//imap_close($mbox);

/*
$result = $client->call('logout', array(
    'session_id'=>$session_id,
  )
);
*/
echo "<a href='prichozi.php' class='btn'>Návrat zpět</a>";

require_once(FileUp2("html_footer.inc"));


