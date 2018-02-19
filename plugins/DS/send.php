<?php
require("tmapy_config.inc");
include(FileUp2(".admin/brow_.inc"));
require_once(FileUp2(".admin/config.inc"));
require_once(FileUp2(".admin/db/db_posta.inc"));
require(FileUp2(".admin/funkce.inc"));
require_once(FileUp2(".admin/oth_funkce.inc"));
//require_once(FileUp2("html_header_full.inc"));
require(FileUp2("interface/.admin/soap_funkce.inc"));
require(FileUp2(".admin/nastaveni.inc"));
require(FileUp2(".admin/status.inc"));
require(FileUp2(".admin/upload_.inc"));
require(FileUp2(".admin/isds_.inc"));
require_once(Fileup2("html_header_title.inc"));
$q=new DB_POSTA;

if (!HasRole('vypraveni-ds')) die('Přístup zamítnut.');

$USER_INFO = $GLOBALS["TMAPY_SECURITY"]->GetUserInfo();
$id_user=$USER_INFO["ID"];
$jmeno_uzivatele=$USER_INFO["FNAME"]." ".$USER_INFO["LNAME"];
$LAST_USER_ID=$id_user;
$LAST_TIME=Date('H:m:i');
$LAST_DATE=Date('Y-m-d');

require_once($GLOBALS["TMAPY_LIB"]."/lib/nusoap/lib/nusoap.php"); 
$eed_konektor=$GLOBALS["KONEKTOR"]["SOAP_SERVER"];
$client = new TW_soapclient($eed_konektor, false);
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
    'login'=>'AUTORIZOVANY_PRISTUP',
    'userpasswd'=>'11'
  )
);
$session_id=$result['session_id'];

$schranka=new ISDSbox($GLOBALS[CONFIG_POSTA][DS][ds_user],$GLOBALS[CONFIG_POSTA][DS][ds_passwd],'');


if ($ID_ODCHOZI)
  $pole[]=$ID_ODCHOZI;
else
{
  if (count($_POST)>0)
    $pole=$_POST["SELECT_ID"];
}
if (count($pole)==0)
{
  require_once(FileUp2("html_footer.inc"));
  Die('<span class="caption">Nebyla vybrána žádná zpráva pro odeslání</span>');
}

$q=new DB_POSTA;
$USER_INFO = $GLOBALS["TMAPY_SECURITY"]->GetUserInfo();
$id_user=$USER_INFO["ID"];
$jmeno_uzivatele=$USER_INFO["FNAME"]." ".$USER_INFO["LNAME"];
$LAST_USER_ID=$id_user;
$LAST_TIME=Date('H:m:i');
$LAST_DATE=Date('Y-m-d');

$add_info="last_date='$LAST_DATE',last_time='$LAST_TIME',last_user_id=".$LAST_USER_ID;


while (list($aaa,$bbb)=each($pole))
{
//	EedTools::MaPristupKDokumentu($bbb, 'odeslani DZ');
//  if (JeVeSchvaleni($bbb) || JeKPodpisu($bbb)) continue(1);
  if ($GLOBALS['CONFIG']['BEZ_APROBACE_NELZE_ODESLAT'] && !SchvalenoKladne($bbb)) continue;
  //Die('STOP @');
  $zpravaDS=GetPoleProDS($bbb,$client,$session_id);
  echo "Odesílám datovou zprávu (ID $bbb)... <br/>"; Flush();

//print_r($zpravaDS);
//Die();

  $DS_id=$schranka->CreateMessage($zpravaDS);
  $noerror=false; 
  if ($schranka->StatusCode<>'0000') 
  {
    echo('<b>Chyba: <font color=red>'.TxtEncodingFromSoap($schranka->StatusMessage).'</font></b><br/>');
    $sql="update posta set poznamka='ISDS chyba:".TxtEncodingFromSoap($schranka->StatusMessage)."',$add_info where id=".$bbb;
    $q->query($sql);
  }
  else
  {
    echo "Odesláno úspěšně.<br/>"; Flush();
    echo "Ukládám informaci o odeslání... <br/>"; Flush();
    //uspesne odeslano, jdeme ulozit info
    $sql="insert into posta_DS (posta_id,DS_id,odeslana_posta,datum_odeslani,last_date,last_time,last_user_id) VALUES 
    ($bbb,$DS_id,'t','".Date('d.m.Y H:i:s')."','".$LAST_DATE."','".$LAST_TIME."',$LAST_USER_ID)";
//    echo $sql."<br/>";
    $q->query($sql);
    $sql="update posta set datum_vypraveni='".Date('d.m.Y H:i:s')."',poznamka='ISDS:Odeslano' where id=".$bbb;
//    echo $sql."<br/>";
    $q->query($sql);
    echo "Uloženo.<br/>"; Flush();
//    echo $sql."<br/>";
    NastavStatus($bbb);

    $text = 'dokument (<b>'.$bbb.'</b>) byl vypraven Datovou schránkou. ID datové zprávy je ' . $DS_id;
    EedTransakce::ZapisLog($bbb, $text, 'DOC');

    $noerror=true;
  }
}
//print_r($res);


$result = $client->call('logout', array(
    'session_id'=>$session_id,
  )
);
//echo "Hotovo.<br/>"; Flush();

if ($user && $noerror) //pokud na to kliknul uzivatel a nedoslo k chybe....
{
  echo "<script>window.opener.document.location.reload(); window.close()</script>";
}

if ($user)
echo "<a href='#' class='btn' onclick='window.opener.document.location.reload(); window.close();'>Zavřít</a>";
else
echo "<a href='#' class='btn' onclick='window.opener.document.location.reload(); window.close();'>Zavřít</a>";
//echo "<a href='odchozi.php'>Návrat zpět</a>";

require_once(FileUp2("html_footer.inc"));


