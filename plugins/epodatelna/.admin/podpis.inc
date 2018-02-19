<?php
// the message you want to sign so that recipient can be sure it was you that
// sent it
//$subject=iconv('ISO-8859-2','ISO-8859-1',$subject);

Function OdesliPodepsanyEmail($komu,$datum,$vec,$cj,$kdo)
{
  $tmp_adresar=$GLOBALS["CONFIG_POSTA"]["HLAVNI"]["tmp_adresar"];
//  $text_emailu=(trim($vec)<>'')?$vec:$GLOBALS["CONFIG_POSTA"]["EPODATELNA"]["text_emailu"];
  $text_emailu=$GLOBALS["CONFIG_POSTA"]["EPODATELNA"]["text_emailu"];
  include('.admin/nastaveni.inc');

  $z=array('$VEC$','$DATUM$','$CJ$','$KDO$');
  $na=array($vec,$datum,$cj,$kdo);
  $text_emailu=Str_replace($z,$na,$text_emailu);

  $boundary = md5(uniqid(time()));
  $boddy = "MIME-Version: 1.0\n";
  $boddy .= "Content-Type: multipart/mixed; boundary=\"" . $boundary. "\"\n";
  $boddy .= "From: ".$GLOBALS["CONFIG_POSTA"]["EPODATELNA"]["email_podatelna"]."\n"; 
  $boddy .= "Content-Transfer-Encoding: quoted-printable\n\n";
  $boddy .= "--$boundary\n";
//  $boddy .= "Content-Type: text/plain; charset=\"iso-8859-2\"\n";
  $boddy .= "Content-Type: text/plain; charset=\"UTF-8\"\n";
  $boddy .= "Content-Transfer-Encoding: quoted-printable\n\n";
  $boddy .= TxtEncoding4Soap($text_emailu) . "\n\n";
  $boddy .= "--$boundary--\n";
  
   // save message to file
  $fp = fopen($tmp_adresar."msg.txt", "w");
  fwrite($fp, $boddy);
  fclose($fp);
  $headers = array("From" => $GLOBALS["CONFIG_POSTA"]["EPODATELNA"]["email_podatelna"]);
  if ($GLOBALS[CONFIG_POSTA][EPODATELNA][epodatelna_cert_id]>0)
  {
    $podpis = VratCertifikat(0,$GLOBALS[CONFIG_POSTA][EPODATELNA][epodatelna_cert_id],1);;
    if ($podpis) {
      openssl_pkcs7_sign($tmp_adresar."msg.txt", $tmp_adresar."signed.txt", $podpis, array($podpis, ""), $headers);
      $data = file_get_contents($tmp_adresar."signed.txt");
    }
    else
      $data = file_get_contents($tmp_adresar."msg.txt");
  }
  else
    $data = file_get_contents($tmp_adresar."msg.txt");

  //echo $data;
  
  $parts = explode("\n\n", $data, 2);
  echo "odesilam email ".$komu."<br/>"; Flush();
  $subject = '=?UTF-8?B?'.base64_encode($GLOBALS["CONFIG_POSTA"]["EPODATELNA"]["subject"]).'?=';
//  mail($komu, $subject, $parts[1], $parts[0], '-f'.$epodatelna); //na decine -f zlobilo
  mail($komu, $subject, $parts[1], $parts[0], $GLOBALS[CONFIG_POSTA][EPODATELNA][force]);

}

Function OdesliPodepsanyEmailVir($komu,$datum,$vec,$cj,$kdo, $vir)
{
  $tmp_adresar=$GLOBALS["CONFIG_POSTA"]["HLAVNI"]["tmp_adresar"];
//  $text_emailu=(trim($vec)<>'')?$vec:$GLOBALS["CONFIG_POSTA"]["EPODATELNA"]["text_emailu"];
  $text_emailu=$GLOBALS["CONFIG_POSTA"]["EPODATELNA"]["text_emailu_vir"];
  include('.admin/nastaveni.inc');

  $viry_text = '';
  foreach($vir as $soubor => $nazev) {
    $viry_text = "Soubor: " . $soubor ." - virus: " . $nazev ."\n";
  }
  $z=array('$VEC$','$DATUM$','$CJ$','$KDO$','$SOUBORY$');
  $na=array($vec,$datum,$cj,$kdo, $viry_text);
  $text_emailu=Str_replace($z,$na,$text_emailu);

  $boundary = md5(uniqid(time()));
  $boddy = "MIME-Version: 1.0\n";
  $boddy .= "Content-Type: multipart/mixed; boundary=\"" . $boundary. "\"\n";
  $boddy .= "From: ".$GLOBALS["CONFIG_POSTA"]["EPODATELNA"]["email_podatelna"]."\n";
  $boddy .= "Content-Transfer-Encoding: quoted-printable\n\n";
  $boddy .= "--$boundary\n";
//  $boddy .= "Content-Type: text/plain; charset=\"iso-8859-2\"\n";
  $boddy .= "Content-Type: text/plain; charset=\"UTF-8\"\n";
  $boddy .= "Content-Transfer-Encoding: quoted-printable\n\n";
  $boddy .= TxtEncoding4Soap($text_emailu) . "\n\n";
  $boddy .= "--$boundary--\n";

   // save message to file
  $fp = fopen($tmp_adresar."msg.txt", "w");
  fwrite($fp, $boddy);
  fclose($fp);
  $headers = array("From" => $GLOBALS["CONFIG_POSTA"]["EPODATELNA"]["email_podatelna"]);
  if ($GLOBALS[CONFIG_POSTA][EPODATELNA][epodatelna_cert_id]>0)
  {
    $podpis = VratCertifikat(0,$GLOBALS[CONFIG_POSTA][EPODATELNA][epodatelna_cert_id],1);;
    if ($podpis) {
      openssl_pkcs7_sign($tmp_adresar."msg.txt", $tmp_adresar."signed.txt", $podpis, array($podpis, ""), $headers);
      $data = file_get_contents($tmp_adresar."signed.txt");
    }
    else
      $data = file_get_contents($tmp_adresar."msg.txt");
  }
  else
    $data = file_get_contents($tmp_adresar."msg.txt");

  //echo $data;

  $parts = explode("\n\n", $data, 2);
  echo "odesilam email ".$komu."<br/>"; Flush();
  $subject = '=?UTF-8?B?'.base64_encode($GLOBALS["CONFIG_POSTA"]["EPODATELNA"]["subject_vir"]).'?=';
//  mail($komu, $subject, $parts[1], $parts[0], '-f'.$epodatelna); //na decine -f zlobilo
  mail($komu, $subject, $parts[1], $parts[0], $GLOBALS[CONFIG_POSTA][EPODATELNA][force] ? '-f'.$GLOBALS["CONFIG_POSTA"]["EPODATELNA"]["email_podatelna"] : '' );

}

require(FileUp2("html_footer.inc"));
