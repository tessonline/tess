<?php
require("tmapy_config.inc");
include(FileUp2(".admin/brow_.inc"));
include(FileUp2(".admin/config.inc"));

require(GetAgendaPath('POSTA',false,false).'/lib/tcpdf/tcpdf.php');

require_once(FileUp2(".admin/security_obj.inc"));
require_once(FileUp2(".admin/security_name.inc"));
require_once(FileUp2(".admin/oth_funkce_2D.inc"));

// define barcode style
$style = array(
	'position'  => '',
	'align'  => 'C',
	'stretch'  => false,
	'fitwidth'  => true,
	'cellfitalign'  => '',
	'border'  => false,
	'hpadding'  => 'auto',
	'vpadding'  => 'auto',
	'fgcolor'  => array(0,0,0),
	'bgcolor'  => false, //array(255,255,255),
	'text'  => true,
	'font'  => 'helvetica',
	'fontsize'  => 8,
	'stretchtext'  => 4
);


//Instanciation of inherited class
//$pdf = new PDF();
reset($GLOBALS["CONFIG"]["STITKY"]);
while (list($key,$val) = each($GLOBALS["CONFIG"]["STITKY"])) {
//die("<pre>".print_r($GLOBALS["CONFIG"]["STITKY"])."</pre>");
  If ($val['VALUE'] == $GLOBALS["STITEK"]) {
   $hornix = $val['X']?$val['X']:0;
   $horniy = $val['Y']?$val['Y']:0;
   $otoceni = $val['OTOCENI']?$val['OTOCENI']:'P';
   $sloupcu = $val['SLOUPCU']?$val['SLOUPCU']:1;
   $radku = $val['RADKU']?$val['RADKU']:1;
   $sk = $val['SIRKA_KODU']?$val['SIRKA_KODU']:0;
   $vk = $val['VYSKA_KODU']?$val['VYSKA_KODU']:0;
  }
}
$sirka_bunky = (210-$hornix-$hornix)/$sloupcu;
$vyska_bunky = (297-$horniy-$horniy)/$radku;

if ($sk) $sirka_bunky = $sk;
if ($vk) $vyska_bunky = $vk;

$pdf = new TCPDF($otoceni,'mm','A4', true, 'UTF-8', false);
$pdf->SetMargins($hornix,$horniy);

$pdf->SetFont('freeserif', '', 11);

$pdf->Ln();

$radek = 1;
$sloupec = 1;

If ($GLOBALS["POZICE"])
{
  $radek = floor($GLOBALS["POZICE"]/$sloupcu);
  If ($GLOBALS["POZICE"]/$sloupcu == floor($GLOBALS["POZICE"]/$sloupcu))
    $sloupec = $sloupcu;
  else
  {
    $sloupec = ($GLOBALS["POZICE"]-($radek*$sloupcu));
    $radek++;
  }
  $sloupec = ($sloupec == 0)?1:$sloupec;
}

$q = new DB_POSTA;

$border_tabulky = 0;
$pdf->AddPage();

$ids = is_array($GLOBALS['IDS']) ? implode(",",$GLOBALS['IDS']) : $GLOBALS['EDIT_ID'];
$sql = "select * from posta where id in (".$ids.")";

$q->query ($sql);
$pocet = $q->Num_Rows();

$a = 0;

while (($a<$pocet)) {
  
  $q->Next_Record();
  If ($radek>$radku) {
    $pdf->AddPage();
    $radek = 1;  
  }
  $params = explode(chr(13), $q->Record['POZNAMKA']);
  $data = array();
  foreach($params as $parametr) {
    list($kod, $hodnota) = explode('=', trim($parametr));
    if ($hodnota == 'P') $hodnota = 'prezenční';
    if ($hodnota == 'K') $hodnota = 'kombinovaná';
    if ($hodnota == 'D') $hodnota = 'distanční';
    $data[] = $hodnota;        
  }
  
  $doc = LoadClass('EedCj', $q->Record['ID']);
  $cj_info = $doc->GetCjInfo($q->Record['ID']);
  $cislo_jednaci = $doc->cislo_jednaci;
  
  $owner_id = $q->Record['OWNER_ID'] ? $q->Record['OWNER_ID'] : $q->Record['LAST_USER_ID'];
  $carovy_kod = $cj_info['JID_SPISU'];
  $spisova_znacka = $q->Record['TEXT_CJ'];
  $jmeno_prijmeni = $q->Record['ODESL_TITUL']." ".$q->Record['ODESL_JMENO']." ".$q->Record['ODESL_PRIJMENI'];
  $predchozi_jmpr = $data[0]; 
  $fakulta = $data[1];
  $studijni_program = $data[2];
  $studijni_odbor = $data[3];
  $forma_studia = $data[4];
  $rok_pocatku = $data[5];

  $aktualx = $hornix+($sirka_bunky*($sloupec-1))+2;
  $aktualy = $horniy+($vyska_bunky*($radek-1))+1;
  $pdf->SetXY($aktualx,$aktualy);

  $cara = 1;
  If ($sloupec == $sloupcu) {
    $pdf->Cell($sirka_bunky-4,$vyska_bunky-20,'',$cara,1,'L');
    $radek++;
    $sloupec = 0;
  }
  else
    $pdf->Cell($sirka_bunky-4,$vyska_bunky-20,'',$cara,0,'L');
  $sloupec++;
 
  $posun_y = 7;
  $posun_x = 35;
  
  $pdf->SetXY($aktualx+1,$aktualy+2);
  $pdf->write1DBarcode($carovy_kod, 'C128', '', '', '', 18, 0.33, $style, 'N');
  
  $pdf->SetFont('freeserif','',15);
  
  $pdf->SetXY($aktualx+2,$aktualy+3*$posun_y-1);
  $pdf->Cell($sirka_bunky-4,4,'Spisová značka:',0,0,'L');
  $pdf->SetXY($aktualx+37,$aktualy+3*$posun_y-1);
  $pdf->Cell($sirka_bunky-4,4,$cislo_jednaci,0,0,'L');

  $pdf->SetFont('freeserif','',11);
  
  $pdf->SetXY($aktualx+2,$aktualy+4*$posun_y);
  $pdf->Cell($sirka_bunky-4,4,'Jméno a příjmení:',0,0,'L');
  $pdf->SetXY($aktualx+$posun_x,$aktualy+4*$posun_y);
  $pdf->Cell($sirka_bunky-4,4,$jmeno_prijmeni,0,0,'L');
  
  $pdf->SetXY($aktualx+2,$aktualy+5*$posun_y);
  $pdf->Cell($sirka_bunky-4,4,'Předchozí př. a jm.:',0,0,'L');
  $pdf->SetXY($aktualx+$posun_x,$aktualy+5*$posun_y);
  $pdf->Cell($sirka_bunky-4,4,$predchozi_jmpr,0,0,'L');
  
  $pdf->SetXY($aktualx+2,$aktualy+6*$posun_y);
  $pdf->Cell($sirka_bunky-4,4,'Fakulta:',0,0,'L');
  $pdf->SetXY($aktualx+$posun_x,$aktualy+6*$posun_y);
  $pdf->Cell($sirka_bunky-4,4,$fakulta,0,0,'L');
  
  $pdf->SetXY($aktualx+2,$aktualy+7*$posun_y);
  $pdf->Cell($sirka_bunky-4,4,'Studijní program:',0,0,'L');
  $pdf->SetXY($aktualx+$posun_x,$aktualy+7*$posun_y);
  $pdf->Cell($sirka_bunky-4,4,$studijni_program,0,0,'L');
  
  $pdf->SetXY($aktualx+2,$aktualy+8*$posun_y);
  $pdf->Cell($sirka_bunky-4,4,'Studijní obor:',0,0,'L');
  $pdf->SetXY($aktualx+$posun_x,$aktualy+8*$posun_y);
  $pdf->Cell($sirka_bunky-4,4,$studijni_odbor,0,0,'L');
  
  $pdf->SetXY($aktualx+2,$aktualy+9*$posun_y);
  $pdf->Cell($sirka_bunky-4,4,'Forma studia:',0,0,'L');
  $pdf->SetXY($aktualx+$posun_x,$aktualy+9*$posun_y);
  $pdf->Cell($sirka_bunky-4,4,$forma_studia,0,0,'L');
  
  $pdf->SetXY($aktualx+2,$aktualy+10*$posun_y);
  $pdf->Cell($sirka_bunky-4,4,'Počátek studia:',0,0,'L');
  $pdf->SetXY($aktualx+$posun_x,$aktualy+10*$posun_y);
  $pdf->Cell($sirka_bunky-4,4,$rok_pocatku,0,0,'L');    


  $a++;
}

$file_name = 'stitek.pdf';
header("Expires: 0");
header("Cache-Control: must-revalidate, post-check = 0, pre-check = 0");
header("Pragma: public");
header("Content-Disposition: attachment; filename = $file_name");
header("Content-Transfer-Encoding: binary");

$pdf->Output();
?> 
