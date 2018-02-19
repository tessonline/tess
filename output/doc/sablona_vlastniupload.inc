<?php

$barcode = TxtEncodingToWin($barcode);
$cislo_spisu = TxtEncodingToWin($cislo_spisu);
$datum_prijeti = TxtEncodingToWin($datum_prijeti);
$odbor = TxtEncodingToWin($odbor);
$ADRESA_OSLOVENI = TxtEncodingToWin($ADRESA_OSLOVENI);
$ODESILATEL = TxtEncodingToWin($ODESILATEL);
$ADRESA_JMENO = TxtEncodingToWin($ADRESA_JMENO);
$ADRESA_ULICE = TxtEncodingToWin($ADRESA_ULICE);
$ADRESA_MESTO = TxtEncodingToWin($ADRESA_MESTO);
$ADRESA_ODD = TxtEncodingToWin($ADRESA_ODD);
$ADRESA_KONTOSOBA = TxtEncodingToWin($ADRESA_KONTOSOBA);
$c_jednaci = TxtEncodingToWin($c_jednaci);
$REFERENT_JMENO = TxtEncodingToWin($REFERENT_JMENO);
$REFERENT_TELEFON = TxtEncodingToWin($REFERENT_TELEFON);
$vec = TxtEncodingToWin($vec);
$urednik_email = TxtEncodingToWin($urednik_email);
$jejich_cj = TxtEncodingToWin($jejich_cj);
$urednik_fax = TxtEncodingToWin($urednik_fax);
$dalsi_osoby = TxtEncodingToWin($dalsi_osoby);
$REFERENT_JEN_PRIJMENI = TxtEncodingToWin($REFERENT_JEN_PRIJMENI);
$su_adresa = TxtEncodingToWin($su_adresa);
$su_telefon= TxtEncodingToWin($su_telefon);
$su_mobil = TxtEncodingToWin($su_mobil);
$su_mail = TxtEncodingToWin($su_mail);


//primarne vznikle z Noveho Jicina, predpokladem je prime napojeni do eed pres sambu a pres vyvolavani pres unc cesty
If ($sablona=='odpoved_test')
{

  $cesta="/".$GLOBALS["CONFIG"]["VLASTNI_UPLOAD_VNITRNI"];

  $cela_cesta=$cesta."/sablony";
  $nazev_souboru=md5($id_sablony);
//  $nazev_souboru=$id_sablony;
  $filename=$cela_cesta."/".$nazev_souboru.".rtf";
//  echo $filename."<br/>";
  $fn = FileUpUrl($filename);
  $fp = fopen ($fn, "r");
  $sablona = fread ($fp, filesize ($fn));
  fclose ($fp);

  $z=array("%DATUM_NAROZENI%","%CISLO_SPISU%","%DATUM_PRIJETI%","%ODBOR_REFERENTA%","%ADRESA_OSLOVENI%","%ADRESA_ODESILATELE%","%ADRESA_JMENO%","%ADRESA_ULICE%","%ADRESA_MESTO%","%ADRESA_ODD%","%ADRESA_KONTOSOBA%","%CISLO_JEDNACI%","%UREDNIK_JMENO%","%UREDNIK_TELEFON%","%DNESNI_DATUM%","%VEC_DOPISU%","%UREDNIK_EMAIL%","%JEJICH_CJ%","%UREDNIK_FAX%","%ROZDELOVNIK%","%DATUM_NAROZENI%","%SU_ADRESA%", "%SU_TELEFON%","%SU_MOBIL%","%SU_EMAIL%");
  $na=array($datum_narozeni,$cislo_spisu,$datum_prijeti,$odbor,$ODESILATEL,$ADRESA_OSLOVENI,$ADRESA_JMENO,$ADRESA_ULICE,$ADRESA_MESTO,$ADRESA_ODD,$ADRESA_KONTOSOBA,$c_jednaci,$REFERENT_JMENO,$REFERENT_TELEFON,Date('d.m.Y'),$vec,$urednik_email,$jejich_cj,$urednik_fax,$dalsi_osoby,$datum_narozeni,$su_adresa, $su_telefon, $su_mobil, $su_mail);
  $vysledny=Str_replace($z,$na,$sablona);
  
  $nazev='test.rtf';
  Header("Content-Type: application/rtf");
  Header("Content-Disposition: attachment;filename=$nazev");
  echo $vysledny;   
}

If (($sablona=='odpoved'||$sablona=='sablona_nove') && $GLOBALS["CONFIG"]["ZAPNOUT_VLASTNI_UPLOAD"])
{
  //echo "Jsem tu"; Flush();
  $cesta=$GLOBALS["TMAPY_DIR"]."/".$GLOBALS["CONFIG"]["VLASTNI_UPLOAD_VNITRNI"];

  $cela_cesta_rok=$cesta."/".$cislo_jednaci2;
  $cela_cesta=$cesta."/".$cislo_jednaci2."/".$cislo_jednaci1;
  echo "cesta je".$cela_cesta; FLush();  echo "<hr/>";
  //if (!is_dir($cela_cesta_rok)) {chdir ($cela_cesta); mkdir($cislo_jednaci2,0777);}
  if (!is_dir($cela_cesta_rok)) 
  {
    mkdir($cela_cesta_rok);
    chmod($cela_cesta_rok,0770);
    chown($cela_cesta_rok,'apache');
    chgrp($cela_cesta_rok,$GLOBALS["CONFIG"]["VLASTNI_UPLOAD_SKUPINA"]);
  }
  if (!is_dir($cela_cesta)) 
  {
    mkdir($cela_cesta);
    chmod($cela_cesta,0770);
    chown($cela_cesta,'apache');
    chgrp($cela_cesta,$GLOBALS["CONFIG"]["VLASTNI_UPLOAD_SKUPINA"]);
  }
  
  $nazev_souboru=md5($cislo_jednaci2.$cislo_jednaci1);
  
  $celeunc=$cela_cesta."/".$nazev_souboru.".rtf";
  $uncwin="\\\\".$GLOBALS["CONFIG"]["VLASTNI_UPLOAD_SERVER"]."/".$GLOBALS["CONFIG"]["VLASTNI_UPLOAD_URL"]."/".$cislo_jednaci2."/".$cislo_jednaci1."/".$nazev_souboru.".rtf";

  echo "Cele UNC LINUX ".$celeunc;echo "<hr/>";
  echo "Cele UNC WIN ".$uncwin;echo "<hr/>";
  if (!file_exists($celeunc))  
  {  
  echo "Jdu vytvaret soubor<hr/>"; Flush();
    
    $soubor="./".$GLOBALS["CONFIG"]["PREFIX"]."/".$filename;
//    If ($sablona=='sablona_nove')
    {
      $cesta="/".$GLOBALS["CONFIG"]["VLASTNI_UPLOAD_VNITRNI"];
    
      $cela_cesta=$cesta."/sablony";
      $nazev_souboru=md5($GLOBALS["id_sablony"]);
      echo "id sablonz je ".$GLOBALS["id_sablony"];
    //  $nazev_souboru=$id_sablony;
      $soubor=$cela_cesta."/".$nazev_souboru.".rtf";
    echo $soubor."<br/>";
    }
    
    $fn = FileUpUrl($soubor);
    $fp = fopen ($fn, "r");
    $sablona_soubor = fread ($fp, filesize ($fn));
    fclose ($fp);
//    $z=array("CISLO_SPISU","DATUM_PRIJETI","ODBOR_REFERENTA","ADRESA_ODESILATELE","ADRESA_JMENO","ADRESA_ULICE","ADRESA_MESTO","CISLO_JEDNACI","UREDNIK_JMENO","UREDNIK_TELEFON","DNESNI_DATUM","VEC_DOPISU","UREDNIK_EMAIL","JEJICH_CJ","UREDNIK_FAX");
//    $na=array($cislo_spisu,$datum_prijeti,$odbor,$ODESILATEL,$ADRESA_JMENO,$ADRESA_ULICE,$ADRESA_MESTO,$c_jednaci,$REFERENT_JMENO,$REFERENT_TELEFON,Date('d.m.Y'),$vec,$urednik_email,$jejich_cj,$urednik_fax);
//    If ($sablona=='sablona_nove')
    {  
      $z=array("%CAROVY_KOD%","%CISLO_SPISU%","%DATUM_PRIJETI%","%ODBOR_REFERENTA%","%ADRESA_OSLOVENI%","%ADRESA_ODESILATELE%","%ADRESA_JMENO%","%ADRESA_ULICE%","%ADRESA_MESTO%","%ADRESA_ODD%","%ADRESA_KONTOSOBA%","%CISLO_JEDNACI%","%UREDNIK_JMENO%","%UREDNIK_TELEFON%","%DNESNI_DATUM%","%VEC_DOPISU%","%UREDNIK_EMAIL%","%JEJICH_CJ%","%UREDNIK_FAX%","%ROZDELOVNIK%");
      $na=array($barcode,$cislo_spisu,$datum_prijeti,$odbor,$ADRESA_OSLOVENI,$ODESILATEL,$ADRESA_JMENO,$ADRESA_ULICE,$ADRESA_MESTO,$ADRESA_ODD,$ADRESA_KONTOSOBA,$c_jednaci,$REFERENT_JMENO,$REFERENT_TELEFON,Date('d.m.Y'),$vec,$urednik_email,$jejich_cj,$urednik_fax,$dalsi_osoby);
    }
    $vysledny=Str_replace($z,$na,$sablona_soubor);
      
    //Die(print_r($z));
    $fp=Fopen($celeunc,'w');
    fWrite($fp,$vysledny);
    Fclose($fp);
    echo "Soubor zapsan, jdu nastavit prava<hr/>";Flush();
    chmod($celeunc,0666);
    chown($celeunc,'apache');
    chgrp($celeunc,$GLOBALS["CONFIG"]["VLASTNI_UPLOAD_SKUPINA"]);
    echo "Hotovo, soubor vytvoren<hr/>";Flush();
  }
  echo "Tak ho jdeme vnutit uzivateli<hr/>";Flush();
  echo "Otviram soubor ".$uncwin."<hr/>";Flush();

  echo "<script type=\"text/javascript\" src=\"msoffice.js\"></script>
<body onload=\"startOffice('\\\\".$uncwin."','Word',0);\">";
}

If ($sablona=='delete_file' && $GLOBALS["CONFIG"]["ZAPNOUT_VLASTNI_UPLOAD"])
{
  //funkce, ktera umozni smazat jiz existujici vytvoreny soubor
  $cesta=$GLOBALS["TMAPY_DIR"]."/".$GLOBALS["CONFIG"]["VLASTNI_UPLOAD_VNITRNI"];
  $cela_cesta_rok=$cesta."/".$cislo_jednaci2;
  $cela_cesta=$cesta."/".$cislo_jednaci2."/".$cislo_jednaci1;
  $nazev_souboru=md5($cislo_jednaci2.$cislo_jednaci1);
  $celeunc=$cela_cesta."/".$nazev_souboru.".rtf";
  echo $celeunc;
  if (file_exists($celeunc))  
  {
   if (unlink($celeunc))
      echo "<script>alert('Soubor byl smazán');</script>";
  else  
    echo "<script>alert('Soubor se nepodařilo smazat!');</script>";
  }
  else
    echo "<script>alert('Soubor neexistuje, nepodařilo se ho smazat!');</script>";
  echo "<script>parent.document.location.href='../../edit.php?edit&EDIT_ID=".$GLOBALS["ID"]."&cacheid=';</script>";
  //echo "<script>window.opener.document.location.reload();</script>";
}

If ($sablona=='sablona' && $GLOBALS["CONFIG"]["ZAPNOUT_VLASTNI_UPLOAD"])
{
//  echo "Jsem tu"; Flush();
  $cesta=$GLOBALS["TMAPY_DIR"]."/".$GLOBALS["CONFIG"]["VLASTNI_UPLOAD_VNITRNI"];

  $cela_cesta=$cesta."/sablony/";
  echo "cesta je".$cela_cesta; FLush();  echo "<hr/>";
  //if (!is_dir($cela_cesta_rok)) {chdir ($cela_cesta); mkdir($cislo_jednaci2,0777);}
  if (!is_dir($cela_cesta)) {
    mkdir($cela_cesta);
    chmod($cela_cesta,0770);
    chown($cela_cesta,'apache');
    chgrp($cela_cesta,$GLOBALS["CONFIG"]["VLASTNI_UPLOAD_SKUPINA"]);
  }
  
  $nazev_souboru=md5($ID);
  $celeunc=$cela_cesta."/".$nazev_souboru.".rtf";
  echo "Cele UNC LINUX ".$celeunc;echo "<hr/>";
  $uncwin="\\\\".$GLOBALS["CONFIG"]["VLASTNI_UPLOAD_SERVER"]."/".$GLOBALS["CONFIG"]["VLASTNI_UPLOAD_URL"]."/sablony/".$nazev_souboru.".rtf";
  echo "Cele UNC WIN ".$uncwin;echo "<hr/>";
  if (!file_exists($celeunc))  
  {  
  echo "Jdu vytvaret soubor<hr/>"; Flush();
    $fn = FileUpUrl("./prazdny.rtf");
    $fp = fopen ($fn, "r");
    $sablona = fread ($fp, filesize ($fn));
    fclose ($fp);

    $fp=Fopen($celeunc,'w');
    fWrite($fp,$sablona);
    Fclose($fp);
    echo "Soubor zapsan, jdu nastavit prava<hr/>";Flush();
    chmod($celeunc,0777);
    chown($celeunc,'apache');
    chgrp($celeunc,$GLOBALS["CONFIG"]["VLASTNI_UPLOAD_SKUPINA"]);
    echo "Hotovo, soubor vytvoren<hr/>";Flush();
  }
  echo "Tak ho jdeme vnutit uzivateli<hr/>";Flush();
  echo "Otviram soubor ".$uncwin."<hr/>";Flush();
  echo "<script type=\"text/javascript\" src=\"msoffice.js\"></script>
<body onload=\"startOffice('\\\\".$uncwin."','Word',0);\">";
}

?>
