<?php
require("tmapy_config.inc");
//define(FPDF_FONTPATH,GetAgendaPath('POSTA',false,false).'/lib/pdf/font2/');
//require(GetAgendaPath('POSTA',false,false).'/lib/pdf/fpdf.php');
require(GetAgendaPath('POSTA',false,false).'/lib/tcpdf/tcpdf.php');

include(FileUp2(".admin/brow_.inc"));
include(FileUp2(".admin/config.inc"));
include(FileUp2(".admin/security_obj.inc"));
include_once(FileUp2('.admin/oth_funkce.inc'));
include_once(FileUp2('.admin/oth_funkce_2D.inc'));
include_once(FileUp2(".admin/security_name.inc"));

$file_name='pokus.pdf';
header("Expires: 0"); 
header("Cache-Control: must-revalidate, post-check=0, pre-check=0"); 
header("Pragma: public"); 
//header("Content-Type: text/html"); 
header("Content-Disposition: attachment; filename=$file_name"); 
header("Content-Transfer-Encoding: binary"); 
//header("<meta HTTP-EQUIV=\"Content-Type\" CONTENT=\"text/html; charset=windows-1250\">");



class PDF extends TCPDF
{
//Page header
function Header()
{
   $this->SetFont('freeserif','B',26);
    //Move to the right
    $this->Cell(190,15,$GLOBALS["CONFIG"]["URAD"].' '.$GLOBALS["CONFIG"]["MESTO"],0,0,C);
    $this->Ln(20);
} 

//Page footer
function Footer()
{
    //Position at 1.0 cm from bottom
    $this->SetY(-10);
    //freeserif italic 8
    $this->SetFont('freeserif','I',8);
    //Page number
    $datum=Date("d.m.Y H:m");
    $this->Cell(0,10,'Stránka '.$this->PageNo().'/{nb}, tisk dne '.$datum,0,0,'C');
}
}

//Instanciation of inherited class
$pdf=new PDF();
$pdf->AddFont('arial','','arial.php');
$pdf->AddFont('arial','B','arialb.php');
//$pdf->AliasNbPages();
$pdf->AddPage();

$pdf->Ln();
//$pdf->SetFont('freeserif','B',15');
$pdf->SetFont('freeserif','B',12);
if ($GLOBALS['ODBOR']=='')
  $pdf->Cell(190,10,'Předávací protokol odchozích dokumentů ',0,2,C);
else
  $pdf->Cell(190,10,'Předávací protokol odchozích dokumentů: '.UkazOdbor($GLOBALS['ODBOR']),0,2,C);

$pdf->Cell(190,7,'od: '.$GLOBALS[DATUM_OD].' do: '.$GLOBALS[DATUM_DO],0,2,C);
if ($GLOBALS[EV_CISLO_OD] || $GLOBALS[EV_CISLO_DO])
$pdf->Cell(190,7,'čísla od: '.$GLOBALS[EV_CISLO_OD].' do: '.$GLOBALS[EV_CISLO_DO],0,2,C);


  $pdf->Cell(20,8,'podací č.',0,0,C);
  $pdf->Cell(35,8,'Jednací číslo',0,0,C);
  $pdf->Cell(115,8,'Adresát',0,0,C);
  $pdf->Cell(20,8,'Doporučeně',0,1,C);

$pdf->SetFont('freeserif','',10);

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
$where.=" AND stornovano is null AND (datum_vypraveni is null)";
If ($GLOBALS[EV_CISLO_OD]) $where.=" AND ev_cislo >= ".$GLOBALS[EV_CISLO_OD]."";
If ($GLOBALS[EV_CISLO_DO]) $where.=" AND ev_cislo <= ".$GLOBALS[EV_CISLO_DO]."";
If ($GLOBALS[CISLO_JEDNACI1_OD]) $where.=" AND cislo_jednaci1 >= ".$GLOBALS[CISLO_JEDNACI1_OD]."";
If ($GLOBALS["CONFIG"]["PREDANI_PRES_CK"]) $where.=" AND datum_predani is not null "; 
If ($GLOBALS[CISLO_JEDNACI1_DO]) $where.=" AND cislo_jednaci1 <= ".$GLOBALS[CISLO_JEDNACI1_DO]."";
if ($GLOBALS['ODBOR'])
{
  //dopocitame podrizene unity
  require(GetAgendaPath('POSTA',false,false).'/.admin/classes/EedSchvalovani.inc');
  $user_obj = new EedUser;
  $odbor=$user_obj->VratOdborZSpisUzlu($GLOBALS['ODBOR']);
  $podrizene_unity = $user_obj->VratPodrizeneUnity($odbor);
  $odbor_pole[]=$GLOBALS['ODBOR'];
  if (count($podrizene_unity)>0)
  while (list($key,$val)=each($podrizene_unity))
  { 
    $uzel=$user_obj->VratSpisUzelZOdboru($key);
    if ($uzel>0) $odbor_pole[]=$uzel['ID'];
  }
  $where.=" AND (ODBOR in (".implode(',',$odbor_pole)."))";

  
}
If ($GLOBALS[REFERENT]) $where.=" AND referent IN (".$GLOBALS["REFERENT"].")"; 
If ($GLOBALS[SUPERODBOR]) $where.=" AND superodbor IN (".$GLOBALS[SUPERODBOR].")"; 
$where.=" and ODESLANA_POSTA='t'";

//Die($where);
//$where.=" AND referent IN (".$GLOBALS["REFERENT"].") and ODESLANA_POSTA='t'";
//echo "Odbor ".$GLOBALS["odbor"];
$q=new DB_POSTA;
//$dorucovatele=array('1'=>'Česká pošta','2'=>'Vlastní doručovatel');
//Die($where);
while (list($key,$val)=each($GLOBALS["CONFIG"]["DRUH_ODESLANI"]))
{
  $id=$val['VALUE'];
  If ($val["PROTOKOL"]==1) $dorucovatele[$id] = $val['LABEL'];
}
while (list($key,$val)=each($GLOBALS["CONFIG"]["TYP_ODESLANI"]))
{
  $id=$val['VALUE'];
  $doporucene[$id] = $val['LABEL'];
}

$pocetxx=0;
while (list($key1,$val1)=each($dorucovatele))
{
//  $pdf->SetFont('freeserif','BU',16);
//  $pdf->Cell(175,15,$val1,0,1,C);
//  $pdf->SetFont('freeserif','',10);
  reset($doporucene);
  while (list ($key, $val) = each ($doporucene)) 
  {

    $sql="select * from posta where".$where." and doporucene='".$key."' and vlastnich_rukou='".$key1."' order by doporucene,cislo_jednaci2,cislo_jednaci1,datum_podatelna_prijeti";
    
    $q->query ($sql);
    $pocet=$q->Num_Rows();
    $pdf->SetFont('freeserif','B',12);
    If ($pocet>0) {
      $pdf->SetFont('freeserif','BU',14);
      $pdf->Cell(175,10,$val1,0,1,C);
      $pdf->SetFont('freeserif','',10);
      $pdf->Cell(175,8,$val.' - '.$pocet.' ks',0,1,C);
    }

    $pdf->SetFont('freeserif','',10);
    //echo $sql;
    while($q->next_record())
    {
      $pocetxx++;
      $id=$q->Record["ID"];
      $PODACI_CISLO=$id;

      $doc = LoadSingleton('EedDokument', $id);
      $CISLO_JEDNACI = $doc->cislo_jednaci;
      $ODESILATEL=UkazAdresu($id,', ');
      If ($q->Record["DOPORUCENE"]=='1') $text='';
      If ($q->Record["DOPORUCENE"]=='2') $text='R';
      If ($q->Record["DOPORUCENE"]=='3') $text='D';
      If ($q->Record["DOPORUCENE"]=='4') $text='DR';
      If ($q->Record["DOPORUCENE"]=='5') $text='DRz';
      If ($q->Record["DOPORUCENE"]=='Z') $text='DR';

      If ($q->Record["OBALKA_NEVRACET"]>0) $text.=' SA';
      If ($q->Record["OBALKA_10DNI"]>0) $text.=' UX';
  
  //    If ($q->Record["DOPORUCENE"]<>"1") {$DOPORUCENE="ANO";} else {$DOPORUCENE="NE";}
    
      $pdf->SetFont('freeserif','',8);
      $pdf->Cell(20,4.5,$PODACI_CISLO,0,0,C);
      $pdf->SetFont('freeserif','B',10);
      $pdf->Cell(40,4.5,$CISLO_JEDNACI,0,0,C);
      $pdf->SetFont('freeserif','',10);
      $y1=$pdf->GetY();
      $pdf->MultiCell(120,4.5,$ODESILATEL,0,L);
      $y2=$pdf->GetY();
      $pdf->SetXY(180,$y1);
      $vyskaradku=$y2-$y1;
      $pdf->Cell(20,4.5,$text,0,1,C);
      //$pdf->MultiCell(20,4.5,$DOPORUCENE,'T','L');
      If ($vyskaradku>4.5) $pdf->Ln();
    
    }
  //  $pdf->Cell(175,2.5,'',0,0,C);
  }
}
$pdf->SetFont('freeserif','B',12);
$pdf->Cell(190,4.5,' ',0,1,L);

require_once(FileUp2(".admin/security_obj.inc"));

$USER_INFO = $GLOBALS["POSTA_SECURITY"]->GetUserInfo(); 
$REFERENT = $USER_INFO["ID"]; 

$pdf->Cell(190,10,'Celkový počet předaných dokumentů: '.$pocetxx,0,1,L);
$pdf->Cell(190,25,'Datum předání: '.Date("d.m.Y"),0,1,L);

//$pdf->Cell(95,15,'Předal: '.UkazUsera($REFERENT),0,0,L);
$pdf->Cell(95,15,'Předal: ',0,0,L);
$pdf->Cell(95,15,'Podpis ...........................................',0,1,L);

$pdf->Cell(95,15,'Převzal ..........................................',0,0,L);
$pdf->Cell(95,15,'Podpis ...........................................',0,1,L);

$pdf->Output();
?> 
