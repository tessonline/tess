<?php
require("tmapy_config.inc");
include(FileUp2(".admin/brow_.inc"));
include(FileUp2(".admin/config.inc"));
define(FPDF_FONTPATH,GetAgendaPath('POSTA',false,false).'/lib/pdf/font2/');
require(GetAgendaPath('POSTA',false,false).'/lib/pdf/fpdf.php');

include(FileUp2(".admin/security_obj.inc"));
include(FileUp2(".admin/security_name.inc"));
include_once(FileUp2(".admin/oth_funkce.inc"));

$file_name='pokus.pdf';
header("Expires: 0"); 
header("Cache-Control: must-revalidate, post-check=0, pre-check=0"); 
header("Pragma: public"); 
header("Content-Disposition: attachment; filename=$file_name"); 
header("Content-Transfer-Encoding: binary"); 


class PDF extends FPDF
{
//Page header
function Header()
{
   $this->SetFont('Arial','B',22);
    //Move to the right
    $this->Cell(190,15,$GLOBALS["CONFIG"]["URAD"].' '.$GLOBALS["CONFIG"]["MESTO"].' - doručovatel',0,1,C);
   $this->SetFont('Arial','B',20);
    $this->Cell(190,8,'protokol č.'.$GLOBALS[PROTOKOL],0,0,C);
    $this->Ln(10);
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
$pdf->AddFont('arial','','arial.php');
$pdf->AddFont('arial','B','arialb.php');
$pdf->AliasNbPages();
$pdf->AddPage();

$pdf->Ln();
//$pdf->SetFont('Arial','B',15');
$pdf->SetFont('Arial','',10);

$q=new DB_POSTA;
$a=new DB_POSTA;
$dorucovatele=array('2'=>'Vlastní doručovatel');
$doporucene=array('1'=>'obyčejně','2'=>'doporučeně','3'=>'doporučeně s dodejkou','4'=>'do vlastních rukou adresáta','5'=>'do vlastních rukou zástupce','P'=>'převzetí podatelnou','C'=>'Cenné psaní','Z'=>'pošta do zahraničí');
$pocetks=0;
while (list($key1,$val1)=each($dorucovatele))
{
  reset($doporucene);
  while (list ($key, $val) = each ($doporucene)) 
  {
//    $sql="select * from posta where".$where." and doporucene='".$key."' and vlastnich_rukou='".$key1."' order by ID";
    $sql='select * from posta where id in (select pisemnost_id from posta_cis_dorucovatel_id where protokol_id='.$GLOBALS[PROTOKOL].') and doporucene=\''.$key.'\'  ORDER BY odbor,doporucene,datum_podatelna_prijeti';
//    echo $sql;
    $q->query ($sql);
    $pocet=$q->Num_Rows();
    $pdf->SetFont('Arial','B',12);
    If ($pocet>0) {
      $pdf->Cell(180,5,'',0,1,L);
      $pdf->Cell(175,8,$val.' - '.$pocet.' ks',0,1,C);
      $pdf->Cell(180,5,'',0,1,L);
    }
    $pdf->SetFont('Arial','',12);
    //echo $sql;
    while($q->next_record())
    {
      $pocetks++;

      $PODACI_CISLO=$q->Record["EV_CISLO"]."/".$q->Record["ROK"];
      
      If ($GLOBALS["CONFIG"]["SHOW_C_JEDNACI"] && $q->Record["CISLO_JEDNACI1"])  
         $CISLO_JEDNACI=strip_tags(FormatCJednaci($q->Record["CISLO_JEDNACI1"],$q->Record["CISLO_JEDNACI2"],$q->Record["REFERENT"],$q->Record["ODBOR"]));

      $ODESILATEL=UkazAdresu($q->Record["ID"],', ');
      
      $text='Věc: '.$q->Record["VEC"];
  //    If ($q->Record["DOPORUCENE"]<>"1") {$DOPORUCENE="ANO";} else {$DOPORUCENE="NE";}

      $pdf->Cell(70,4,'ČJ:'.$CISLO_JEDNACI,0,0,L);
      $pdf->MultiCell(120,4,$ODESILATEL,0,L);
    
      $sql='select * from posta_hromadnaobalka where obalka_id='.$q->Record["ID"];
      $a->query($sql);
      $dalsi_cislo_jednaci="";
      if ($a->Num_Rows()>0)
      {
        while ($a->Next_Record())
        {
          $dalsi_cislo_jednaci[]=strip_tags(FormatCJednaci($a->Record["DOKUMENT_ID"]));
        }
        $pdf->SetFont('Arial','',10);
        $pdf->MultiCell(190,7,"+ ČJ.: ".implode(', ',$dalsi_cislo_jednaci),0,L);
        $pdf->SetFont('Arial','',12);
      }      


//      $pdf->SetXY(180,$y2);
      $pdf->SetFont('Arial','B',12);
      $pdf->Cell(190,7,$text,0,1,L);
      $pdf->Cell(180,3,'',0,1,L);
      $pdf->Cell(110,6,'',0,0,L);
      $pdf->Cell(60,6,'Podpis: .........................................',0,1,L);
      $pdf->SetFont('Arial','',12);
      $pdf->Cell(180,0.1,'',1,1,L);
      $pdf->Cell(180,3,'',0,1,L);
//      $pdf->SetXY(180,$y1);
      //$pdf->MultiCell(20,4.5,$DOPORUCENE,'T','L');
//      If ($vyskaradku>4.5) $pdf->Ln();
    
    }
  //  $pdf->Cell(175,2.5,'',0,0,C);
  }
}
$pdf->SetFont('Arial','B',12);
$pdf->Cell(190,10,' ',0,1,L);

require_once(FileUp2(".admin/security_obj.inc"));

$USER_INFO = $GLOBALS["POSTA_SECURITY"]->GetUserInfo(); 
$REFERENT = $USER_INFO["ID"]; 

$pdf->Cell(190,15,'Datum předání: '.Date("d.m.Y").', počet ks: '.$pocetks,0,1,L);

$pdf->Cell(95,15,'Předal: '.UkazUsera($REFERENT),0,0,L);
$pdf->Cell(95,15,'Podpis ...........................................',0,1,L);

$pdf->Cell(95,15,'Převzal ..........................................',0,0,L);
$pdf->Cell(95,15,'Podpis ...........................................',0,1,L);

$pdf->Output();
?> 
