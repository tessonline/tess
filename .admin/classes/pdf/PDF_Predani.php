<?php
require(GetAgendaPath('POSTA',false,false).'/lib/tcpdf/tcpdf.php');
require_once(GetAgendaPath('POSTA',false,false).'/interface/.admin/soap_funkce.inc');


class PDF_Predani extends TCPDF {
  
  //private $stranek;
  public $z;
  public $na;

  public function generovatPDF($data){
    //set_time_limit(0);
  //  $this->stranek = 1;

    $this->AddPage();
    $this->SetFont('freeserif', '', 11);
    $this->Cell(180,5,'Následující seznam dokumentů byl předán z uživatele '.$this->z.' na uživatele '.$this->na,0,1,'L');
    
    $this->SetXY(10, $this->GetY()+5);
    $this->SetFont('freeserif', '', 11);
    $this->Cell(25, 5, 'ID', 1, 0, 'L');
    $this->Cell(35, 5, 'Číslo jednací', 1, 0, 'L');
    $this->Cell(125, 5, 'Věc', 1, 0, 'L');
    $this->SetFont('freeserif', '', 8);
    $this->SetXY(10, $this->GetY()+5);
    foreach ($data as $val) {
      $y = $this->GetY();
      $this->Cell(25, 5, $val['ID'], 0, 0, 'L');
      $this->Cell(35, 5, $val['CJ'], 0, 0, 'L');
      $this->writeHTMLCell(125, 5, $this->GetX(), $this->GetY(), $val['VEC'], 0, 1, 0, 'L', 1);
      $novyY = $this->GetY();
      $this->SetXY(10, $y);
      $this->Cell(185, ($novyY - $y), '', 1, 0, 'L');
      if ($novyY > 250){
        $novyY = 10;
        $this->AddPage();
      }
      $this->SetXY(10, $novyY);
    }
  }
  
  //Page header
  public function Header() {

    global $cislo_spisu;
    $datum=Date("d.m.Y");
    $this->SetFont('freeserif','B',12);
    //$this->Cell(190,8,,0,0,C);
    $this->Cell(100,5,TxtEncoding4Soap($GLOBALS["CONFIG"]["URAD"].' '.$GLOBALS["CONFIG"]["MESTO"]),0,0,'L');
    $this->Cell(90,5,TxtEncoding4Soap('Předávací protokol - '.$datum),0,1,'R');
    $this->Cell(190,0.1,'',0,0,'R');
  }
  
  //Page footer
  public function Footer() {
    $this->SetY(-8);
    $this->SetFont('freeserif','',8);
    $datum=Date("d.m.Y v H:i");
    $this->Cell(0,4,TxtEncoding4Soap('Stránka '.$this->getAliasNumPage().' / '.$this->getAliasNbPages().', generováno dne '.$datum),0,0,'R');
    $GLOBALS['stranek_pdf']=$GLOBALS['stranek_pdf']+1;
  }
}

