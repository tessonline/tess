<?php
require("tmapy_config.inc");
//require(FileUp2(".admin/run2_.inc"));
//require(FileUp2(".admin/brow_.inc"));

require("tmapy_config.inc");
include(FileUp2(".admin/brow_.inc"));
include(FileUp2(".admin/config.inc"));
require(FileUp2("html_header_full.inc"));


//Uprava datumu
$where="";
//$where.=" odbor IN (".$GLOBALS["ODBOR"].")";
$where.=" (DATUM_PODATELNA_PRIJETI) >= ('".$GLOBALS["DATUM_OD"]."',) AND (DATUM_PODATELNA_PRIJETI) <= ('".$GLOBALS["DATUM_DO"]."',)";

$where.=" AND odeslana_posta='t'";
$where.=" AND hmotnost is not null";
$where2=" AND ((doporucene='2') or (doporucene='3') or (doporucene='4') or (doporucene='5'))";
$where3=" AND (doporucene='Z')";

If ($GLOBALS["ODBOR"]<>'')
  $where.=" AND odbor IN (".$GLOBALS["ODBOR"].")";
	
//UNSET($GLOBALS["ODBOR"]);
$q=new DB_POSTA;
$sql='select * from posta where '.$where.$where2.' ORDER BY xertec_id';
$q->query($sql);
$a=1;
$cena_celkem=0;

$hmotnostCO0=0;
$hmotnostCO1=0;
$hmotnostCO2=0;
$hmotnostCO3=0;
$hmotnostCO4=0;
$hmotnostCO5=0;
$hmotnostCO6=0;

$hmotnostZD0=0;
$hmotnostZD1=0;
$hmotnostZD2=0;
$hmotnostZD3=0;
$hmotnostZD4=0;
$hmotnostZD5=0;
$hmotnostZD6=0;
$hmotnostZD7=0;
$hmotnostZD8=0;

$hmotnostCD0=0;
$hmotnostCD1=0;
$hmotnostCD2=0;
$hmotnostCD3=0;
$hmotnostCD4=0;
$hmotnostCD5=0;
$hmotnostCD6=0;

//vypiseme postu, ktera neni zahranici, ta musi byt az na konci
while ($q->Next_Record())
{
  
  If ($q->Record["DOPORUCENE"]=='2') $text='R';
  If ($q->Record["DOPORUCENE"]=='3') $text='D';
  If ($q->Record["DOPORUCENE"]=='4') $text='DR';
  If ($q->Record["DOPORUCENE"]=='5') $text='DRz';

	If ($hmotnost<21) $hmotnostCD1++;
	If ($hmotnost>20 && $hmotnost<51) $hmotnostCD2++;
	If ($hmotnost>50 && $hmotnost<201) $hmotnostCD3++;
	If ($hmotnost>200 && $hmotnost<501) $hmotnostCD4++;
	If ($hmotnost>500 && $hmotnost<1001) $hmotnostCD5++;
	If ($hmotnost>1000) $hmotnostCD6++;
	$hmotnostCD0++;
	
  $a++;
}

//vypiseme postu do zahranici, musi byt az na konci
$sql='select * from posta where '.$where.$where3.' ORDER BY xertec_id';
$q->query($sql);
//$a=1;
//$cena_celkem=0;

while ($q->Next_Record())
{
  
  If ($q->Record["DOPORUCENE"]=='Z') $text='DR';
 	If ($hmotnost<11) $hmotnostZD1++;
	If ($hmotnost>10 && $hmotnost<21) $hmotnostZD2++;
	If ($hmotnost>20 && $hmotnost<51) $hmotnostZD3++;
	If ($hmotnost>50 && $hmotnost<201) $hmotnostZD5++;
 	If ($hmotnost>200 && $hmotnost<501) $hmotnostZD6++;
	If ($hmotnost>500 && $hmotnost<1001) $hmotnostZD7++;
	If ($hmotnost>1000) $hmotnostZD8++;
	$hmotnostZD0++;

  $a++;
}

//spocitame obycejny obalky
$sql="select * from posta where ".$where." AND (doporucene='1') ORDER BY xertec_id";
$q->query($sql);
$a=1;
while ($q->Next_Record())
{
	$hmotnost=$q->Record["HMOTNOST"];
  $druh_zasilky=$q->Record["DRUH_ZASILKY"];  
	If ($hmotnost<21 && $druh_zasilky==3) $hmotnostCO1++; //psani za obyc cenu
	If ($hmotnost<21 && $druh_zasilky<>3) $hmotnostCO1a++; //drazi psani
	If ($hmotnost>20 && $hmotnost<51) $hmotnostCO2++;
	If ($hmotnost>50 && $hmotnost<201) $hmotnostCO3++;
	If ($hmotnost>200 && $hmotnost<501) $hmotnostCO4++;
	If ($hmotnost>500 && $hmotnost<1001) $hmotnostCO5++;
	If ($hmotnost>1000) $hmotnostCO6++;
	$hmotnostCO0++;
}

$hmotnostCO1=$hmotnostCO1+$GLOBALS[OBYC1];
$hmotnostCO1a=$hmotnostCO1a+$GLOBALS[OBYC2];


$text="
VYKAZ O POCTU A SKLADBE ZASILEK ZA OBDOBI
od $GLOBALS[DATUM_OD] do $GLOBALS[DATUM_DO]

Odesilatel: ".$GLOBALS[CONFIG][URAD]." ".$GLOBALS[CONFIG][MESTO]."


OBYCEJNE PSANI:
---------------
Obycejne standardni psani do 20g - $hmotnostCO1
Ostatni obycejne psani do 20g - $hmotnostCO1a
Obycejne psani do 50g - $hmotnostCO2
Obycejne psani do 200g - $hmotnostCO3
Obycejne psani do 500g - $hmotnostCO4
Obycejne psani do 1kg - $hmotnostCO5
Obycejne psani do 2kg - $hmotnostCO6
Celkem obycejne psani - $hmotnostCO0

DOPORUCENE PSANI:
-----------------
Doporucene psani do 20g - $hmotnostCD1
Doporucene psani do 50g - $hmotnostCD2
Doporucene psani do 200g - $hmotnostCD3
Doporucene psani do 500g - $hmotnostCD4
Doporucene psani do 1kg - $hmotnostCD5
Doporucene psani do 2kg - $hmotnostCD6
Celkem doporucene psani - $hmotnostCD0

DOPORUCENE DO ZAHRANICI:
------------------------
Doporucene do zahranici do 10g - $hmotnostZD1
Doporucene do zahranici do 20g - $hmotnostZD2
Doporucene do zahranici do 50g - $hmotnostZD3
Doporucene do zahranici do 100g - $hmotnostZD4
Doporucene do zahranici do 250g - $hmotnostZD5
Doporucene do zahranici do 500g - $hmotnostZD6
Doporucene do zahranici do 1kg - $hmotnostZD7
Doporucene do zahranici do 2kg - $hmotnostZD8
Celkem doporucene do zahranici - $hmotnostZD0
";
echo nl2br($text);
require(FileUp2("html_footer.inc"));


