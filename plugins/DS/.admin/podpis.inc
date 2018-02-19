<?php
// the message you want to sign so that recipient can be sure it was you that
// sent it
//$subject=iconv('ISO-8859-2','ISO-8859-1',$subject);

Function OdesliPodepsanyEmail($komu,$datum,$vec,$cj,$kdo)
{
  include('.admin/nastaveni.inc');

  $z=array('%VEC%','%DATUM%','%CJ%','%KDO%');
  $na=array($vec,$datum,$cj,$kdo);
  $text_emailu=Str_replace($z,$na,$text_emailu);

  $boundary = md5(uniqid(time()));
  $boddy = "MIME-Version: 1.0\n";
  $boddy .= "Content-Type: multipart/mixed; boundary=\"" . $boundary. "\"\n";
  $boddy .= "Content-Transfer-Encoding: quoted-printable\n\n";
  $boddy .= "--$boundary\n";
  $boddy .= "Content-Type: text/plain; charset=\"iso-8859-2\"\n";
  $boddy .= "Content-Transfer-Encoding: quoted-printable\n\n";
  $boddy .= $text_emailu . "\n\n";
  $boddy .= "--$boundary--\n";


  
   // save message to file
  $fp = fopen($tmp_adresar."msg.txt", "w");
  fwrite($fp, $boddy);
  fclose($fp);
  $headers = array("From" => $email_podatelna);
  
  openssl_pkcs7_sign($tmp_adresar."msg.txt", $tmp_adresar."signed.txt", $podpisovy_klic, array($podpisovy_klic, "123456"), $headers);
  
  $data = file_get_contents($tmp_adresar."signed.txt");
  
  //echo $data;
  
  $parts = explode("\n\n", $data, 2);
  echo "odesilam email ".$komu."<br/>"; Flush();
  mail($komu, $subject, $parts[1], $parts[0]);

}
require(FileUp2("html_footer.inc"));
