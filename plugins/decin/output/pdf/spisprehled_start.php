<?php
$GLOBALS['stranek_pdf']=1;

class PDF_Spis extends PDF_MC_Table {
  //Page header
  function Header() {
      global $cislo_spisu;
      $this->SetFont('Arial','',8);
      //$this->Cell(190,8,,0,0,C);
      $this->Cell(100,5,$GLOBALS["CONFIG"]["URAD"].' '.$GLOBALS["CONFIG"]["MESTO"],0,0,'L');
      $this->SetFont('Arial','B',12);
      $this->Cell(90,5,'Spisová značka: '.$cislo_spisu,0,1,'R');
      $this->Cell(190,0.1,'',1,1,'R');

      $this->Ln(5);
  } 
  //Page footer
  function Footer() {
      $this->SetY(-8);
      $this->Cell(190,0.1,'',1,1,'R');
      $this->SetFont('Arial','',8);
      $datum=Date("d.m.Y v H:i");
      $this->Cell(0,4,'Stránka '.$this->PageNo().' / {nb}, tisk dne '.$datum,0,0,'R');
      $GLOBALS['stranek_pdf']=$GLOBALS['stranek_pdf']+1;
  }
  function CheckPageBreak($h) {
  	//If the height h would cause an overflow, add a new page immediately
  	if($this->GetY()+$h>$this->PageBreakTrigger) {
    	$this->AddPage($this->CurOrientation);
    }
  }
}


set_time_limit(0);

//$pdf=new PDF_MC_Table('P','mm','A3');
$pdf=new PDF_Spis('P','mm','A4');
$pdf->AliasNbPages();
$pdf->SetMargins(10,5,10);
//$pdf->SetAutoPageBreak(0,5);
$pdf->AddFont('arial','','arial.php');
$pdf->AddFont('arial','B','arialb.php');
$pdf->SetFillColor(225,225,225);
$pdf->AddPage();

$pdf->SetXY(10,15);
$pdf->SetFont('Arial','',12);
$pdf->Cell(35,6,'Spisová značka: ',0,0,'L',0);
$pdf->SetFont('Arial','B',12);
$pdf->Cell(155,6,$cislo_spisu,0,1,'L',1);

$pdf->SetXY(10,25);
$pdf->SetFont('Arial','',12);
$pdf->Cell(35,6,'Předmět řízení: ',0,0,'L',0);
$pdf->SetFont('Arial','B',12);
$pdf->MultiCell(155,5 ,iconv('WINDOWS-1250','ISO-8859-2', $vec),0,'L',1);

$pdf->Cell(35,4,'',0,1,'L',0);

$pdf->SetFont('Arial','',12);
$pdf->Cell(35,6,'Odbor: ',0,0,'L',0);
$pdf->SetFont('Arial','B',12);
$pdf->Cell(50,6,$zkratka_odboru_hlavni,0,0,'L',1);
$pdf->SetFont('Arial','',12);
$pdf->Cell(50,6,'Spisový znak, režim: ',0,0,'R',0);
$pdf->SetFont('Arial','B',12);
$pdf->Cell(55,6,$skartace_text,0,1,'L',1);
$pdf->Cell(35,4,'',0,1,'L',0);

$pdf->SetFont('Arial','',12);
$pdf->Cell(35,6,'Uzavřeno dne: ',0,0,'L',0);
$pdf->SetFont('Arial','B',12);
$pdf->Cell(50,6,$uzavreni_spisu,0,0,'L',1);
$pdf->SetFont('Arial','',12);
$pdf->Cell(50,6,'Založeno do spisovny: ',0,0,'R',0);
$pdf->SetFont('Arial','B',12);
$pdf->Cell(55,6,'',0,1,'L',1);

$pdf->Cell(35,15,'',0,1,'L',0);
$pdf->SetFont('Arial','',12);
$pdf->Cell(180,6,'Zpracovatel:',0,1,'L',0);


$pdf->SetFont('Arial','B',10);
//Table with 20 rows and 4 columns
$pdf->Cell(20,6,'č.',1,0,'L',1);
$pdf->Cell(90,6,'Jméno, příjmení, evidenční číslo',1,0,'L',1);
$pdf->Cell(40,6,'Od',1,0,'L',1);
$pdf->Cell(40,6,'Do',1,1,'L',1);

$pdf->SetWidths(array(20,90,40,40));
$pdf->SetHeight(5);
//print_r($referenti); Die();
$pdf->SetFont('Arial','',10);
while (list($key,$val)=each($referenti))
  $pdf->Row($val);
//$pdf->SetWidths(array(5,15,15,65,15,55,15,25,34,1,1));
//srand(microtime()*1000000);
$pdf->Cell(35,15,'',0,1,'L',0);
$pdf->SetFont('Arial','',12);
$pdf->Cell(180,6,'Přehled:',0,1,'L',0);

$pdf->SetHeight(3);

$pdf->SetFont('Arial','B',6);
$pdf->SetWidths(array(5,30,14,27,36,9,9,15,15,15,15));
$pdf->SetAligns(array('center','left','left','left','left','C','C','left','left','left','left'));
$pdf->SetFont('Arial','B',8);
//Table with 20 rows and 4 columns
$pdf->Cell(5,6,'Č.',1,0,'L',1);
$pdf->Cell(30,6,'Č.j.',1,0,'L',1);
$pdf->Cell(14,6,'Vloženo',1,0,'L',1);
$pdf->Cell(27,6,'Původce',1,0,'L',1);
$pdf->Cell(36,6,'Obsah',1,0,'L',1);
$pdf->Cell(9,6,'Listů',1,0,'L',1);
$pdf->Cell(9,6,'Příloh',1,0,'L',1);
$pdf->Cell(15,6,'Druh',1,0,'L',1);
$pdf->Cell(15,6,'Vypravení',1,0,'L',1);
$pdf->Cell(15,6,'Doručení',1,0,'L',1);
$pdf->Cell(15,6,'PM',1,1,'L',1);
//$pdf->Row(array('č.','Vloženo','Původce','Obsah','Č.j.','listů','příloh','Druh příloh','Datum PM','Datum doručení','Datum vypravení'));
$pdf->SetFont('Arial','',6);

while (list($key,$val)=each($hodnoty))
{
  $pdf->Row($val);
  $text=$poznamka_pole[$key];
  //echo $text;
  //if (strlen($text)>2) 
  if ($prodomo==1) {
    $pdf->MultiCell(190,4,'Poznámka: '.$text,1,L);
  }
}
$pdf->SetFont('Arial','B',12);
$pdf->Cell(190,4.5,' ','T',1,L);

$pdf->Cell(190,10,'Celkový počet předaných listů: '.($pocet_listu_celkem).'+{nb}',0,1,L);
$nadpis=false;
while (list($key,$val)=each($pocet_priloh_celkem)) {
  if ($val>0) {
   if (!$nadpis) {
      $pdf->Cell(190,7,'Celkový počet předaných příloh:',0,1,L);
      $nadpis=true;
   }
   $pdf->Cell(190,5,' - '.$key.': '.$val,0,1,L);
  }
}
$pdf->Cell(190,25,'Datum předání: '.Date("d.m.Y"),0,1,L);

$USER_INFO = $GLOBALS["POSTA_SECURITY"]->GetUserInfo();
$REFERENT = $USER_INFO["ID"];

$pdf->Cell(95,12,'Předal: '.UkazUsera($REFERENT),0,0,L);
$pdf->Cell(95,12,'Podpis ...........................................',0,1,L);

$pdf->Cell(95,12,'Převzal ..........................................',0,0,L);
$pdf->Cell(95,12,'Podpis ...........................................',0,1,L);

$pdf->Cell(95,12,'Schválil ..........................................',0,0,L);
$pdf->Cell(95,12,'Podpis ...........................................',0,1,L);
$sql='update posta_spisobal set listu=listu+'.$GLOBALS['stranek_pdf'].' where posta_id='.$min_id;
$a->query($sql);

$pdf->Output();
Die();