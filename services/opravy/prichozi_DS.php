<?php
require("tmapy_config.inc");
include(FileUp2(".admin/run2_.inc"));
require_once(FileUp2(".admin/config.inc"));
require_once(FileUp2(".admin/db/db_posta.inc"));
require(FileUp2("plugins/DS/.admin/funkce.inc"));
require_once(FileUp2("html_header_full.inc"));
require(FileUp2("interface/.admin/soap_funkce.inc"));
require(FileUp2("plugins/DS/.admin/nastaveni.inc"));
require(FileUp2(".admin/upload_.inc"));
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

$sql="select * from posta_DS where odeslana_posta='f' and posta_id=1000511821 order by posta_id asc";
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
  $prichozi_existuje=false;


  $upload_records = $uplobj['table']->GetRecordsUploadForAgenda($posta_id);
//  print_r($upload_records);
  $seznam_souboru=array();
  
  while (list($key,$val)=each($upload_records)) 
  {
    if ($val['NAME']=='prichozi_datova_prava.zfo') $prichozi_existuje=true;
  }

 //zkusime ulozit celou DZ
  if (!$prichozi_existuje)   {
    $soubory = GetSouborzDS($id, $schranka);
    $ulozeno = array();
    while (list($key,$val)=each($soubory)) {
      $citac++;
      $cesta=$GLOBALS[CONFIG_POSTA][HLAVNI][tmp_adresar].$id.'/';
      $pripona=substr($val[FILE_NAME],strrpos($val[FILE_NAME],'.'));
      $val[FILE_NAME]=$dm_id.'-'.$citac;
      $tmp_soubor=$cesta.$val[FILE_NAME];

      $GLOBALS['DESCRIPTION'] = TxtEncodingFromSoap($val[filedesc]);
      $GLOBALS['TYPEFILE'] = $val[filetype];
      $GLOBALS['LAST_USER_ID'] = $val[LAST_USER_ID];
      $fname=$val[filename];
      $fname=str_replace("\\","",$fname);
      //pokud nemame nazev souboru, nebo pokud je nulovy, nebo pokud poslali dva soubory se stejnym nazvem
//        echo "Pripona je $pripona, soubor je $fname puvodni je ".$val[FILE_NAME]." x ".strlen(TxtEncodingFromSoap($fname))." ".in_array($fname,$ulozeno)."<br/>";
      if (strlen(TxtEncodingFromSoap($fname))<1 || in_array($fname,$ulozeno)) {
        $pripona=substr($fname,strpos($fname,'.'));
        $fname='soubor_'.$dm_id.'-'.$citac.$pripona; $add_text='<br/>&nbsp;zmena nazvu z: '.$valz[filename];
        $GLOBALS['RENAME'] = $fname;
      }
      else
        $GLOBALS['RENAME'] = TxtEncodingFromSoap($val[filename]);

      $ulozeno[]=$val[filename]; //ulozime nazev souboru, obcas poslou soubory s duplicitnim nazvem


      $file_exists = false;
      //testneme, jestli uz v uploadu soubor neni
      foreach($upload_records as $filex) {
        if ($filex['NAME'] == $GLOBALS['RENAME']) $file_exists = true;
      }

      if (!$file_exists) {
        $cesta=$GLOBALS[CONFIG_POSTA][HLAVNI][tmp_adresar].$id.'/';
        if (!is_dir($cesta)) mkdir($cesta);

        $fp = fopen($tmp_soubor, "w");
        fwrite($fp, base64_decode($val[filecont]));
        fclose($fp);

        if (filesize($tmp_soubor)<1) echo '<font color=red><b>Soubor '.$GLOBALS['RENAME'].' ma velikost 0 bajtu!!!</b></font><br/>';

        echo "Ulozime soubor $tmp_soubor  - " . $GLOBALS['RENAME'] . '<br/>';
        $ret = $uplobj['table']->SaveFileToAgendaRecord(TxtEncodingFromSoap($tmp_soubor), $posta_id);
        if ($ret[err_msg]<>'') echo 'Chyba pri ulozeni souboru '.$val["NAME"].': '.$ret[err_msg];
      }
//        else unlink($tmp_soubor);
    }
  }
  UNSET($client);  

}

echo "<script>document.getElementById('upl_wait_message').innerHTML = 'Hotovo'</script>";Flush();



require(FileUp2("html_footer.inc"));
