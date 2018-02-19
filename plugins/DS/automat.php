<?php
/*
require("tmapy_config.inc");
include(FileUp2(".admin/brow_.inc"));
require_once(FileUp2(".admin/config.inc"));
require_once(FileUp2(".admin/db/db_posta.inc"));
include(FileUp2(".admin/isds_.inc"));
include(".admin/funkce.inc");
include(FileUp2(".admin/soap_funkce.inc"));
include(FileUp2(".admin/nastaveni.inc"));
*/
require("tmapy_config.inc");
include(FileUp2(".admin/brow_.inc"));
@include(FileUp2(".admin/run2_.inc"));
require_once(FileUp2(".admin/config.inc"));
require_once(FileUp2(".admin/db/db_posta.inc"));
require_once(FileUp2(".admin/oth_funkce.inc"));
//require_once(FileUp2("html_header_full.inc"));
require(FileUp2("interface/.admin/soap_funkce.inc"));
require(FileUp2(".admin/funkce.inc"));
require(FileUp2(".admin/nastaveni.inc"));
require(FileUp2(".admin/status.inc"));
require(FileUp2(".admin/isds_.inc"));
require_once(FileUp2(".admin/classes/EedDatovaZprava.inc"));

$dbDS=new DB_POSTA;
$c=new DB_POSTA;
$a=new DB_POSTA;
require_once(FileUp2(".admin/upload_.inc"));

$software_id='DS';
list($dny[1],$dny[2],$dny[3],$dny[4],$dny[5],$dny[6],$dny[0])=explode(',',$GLOBALS[CONFIG_POSTA][DS][ds_automat_vyzvedani]);
$denvtydnu=Date('w');
$do=0;
list($od,$do)=@explode('-',$dny[$denvtydnu]);

//testneme, jestli je na to cas.
if (!($do<>0 && $od<Date('Hi') && $do>Date('Hi')))
{
      Die('neni open'); //dneska se nema otvirat DS
   
}

$USER_INFO = $GLOBALS["TMAPY_SECURITY"]->GetUserInfo();
$id_user=$USER_INFO["ID"];
$jmeno_uzivatele=$USER_INFO["FNAME"]." ".$USER_INFO["LNAME"];
$LAST_USER_ID=$id_user;
$LAST_TIME=Date('H:i:s');
$LAST_DATE=Date('Y-m-d');

$add_info="last_date='$LAST_DATE',last_time='$LAST_TIME',last_user_id=".$LAST_USER_ID;


if ($GLOBALS[CONFIG_POSTA][DS][ds_cert_id]) $certifikat=VratCestukCertifikatu(0,$GLOBALS[CONFIG_POSTA][DS][ds_cert_id],1); else 
$certifikat='';
$schranka=new ISDSbox($GLOBALS[CONFIG_POSTA][DS][ds_user],$GLOBALS[CONFIG_POSTA][DS][ds_passwd],$certifikat);
if (!$schranka->ValidLogin)
{
  $text='(AUTOMAT) - Nepodařilo se připojit k ISDS';
  WriteLog($software_id,$text,$session_id,1);
  echo ("<span class='caption'>Nepodařilo se připojit k ISDS.</span><br/><span class='text'>Zkontrolujte uživatelské jméno a heslo.<br/>".$schranka->ErrorInfo."</span>");
  require(FileUp2("html_footer.inc"));
  exit();
}

$q=new DB_POSTA;
/*
//inicializace NuSOAP
require_once($GLOBALS["TMAPY_LIB"]."/lib/nusoap/lib/nusoap.php");
$eed_konektor=$GLOBALS["KONEKTOR"]["SOAP_SERVER"];
$client = new soapclient($eed_konektor, false);
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
*/
$status=96;
$dnes='2011-01-01T00:00:00';
$res=$schranka->GetListOfReceivedMessages($dnes,$zitra,0,100,$status);
if ($schranka->StatusCode<>'0000') Die('not 000');
$ds = new EedDatovaZprava();
$ds->VlozNoveZpravy($res);

while (list($aaa,$bbb)=@each($res[dmRecord]))
{
  $text='(AUTOMAT) - ukládám zprávu z DS s ID:'.$bbb[dmID];
  WriteLog($software_id,$text,$session_id);
  if ($val[dmPersonalDelivery]=='true')
  {
    $text='(AUTOMAT) - zpráva ID:'.$bbb[dmID].' je do vlastních rukou, nenahrávám.';
    WriteLog($software_id,$text,$session_id);
  }
  else
  {
    $soubor=array();
    $soubor=GetSouborzDS($bbb[dmID],$schranka);
    //ulozime soubory
    $cesta=$GLOBALS[CONFIG_POSTA][HLAVNI][tmp_adresar].$bbb[dmID].'/';
    if (!is_dir($cesta)) mkdir($cesta);
    $ulozeno=array();
    $citac=0;
    while (list($keyz,$valz)=each($soubor))
    {
      $citac++;
      $fname=$valz[filename];
      $pripona=substr($fname,strpos($fname,'.'));
      //$fname=TxtEncodingFromSoap($fname);
      $fname=str_replace("\\","",$fname);
      $add_text='';
      //pokud nemame nazev souboru, nebo pokud je nulovy, nebo pokud poslali dva soubory se stejnym nazvem
      if (strlen(TxtEncodingFromSoap($fname))<1 || in_array($fname,$ulozeno)) {$fname='soubor_'.$val[dmID].'-'.$citac.$pripona; $add_text='<br/>&nbsp;<i>zmena nazvu '.$valz[filename].'</i>';}
      $valz[filename]=$bbb[dmID].'-'.$citac;
      $ulozeno[]=$valz[filename]; //ulozime nazev souboru, obcas poslou soubory s duplicitnim nazvem
      $fp = fopen($cesta.$valz[filename], "w");
      fwrite($fp, base64_decode($valz[filecont]));
      fclose($fp);
        
    }
    UlozDZ($bbb[dmID],1,$session_id,1);
  }
}
//nacteme dorucenky
$sql="select * from posta_DS where odeslana_posta='t' and ((datum_precteni is NULL) or (datum_doruceni is NULL)) order by posta_id desc";
//echo $sql;
$c=new DB_POSTA;
$a=new DB_POSTA;
$dbDS = new DB_POSTA;
$dbDS->query($sql);
while ($dbDS->Next_Record())
{
  $id=$dbDS->Record[DS_ID];
  $posta_id=$dbDS->Record[POSTA_ID];
  $test=$schranka->GetDeliveryInfo($id);
  //echo "Vyskledek je";
  $doruceni=ConvertDatumToString($test[dmDeliveryTime]);
  $precteni=ConvertDatumToString($test[dmAcceptanceTime]);

  include('.admin/dorucenky.inc');

  $text='(AUTOMAT) - ukládám doručenku k ID:'.$posta_id.', vypraveno v '.$doruceni.', doručeno v '.$precteni;
  WriteLog($software_id,$text,$session_id);
}
