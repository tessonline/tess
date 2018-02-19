<?php
require('tmapy_config.inc');
include(FileUp2(".admin/run2_.inc"));
require(FileUp2('.admin/brow_.inc'));
require_once(FileUp2('.admin/funkce.inc'));
require_once(FileUp2('.admin/oth_funkce_2D.inc'));
require_once(FileUp2('interface/.admin/soap_funkce.inc'));
require_once($GLOBALS["TMAPY_LIB"]."/lib/nusoap/lib/nusoap.php");

require_once(FileUp2(".admin/podpis.inc"));
require_once(FileUp2(".admin/status.inc"));
require_once(FileUp2("lib/elpodpis/function.inc"));
require_once(FileUp2(".admin/classes/e_signing/SMimeFile.php"));
require_once(FileUp2(".admin/classes/e_signing/Email.php"));

$software_id='ePodatelna';
$q = new DB_POSTA;
$sql = "select record_uid from posta_epodatelna where smer = 'f'";
$q->query($sql);
while ($q->Next_Record()) $jiz_nactene[] = $q->Record[RECORD_UID];

$USER_INFO = $GLOBALS["TMAPY_SECURITY"]->GetUserInfo();
$id_user=$USER_INFO["ID"] ? $USER_INFO["ID"] : 99;
$jmeno_uzivatele=$USER_INFO["FNAME"]." ".$USER_INFO["LNAME"];
$LAST_USER_ID=$id_user;
$LAST_TIME=Date('H:i:s');
$LAST_DATE=Date('Y-m-d');

$eed_konektor=$GLOBALS["KONEKTOR"]["SOAP_SERVER"];
if (strpos($eed_konektor,'?')) $eed_konektor.='&LAST_USER_ID='.$USER_INFO["ID"];
else $eed_konektor.='?LAST_USER_ID='.$id_user;

$client = new tw_soapclient($eed_konektor, false);
$client->soap_defencoding='UTF-8';
$client->decodeUTF8(false);
$err = $client->getError();
$result = $client->call('login', array(
    'software_id'=>'EPODATELNA',
    'username'=>'AUTORIZOVANY_PRISTUP',
    'userpasswd'=>'11'
  )
);
if ($result['return']['RESULT']<>'OK') Die('neni konexe na soap');
$session_id=$result['session_id'];

$qq = new DB_POSTA;
$sql="select * from posta_konfigurace where kategorie='EPODATELNA' and odbor is null";
$qq->query($sql);
$a = 0;
while ($qq->Next_Record()) {
  $kategorie=$qq->Record[KATEGORIE];
  $parametr=$qq->Record[PARAMETR];
  $hodnota=$qq->Record[HODNOTA];
  $so = $qq->Record['SUPERODBOR'] ? $qq->Record['SUPERODBOR'] : 0;
  $GLOBALS["temp_podatelna"][$kategorie][$so]['SUPERODBOR']=$so;
  $GLOBALS["temp_podatelna"][$kategorie][$so][$parametr]=$hodnota;
}

$sql="select * from posta_konfigurace where kategorie='EPODATELNA' and odbor is not null";
$qq->query($sql);
$a = 0;
while ($qq->Next_Record()) {
  $kategorie=$qq->Record[KATEGORIE];
  $parametr=$qq->Record[PARAMETR];
  $hodnota=$qq->Record[HODNOTA];
  $odbor=$qq->Record[ODBOR];
  $klic = $qq->Record['SUPERODBOR'] + ($odbor*1000);
  $so = $qq->Record['SUPERODBOR'];
  $GLOBALS["temp_podatelna"][$kategorie][$klic] = $GLOBALS["temp_podatelna"][$kategorie][$so];
  $GLOBALS["temp_podatelna"][$kategorie][$klic]['SUPERODBOR']=$so;
  $GLOBALS["temp_podatelna"][$kategorie][$klic][$parametr]=$hodnota;
}


foreach($GLOBALS["temp_podatelna"][$kategorie] as $key => $podatelna ) {
  if ($podatelna['username']) {
    $GLOBALS['CONFIG_POSTA']['EPODATELNA'] = $podatelna;
    if (strlen($podatelna['imap_adresa'])<5) continue;
    $so = $podatelna['SUPERODBOR'];
    require(FileUp2('.admin/nastaveni.inc'));

    echo Date('d.m.Y H:i:s') . "Nacitam pro " . $eed_folder ." pro so = $so<br/>";

    $mbox_eed = imap_open($eed_folder, $GLOBALS["CONFIG_POSTA"]["EPODATELNA"]["username"], $GLOBALS["CONFIG_POSTA"]["EPODATELNA"]["passwd"]);
    $sorted = imap_sort($mbox_eed, SORTARRIVAL,  1); // setridime zpravy
    $count = count($headers);


    while (list($key, $val) = each($sorted)) {
      unset($email);
      $email = VratEmailPole($mbox_eed, $val, 0);

      if (!in_array($email[message_id], $jiz_nactene)) {
        echo Date('d.m.Y H:i:s') . "- jdeme ulozit novy email
    ";
        $text='(AUTOMAT) - ukládám zprávu z epodatelny:' . $email['message_id'];
        WriteLog($software_id,$text,$session_id);
        UlozitMail($val, $session_id, $so);
      }
    }


  }
}

