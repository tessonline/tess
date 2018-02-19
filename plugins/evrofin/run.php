<?php
require("tmapy_config.inc");
include(FileUp2(".admin/brow_.inc"));
include_once(FileUp2(".admin/security_.inc"));
include_once(FileUp2(".admin/security_name.inc"));
include_once(FileUp2(".admin/config.inc"));
include_once(FileUp2(".admin/convert.inc"));

If ($GLOBALS["CONFIG"]["DB"]=='psql')
{
  $where.=" (DATUM_PODATELNA_PRIJETI) >= ('".$GLOBALS["DATUM_OD"]."')";
  $where.=" AND (DATUM_PODATELNA_PRIJETI) <= ('".$GLOBALS["DATUM_DO"]."')";
}
If ($GLOBALS["CONFIG"]["DB"]=='mssql')
{
  $where.=" CONVERT(datetime,datum_podatelna_prijeti,104) >= CONVERT(datetime,'".$GLOBALS["DATUM_OD"]."',104)";
  $where.=" AND CONVERT(datetime,datum_podatelna_prijeti,104) <= CONVERT(datetime,'".$GLOBALS["DATUM_DO"]."',104)";
}

$where.=" AND odes_typ<>'X'";
//jen odeslane pisemnosti
$where.=" AND odeslana_posta='t'";
//jen pisemnosti na ceskou postu
$where.=" AND vlastnich_rukou='1'";
$where.=" AND odes_typ<>'Z'";
$where.=" AND doporucene<>'1'";

$where.=" AND odbor IN (".$GLOBALS["ODBOR"].")";
 

$dnesnidatum=date("md");

$odbor2=UkazOdbor($GLOBALS["ODBOR"]);
$file_name='import_tmapy.csv'; 

//$cesta=$GLOBALS["TMAPY_DIR"].$SERVER_CONFIG["AGENDA_PATH"]["UPLOAD_SERVER_DIR"]."/evrofin/";
$cesta=$GLOBALS["TMAPY_DIR"].$SERVER_CONFIG["AGENDA_PATH"]["UPLOAD_SERVER_DIR"]."/";
$file_evrofin = $cesta.$file_name;
$fp=FOpen($file_evrofin,'w');

//header("<meta HTTP-EQUIV=\"Content-Type\" CONTENT=\"text/html; charset=windows-1250\">");

//require(FileUp2("html_header_full.inc"));
$q = new db_posta;
$sql = "select * from posta where".$where." order by doporucene,cislo_jednaci2,cislo_jednaci1,datum_podatelna_prijeti";
//die($sql);
$q->query($sql);
$pocetid=0;
$naseposta="59231";
$radek="";
$oddelovac = ";";
while($q->next_record())
{ 
//Datum|Typ zásilky|Dodejka|Do vl. rukou|Do vl.r. zástupce|Název adresáta|Ulice|Číslo popisné|Číslo orientační|Obec|PSČ|Pracovník + ',' + odbor|   
  If ($q->Record["ODESLANA_POSTA"]=="t")
  {
    $ck=$q->Record['EV_CISLO'].'/'.$q->Record['ROK'];
    $radek=$q->Record['ID'].$oddelovac;
    $radek.=$ck.$oddelovac;
    If (strpos($q->Record["DATUM_PODATELNA_PRIJETI"]," ")) 
      $datum_prijeti=substr($q->Record["DATUM_PODATELNA_PRIJETI"],0,strpos($q->Record["DATUM_PODATELNA_PRIJETI"],' '));
    else
      $datum_prijeti=$q->Record["DATUM_PODATELNA_PRIJETI"];
          
    $radek.=$datum_prijeti.$oddelovac; 
//    $radek.=$evcislo.'|'.$evcislo.'|'.$evcislo;
//    $radek.='| | ';
    If ($q->Record["DOPORUCENE"]=='C') {$sluzby=53;}
    If ($q->Record["DOPORUCENE"]=='2') {$sluzby=51;}
    If ($q->Record["DOPORUCENE"]=='3') {$sluzby=51+3;}
    If ($q->Record["DOPORUCENE"]=='4') {$sluzby=53+33;}
    If ($q->Record["DOPORUCENE"]=='5') {$sluzby=53+32;}
  
    If ($q->Record["OBALKA_NEVRACET"]>0) {$sluzby=$sluzby+37;}
    If ($q->Record["OBALKA_10DNI"]>0) {$sluzby=$sluzby+22;}
    $radek.=$sluzby.$oddelovac;
   
    $radek.=$q->Record["ODESL_PRIJMENI"].' '.$q->Record["ODESL_JMENO"].$oddelovac;
    $radek.=$q->Record["ODESL_ULICE"].$oddelovac;
    $radek.=$q->Record["ODESL_CP"].$oddelovac;
    $radek.=$q->Record["ODESL_COR"].$oddelovac;
    $radek.=str_replace(' ','',$q->Record["ODESL_PSC"]).$oddelovac;
    $radek.=$q->Record["ODESL_POSTA"].$oddelovac;
  }

}

fwrite($fp,$radek);
fclose($fp);
//$retezec=to_utf8($retezec,"win1250"); 
?>
