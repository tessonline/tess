<?php
require("tmapy_config.inc");
include_once(FileUp2('.admin/classes/dokument/Temp.php'));

include(FileUp2(".admin/brow_.inc"));
include_once(FileUp2(".admin/config.inc"));
include_once(FileUp2(".admin/convert.inc"));
include_once(FileUp2(".admin/form_func.inc"));
//require_once(FileUp2(".admin/form_func_ev.inc"));
include_once(FileUp2(".admin/db/db_posta.inc"));
include_once(FileUp2(".admin/security_name.inc"));
include_once(FileUp2(".admin/barcode39.inc"));
include_once(FileUp2(".admin/oth_funkce.inc"));
include_once($GLOBALS['TMAPY_LIB'] . '/oohforms.inc');
include_once(FileUp2(".admin/el/of_select_.inc"));

include_once(FileUp2("services/spisovka/uzavreni_spisu/funkce.inc"));
function TxtEncodingToWin($text) {
  return iconv('UTF-8', 'WINDOWS-1250', $text);
}

//dokument pro test
//$GLOBALS["ID"] = 1000507965;

set_time_limit(0);
$w = new DB_POSTA;
$sql = 'select * from posta where id = '.$GLOBALS["ID"];
$w->query($sql);
$w->Next_Record();


$date_items = array ("ODESL_DATNAR","JEJICH_CJ_DNE","DATUM_REFERENT_PRIJETI","LHUTA_VYRIZENI","DATUM_VYRIZENI","DATUM_PODATELNA_PRIJETI","DATUM_VYPRAVENI","DATUM_DORUCENI","DATUM_PM");
$of_select_items = array(
  "ODBOR"=>"of_select_vsechny_spisuzly",
  "ODESL_ODBOR"=>"of_select_interni_spisuzly",
  "REFERENT"=>"of_select_referent",
//  "AGENDA_DOKUMENTU"=>"of_select_",
  "TYP_POSTY"=>"of_select_typ_posty",
  "TYP_DOKUMENTU"=>"of_select_typ_dokumentu",
  "ODES_TYP"=>"of_select_odes_typ",
  "ODESL_OSLOVENI"=>"of_select_osloveni",
  "ZPUSOB_PODANI"=>"of_select_druh_prijeti",
  "SKARTACE"=>"of_select_skartace",
  "SKARTACEKOD"=>"of_select_skartace_kod",
  "DOPORUCENE"=>"of_select_typ_odeslani",
  "ZPUSOB_VYPRAVENI" => "of_select_druh_odeslani",
);

$default_from = array();
$default_to = array();
foreach ($w->Record as $key => $value)
{
  if (!is_numeric($key)) {
    if ($key=="VLASTNICH_RUKOU") $key = "ZPUSOB_VYPRAVENI";
    if ($key=="KOD") $key = "SKARTACEKOD";
    $default_from[] = '%'.$key.'%';
    if (in_array($key,$date_items))
      $default_to[] = html_entity_decode($w->dbdate2str($value),null,'utf-8');
      elseif (array_key_exists($key,$of_select_items)) {
        $a = array();
        if ($key == "REFERENT") $a = array('fullselect' => true);
        $of_select_data = getSelectDataEed(new $of_select_items[$key]($a));
        $val = html_entity_decode($of_select_data[$value],null,'utf-8');
        $default_to[] = ltrim($val," ");        
      }
      else {
        $default_to[] = html_entity_decode ($value,null,'utf-8');
        
      }
  }
}

$x = implode(',',$default_from);

//$vec = strTr($w->Record["VEC"],$tr_from,$tr_to);
$vec = $w->Record["VEC"];
$psc_bez_mezer = str_replace(' ', '', $w->Record["ODESL_PSC"]);
$psc = mb_substr($psc_bez_mezer,0,3)." ".mb_substr($psc_bez_mezer,3,2);

$agendy = getSelectDataEed(new of_select_agenda_dokumentu(array()));
$agenda_dokumentu = $agendy[VratAgenduDokumentu($w->Record['TYP_POSTY'])];

If ($w->Record["ODESL_CP"]) $cislo = $w->Record["ODESL_CP"];
If ($w->Record["ODESL_COR"]) $cislo = $w->Record["ODESL_COR"];
If ($w->Record["ODESL_COR"] && $w->Record["ODESL_CP"]) $cislo = $w->Record["ODESL_CP"]."/".$w->Record["ODESL_COR"];
 
$datum_prijeti = $w->Record["DATUM_PODATELNA_PRIJETI"];
$den_prijeti = date("j.n.Y", strtotime($w->Record["DATUM_PODATELNA_PRIJETI"]));
$datum_prijeti = mb_substr($datum_prijeti,0,strpos($datum_prijeti,' '));
$datum_prijeti = date("j.n.Y", strtotime($datum_prijeti));

If ($w->Record["ODESLANA_POSTA"] == 't') $datum_prijeti = '';

If (($w->Record["ODES_TYP"]<>"A") and ($w->Record["ODES_TYP"]<>"P"))
{
  $ODESILATEL = $w->Record["ODESL_TITUL"]." ".$w->Record["ODESL_JMENO"]." ".$w->Record["ODESL_PRIJMENI"]." \\par ".$w->Record["ODESL_ULICE"]." ".$cislo." \\par ".$psc." ".$w->Record["ODESL_POSTA"];
  $ODESILATEL_OTOC = $w->Record["ODESL_PRIJMENI"]." ".$w->Record["ODESL_JMENO"]." ".$w->Record["ODESL_TITUL"]." \\par ".$w->Record["ODESL_ULICE"]." ".$cislo." \\par ".$psc." ".$w->Record["ODESL_POSTA"];
  $ADRESA_JMENO = $w->Record["ODESL_TITUL"]." ".$w->Record["ODESL_JMENO"]." ".$w->Record["ODESL_PRIJMENI"];
  $ADRESA_ULICE = $w->Record["ODESL_ULICE"]." ".$cislo;
  $ADRESA_MESTO = $psc."  ".mb_strtoupper($w->Record["ODESL_POSTA"]);
}
If ($w->Record["ODESL_OSLOVENI"]) 
{
  $yyy = new DB_POSTA;
  $yyy->query('select nazev from posta_cis_osloveni where id = '.$w->Record["ODESL_OSLOVENI"]); $yyy->Next_Record();
  $ADRESA_OSLOVENI = $yyy->Record["NAZEV"];
}

If (($w->Record["ODES_TYP"] == "P") || ($w->Record["ODES_TYP"] == "U"))
{
  $odesl_firma = $w->Record["ODESL_PRIJMENI"];
  $ODESILATEL = $w->Record["ODESL_PRIJMENI"]." \\par ";
  $ADRESA_JMENO = $w->Record["ODESL_PRIJMENI"];
//  If (trim($w->Record["ODESL_ODD"])<>'') {$ADRESA_JMENO .= ", ".$w->Record["ODESL_ODD"];$ODESILATEL .= "\\par ".$w->Record["ODESL_ODD"]; }
//  If (trim($w->Record["ODESL_OSOBA"])<>'') {$ADRESA_JMENO .= ", ".$w->Record["ODESL_OSOBA"];$ODESILATEL .= "\\par ".$w->Record["ODESL_OSOBA"]; }
  $ADRESA_ULICE = $w->Record["ODESL_ULICE"]." ".$cislo;
  $ADRESA_MESTO = $psc."  ".mb_strtoupper($w->Record["ODESL_POSTA"]);

// If ($w->Record["ODESL_ICO"]<>"") {$ODESILATEL .= "IČO ".$w->Record["ODESL_ICO"]." \\par ";

  $ODESILATEL .= $w->Record["ODESL_ULICE"]." ".$cislo." \\par ".$psc." ".$w->Record["ODESL_POSTA"];
}

$ADRESA_ODD = $w->Record["ODESL_ODD"];
$ADRESA_KONTOSOBA = $w->Record["ODESL_OSOBA"];

$zkratka_odboru = UkazOdbor($w->Record["ODBOR"],true,false);

$USER_INFO = $GLOBALS["POSTA_SECURITY"]->GetUserInfo(); 
if ($GLOBALS[CONFIG][OTOCIT_JMENO_ZPRACOVATELE])
  $REFERENT_JMENO = $USER_INFO["FNAME"]." ".$USER_INFO["LNAME"];
else
  $REFERENT_JMENO = $USER_INFO["LNAME"]." ".$USER_INFO["FNAME"];
$REFERENT_JEN_PRIJMENI = $USER_INFO["LNAME"];
$REFERENT_TELEFON = $USER_INFO["PHONE"]; 
$urednik_email = $USER_INFO["EMAIL"];
$urednik_fax = $USER_INFO["FAX"];
If ($USER_INFO["TITLE_1"]) $REFERENT_JMENO = $USER_INFO["TITLE_1"]." ".$REFERENT_JMENO;
If ($USER_INFO["TITLE_2"]) $REFERENT_JMENO = $REFERENT_JMENO.", ".$USER_INFO["TITLE_2"];

//$REFERENT_JMENO = iconv('ISO-8859-2', 'WINDOWS-1250', $REFERENT_JMENO);
//echo "onma".$REFERENT_JMENO;
$ev_cislo = $w->Record["EV_CISLO"];
$rok = $w->Record["ROK"];

//$REFERENT_JEN_PRIJMENI = iconv('ISO-8859-2', 'WINDOWS-1250', $USER_INFO['LNAME']);

//nastavime hodnoty pro novy UPLOAD
$cislo_jednaci1 = $w->Record["CISLO_JEDNACI1"];
$cislo_jednaci2 = $w->Record["CISLO_JEDNACI2"];

$doc = LoadClass('EedDokument', $w->Record['ID']);
$podaci_cislo = $doc->barcode;

//$c_jednaci = FormatCJednaci($w->Record["CISLO_JEDNACI1"],$w->Record["CISLO_JEDNACI2"],$w->Record["REFERENT"],$w->Record["ODBOR"],$w->Record['ID']);
 $cjObject = LoadClass('EedCj', $w->Record['ID']);
  $cj = $cjObject->GetCjInfo($w->Record['ID']);
  $c_jednaci = $doc->cislo_jednaci;

$cislo_spisu = $cj['CELE_CISLO'];
$nazev_spisu = $cj['CELY_NAZEV'];

$jejich_cj = $w->Record["JEJICH_CJ"];
$jejich_cj_dne = $w->dbdate2str($w->Record["JEJICH_CJ_DNE"]);

$zkratka_ref = UkazUsera($w->Record["REFERENT"],true);
$odbor = UkazOdbor($w->Record["ODBOR"],false,true);

$datum_narozeni = $w->dbdate2str($w->Record["ODESL_DATNAR"]);
$datum_narozeni = str_replace('&nbsp;', '', $datum_narozeni);
$su = LoadClass('EedSpisUzelKontakt', $w->Record["ODBOR"]);

$su_adresa = $su->adresa;
$su_telefon= $su->telefon;
$su_mobil = $su->mobil;
$su_mail = $su->email;
$su_web = $su->web;


//rozdelovnik

//IF ($w->Record['ODES_TYP']<>'X')
//  $dalsi_osoby = str_replace(array("<br/>","&nbsp;"),array("\par "," "),UkazOdesilatele($w->Record['DALSI_PRIJEMCI'],'x'));

//$vec = StrTr($vec, $tr_from, $tr_to);
// $odbor = StrTr($odbor, $tr_from, $tr_to);
// $ODESILATEL = StrTr($ODESILATEL, $tr_from, $tr_to);
// $ODESILATEL_OTOC = StrTr($ODESILATEL_OTOC, $tr_from, $tr_to);
// $ADRESA_OSLOVENI = StrTr($ADRESA_OSLOVENI, $tr_from, $tr_to);
// $ADRESA_JMENO = StrTr($ADRESA_JMENO, $tr_from, $tr_to);
// $ADRESA_ODD = StrTr($ADRESA_ODD, $tr_from, $tr_to);
// $ADRESA_KONTOSOBA = StrTr($ADRESA_KONTOSOBA, $tr_from, $tr_to);
// $ADRESA_ULICE = StrTr($ADRESA_ULICE, $tr_from, $tr_to);
// $ADRESA_MESTO = StrTr($ADRESA_MESTO, $tr_from, $tr_to);
// $zkratka_odboru = StrTr($zkratka_odboru, $tr_from, $tr_to);
// $c_jednaci = StrTr($c_jednaci, $tr_from, $tr_to);
// $jejich_cj = StrTr($jejich_cj, $tr_from, $tr_to);
// $podaci_cislo = $w->Record["EV_CISLO"]."/".$w->Record["ROK"];
// //$REFERENT_JMENO = StrTr($REFERENT_JMENO, $tr_from, $tr_to);
// $dalsi_osoby = StrTr($dalsi_osoby, $tr_from, $tr_to);

//vypocitame kontrolni znak
$soucet = 0;
For ($a = 0;$a<strlen($podaci_cislo);$a++)
{
  $znak = array_search(mb_substr($podaci_cislo,$a,1),$code39);
  $soucet = $soucet+$znak;
  
}
$kontrola = $soucet%43;

//$podaci_cislo_bar = '*'.$podaci_cislo.$code39[$kontrola].'*';

include(FileUp2('/lib/pdf/barcode128/barcode.php'));
//include(FileUp2('/lib/pdf/barcode39/pict39.php'));
/*
$barcode = '{\pict\pngblip\picw200\pich40\wbmbitspixel1\wbmplanes1\wbmwidthbytes22
'.Code128Pic($podaci_cislo).'}';

*/
If ($w->Record['SKARTACE']>0) {
  $skartace = Skartace_Pole($w->Record['SKARTACE']);

}

//nacteme spisovy prebal a prehled 
include('prebal.inc');
include('prehled.inc');
include('prehled_dilu.inc');

//$vec = StrTr($vec, $tr_from, $tr_to);
//$cislo_spisu = StrTr($cislo_spisu, $tr_from, $tr_to);
//nacteme sablony
If ($GLOBALS["CONFIG"]["ZAPNOUT_VLASTNI_UPLOAD"])
  include('sablona_vlastniupload.inc');
else
  include('sablona_obecne.inc');

