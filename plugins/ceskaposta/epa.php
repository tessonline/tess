<?php
require("tmapy_config.inc");
require(FileUp2(".admin/brow_.inc"));
require(FileUp2(".admin/out_encoding.inc"));
/*
Identifikace věty odesílatel	13	Pevný text: odesílatel
Příjmení a jméno odesílatele  	30	
PSČ odesílatele	5	
Obec	40	
Část obce	40	
Ulice	40	
Č.p.	6	Číslo popisné
Č.o.	6	Číslo orientační
ISO kód země	2	CZ nebo prázdná hodnota


Identifikační číslo zásilky	13	Čárový kód nebo prázdná hodnota	N
Příjmení a jméno adresáta / Název firmy  	30		A
PSČ adresáta 	5		A
Obec	40		A
Část obce	40		A
Ulice	40		A (u obcí s uličním systémem)
Č.p.	6	Číslo popisné	A (je-li známé)
Č.o.	6	Číslo orientační	A (je-li známé)
ISO kód země	2	U zásilek do ČR se uvede CZ nebo prázdné pole.	A
Telefon adresáta	20	"Formát ""+420xxxxxxxxx""
V případě, že zadáte mobilní telefonní číslo, tak bude automaticky adresátovi avizováno dodávání zásilky. Při poskytnutí kontaktních údajů je standardem včasná informovanost o příchodu zásilky s možností změny dispozic, když je zásilka na cestě."	N (u produktu Na poštu se jedná o povinný údaj)
E-mail adresáta	50	"Formát ""xxx@xxx.xxx""
V případě, že zadáte mobilní e-mail, tak bude automaticky adresátovi avizováno dodávání zásilky. Při poskytnutí kontaktních údajů je standardem včasná informovanost o příchodu zásilky s možností změny dispozic, když je zásilka na cestě."	N (u produktu Na poštu se jedná o povinný údaj)
Hmotnost zásilky v kg	6	Formát (2.3) "xx.xxx" 	A
Požadované doplňkové služby k zásilce	30	Číselné kódy služeb, oddělené znakem "+"	A
Udaná cena v Kč	12	Formát (9.2) "xxxxxxx.xx"	N
Částka dobírky v Kč	12	Formát (9.2) "xxxxxxxxx.xx"	A (v případě služby Dobírka)
Variabilní symbol dobírkové Pk	10	Pouze u dobírky	A (v případě služby dobírka)
Variabilní symbol zásilky	10	Identifikace zásilky pro potřeby podavatele	N
Poznámka	neomezeno	Pro potřeby podavatele (např. pro napárování podacího čísla zásilky s číslem jednacím v systému podavatele)	N
Kód MRN 		"Kód MRN z vývozního dokladu pro zásilky do zahraničí.
Uvádí se u zásilek zasílaných do zahraničí s celním prohlášením (k zásilce je přiložen vývozní doklad)."	A (v případě je-li zásilka posílána do zahraničí, povinné zadání se službou 44)
Celní obsah zásilky	50	Popis celního obsahu zásilky u zásilek do zahraničí.	N
Id. číslo hlavní zásilky	13	Identifikační číslo hlavní zásilky ve vícekusové zásilce.	povinné v případě podání vícekusové zásilky
Pořadové číslo zásilky	2	Pořadové číslo zásilky ve vícekusové zásilce. Nesmí být vyšší než celkový počet zásilek ve vícekusové zásilce	povinné v případě podání vícekusové zásilky
Celkový počet zásilek	2	Celkový počet zásilek ve vícekusové zásilce (max. 99 ks)	povinné v případě podání vícekusové zásilky
Částka předpokládaného výplatného v Kč	12	Formát (9.2) "xxxxxxxxx.xx"	N
Datum podání zásilky	8	Předpokládaný datum podání zásilky. Formát "ccyymmdd"	N
Čas podání zásilky	8	Předpokládaný čas podání zásilky. Formát "hh:mm:ss"	N
*/

$c1 = array();
$temp = explode('|', $GLOBALS['CONFIG_POSTA']['HLAVNI']['POSTA_PROTOKOL_ODESILATEL']);

//Fakulta humanitních studií UK|15800|Praha 5 -Jinonice||U Kříže|8||tel. 251080388|mail: dekanat@fhs.cuni.cz
$c1[] = 'Odesilatel:';
$c1[] = $temp[0]; //odesilatel
$c1[] = $temp[1]; //odesilatel
$c1[] = $temp[2]; //odesilatel
$c1[] = $temp[2];; //odesilatel
$c1[] = $temp[4]; //odesilatel
$c1[] = $temp[5]; //odesilatel
$c1[] = $temp[6]; //odesilatel
$c1[] = $temp[7]; //odesilatel
$c1[] = $temp[8]; //odesilatel

// $c1[] = $GLOBALS['CONFIG']['URAD'] . ' '.$GLOBALS['CONFIG']['MESTO'];
// $c1[] = $GLOBALS['CONFIG']["PSC"];
// $c1[] = $GLOBALS['CONFIG']["OBEC"];
// $c1[] = $GLOBALS['CONFIG']["COBCE"];
// $c1[] = $GLOBALS['CONFIG']["ULICE"];
// $c1[] = $GLOBALS['CONFIG']["CP"];
// $c1[] = $GLOBALS['CONFIG']["CO"];
// $c1[] = 'CZ';

/*
$c1[] = $GLOBALS['CONFIG']["TELEFON_ODESILATELE"];
$c1[] = $GLOBALS['CONFIG']["EMAIL_ODESILATELE"];
$c1[] = $GLOBALS['CONFIG']["CISLO_ZAK_KARTY_CP"]; 
 */

$prvni_veta = implode(';', enc_array($c1));
$q = new DB_POSTA;
$druha_veta = array();
$ID = (int) $ID;
$sql="select * from posta where id in (select pisemnost_id from posta_cis_ceskaposta_id where protokol_id=".$ID.") and doporucene<>'1' ORDER BY xertec_id,doporucene,cislo_jednaci2,cislo_jednaci1 asc";
$q->query($sql);
while($q->Next_Record()) {
  $c2 = array();
  $c2[0] = EedCeskaPosta::VratCK($q->Record['ID']);
  $c2[1] = $q->Record['ODESL_PRIJMENI'] . ' ' . $q->Record['ODESL_JMENO'];
  $c2[2] = $q->Record['ODESL_PSC'] ? $q->Record['ODESL_PSC'] : ' ';
  $c2[3] = $q->Record['ODESL_POSTA'] ? $q->Record['ODESL_POSTA'] : ' ';
  $c2[4] = ' ';
  $c2[5] = $q->Record['ODESL_ULICE'] ? $q->Record['ODESL_ULICE'] : ' ';
  $c2[6] = $q->Record['ODESL_CP']  ? $q->Record['ODESL_CP'] : ' ';
  $c2[7] = $q->Record['ODESL_COR'] ? $q->Record['ODESL_COR'] : ' ';
  $c2[8] = 'CZ';
  $c2[9] = ''; //tel
  $c2[10] = $q->Record['ODESL_EMAIL'];
  $c2[11] = round($q->Record['HMOTNOST']/1000, 3); //hmotnost zasilky

  $sluzby = array();
  If ($q->Record["OBALKA_NEVRACET"]>0) $sluzby[]='37'; //SA
  If ($q->Record["OBALKA_10DNI"]>0) $sluzby[]='22'; //UX

  $c2[12] = implode('+',$sluzby); //doplnove sluzby A+A+A
  $c2[13] = ''; //udana cena
  $c2[14] = ''; //castka dobirkz
  $c2[15] = ''; //var.symbol dobirkove PK
  $c2[16] = ''; //var.symbol zasilky
  $c2[17] = $q->Record['TEXT_CJ'];; //poznamka
  $c2[18] = ''; //kod MRN
  $c2[19] = ''; //celni obsah
  $c2[20] = ''; //ID hlavni zasilky ve vicekusove zasilce
  $c2[21] = ''; //poradove cislo zasilky ve vicekusove zasilce
  $c2[22] = ''; //celkovy pocet zasilek ve vicekusove zasilce
  $c2[23] = ''; //castka vyplatneho
  $c2[24] = Date('Ymd'); //datum podani
  $c2[25] = ''; //cas predani

  $druha_veta[] = implode(';', enc_array($c2));
}

$cr = chr(10).chr(13);

$file = $prvni_veta.$cr;
$file .= implode($cr, $druha_veta);
$content_type = "application/csv";
header("Content-type: $content_type");

header("Content-Disposition: attachment; filename=\"epa".$ID."_utf8.csv\"");

echo $file;

