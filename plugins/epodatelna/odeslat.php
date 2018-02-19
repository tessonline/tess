<?php
require("tmapy_config.inc");
include(FileUp2(".admin/brow_.inc"));
require_once(FileUp2(".admin/config.inc"));
require_once(FileUp2(".admin/db/db_posta.inc"));
require_once(FileUp2(".admin/oth_funkce.inc"));
require_once(FileUp2("html_header_full.inc"));
require(FileUp2(".admin/nastaveni.inc"));
require(FileUp2(".admin/funkce.inc"));
require(FileUp2(".admin/status.inc"));
require(FileUp2(".admin/odesilani.inc"));
require(FileUp2("interface/.admin/soap_funkce.inc"));

if (!HasRole('vypraveni-email')) die('Přístup zamítnut.');

$ID_ODCHOZI=$ID_ODCHOZI?$ID_ODCHOZI:$ID;
$q=new DB_POSTA;
//inicializace NuSOAP
require_once($GLOBALS["TMAPY_LIB"]."/lib/nusoap/lib/nusoap.php"); 
$eed_konektor='http://'.$_SERVER[HTTP_HOST].'/ost/posta/interface/konektor/server/soap.php';
$client = new tw_soapclient($eed_konektor, false);
$client->soap_defencoding='UTF-8';
$client->decodeUTF8(false);
$err = $client->getError();
if ($err) {
    echo "<script>document.getElementById('upl_wait_message').style.display = 'none'</script>";
    echo $button_back;
    Die('AEC server e-podatelny není dostupný');
}
$result = $client->call('login', array(
    'software_id'=>'EPODATELNA',
    'username'=>'AUTORIZOVANY_PRISTUP',
    'userpasswd'=>'11'
  )
);

$USER_INFO = $GLOBALS["TMAPY_SECURITY"]->GetUserInfo();
$id_user=$USER_INFO["ID"];
$jmeno_uzivatele=$USER_INFO["FNAME"]." ".$USER_INFO["LNAME"];
$LAST_USER_ID=$id_user;
$LAST_TIME=Date('H:i:s');
$LAST_DATE=Date('Y-m-d');
if ($result['return']['RESULT']<>'OK') Die('neni konexe na soap');
$session_id=$result['session_id'];
//echo "Otvírám emailovou schránku...<br/>"; Flush();

if ($ID_ODCHOZI)
  $pole[]=$ID_ODCHOZI;
else
{
  if (count($_POST)>0)
    $pole[]=$_POST["ID"];
}

if (count($pole)==0)
{
  require_once(FileUp2("html_footer.inc"));
  Die('<span class="caption">Nebyl vybrán žádný email pro načtení</span>');
}

$sql='select * from posta where id in ('.implode(',',$pole).')';
$q->query($sql);
while ($q->Next_Record()) {
  $emaily = explode(',', $q->Record[ODESL_EMAIL]);
  foreach ($emaily as $email) {
    $email = str_replace(' ', '', $email);
    if (!filter_var($email, FILTER_VALIDATE_EMAIL)) {
      echo '<p><font color=red><b>CHYBA: E-mailová adresa příjemce je neplatná (nekorektní zápis).</b></font></p>';
      echo '<input type="button" class="btn" onclick="Zavri();" value="   Zavřít    ">';
      require(FileUp2("html_footer.inc"));
      Die();
    }
  }
  echo "Zpracovávám email pro ".htmlentities($q->Record[ODESL_EMAIL])."<br/>"; Flush();
  $dokument_id=$q->Record[ID];
  $result = $client->call('get_files', array(
    'session_id'=>$session_id,
    'dokument_id'=>$dokument_id,
    )
  );
  $vec=$q->Record['ODESL_SUBJ']?$q->Record['ODESL_SUBJ']:$q->Record['VEC'];
  $cj = LoadClass('EedCj', $q->Record['ID']);
  $vec .= " (ČJ: " . $cj->cislo_jednaci.")";
//X-Confirm-reading-to 	Address to which notifications are to be sent and a request to get delivery notifications
//echo $q->Record[ODESL_EMAIL]." x ".$q->Record[ODESL_BODY]." x ".$q->Record[DATUM_PODATELNA_PRIJETI]." x ".$q->Record[VEC];
  $email=OdesliEmail($q->Record[ODESL_EMAIL], $q->Record[ODESL_BODY], $q->Record[DATUM_PODATELNA_PRIJETI], $vec,$result[soubory], $USER_INFO);

  if ($email['message_id']) {
    $sql="insert into posta_epodatelna (mailbox,smer,uid,record_uid,dokument_id,last_date,last_time,last_user_id)
    VALUES ('".$name_of_eed_folder."','t',".$email[id].",'".$email[message_id]."',$dokument_id,'".$LAST_DATE."','".$LAST_TIME."',".$LAST_USER_ID.");
    ";
  //    echo $sql."<br/>";
    $q->query($sql);

    $sql="update posta set datum_vypraveni='".Date('d.m.Y H:i:s')."',status=1,last_date='".$LAST_DATE."',last_time='".$LAST_TIME."',last_user_id=".$LAST_USER_ID." where id=".$dokument_id;
    $q->query($sql);
    $text = 'dokument (<b>'.$dokument_id.'</b>) byl vypraven přes e-mail. UID emailu je ' . $email[message_id];
    EedTransakce::ZapisLog($dokument_id, $text, 'DOC');
    NastavStatus($dokument_id, $LAST_USER_ID);
  }

}

Flush();
echo '<p><br/></p>';
echo '<input type="button" class="btn" onclick="Zavri();" value="   Zavřít    ">';

echo "<script>
  function Zavri() {
    window.opener.document.location.reload();
    window.close();
  }
</script>";
require(FileUp2("html_footer.inc"));
