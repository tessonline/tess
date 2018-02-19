<?php

define(FPDF_FONTPATH, GetAgendaPath('POSTA', false, false) . '/lib/pdf/font2/');
require(GetAgendaPath('POSTA', false, false) . '/lib/pdf/fpdf.php');
require(GetAgendaPath('POSTA', false, false) . '/lib/pdf/barcode.php');

class PDF extends FPDF {
  
  var $angle=0;

  function Header() {
  }  
  
  function Footer() {
    $this->SetFont('Arial', '', 6);
    $datum = Date("d.m.Y H:m");
    $this->SetXY(15, -10);
    $this->Cell(0, 3, 'Vygenerováno v programu Evidence dokumentů - modul ePodatelna, (c) T-MAPY spol. s r.o., www.tmapy.cz', 0, 0, 'L');
    $this->SetXY(-10, -10);
    $this->Cell(-5, 3, 'Stránka ' . $this->PageNo() . '/{nb}, tisk dne ' . $datum, 0, 0, 'R');
  }
  
  function Rotate($angle, $x=-1, $y=-1) {
    
    if ($x == -1)
      $x = $this->x;
    
    if ($y == -1)
      $y = $this->y;
    
    if ($this->angle != 0)
      $this->_out('Q');
    
    $this->angle = $angle;
    
    if ($angle != 0) {      
      $angle *= M_PI / 180;
      $c = cos($angle);
      $s = sin($angle);
      $cx = $x * $this->k;
      $cy = ($this->h - $y) * $this->k;
      $this->_out(sprintf('q %.5f %.5f %.5f %.5f %.2f %.2f cm 1 0 0 1 %.2f %.2f cm',$c,$s,-$s,$c,$cx,$cy,-$cx,-$cy));
    }
  }
  
  function _endpage() {
    if ($this->angle != 0) {
      $this->angle = 0;
      $this->_out('Q');
    }
    parent::_endpage();
  }
    
  function RotatedText($x, $y, $txt, $angle) {
    //Text rotated around its origin
    $this->Rotate($angle, $x, $y);
    $this->Text($x, $y, $txt);
    $this->Rotate(0);
  }
}
