<?php
require(GetAgendaPath('POSTA',false,false).'/lib/tcpdf/tcpdf.php');
require_once(GetAgendaPath('POSTA',false,false).'/interface/.admin/soap_funkce.inc');

$GLOBALS['stranek_pdf']=1;

class PDF_Spis extends TCPDF {
  //Page header
  function Header() {
      global $cislo_spisu;
      $this->SetFont('freeserif','B',12);
      //$this->Cell(190,8,,0,0,C);
      $this->Cell(100,5,TxtEncoding4Soap($GLOBALS["CONFIG"]["URAD"].' '.$GLOBALS["CONFIG"]["MESTO"]),0,0,'L');
       $this->Cell(90,5,TxtEncoding4Soap('Transakční protokol - '.$GLOBALS['CZ_DATUM']),0,1,'R');
      $this->Cell(190,0.1,'',0,0,'R');
//
//       $this->Ln(5);
  } 
  //Page footer
  function Footer() {
      $this->SetY(-8);
      $this->SetFont('freeserif','',8);
      $datum=Date("d.m.Y v H:i");
      $this->Cell(0,4,TxtEncoding4Soap('Stránka '.$this->getAliasNumPage().' / '.$this->getAliasNbPages().', generováno dne '.$datum),0,0,'R');
      $GLOBALS['stranek_pdf']=$GLOBALS['stranek_pdf']+1;
  }
}


set_time_limit(0);

//$pdf=new PDF_MC_Table('P','mm','A3', $unicode=true, $encoding='UTF-8', $diskcache=false, $pdfa=false);
$pdf=new PDF_Spis('P','mm','A4', true, 'UTF-8', true, true);
//$pdf->AliasNbPages();
$GLOBALS['stranek_pdf'] = 1;

$pdf->AddPage();


$pdf->SetFont('freeserif', '', 11);
$pdf->Cell(15,5,'ID',1,0,'L');
$pdf->Cell(15,5,TxtEncoding4Soap('ČAS'), 1,0,'L');
$pdf->Cell(25,5,'JID',1,0,'L');
$pdf->Cell(30,5,'KDO',1,0,'L');
$pdf->Cell(95,5,'POPIS',1,1,'L');
$pdf->SetFont('freeserif', '', 8);

while (list($key,$val)=each($data)) {
  $y = $pdf->GetY();
  $pdf->Cell(15,5,$val['ID'],0,0,'L');
  $pdf->Cell(15,5,substr($val['LAST_TIME'], 10,10),0,0,'L');
  $pdf->Cell(25,5,$GLOBALS['CONFIG']['ID_PREFIX'].$val['DOC_ID'],0,0,'L');
  $pdf->Cell(30,5,TxtEncoding4Soap($val['JMENO']),0,0,'L');

  $pdf->writeHTMLCell(95,5,$pdf->GetX(), $pdf->GetY(), TxtEncoding4Soap($val['TEXT']), 0, 1, 0, 'L',1);
  $novyY = $pdf->GetY();
  $pdf->SetXY(10, $y);
  $pdf->Cell(180,($novyY-$y),'',1,0,'L');
  if ($novyY >250) {
    $novyY = 10;
    $pdf->AddPage();
  }
  $pdf->SetXY(10, $novyY);
}


$data_protokol = $pdf->Output($GLOBALS['FILE_NAME'], 'S');

