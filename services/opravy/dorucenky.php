<?php
require("tmapy_config.inc");
include(FileUp2(".admin/brow_.inc"));
require_once(FileUp2(".admin/config.inc"));
require_once(FileUp2(".admin/db/db_posta.inc"));
require(FileUp2("interface/DS/.admin/funkce.inc"));
require_once(FileUp2("html_header_full.inc"));
require(FileUp2("interface/.admin/soap_funkce.inc"));
require(FileUp2("interface/DS/.admin/nastaveni.inc"));
//require(FileUp2(".admin/security_.inc"));
require(FileUp2(".admin/isds_.inc"));
$q=new DB_POSTA;
$c=new DB_POSTA;
$a=new DB_POSTA;
set_time_limit(0);

$USER_INFO = $GLOBALS["TMAPY_SECURITY"]->GetUserInfo();
$id_user=$USER_INFO["ID"];
$jmeno_uzivatele=$USER_INFO["FNAME"]." ".$USER_INFO["LNAME"];
$LAST_USER_ID=$id_user;
$LAST_TIME=Date('H:m:i');
$LAST_DATE=Date('Y-m-d');

//inicializace NuSOAP
require_once($GLOBALS["TMAPY_LIB"]."/lib/nusoap/lib/nusoap.php"); 
$eed_konektor=$GLOBALS["KONEKTOR"]["SOAP_SERVER"];

if (strpos($eed_konektor,'?')) $eed_konektor.='&LAST_USER_ID='.$USER_INFO["ID"];
else $eed_konektor.='?LAST_USER_ID='.$USER_INFO["ID"];

$uplobj=Upload(array('create_only_objects'=>true,'agenda'=>'POSTA','noshowheader'=>true));
//print_r($result);

echo '<div id="upl_wait_message" class="text" style="display:block"></div>';
echo "<script>document.getElementById('upl_wait_message').innerHTML = 'Kontaktuji datovou schránku...'</script>";Flush();

$add_info="last_date='$LAST_DATE',last_time='$LAST_TIME',last_user_id=".$LAST_USER_ID;

$schranka=new ISDSbox($GLOBALS[CONFIG_POSTA][DS][ds_user],$GLOBALS[CONFIG_POSTA][DS][ds_passwd],'');

$sql="select * from posta_DS where odeslana_posta='t' order by posta_id asc";
//echo $sql;
$q->query($sql);
$pocet_zprav=$q->Num_Rows();
while ($q->Next_Record())
{
  $pocitadlo++;
  $id=$q->Record[DS_ID];
  $posta_id=$q->Record[POSTA_ID];
  $text_dorucenka='';

  echo "<script>document.getElementById('upl_wait_message').innerHTML = 'Zpracovávám zprávu ".$id." - ".$pocitadlo."/".$pocet_zprav."'</script>";Flush();

  $cela_DZ_ulozena=false;
  $odchozi_existuje=false;
  $dorucenka_existuje=false;

/*

  $result = $client->call('get_files', array(
    'session_id'=>$session_id,
    'dokument_id'=>$posta_id,
    )
  );
  while (list($key,$val)=each($result[soubory]))
  {
    if ($val['FILE_NAME']=='dorucenka.zfo') $dorucenka_existuje=true;
    if ($val['FILE_NAME']=='odchozi_datova_prava.zfo') $odchozi_existuje=true;
  }
  */

  $upload_records = $uplobj['table']->GetRecordsUploadForAgenda($posta_id);
//  print_r($upload_records);
  $seznam_souboru=array();
  
  while (list($key,$val)=each($upload_records)) 
  {
    if ($val['NAME']=='dorucenka.zfo') $dorucenka_existuje=true;
    if ($val['NAME']=='odchozi_datova_prava.zfo') $odchozi_existuje=true;
  }
  if (!$dorucenka_existuje || !$odchozi_existuje)
  {
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
        'login'=>'AUTORIZOVANY_PRISTUP',
        'userpasswd'=>'11'
      )
    );
    $session_id=$result['session_id'];
  }
  
  if (!$dorucenka_existuje)
  {
    $dorucenka_signed=$schranka->GetSignedDeliveryInfo($id);
    $podepsano=$dorucenka_signed[dmSignature];
    $test=$schranka->GetDeliveryInfo($id);
    $doruceni_datum=ConvertDatumToString($test[dmDeliveryTime]);
    $precteni=ConvertDatumToString($test[dmAcceptanceTime]);

    if (strlen($podepsano)>100 && strlen($precteni)>5)   //pokud dorucenka existuje
    {
      $soubor[0]['FILE_NAME']='dorucenka.zfo';
      $soubor[0]['FILE_DESC']=TxtEncoding4Soap('<i>doručenka podepsaná MV ČR</i>');
      $soubor[0]['BIND_TYPE']='application/octet-stream';
      $soubor[0]['FILE_DATA']=$podepsano;
  
  
      $result = $client->call('send_files', array(
        'session_id'=>$session_id,
        'dokument_id'=>$posta_id,
        'soubory'=>$soubor
        )
      );
      if ($result['return']['RESULT']<>'OK') 
      { 
        echo 'Nepodařilo se uložit soubory:<br/> ';Flush();
        echo '<pre>' . htmlspecialchars($client->response, ENT_QUOTES) . '</pre>';
        Die();
      } 
      else echo '<b>'.$posta_id.' - <i>doručenka uložena</i></b><br/>';
    }  else echo '<font color=red><b>DZ: '.$id.' - <i>nelze stáhnout doručenku</i></b></font><br/>';

  }
   //zkusime ulozit celou DZ
  if (!$odchozi_existuje)
  {
    $zprava_signed=$schranka->SignedSentMessageDownload($id);
    $podepsano=$zprava_signed['dmSignature'];
    if (strlen($podepsano)>100)
    {
    //  $podepsano=base64_decode($podepsano);
      $soubor[0]['FILE_NAME']='odchozi_datova_prava.zfo';
      $soubor[0]['FILE_DESC']=TxtEncoding4Soap('<i>odchozí datová zpráva podepsaná MV ČR</i>');
      $soubor[0]['BIND_TYPE']='application/octet-stream';
      $soubor[0]['FILE_DATA']=$podepsano;
  //    echo "Ukládám přílohy... <br/>"; Flush();
  
      $result = $client->call('send_files', array(
        'session_id'=>$session_id,
        'dokument_id'=>$posta_id,
        'soubory'=>$soubor
        )
      );
    
      if ($result['return']['RESULT']<>'OK') 
      { 
        echo 'Nepodařilo se uložit soubory:<br/> ';Flush();
        echo '<pre>' . htmlspecialchars($client->response, ENT_QUOTES) . '</pre>';
        Die();
      } 
      else echo '<b>'.$posta_id.' - <i>celá DZ uložena</i></b><br/>';
    }  else echo '<font color=red><b>DZ: '.$id.' - <i>nelze stáhnout celou DZ</i></b></font><br/>';
  }
  UNSET($client);  

}

echo "<script>document.getElementById('upl_wait_message').innerHTML = 'Hotovo'</script>";Flush();



require(FileUp2("html_footer.inc"));
