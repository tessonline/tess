<?php
require("tmapy_config.inc");
require(FileUp2(".admin/brow_.inc"));
define(FPDF_FONTPATH,GetAgendaPath('POSTA',false,false).'/lib/pdf/font2/');
require(GetAgendaPath('POSTA',false,false).'/lib/pdf/fpdf.php');
require(GetAgendaPath('POSTA',false,false).'/lib/pdf/mc_table.php');
require("tmapy_config.inc");
include_once(FileUp2(".admin/brow_.inc"));
include_once(FileUp2(".admin/config.inc"));
include_once(FileUp2(".admin/security_.inc"));
include_once(FileUp2(".admin/security_name.inc"));
include_once(FileUp2(".admin/oth_funkce.inc"));
//require_once(Fileup2("html_header_full.inc"));


header("Cache-Control: must-revalidate, post-check = 0, pre-check = 0"); 
header("Pragma: public"); 

set_time_limit(0);

class PDF_Podaci_Kniha extends PDF_MC_Table
{
  //Page header
  function Header()
  {
      global $mesic,$rok;
      $this->SetFont('Arial','I',8);
      //$this->Cell(190,8,,0,0,C);
//      $this->Cell(0,3,'zapůjční protokol',0,0,'R');
      $this->Ln(1);
  } 
  //Page footer
  function Footer()
  {
      $this->SetY(-8);
      $this->SetFont('Arial','',8);
      $datum = Date("d.m.Y v H:m");
      $this->Cell(0,8,'zapůjční protokol '.$GLOBALS["CONFIG"]["URAD"].' '.$GLOBALS["CONFIG"]["MESTO"].'              Stránka '.$this->PageNo().' / {nb}, tisk dne '.$datum,0,0,'R');
  }
  function CheckPageBreak($h)
  {
  	//If the height h would cause an overflow, add a new page immediately
  	if($this->GetY()+$h>$this->PageBreakTrigger)
  	{
    	$this->AddPage($this->CurOrientation);
      $this->Row(array('jednací číslo','nazev','Rok vzniku','Sk.znak a lhůta','Místo uložení','Pozn.o trvalém vyřazení'));
    }
  }
  function Row_Storno($data,$storno)
  {
  	//Calculate the height of the row
  	$nb = 0;
  	for($i = 0;$i<count($data);$i++)
  		$nb = max($nb,$this->NbLines($this->widths[$i],$data[$i]));
  	$h = 3*$nb;
  	$puv_x = $this->GetX();
  	//Issue a page break first if needed
  	$this->CheckPageBreak($h);
  	//Draw the cells of the row
  	for($i = 0;$i<count($data);$i++)
  	{
  		$w = $this->widths[$i];
  		$a = isset($this->aligns[$i]) ? $this->aligns[$i] : 'L';
  		//Save the current position
  		$x = $this->GetX();
  		$y = $this->GetY();
  		//Draw the border
  		$this->Rect($x,$y,$w,$h);
  		//Print the text
  		$this->MultiCell($w,3,$data[$i],0,$a);
  		//Put the position to the right of the cell
  		$this->SetXY($x+$w,$y);
  	}
  	$nov_x = $this->GetX();
  	$this->Line($puv_x+1,$y+1,$nov_x-1,($y+$h)-2);
  	$this->setXY($puv_x,$y+($h/2));
    $this->Cell(($nov_x-$puv_x),($h/2)-1,strip_tags($storno),0,0,'C');
  	$this->setXY($puv_x,$y);
  	//Go to the next line
  	$this->Ln($h);
  }
}


//die('jsem tu');
Function Vyrizeno($id,$id2,$id3,$smer)
{
  $res = "";
  If ($id && $id2 && $id3) {
    $sqlxx = "select datum_podatelna_prijeti from posta where cislo_jednaci1 = ".$id." and cislo_jednaci2 = ".$id2." and id<>$id3 ORDER BY ev_cislo";
    $b = new DB_POSTA;
    $b->query ($sqlxx);
    while($b->next_record()) {    
       $DATUM = $b->Record["DATUM_PODATELNA_PRIJETI"];
    }
  } 
  else {
    $DATUM = 'neni';
  }
  $res = $DATUM;
  return $res;
}

Function Skartace($skartace)
{
  $res = "";
  If ($skartace>0) {
    $a = new DB_POSTA;
    $sql = 'select skar_znak, doba, text from cis_posta_skartace where id = '.$skartace;
    $a->query($sql);
    $a->Next_Record();
    $text_skartace = str_replace('STARE - ','',$a->Record["TEXT"]);
    $text = substr($text_skartace,0,strpos($text_skartace,' '));
    $res = $text." ".$a->Record["SKAR_ZNAK"]."/".$a->Record["DOBA"];
  }
  return $res;
}

$superodbor = "";

$q = new DB_POSTA;


$sql = 'select * from posta_cis_spisovna order by id';
$q->query($sql);
while ($q->Next_Record()) $spisovny[$q->Record['ID']] = $q->Record['SPISOVNA'];


$sql = 'select * from posta_spisovna_zapujcky where id = '.$GLOBALS['id'];
$q->query($sql);  $q->Next_Record(); $zapujcka = $q->Record;


if ($zapujcka['RUCNE'] == 1) {
}
else {
  $sql = 'select * from posta where id in (select posta_id from posta_spisovna_zapujcky_id where zapujcka_id = '.$GLOBALS[id].')';
}
//print_r($spisovny)
//echo $sql;
$q->query($sql);
$celkovy_pocet = $q->Num_Rows();

//$pdf = new PDF_MC_Table('P','mm','A3');
$pdf = new PDF_Podaci_Kniha('P','mm','A4');
$pdf->AliasNbPages();
$pdf->Open();
$pdf->SetMargins(10,15);
$pdf->AddPage();
$pdf->AddFont('arial','','arial.php');
$pdf->AddFont('arial','B','arialb.php');

$pdf->SetFont('Arial','B',20);
$pdf->SetXY(1,5);
$pdf->Cell(200,25,'Zápůjční protokol dokumentů ze spisovny',0,1,'C');

$pdf->SetFont('Arial','',12);
$pdf->SetXY(120,20);
$pdf->Cell(80,10,'Číslo protokolu: '.$GLOBALS['id'],0,1,'L');
$pdf->SetXY(10,30);
//$pdf->AddPage();
//Table with 20 rows and 4 columns
$pdf->SetWidths(array(30,70,25,20,10,15,15));
//$pdf->SetWidths(array(5,15,15,65,15,55,15,25,34,1,1));
//srand(microtime()*1000000);
$pdf->SetFont('Arial','B',7);
//$pdf->Row(array('Sm','č.p.','č.j.','datum','Odesílatel/Adresát','Věc','Odbor','Vyřízeno','Skar','rekomando/poąta'));
$pdf->Row(array('jednací číslo','nazev','Rok vzniku','Sk.znak a lhůta','Listů','Místo uložení','Pozn.o trvalém vyřazení'));
$pdf->SetFont('Arial','',7);
$spisovna_id = $zapujcka['SPISOVNA_ID'];

while($q->next_record())
{
  $i++;

  $cj = $q->Record["CISLO_JEDNACI1"];
  $pocetl = $q->Record['POCET_LISTU'];
  $pocet_listu = $pocet_listu+$pocetl;

  $id = $q->Record["ID"];
  If ($q->Record["ODESLANA_POSTA"] == "f") {$smer = ">";}
  $podaci_cislo = $q->Record["EV_CISLO"]."/".$q->Record["ROK"];

  If ($GLOBALS["CONFIG"]["SHOW_C_JEDNACI"])
    $CISLO_JEDNACI = FormatCJednaci($q->Record["CISLO_JEDNACI1"],$q->Record["CISLO_JEDNACI2"],$q->Record["REFERENT"],$q->Record["ODBOR"]);
  else
    $CISLO_JEDNACI =  FormatSpis($q->Record["CISLO_SPISU1"],$q->Record["CISLO_SPISU2"],$q->Record["REFERENT"],$q->Record["ODBOR"],'',$q->Record["PODCISLO_SPISU"]);
  $cj = $q->Record["CISLO_JEDNACI1"].'/'.$q->Record["CISLO_JEDNACI2"];
  $ODESILATEL = UkazAdresu($id,', '); 

  If ($q->Record["ODESLANA_POSTA"] == 't' && $q->Record["ID_PUVODNI"] == '') $ODESILATEL .= '
VLASTNÍ DOKUMENT';

  If ($q->Record["ODES_TYP"] == 'X') $ODESILATEL .= ' 
VNITŘNÍ POŠTA';
  $VEC = $q->Record["VEC"];
  $datum = substr($q->Record["DATUM_PODATELNA_PRIJETI"],0,strpos($q->Record["DATUM_PODATELNA_PRIJETI"]," "));
  $datum = $q->Record["DATUM_PODATELNA_PRIJETI"];
  $znak = $q->Record["SKAR_ZNAK"];
  $cj1 = $q->Record["CISLO_JEDNACI1"];
  $cj2 = $q->Record["CISLO_JEDNACI2"];
  If ($q->Record["DOBA"]<>"") {$znak .= '/'.$q->Record["DOBA"];}
  $znak = Skartace($q->Record["SKARTACE"]);    
  $rekomando = $q->Record["ODESL_REKOMANDO"];
  $jejich_cj = $q->Record["JEJICH_CJ"];
  $odbor = UkazOdbor($q->Record["ODBOR"],true).' / '.UkazUsera($q->Record["REFERENT"],true);
  If ($q->Record["ODESL_POSTAODESL"]<>"") {$rekomando .= '/'.$q->Record["ODESL_POSTAODESL"];}
  $vyrizeno = '';
  $datum_vyr = Vyrizeno($cj1,$cj2,$id,$smer);
//    If (!$datum_vyr && $smer == ">") $vyrizeno = ($q->Record["ZPUSOB_VYRIZENI"]?$q->Record["ZPUSOB_VYRIZENI"]:'vzato na vědomí');
  $priloh = ($q->Record["POCET_PRILOH"] == 0)?'':$q->Record["POCET_PRILOH"];
  $poradove_cislo = $q->Record["CISLO_JEDNACI1"];            

  if ($zapujcka['RUCNE']  ==  1) {
    $pdf->Row(array($zapujcka['RUCNE_CJ'],'','','','',$spisovny[$spisovna_id],''));
  }
  else {
    $pdf->Row(array($CISLO_JEDNACI,$VEC,$datum,$znak,$pocetl,$spisovny[$spisovna_id],''));
    
  }
}


$pdf->SetFont('Arial','B',12);
$pdf->Cell(190,4.5,' ','T',1,L);

if ($zapujcka['RUCNE'] == 0) {
  $pdf->Cell(190,10,'Celkový počet předaných listů: '.$pocet_listu,0,1,L);
}
$pdf->Cell(190,15,'',0,1,L);
$pdf->Cell(190,10,'Datum zapůjčení: '.$q->dbdate2str($zapujcka['VYTVORENO']),0,1,L);

$pdf->Cell(95,10,'Předal: '.UkazUsera($zapujcka['VYTVORENO_KYM']),0,0,L);
$pdf->Cell(95,10,'Podpis ...........................................',0,1,L);

$pdf->Cell(95,10,'Převzal: '.UkazUsera($zapujcka['PUJCENO_KOMU']),0,0,L);
$pdf->Cell(95,10,'Podpis ...........................................',0,1,L);



if ($zapujcka['VRACENO']<>'')
{
  $pdf->Cell(190,15,'',0,1,L);
  $pdf->Cell(190,10,'Datum vrácení: '.$q->dbdate2str($zapujcka['VRACENO']),0,1,L);
  
  $pdf->Cell(95,10,'Předal: '.UkazUsera($zapujcka['PUJCENO_KOMU']),0,0,L);
  $pdf->Cell(95,10,'Podpis ...........................................',0,1,L);
  
  $pdf->Cell(95,10,'Převzal: '.UkazUsera($zapujcka['VRACENO_KOMU']),0,0,L);
  $pdf->Cell(95,10,'Podpis ...........................................',0,1,L);
}
$pdf->Output();
//echo "<script>document.getElementById('upl_wait_message2').style.display  =  'none'</script>";
//echo "<span class = text>Vytvořen soubor $filename. <a href = 'getfile.php?file = $filename'>Klikněte pro jeho stažení</a>.</span>";
//require_once(Fileup2("html_footer.inc"));

?>
