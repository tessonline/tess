<?php
require("tmapy_config.inc");
//require(FileUp2(".admin/run2_.inc"));
//require(FileUp2(".admin/brow_.inc"));

require("tmapy_config.inc");
include(FileUp2(".admin/brow_.inc"));
include(FileUp2(".admin/config.inc"));
include(FileUp2(".admin/security_obj.inc"));
include_once(FileUp2(".admin/oth_funkce.inc"));
define(FPDF_FONTPATH,GetAgendaPath('POSTA',false,false).'/lib/pdf/font2/');
require(GetAgendaPath('POSTA',false,false).'/lib/pdf/fpdf.php');

$file_name='pokus.pdf';
header("Expires: 0"); 
header("Cache-Control: must-revalidate, post-check=0, pre-check=0"); 
header("Pragma: public"); 
//header("Content-Type: text/html"); 
header("Content-Disposition: attachment; filename=$file_name"); 
header("Content-Transfer-Encoding: binary"); 
//header("<meta HTTP-EQUIV=\"Content-Type\" CONTENT=\"text/html; charset=windows-1250\">");


Function ShowCell($x,$y,$width,$text)
{
//MultiCell(float w, float h, string txt [, mixed border [, string align [, int fill]]]) 

}

class PDF extends FPDF
{
  //Page header
  function Header()
  {
     $this->SetFont('Arial','B',11);
      //Move to the right
     $this->SetXY(119,11);
     $this->Cell(48,4,"POŠTOVNÍ PODACÍ ARCH",0,0,C);
     $this->Ln(20);
  } 
  
  //Page footer
  function Footer()
  {
      //Position at 1.0 cm from bottom
      $this->SetY(-10);
      //Arial italic 8
      $this->SetFont('Arial','',6);
      //Page number
      $datum=Date("d.m.Y H:m");
      $this->Cell(0,10,'vytištěno v programu Evidence písemností, (c) T-MAPY spol. s r.o., www.tmapy.cz',0,0,'L');
      $this->Cell(0,10,'Stránka '.$this->PageNo().'/{nb}, tisk dne '.$datum,0,0,'R');
  }
}

//Instanciation of inherited class
$pdf=new PDF();
$pdf->AddFont('arial','','arial.php');
$pdf->AddFont('arial','B','arialb.php');
$pdf->AliasNbPages();
$pdf->AddPage('L');

$pdf->Ln();
//$pdf->SetFont('Arial','B',15');

include('pdf_inc/tabulka.inc');
$pdf->SetXY(255.3,14.7);
$pdf->SetFont('Arial','',14);
$pdf->Cell(23.6,10.6,$GLOBALS[PROTOKOL],1,1,C);

$pdf->SetFont('Arial','',8);

/*
//Uprava datumu
$where="";
//$where.=" odbor IN (".$GLOBALS["ODBOR"].")";
$where.=" (DATUM_PODATELNA_PRIJETI) >= ('".$GLOBALS["DATUM_OD"]."',) AND (DATUM_PODATELNA_PRIJETI) <= ('".$GLOBALS["DATUM_DO"]."',)";

//jen odeslane pisemnosti
$where.=" AND odeslana_posta='t'";
//jen pisemnosti na ceskou postu
$where.=" AND vlastnich_rukou='1'";
//jen dokuemnty, ktere jsou zvazene?parametr v configu
If ($GLOBALS["CONFIG"]["CPOST_VAZIT"]) $where.=" AND hmotnost is not null";
//a ktere tedy obalky, hle obycejne se tam neeviduji
$where2=" AND ((doporucene='2') or (doporucene='3') or (doporucene='4') or (doporucene='5'))";
$where3=" AND (doporucene='Z')";

If ($GLOBALS["ODBOR"]<>'')
  $where.=" AND odbor IN (".$GLOBALS["ODBOR"].")";
	
UNSET($GLOBALS["ODBOR"]);
$q=new DB_POSTA;

If ($GLOBALS["CONFIG"]["CPOST_VAZIT"]) 
  $sql='select * from posta where '.$where.$where2.' ORDER BY xertec_id';
else
  $sql='select * from posta where '.$where.$where2.' ORDER BY doporucene,datum_podatelna_prijeti';
*/

//echo $sql;
//Die();
//$q->query($sql);
$a=1;
$cena_celkem=0;

$q=new DB_POSTA;
//If ($cenne=1)
//  $sql="select * from posta where id in (select pisemnost_id from posta_cis_ceskaposta_id where protokol_id=".$GLOBALS[PROTOKOL].") and DOPORUCENE like 'C' ORDER BY doporucene,cislo_jednaci2,cislo_jednaci1,datum_podatelna_prijeti";
//else
//  $sql="select * from posta where id in (select pisemnost_id from posta_cis_ceskaposta_id where protokol_id=".$GLOBALS[PROTOKOL].") and DOPORUCENE not like 'C' ORDER BY doporucene,cislo_jednaci2,cislo_jednaci1,datum_podatelna_prijeti";
  $sql="select * from posta where id in (select pisemnost_id from posta_cis_dorucovatel_id where protokol_id=".$GLOBALS[PROTOKOL].") ORDER BY doporucene,cislo_jednaci2,cislo_jednaci1,datum_podatelna_prijeti";

//Die($sql);
$q->query($sql);
If ($GLOBALS[c1]) {$pocitame=true; $cislood=$GLOBALS[c1];}
$stranka=1;
//vypiseme postu, ktera neni zahranici, ta musi byt az na konci
while ($q->Next_Record())
{
	If (($a>15)or($puvodni<>$q->Record["DOPORUCENE"] && $puvodni=='C')or($puvodni<>$q->Record["DOPORUCENE"] && $q->Record["DOPORUCENE"]=='C'))
	{
	  //dalsi stranka
    $pdf->SetFont('Arial','B',8);
    $pdf->SetXY(196.3,178);
    $pdf->Cell(19,8,' ',0,0,C);
//    $pdf->Cell(20,7,sprintf ("%01.2f", $cena_celkem),0,0,C);
    If ($GLOBALS["CONFIG"]["CPOST_VAZIT"]) 
      $pdf->Cell(20,8,number_format($cena_celkem,2,',',''),0,0,C);
    else
      $pdf->Cell(20,8,' ',0,0,C);
//number_format($number, 2, ',', ' ');
    $pdf->Cell(20,8,' ',0,0,C);
    $pdf->AddPage('L');
		$pdf->Ln();
		include('pdf_inc/tabulka.inc');
    $pdf->SetXY(255.3,14.7);
	  $stranka++;
    $pdf->Cell(23.6,10.6,$GLOBALS[PROTOKOL].' (str. '.$stranka.')',1,1,C);
	  $a=1;
    $pdf->SetXY(10,51);
    $pdf->SetFont('Arial','',8);
		$cena_celkem=0;
	}


  $b=($a*8)+50;
  //zjistime, zda nepresahl pocet na dorucenky, pokud jo, pak nastavime na c3
  If ($cislood>$GLOBALS[c2] && $GLOBALS[c2]) $cislood=$GLOBALS[c3];

  $pdf->SetXY(10,$b);
//  $pdf->Cell(27,8,$q->Record["EV_CISLO"].'/'.$q->Record["ROK"],1,0,C);
  If ($GLOBALS[c1]) $pdf->Cell(27,8,$cislood,1,0,C);
  else
  $pdf->Cell(27,8,'',1,0,C);
  $pdf->SetXY(37,$b+1);
  $pdf->MultiCell(47,3,$q->Record["ODESL_PRIJMENI"].' '.$q->Record["ODESL_JMENO"],'L','L');
  $pdf->SetXY(84,$b+1);
  $pdf->MultiCell(35,3,$q->Record["ODESL_PSC"].' '.$q->Record["ODESL_POSTA"],'L','L');
  $pdf->SetXY(119,$b+1);
  $pdf->MultiCell(41,3,$q->Record["ODESL_ULICE"].' '.$q->Record["ODESL_CP"].' '.$q->Record["ODESL_COR"],'L','L');

	$hmotnost=$q->Record["HMOTNOST"];
  $pdf->SetXY(160,$b);
	$hmotnost_kg=floor($hmotnost/1000);
	$hmotnost_g=$hmotnost-($hmotnost_kg*1000);

  If ($GLOBALS["CONFIG"]["CPOST_VAZIT"]) 
    $pdf->MultiCell(7,8,$hmotnost_kg,0,'C');
  else
    $pdf->MultiCell(7,8,'',0,'C');
  
  $pdf->SetXY(167,$b);
  If ($GLOBALS["CONFIG"]["CPOST_VAZIT"]) 
    $pdf->MultiCell(10,8,$hmotnost_g,0,'C');
	else
    $pdf->MultiCell(10,8,'',0,'C');
	
  $pdf->SetXY(177,$b);
//  $pdf->MultiCell(14,8,'0',0,'C');
  $pdf->MultiCell(14,8,'',0,'C');
  $pdf->SetXY(191,$b);
//  $pdf->MultiCell(7,8,'0');
  $pdf->MultiCell(7,8,'');
  $pdf->SetXY(196.3,$b);
  $pdf->Cell(19,8,' ',1,0,C);
	$cena=$q->Record["CENA"];
	$cena_celkem=$cena_celkem+$cena;
  If ($GLOBALS["CONFIG"]["CPOST_VAZIT"]) 
    $pdf->Cell(20,8,number_format($cena,2,',',''),0,0,C);
  else
    $pdf->Cell(20,8,' ',0,0,C);
  $pdf->Cell(20,8,' ',1,0,C);
  
  If ($q->Record["DOPORUCENE"]=='2') $text='R';
  If ($q->Record["DOPORUCENE"]=='3') $text='D';
  If ($q->Record["DOPORUCENE"]=='4') $text='DR';
  If ($q->Record["DOPORUCENE"]=='5') $text='DZ';
  $cj=strip_tags(FormatCJednaci($q->Record["CISLO_JEDNACI1"],$q->Record["CISLO_JEDNACI2"],$q->Record["REFERENT"],$q->Record["ODBOR"]));
  $pdf->SetFont('Arial','B',8);
  $pdf->Cell(23.6,4,$text,0,0,C);
  $pdf->SetXY(255.3,$b+4);
  $pdf->SetFont('Arial','',6);
  $pdf->Cell(23.6,4,$cj,0,0,C);
  $pdf->SetFont('Arial','',8);
  $cislood++;
  $a++;
  $puvodni=$q->Record["DOPORUCENE"];
}

/*
//vypiseme postu do zahranici, musi byt az na konci
$sql='select * from posta where '.$where.$where3.' ORDER BY xertec_id';
$q->query($sql);
//$a=1;
//$cena_celkem=0;

while ($q->Next_Record())
{
	If ($a>15)
	{
	  //dalsi stranka
    $pdf->SetFont('Arial','B',8);
    $pdf->SetXY(196.3,178);
    $pdf->Cell(19,8,' ',0,0,C);
//    $pdf->Cell(20,7,sprintf ("%01.2f", $cena_celkem),0,0,C);
    If ($GLOBALS["CONFIG"]["CPOST_VAZIT"]) 
      $pdf->Cell(20,8,number_format($cena_celkem,2,',',''),0,0,C);
    else
      $pdf->Cell(20,8,' ',0,0,C);
//number_format($number, 2, ',', ' ');
    $pdf->Cell(20,8,' ',0,0,C);
    $pdf->AddPage('L');
		$pdf->Ln();
		include('pdf_inc/tabulka.inc');
	  $a=1;
    $pdf->SetXY(10,51);
    $pdf->SetFont('Arial','',8);
		$cena_celkem=0;
	}


  $b=($a*8)+50;

  $pdf->SetXY(10,$b);
//  $pdf->Cell(27,8,$q->Record["EV_CISLO"].'/'.$q->Record["ROK"],1,0,C);
  $pdf->Cell(27,8,'',1,0,C);
  $pdf->SetXY(37,$b+1);
  $pdf->MultiCell(47,3,$q->Record["ODESL_PRIJMENI"].' '.$q->Record["ODESL_JMENO"],'L','L');
  $pdf->SetXY(84,$b+1);
  $pdf->MultiCell(35,3,$q->Record["ODESL_PSC"].' '.$q->Record["ODESL_POSTA"],'L','L');
  $pdf->SetXY(119,$b+1);
  $pdf->MultiCell(41,3,$q->Record["ODESL_ULICE"].' '.$q->Record["ODESL_CP"].' '.$q->Record["ODESL_COR"],'L','L');

	$hmotnost=$q->Record["HMOTNOST"];
  $pdf->SetXY(160,$b);
	$hmotnost_kg=floor($hmotnost/1000);
	$hmotnost_g=$hmotnost-($hmotnost_kg*1000);
  $pdf->MultiCell(7,8,$hmotnost_kg,0,'C');
  $pdf->SetXY(167,$b);
  $pdf->MultiCell(10,8,$hmotnost_g,0,'C');
	
  $pdf->SetXY(177,$b);
//  $pdf->MultiCell(14,8,'0',0,'C');
  $pdf->MultiCell(14,8,'',0,'C');
  $pdf->SetXY(191,$b);
//  $pdf->MultiCell(7,8,'0');
  $pdf->MultiCell(7,8,'');
  $pdf->SetXY(196.3,$b);
  $pdf->Cell(19,8,'0,00',1,0,C);
	$cena=$q->Record["CENA"];
	$cena_celkem=$cena_celkem+$cena;
  $pdf->Cell(20,8,number_format($cena,2,',',''),0,0,C);
  $pdf->Cell(20,8,'0,00',1,0,C);
  
  If ($q->Record["DOPORUCENE"]=='Z') $text='DR';
 
  $pdf->Cell(23.6,8,$text,1,0,C);

  $a++;
}

*/
$pdf->SetFont('Arial','B',8);
$pdf->SetXY(196.3,178);
$pdf->Cell(19,8,' ',0,0,C);
//    $pdf->Cell(20,7,sprintf ("%01.2f", $cena_celkem),0,0,C);

If ($GLOBALS["CONFIG"]["CPOST_VAZIT"]) 
  $pdf->Cell(20,8,number_format($cena_celkem,2,',',''),0,0,C);
else
  $pdf->Cell(20,8,'',0,0,C);
//$pdf->Cell(20,8,$cena_celkem,0,0,C);

//number_format($number, 2, ',', ' ');
$pdf->Cell(20,8,' ',0,0,C);

//echo $sql;


$pdf->Output();

?>

