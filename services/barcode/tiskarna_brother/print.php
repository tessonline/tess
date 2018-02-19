<?php
//Drive head 012-707
function lpr($STR,$PRN) {
  if ($PRN && $STR) {
     $prn=$PRN;
     $CMDLINE="lpr -P $prn -l ";
     $pipe=popen("$CMDLINE" , 'w' );
     if (!$pipe) {
        print "Chyba při tisku.";
        return "";
     }
     fputs($pipe,$STR);
     pclose($pipe);
  }
  else {
     print "Chyba - chybějící tiskárna nebo data.";
     return "";
  }
}

$linefeed = chr(13).chr(10);
$text.="Městský  úřad Chodov";
$text.=chr(27).chr(15); //nastavime zuzene pismo
$text.="- podatelna";
$text.=chr(27).chr(18); //zrusime zuzene pismo
$text.=chr(10); //odradkujeme
//carovy kod 27 105 [Parameters] 66 or 98 [Bar code data] 92
$text.=chr(27).chr(105).'t0t1w2'.chr(66).'15525/2008'.chr(92);
$text.=$linefeed;
$text.=chr(27).chr(15); //nastavime zuzene pismo
$text.="Dolo:".chr(27).chr(69); //nastavime tucne
$text.="31.12.2008 12:00:59";
$text.=chr(27).chr(69); //zrusime tucne pismo
$text.="|Počet příloh|Počet listů";
$text.=$linefeed;
$text.="Č.j.:".chr(27).chr(69); //nastavime tucne
$text.="12525/2008";
$text.="|    5    |    8";
$text.=chr(27).chr(69); //zrusime tucne pismo
$text.=$linefeed;



   // dos linefeed CR + LF
   
   // unix linefeed LF
   //$linefeed = chr(10);
   
   $prn_str =  "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
   $prn_str .= $linefeed;
   $prn_str .= "abcdefghijklmnopqrstuvwxyz";
   $prn_str .= $linefeed;

   // unix printer name
   $printer = "onma-brother";
   
   lpr($prn_str,$printer);
echo nl2br($text);
//lpr($text,'onma-brother');

