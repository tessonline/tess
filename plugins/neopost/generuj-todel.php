<?php
require("tmapy_config.inc");
include(FileUp2(".admin/brow_.inc"));

Function Odbor($id)
{
  $w=new DB_POSTA;
  $sql="SELECT o.id,g.name FROM cis_posta_odbory o LEFT JOIN security_group g ON g.id=o.id_odbor where o.id=".$id;
  $w->query ($sql);
  $w->Next_Record();
  $odbor=$w->Record["NAME"];
  return $odbor;
}
Function Referent($id)
{
  $w=new DB_POSTA;
  $sql="SELECT lname,fname FROM security_user WHERE id=".$id;
  $w->query ($sql);
  $w->Next_Record();
  $odbor=$w->Record["FNAME"]." ".$w->Record["LNAME"];
  return $odbor;
}


$dnesnidatum=date("md");
$odbor2=Odbor($odbor);
$file_name=$odbor2.$dnesnidatum.'.alb'; 
header("Expires: 0"); 
header("Cache-Control: must-revalidate, post-check=0, pre-check=0"); 
header("Pragma: public"); 
//header("Content-Type: text/html"); 
header("Content-Disposition: attachment; filename=$file_name"); 
header("Content-Transfer-Encoding: binary"); 
header("<meta HTTP-EQUIV=\"Content-Type\" CONTENT=\"text/html; charset=windows-1250\">");

//require(FileUp2("html_header_full.inc"));
$q = new db_posta;
$sql = "select * from posta where id in (".$id.")";
$q->query($sql);
$pocetid=0;
$naseposta="59231";
$radek="";
while($q->next_record())
{    
If ($q->Record["ODESLANA_POSTA"]=="t")
  {    
    $evcislo=$q->Record["EV_CISLO"]."/".$q->Record["ROK"];
    
    $radek.=$evcislo.'|'.$evcislo.'|'.$evcislo;
    $radek.='| | ';
    
    If ($q->Record["DOPORUCENE"]=='1') {$radek.="|A|N|N|N";} // obyc
    If ($q->Record["DOPORUCENE"]=='2') {$radek.="|N|A|N|N";} // doporucene
    If ($q->Record["DOPORUCENE"]=='3') {$radek.="|N|N|A|N";} // s dodejkou
    If ($q->Record["DOPORUCENE"]=='4') {$radek.="|N|N|N|A";} // do vlastnich rukou

    $radek.= '| | |'.$naseposta.'| | | ';

    $radek.= '|'.$q->Record["ODESL_ODD"].' '.$q->Record["ODESL_OSOBA"];

    $radek.= '|'.$q->Record["ODESL_PRIJMENI"].' '.$q->Record["ODESL_JMENO"];
    $radek.= '|'.$q->Record["ODESL_ULICE"].' '.$q->Record["ODESL_CP"];
    $radek.= '|'.$q->Record["ODESL_POSTA"];
    $radek.= '|'.$q->Record["ODESL_PSC"];
    $radek.= '|Česká Republika';
    $radek.= '|'.Referent($q->Record["REFERENT"]);
    $radek.= '|'.Odbor($q->Record["ODBOR"]);
    
    If ($q->Record["CISLO_SPISU1"]<>'') {$radek.= '|'.$q->Record["CISLO_SPISU1"].'/'.$q->Record["CISLO_SPISU2"].'/'.$q->Record["PODCISLO_SPISU"];}
    $radek.= '|';

    $radek.= "\n\r";
  }

}

echo $radek;

$retezec=to_utf8($retezec,"win1250"); 
?>
