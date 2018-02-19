<?php
//   $client = new TW_SoapClient($eed_konektor, false);
//   $client->soap_defencoding='UTF-8';
//   $client->decodeUTF8(false);
//   $err = $client->getError();
//   if ($err) {
//       echo "<script>document.getElementById('upl_wait_message').style.display = 'none'</script>";
//       echo $button_back;
//       Die('Konektor EED není dostupný');
//   }
//   $result = $client->call('login', array(
//       'software_id'=>'DS',
//       'login'=>'AUTORIZOVANY_PRISTUP',
//       'userpasswd'=>'11'
//     )
//   );
//   $session_id=$result['session_id'];

//  echo $dbDS->Record[DS_ID]."<br/>";
  $b++;
  $id=$dbDS->Record[DS_ID];
  $posta_id=$dbDS->Record[POSTA_ID];

  echo "<script>document.getElementById('upl_wait_message').innerHTML = 'Zpracovávám zprávu ".$id." - ".$b."/".$pocet_dorucenek."'</script>";Flush();

  $test=$schranka->GetDeliveryInfo($id);
  echo "<script>document.getElementById('upl_wait_message').innerHTML = 'Načteno getdeliveryinfo ".$id." - ".$b."/".$pocet_dorucenek."'</script>";Flush();
  
  $doruceni_datum=ConvertDatumToString($test[dmDeliveryTime]);
  $precteni=ConvertDatumToString($test[dmAcceptanceTime]);
  $doruceni_cislo=$test[dmMessageStatus];
  $doruceni=$GetListOfMessagesResponse[$doruceni_cislo];
//  print_r($doruceni);

  if (strlen($precteni)>5) {
    //ISDS obcas nevracelo datum doruceni, tak at si nesmazem uz zapsane datum
    $sql="update posta set datum_doruceni='".$precteni."',datum_vypraveni='".$doruceni_datum."',poznamka='ISDS: ".$doruceni."',$add_info where id=".$posta_id;
    $c->query($sql);
    echo "<script>document.getElementById('upl_wait_message').innerHTML = 'Nastaveno datum doručeni,vypravení ".$id." - ".$b."/".$pocet_dorucenek."'</script>";Flush();
    NastavStatus($posta_id);
    echo "<script>document.getElementById('upl_wait_message').innerHTML = 'Nastaven status ".$id." - ".$b."/".$pocet_dorucenek."'</script>";Flush();
  }

  //echo $sql;
  $text_dorucenka='';

  $cela_DZ_ulozena=false;
  $soubor_existuje=false;
  $dorucenka_existuje=false;
  $soubory=array();
  $uplobj = Upload(array('create_only_objects'=>true,'agenda'=>'POSTA','noshowheader'=>true));
  $upload_records = $uplobj['table']->GetRecordsUploadForAgenda($posta_id); 
  unset($uplobj);
  if (is_array($soubor)) unset($soubor);
  $soubor=array();
  while (list($key,$val)=each($upload_records)) {
    if ($val['NAME']=='dorucenka.zfo') $dorucenka_existuje = true;
    if ($val[NAME]=='odchozi_datova_zprava.zfo') $soubor_existuje=true;
  }

  if (strlen($precteni)>5 && !$dorucenka_existuje) {
    //jdeme ulozit dorucenku
    echo "<script>document.getElementById('upl_wait_message').innerHTML = 'Jdu uložit doručenku ".$id." - ".$b."/".$pocet_dorucenek."'</script>";Flush();
    $dorucenka_signed=$schranka->GetSignedDeliveryInfo($id);
    $podepsano=$dorucenka_signed[dmSignature];
  //  $podepsano=base64_decode($podepsano);
//    echo "Ukladam dorucenku pro posta Id ".$posta_id;
    $soubor[0]['FILE_NAME']='dorucenka.zfo';
    $soubor[0]['FILE_DESC']=TxtEncoding4Soap('<i>doručenka podepsaná MV ČR</i>');
    $soubor[0]['BIND_TYPE']='application/octet-stream';
    $soubor[0]['FILE_DATA']=$podepsano;
//    echo "Ukládám přílohy... <br/>"; Flush();

    $cesta_slozka_dorucenka = $GLOBALS["CONFIG_POSTA"]["HLAVNI"]["tmp_adresar"].DIRECTORY_SEPARATOR.$posta_id.DIRECTORY_SEPARATOR;
    $cesta_dorucenka = $cesta_slozka_dorucenka . $soubor[0]['FILE_NAME'];
    if(!file_exists($cesta_slozka_dorucenka)) {
      mkdir($cesta_slozka_dorucenka);
    }
    $ulozeni_dorucenky = fopen($cesta_dorucenka, 'w');
    fwrite($ulozeni_dorucenky, base64_decode($soubor[0]['FILE_DATA']));
    fclose($ulozeni_dorucenky);
    $GLOBALS['DESCRIPTION'] = '<i>doručenka podepsaná MV ČR</i>';
    $uplobj_dorucenka = Upload(array('create_only_objects' => true, 'agenda' => 'POSTA', 'noshowheader' => true));
    $uplobj_dorucenka['table']->saveFileToAgendaRecord($cesta_dorucenka, $posta_id);
    
//    if ($result['return']['RESULT']<>'OK') {
//      echo 'Nepodařilo se uložit soubory:<br/> ';Flush();
//      echo (strlen($soubor[0]['FILE_DATA'])/1024).' kB';
//      echo '<pre>' . htmlspecialchars($client->response, ENT_QUOTES) . '</pre>';
//      Die();
//    } 
//    else $text_dorucenka='<b><i>doručenka uložena</i></b>';
    echo "<script>document.getElementById('upl_wait_message').innerHTML = 'Doručenka uložena ".$id." - ".$b."/".$pocet_dorucenek."'</script>";Flush();

  }
   //zkusime ulozit celou DZ
//   echo "Doruceni je $doruceni_cislo ".$soubor_existuje;
  if ($doruceni_cislo>3 && !$soubor_existuje) {
    echo "<script>document.getElementById('upl_wait_message').innerHTML = 'Jdu načíst podepsanou DZ ".$id." - ".$b."/".$pocet_dorucenek."'</script>";Flush();
    $zprava_signed=$schranka->SignedSentMessageDownload($id);
    $podepsano=$zprava_signed['dmSignature'];
    
    echo "<script>document.getElementById('upl_wait_message').innerHTML = 'Jdu uložit podepsanou DZ ".$id." - ".$b."/".$pocet_dorucenek."'</script>";Flush();
  //  $podepsano=base64_decode($podepsano);
    $soubor[0]['FILE_ID']='';
    $soubor[0]['FILE_NAME']='odchozi_datova_zprava.zfo';
    $soubor[0]['FILE_DESC']=TxtEncoding4Soap('<i>odchozí datová zpráva podepsaná MV ČR</i>');
    $soubor[0]['BIND_TYPE']='application/octet-stream';
    $soubor[0]['FILE_DATA']=$podepsano;
//    echo "Ukládám přílohy... <br/>"; Flush();
    if (strlen($podepsano)>1) {
      $cesta_slozka_odz = $GLOBALS["CONFIG_POSTA"]["HLAVNI"]["tmp_adresar"].DIRECTORY_SEPARATOR.$posta_id.DIRECTORY_SEPARATOR;
      $cesta_odz = $cesta_slozka_odz . $soubor[0]['FILE_NAME'];
      if(!file_exists($cesta_slozka_odz)) {
        mkdir($cesta_slozka_odz);
      }
      $ulozeni_odz = fopen($cesta_odz, 'w');
      fwrite($ulozeni_odz, base64_decode($soubor[0]['FILE_DATA']));
      fclose($ulozeni_odz);
      $GLOBALS['DESCRIPTION'] = '<i>odchozí datová zpráva podepsaná MV ČR</i>';
      $uplobj_odz = Upload(array('create_only_objects' => true, 'agenda' => 'POSTA', 'noshowheader' => true));
      $ret = $uplobj_odz['table']->saveFileToAgendaRecord($cesta_odz, $posta_id);
//      if ($result['return']['RESULT']<>'OK') {
//        echo 'Nepodařilo se uložit soubory:<br/> ';Flush();
//        echo (strlen($soubor[0]['FILE_DATA'])).' kB';
//        echo '<pre>' . htmlspecialchars($client->request, ENT_QUOTES) . '</pre>';
//        echo '<pre>' . htmlspecialchars($client->response, ENT_QUOTES) . '</pre>';
//        Die();
//      } 
    }
    else $cela_DZ_ulozena=true;

    echo "<script>document.getElementById('upl_wait_message').innerHTML = 'Podepsaná DZ uložena ".$id." - ".$b."/".$pocet_dorucenek."'</script>";Flush();

  }
  if ($doruceni_datum <> '')
    $sql="update posta_DS set datum_doruceni='".$doruceni_datum."' where ds_id=".$id;
  if ($precteni <> '' && $doruceni_datum <> '')
    $sql="update posta_DS set datum_precteni='".$precteni."',datum_doruceni='".$doruceni_datum."' where ds_id=".$id;

  $c->query($sql);
