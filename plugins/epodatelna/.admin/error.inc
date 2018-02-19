<?php

Function OdesliEmail($komu,$text_email,$datum,$vec,$soubory, $USER_INFO) {
  include('.admin/nastaveni.inc');
  $tmp_adresar = $GLOBALS["CONFIG_POSTA"]["HLAVNI"]["tmp_adresar"];
  $epodatelna = $GLOBALS["CONFIG_POSTA"]["EPODATELNA"]["email_podatelna"];
  $boundary = md5(uniqid(time()));
  $message_id=$boundary.".EED@".$_SERVER['SERVER_NAME'];
  $boddy = "MIME-Version: 1.0\n";
  $boddy .= "Content-Type: multipart/mixed; boundary=\"" . $boundary. "\"\n";
  $boddy .= "Message-ID: <".$message_id.">\n";  
//  $boddy .= "From: ".$GLOBALS["CONFIG_POSTA"]["EPODATELNA"]["email_podatelna"]."\n";
  $boddy .= "From: ePodatelna <".$GLOBALS["CONFIG_POSTA"]["EPODATELNA"]["email_podatelna"].">\n";
//  $boddy .= "Return-receipt-to: ".$epodatelna."\n";
//  $boddy .= "X-Confirm-Reading-To: ".$epodatelna." \n";
//  $boddy .= "Disposition-Notification-To: ".$epodatelna." \n";
  $boddy .= "Content-Transfer-Encoding: quoted-printable\n\n";
  $hlavicka_mailu = $boddy;
  $boddy .= "--$boundary\n";
  $boddy .= "Content-Type: text/plain; charset=\"utf-8\"\n";
  $boddy .= "Content-Transfer-Encoding: quoted-printable\n\n";
  $nl = "\n\n";
  $text_email .= $nl;
  $text_email .= 'Server: '. $_SERVER[HTTP_HOST] . $nl;
  $text_email .= 'Kde: ' . $_SERVER[REQUEST_URI] . $nl;
  $text_email .= 'Kdo: ' . $_SERVER[REMOTE_USER] . $nl;
  $text_email .= 'Kdy: ' . Date('d.m.Y H:i:s') . $nl;
  
  
  $boddy .= $text_email. $nl;


  while(list($key,$val)=@each($soubory)) {
    $boddy .= "--$boundary\n";
    $boddy .= "Content-Type: ".$val[BIND_TYPE]."; name=\"".$val[FILE_NAME]."\"\n";
    $boddy .= "Content-Transfer-Encoding: base64\n";
    $boddy .= "Content-Disposition: attachment;\n\n";
    $boddy .= chunk_split(base64_encode($val[FILE_DATA])) . "\n\n";
  } 
  $boddy .= "--$boundary--\n";

  $fp = fopen($tmp_adresar."msg.txt", "w");
  fwrite($fp, $boddy);
  fclose($fp);

  if ($GLOBALS[CONFIG_POSTA][EPODATELNA][epodatelna_cert_id]>0) {
    $podpis = VratCertifikat(0,$GLOBALS[CONFIG_POSTA][EPODATELNA][epodatelna_cert_id],1);;
    if ($podpis) {
      $headers['From'] = $GLOBALS["CONFIG_POSTA"]["EPODATELNA"]["email_podatelna"];
      $headers['Return-receipt-to'] = $epodatelna;
      $headers['Subject'] = '=?UTF-8?B?'.base64_encode($vec).'?=';;
//      $headers['X-Confirm-Reading-To'] = $epodatelna;
      //$headers['Disposition-Notification-To'] = $epodatelna;
      $podpis = VratCertifikat(0,$GLOBALS[CONFIG_POSTA][EPODATELNA][epodatelna_cert_id],1);;
      if ($podpis) {
        $fp = fopen($tmp_adresar."signKey.pem", "w");
        fwrite($fp, $podpis);
        fclose($fp);
        if (openssl_pkcs7_sign($tmp_adresar."msg.txt", $tmp_adresar."signed.txt", 'file://'.realpath($tmp_adresar."signKey.pem"), array('file://'.realpath($tmp_adresar."signKey.pem"), ""), $headers, PKCS7_DETACHED)) {
          $data = file_get_contents($tmp_adresar."signed.txt");
        }
        else {
          $data = file_get_contents($tmp_adresar."msg.txt");
        }
        unlink($tmp_adresar."signKey.pem");
      }
      else {
        $data = file_get_contents($tmp_adresar."msg.txt");
      }

    }
    else {
      $data = file_get_contents($tmp_adresar."msg.txt");
    }
  }
  else {
    $data = file_get_contents($tmp_adresar."msg.txt");
  }
  
  $parts = explode("\n\n", $data, 2);
  $subject = '=?UTF-8?B?'.base64_encode($vec).'?=';
  if ($a=mail($komu, $subject, $parts[1], $parts[0],  (strlen($GLOBALS[CONFIG_POSTA][EPODATELNA][force]>1) ? '-f' : '' ))) {
  }
  else {
    print_r($a);
    echo '<b><font color=red>Nastala chyba při odesílání. Email nebyl odeslán.</font></b><br/>';
  }
  
  //print_r($a);
  $return=array('id'=>1,'message_id'=>$message_id);
  return $return;
}
