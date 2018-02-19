<?php
//define(FPDF_FONTPATH,GetAgendaPath('POSTA',false,false).'/lib/pdf/font2/');
//require(GetAgendaPath('POSTA',false,false).'/lib/pdf/fpdf.php');
require(GetAgendaPath('POSTA',false,false).'/lib/tcpdf/tcpdf.php');
require("tmapy_config.inc");
include(FileUp2(".admin/brow_.inc"));
include(FileUp2(".admin/config.inc"));
include_once(FileUp2('.admin/convert.inc'));
include_once(FileUp2('.admin/oth_funkce.inc'));
include_once(FileUp2('.admin/oth_funkce_2D.inc'));
include_once(FileUp2('.admin/security_name.inc'));
include_once(FileUp2('.admin/security_obj.inc'));

$file_name='predavaci_protokol.pdf';
header("Expires: 0"); 
header("Cache-Control: must-revalidate, post-check=0, pre-check=0"); 
header("Pragma: public"); 
//header("Content-Type: text/html"); 
header("Content-Disposition: attachment; filename=$file_name"); 
header("Content-Transfer-Encoding: binary"); 



class PDF extends TCPDF
{
//Page header
function Header()
{
    //Logo
  //  $this->Image('../../images/logo.png',55,8,100);
    //freeserif bold 15
    //Line break
//    $this->Ln(20);
   $this->SetFont('freeserif','B',26);
    //Move to the right
    $this->Cell(190,15,$GLOBALS["CONFIG"]["URAD"].' '.$GLOBALS["CONFIG"]["MESTO"],0,0,C);
    $this->Ln(20);

    //Title
    //$hlavicka='Předávací protokol došlé pošty odbor';
  //  $this->Cell(30,10,$hlavicka,1,0,'C');
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
$pdf->Open();
//$pdf->AliasNbPages();
//$pdf->AddFont('arial','','arial.php');
//$pdf->AddFont('arial','B','arialb.php');
//$pdf->AddFont('arial','I','ariali.php');
//$pdf->SetAutoPageBreak(0);
$pdf->AddPage();

$pdf->Ln();
//$pdf->SetFont('freeserif','B',15');
$pdf->SetFont('freeserif','B',12);
if ($GLOBALS['ODBOR']>0) $odbor=UkazOdbor($GLOBALS[ODBOR]);
$pdf->Cell(190,10,'Předávací protokol příchozích dokumentů: '.$odbor,0,2,C);
$pdf->Cell(190,7,'od: '.$GLOBALS[DATUM_OD].' do: '.$GLOBALS[DATUM_DO],0,2,C);
if ($GLOBALS[EV_CISLO_OD] || $GLOBALS[EV_CISLO_DO])
$pdf->Cell(190,7,'podací čísla od: '.$GLOBALS[EV_CISLO_OD].' do: '.$GLOBALS[EV_CISLO_DO],0,2,C);
if ($GLOBALS[CISLO_JEDNACI1_OD] || $GLOBALS[CISLO_JEDNACI1_DO])
$pdf->Cell(190,7,'čísla jednací od: '.$GLOBALS[CISLO_JEDNACI1_OD].' do: '.$GLOBALS[CISLO_JEDNACI1_DO],0,2,C);

  $pdf->Cell(20,8,StrTr('ID',$tr_from,$tr_to),0,0,C);
  $pdf->Cell(35,8,StrTr('Jednací číslo',$tr_from,$tr_to),0,0,C);
  $pdf->Cell(80,8,StrTr('Adresa / Věc',$tr_from,$tr_to),0,0,C);
  $pdf->Cell(80,8,StrTr('',$tr_from,$tr_to),0,1,C);

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

//v pripade, za zadame pouze cislo jednaci nebo podaci, tak nebudeme brat v uvahu datum
If ($GLOBALS[EV_CISLO_OD]>0||$GLOBALS[CISLO_JEDNACI1_OD]>0) $where=" 1=1 ";

If ($GLOBALS[EV_CISLO_OD]) $where.=" AND id >= ".$GLOBALS[EV_CISLO_OD]."";
If ($GLOBALS[EV_CISLO_DO]) $where.=" AND id <= ".$GLOBALS[EV_CISLO_DO]."";
If ($GLOBALS[CISLO_JEDNACI1_OD]) $where.=" AND cislo_jednaci1 >= ".$GLOBALS[CISLO_JEDNACI1_OD]."";
If ($GLOBALS[CISLO_JEDNACI1_DO]) $where.=" AND cislo_jednaci1 <= ".$GLOBALS[CISLO_JEDNACI1_DO]."";
If ($GLOBALS["CONFIG"]["PREDANI_PRES_CK"]) $where.=" AND datum_predani is not null "; 
If ($GLOBALS[PODATELNA_ID]) $where.=" AND podatelna_id IN (".$GLOBALS[PODATELNA_ID].")";
If ($GLOBALS[SUPERODBOR]) $where.=" AND superodbor IN (".$GLOBALS[SUPERODBOR].")"; 

$where.=" AND stornovano is null";
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

$where.=" AND odes_typ<>'X' and ODESLANA_POSTA='f' order by ev_cislo DESC";
//echo "Odbor ".$GLOBALS["odbor"];
$q=new DB_POSTA;


$sql="select * from posta where".$where;
//Die($sql);
$q->query ($sql);
//echo $sql;
$vyska=50;
//$pdf->Ln();
$pocet=0;
while($q->next_record())
{
  $pocet++;
  $vyska=$vyska+10;
  $id=$q->Record["ID"];
  $PODACI_CISLO=$q->Record["EV_CISLO"]."/".$q->Record["ROK"];

  $doc = LoadSingleton('EedDokument', $id);
  $CISLO_JEDNACI = $doc->cislo_jednaci;

  $ODESILATEL=UkazAdresu($id,', ');
  $VEC=$q->Record["VEC"];
  $y1=$pdf->GetY();
  $pdf->SetFont('freeserif','',8);
  $pdf->Cell(20,4.5,$id,'T',0,C);
  $pdf->SetFont('freeserif','B',10);
  $pdf->Cell(40,4.5,$CISLO_JEDNACI,'T',0,C);
  $pdf->SetFont('freeserif','',10);
  $pdf->MultiCell(0,5,$ODESILATEL,'T','L');
//  $y2=$pdf->GetY();
//  $pdf->SetXY(130,$y1);
//  $vyskaradku=$y2-$y1;
  $pdf->Cell(10,7,'','0',0,R);
  $pdf->SetFont('freeserif','I',10);
  $pdf->MultiCell(0,5,'Věc: '.$VEC,'0','L');
  $pdf->SetFont('freeserif','',10);
If ($vyskaradku>5) $pdf->Ln();

}

$pdf->SetFont('freeserif','B',12);
$pdf->Cell(190,4.5,' ','T',1,L);

$pdf->Cell(190,10,'Celkový počet předaných dokumentů: '.$pocet,0,1,L);
$pdf->Cell(190,25,'Datum předání: '.Date("d.m.Y"),0,1,L);

$USER_INFO = $GLOBALS["POSTA_SECURITY"]->GetUserInfo(); 
$REFERENT = $USER_INFO["ID"]; 

//$pdf->Cell(95,15,'Předal: '.UkazUsera($REFERENT),0,0,L);
$pdf->Cell(95,15,'Předal: ',0,0,L);
$pdf->Cell(95,15,'Podpis ...........................................',0,1,L);

$pdf->Cell(95,15,'Převzal ..........................................',0,0,L);
$pdf->Cell(95,15,'Podpis ...........................................',0,1,L);

$pdf->Output();
?> 
