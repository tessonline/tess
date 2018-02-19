<?php
define(FPDF_FONTPATH,GetAgendaPath('POSTA',false,false).'/lib/pdf/font2/');
require(GetAgendaPath('POSTA',false,false).'/lib/pdf/fpdf.php');
require("tmapy_config.inc");
include(FileUp2(".admin/brow_.inc"));
include(FileUp2(".admin/config.inc"));
include_once(FileUp2('.admin/convert.inc'));
include_once(FileUp2('.admin/upload_.inc'));
include_once(FileUp2('.admin/oth_funkce.inc'));
include_once(FileUp2('.admin/security_name.inc'));
include_once(FileUp2('.admin/security_obj.inc'));

$file_name='predavaci_protokol.pdf';
/*
header("Expires: 0"); 
header("Cache-Control: must-revalidate, post-check=0, pre-check=0"); 
header("Pragma: public"); 
//header("Content-Type: text/html"); 
header("Content-Disposition: attachment; filename=$file_name"); 
header("Content-Transfer-Encoding: binary"); 

*/

class PDF extends FPDF
{
//Page header
function Header()
{
    //Logo
  //  $this->Image('../../images/logo.png',55,8,100);
    //Arial bold 15
    //Line break
//    $this->Ln(20);
   $this->SetFont('Arial','B',26);
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
    //Arial italic 8
    $this->SetFont('Arial','I',8);
    //Page number
    $datum=Date("d.m.Y H:m");
    $this->Cell(0,10,'Stránka '.$this->PageNo().'/{nb}, tisk dne '.$datum,0,0,'C');
}
}

//Instanciation of inherited class
$pdf=new PDF();
$pdf->Open();
$pdf->AliasNbPages();
$pdf->AddFont('arial','','arial.php');
$pdf->AddFont('arial','B','arialb.php');
$pdf->AddFont('arial','I','ariali.php');
//$pdf->SetAutoPageBreak(0);
$pdf->AddPage();

//$pdf->Ln();
//$pdf->SetFont('Arial','B',15');
$pdf->SetFont('Arial','B',12);
$odbor=UkazOdbor($GLOBALS[ODBOR]);
if ($GLOBALS["smer"]=='prichozi')
  $pdf->Cell(190,7,'Protokol příchozích dokumentů do DS',0,2,C);
else
  $pdf->Cell(190,7,'Protokol dokumentů odeslaných do DS ',0,2,C);
$pdf->Cell(190,10,'od: '.$GLOBALS[DATUM_OD].' do: '.$GLOBALS[DATUM_DO],0,2,C);

$pdf->SetFont('Arial','B',12);
if ($GLOBALS["smer"]=='prichozi')
{
  $pdf->Cell(30,8,StrTr('ID DZ : ID DS / ČJ',$tr_from,$tr_to),'B',0,C);
  $pdf->Cell(130,8,StrTr('Adresát / Věc',$tr_from,$tr_to),'B',0,C);
  $pdf->Cell(30,8,StrTr('Načteno / příloh',$tr_from,$tr_to),'B',1,C);
}
else
{
  $pdf->Cell(30,8,StrTr('ID DZ : ID DS / ČJ / Odesláno',$tr_from,$tr_to),'B',0,L);
  $pdf->Cell(160,8,StrTr('Adresát / Věc / Doručeno, přečteno, přílohy',$tr_from,$tr_to),'B',1,C);
}

$pdf->SetFont('Arial','',10);
If ($GLOBALS["CONFIG"]["DB"]=='psql')
{
  $where.=" datum_odeslani >= '".$GLOBALS["DATUM_OD"]."'";
  $where.=" AND datum_odeslani <= '".$GLOBALS["DATUM_DO"]."'";
}

if ($GLOBALS["smer"]=='prichozi')
  {$where.=" AND odeslana_posta='f'"; $order=" order by ds_ID ASC";}
else
  {$where.=" AND odeslana_posta='t'"; $order=" order by (datum_odeslani) ASC";}
//echo "Odbor ".$GLOBALS["odbor"];
$q=new DB_POSTA;
$a=new DB_POSTA;

$uplobj=Upload(array('create_only_objects'=>true,'agenda'=>'POSTA','noshowheader'=>true));

$sql="select * from posta_DS where".$where.$order;;
$q->query ($sql);
//echo $sql;
$celkova_velikost=0;
$vyska=50;
//$pdf->Ln();
$pocet=0;
while($q->next_record())
{
  $pocet++;
  $vyska=$vyska+10;
  $id=$q->Record["POSTA_ID"];
  $sqla='select * from posta where id='.$id;
  $a->query($sqla); $a->Next_Record();
  If ($GLOBALS["CONFIG"]["SHOW_C_JEDNACI"])
    $cislo_jednaci=strip_tags(FormatCJednaci($a->Record["CISLO_JEDNACI1"],$a->Record["CISLO_JEDNACI2"],$a->Record["REFERENT"],$a->Record["ODBOR"]));
  else
    $cislo_jednaci=strip_tags(FormatSpis($a->Record["ID"]));
  $y1=$pdf->GetY();

  //spocitame velikost priloh
  $upload_records = $uplobj['table']->GetRecordsUploadForAgenda($id); 
  while (list($key,$val)=each($upload_records))
  {
    if ($val[NAME]<>'prichozi_datova_prava.zfo' && $val[NAME]<>'odchozi_datova_prava.zfo' && $val[NAME]<>'dorucenka.zfo') $velikost=$val[FILESIZE];
  }


  if ($GLOBALS["smer"]=='prichozi')
  {
    $pdf->SetFont('Arial','',8);
    $pdf->Cell(30,4.5,$q->Record[DS_ID].' : '.$a->Record[ODESL_DATSCHRANKA],'',0,L);
    $pdf->Cell(135,4.5,UkazAdresu($id,', '),0,0,L);
    $pdf->Cell(25,4.5,$q->Record[DATUM_ODESLANI],0,1,L);
    $pdf->SetFont('Arial','B',8);
    $pdf->Cell(40,4.5,$cislo_jednaci,'B',0,L);
    $pdf->Cell(125,4.5,$a->Record[VEC],'B',0,L);
    $pdf->Cell(25,4.5,round($velikost/1024)." Kb",'B',1,R);
  }
  else
  {
    $pdf->SetFont('Arial','',8);
    $pdf->Cell(30,4.5,$q->Record[DS_ID].' : '.$a->Record[ODESL_DATSCHRANKA],'',0,L);
    $pdf->Cell(160,4.5,UkazAdresu($id,', '),0,1,L);
    $pdf->SetFont('Arial','B',8);
    $pdf->Cell(40,4.5,$cislo_jednaci,'',0,L);
    $pdf->Cell(130,4.5,$a->Record[VEC],0,1);
    $pdf->Cell(30,4.5,$q->Record[DATUM_ODESLANI],'B',0,L);
    $pdf->SetFont('Arial','',8);
    $pdf->Cell(60,4.5,"Doručeno *: ".$q->Record[DATUM_DORUCENI],'B',0,L);
    $pdf->Cell(60,4.5,"Přečteno *: ".$q->Record[DATUM_PRECTENI],'B',0,L);
    $pdf->Cell(40,4.5,"Velikost příloh: ".round($velikost/1024)." Kb",'B',1,L);
  }
  $celkova_velikost=$celkova_velikost+$velikost;
//  $y2=$pdf->GetY();
//  $pdf->SetXY(130,$y1);
//  $vyskaradku=$y2-$y1;
  
  If ($vyskaradku>5) $pdf->Ln();
}

if ($GLOBALS["smer"]=='odchozi')
{
  $pdf->SetFont('Arial','I',8);
  $pdf->Cell(190,7,"*) hodnota datumu je převzata z ISDS, pokud byla v době načtení známa",0,0,L);
}
$pdf->SetFont('Arial','B',12);
$pdf->Cell(190,6,' ','T',1,L);

$pdf->Cell(190,6,'Celkový počet předaných dokumentů: '.$pocet,0,1,L);
$pdf->Cell(190,10,'Celkový součet příloh: '.number_format($celkova_velikost/1024/1024, 2, '.', ' ')." MB",0,1,L);
/*
$pdf->Cell(190,10,'Datum předání: '.Date("d.m.Y"),0,1,L);

$USER_INFO = $GLOBALS["POSTA_SECURITY"]->GetUserInfo(); 
$REFERENT = $USER_INFO["ID"]; 

$pdf->Cell(95,15,'Předal: '.UkazUsera($REFERENT),0,0,L);
$pdf->Cell(95,15,'Podpis ...........................................',0,1,L);

$pdf->Cell(95,15,'Převzal ..........................................',0,0,L);
$pdf->Cell(95,15,'Podpis ...........................................',0,1,L);
*/
$pdf->Output();
?> 
