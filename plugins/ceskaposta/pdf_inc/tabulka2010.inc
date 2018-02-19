<?php
$pdf->SetFont('Arial','',10);

$pdf->SetFont('Arial','B',10);
$pdf->SetXY(7,26);
$pdf->SetLineWidth(0.4);
$pdf->Cell(13,16,"",1,0,C);
$pdf->Cell(60,16,'Podací znaky',1,0,C);
$pdf->Cell(52,16,'',1,0,C);
$pdf->Cell(21,16,'Dobírka',1,0,C);
$pdf->Cell(20,16,'',1,0,C);
$pdf->Cell(30,16,'',1,1,C);

$pdf->SetXY(5,30);
$pdf->MultiCell(17,4,"Poř. číslo",0,C);
$pdf->SetXY(79,28);
$pdf->MultiCell(52,4,'Adresát-jméno,příjmení ulice,číslo domu, PSČ,místo určení',0,C);
$pdf->SetXY(153,30);
$pdf->MultiCell(20,4,'Udaná cena',0,C);
$pdf->SetXY(173,28);
$pdf->MultiCell(30,4,'Poznámka, doplňkové služby',0,C);



$pdf->SetXY(7,42);
$pdf->Cell(196,210,'',1,1,C);
$pdf->SetXY(7,42);
$pdf->Cell(73,210,'',1,1,C);


$podavatel = $GLOBALS["CONFIG_POSTA"]["HLAVNI"]["POSTA_PROTOKOL_PODAVATEL"];
if (strpos($podavatel, '|')>0) {
  $temp = explode('|', $podavatel);
  $podavatel = $temp[0].', '.$temp[3].' '.$temp[4].' '.$temp[5].', '. $temp['1'].' ' . $temp['2'];
}
$odesilatel = $GLOBALS["CONFIG_POSTA"]["HLAVNI"]["POSTA_PROTOKOL_ODESILATEL"];
if (strpos($odesilatel, '|')>0) {
  $temp = explode('|', $odesilatel);
  $odesilatel = $temp[0].', '.$temp[3].' '.$temp[4].' '.$temp[5].', '. $temp['1'].' ' . $temp['2'];
}
//Fakulta humanitních studií UK|15800|Praha 5 -Jinonice||U Kříže|8||tel. 251080388|mail: dekanat@fhs.cuni.cz


$pdf->SetXY(7,0);
$pdf->SetFont('Arial','',10);
$pdf->SetXY(6,10);
$pdf->Cell(50,5,'Podavatel: '. $podavatel,0,0,'L');
$pdf->SetXY(6,15);
//$pdf->Cell(210,5,'Odesílatel: '.$GLOBALS["CONFIG"]["URAD"].' '.$GLOBALS["CONFIG"]["MESTO"],0,0,'L');
$pdf->Cell(210,5,'Odesílatel: '.$odesilatel,0,0,'L');
$pdf->SetFont('Arial','',8);
/*$pdf->SetXY(10,10);
$pdf->Cell(190,5,'Datum: '.$GLOBALS['datum_od'].' - '.$GLOBALS['datum_do'],0,0,'R');*/

/*$pdf->SetXY(10,20);
$pdf->Cell(190,3,'Placeno v hotovosti/Placeno převodem/Výplatní stroj',0,0,'R');*/

$pdf->SetXY(6,22);
$pdf->Cell(190,3,'Úhrada ceny: v hotovosti/převodem/výplatním strojem/Kreditem/poštovními známkami (Nehodící se škrtněte)',0,0,'L');

$pdf->SetLineWidth(0.1);
For($a=0; $a<10; $a++)
{
  $pdf->SetXY(7,42+($a*21));
  $pdf->Cell(13,21,"",1,0,C);
  $pdf->Cell(60,21,'',1,0,C);
  $pdf->Cell(52,21,'',1,0,C);
  $pdf->Cell(21,21,'',1,0,C);
  $pdf->Cell(20,21,'',1,0,C);
  $pdf->Cell(30,21,'',1,1,C);
}
/*
//tabulka
$pdf->SetXY(10,36);
  $pdf->Cell(27,22,'',1,0,C);
  $pdf->Cell(47,22,'',1,0,C);
  $pdf->Cell(35,22,'',1,0,C);
  $pdf->Cell(41,22,'',1,0,C);
  $pdf->Cell(36,22,'',1,0,C);
  $pdf->Cell(0.3,22,'',1,0,C);
  $pdf->Cell(59,22,'',1,0,C);
  $pdf->Cell(0.2,22,'',1,0,C);
  $pdf->Cell(23,22,'',1,1,C);
$pdf->SetXY(160,36);
  $pdf->Cell(17,13,'',1,0,C);
  $pdf->Cell(19,13,'',1,0,C);
  $pdf->Cell(0.3,22,'',1,0,C);
  $pdf->Cell(19,13,'',1,0,C);
  $pdf->Cell(20,13,'',1,0,C);
  $pdf->Cell(20,13,'',1,0,C);
$pdf->SetXY(160,49);
  $pdf->Cell(7,4.5,'',1,0,C);
  $pdf->Cell(10,4.5,'',1,0,C);
  $pdf->Cell(14,4.5,'',1,0,C);
  $pdf->Cell(5,4.5,'',1,0,C);
  $pdf->Cell(0.3,4.5,'',1,0,C);
  $pdf->Cell(19,4.5,'',1,0,C);
  $pdf->Cell(20,4.5,'',1,0,C);
  $pdf->Cell(20,4.5,'',1,0,C);
$pdf->SetXY(196.3,36);
  $pdf->Cell(19,4,'',1,0,C);

$pdf->SetXY(10,36);
  $pdf->Cell(27,10,'podací',0,0,C);
  $pdf->Cell(47,10,'Jméno a příjmení adresáta',0,0,C);
  $pdf->Cell(35,10,'Adresní pošta',0,0,C);
  $pdf->Cell(41,10,'',0,0,C);
  $pdf->Cell(17,10,'Hmotnost',0,0,C);
  $pdf->Cell(19,10,'Dobírka',0,0,C);

$pdf->SetXY(196,38);
$pdf->SetFont('Arial','',9);
  $pdf->Cell(19.3,10,'Vplacená',0,0,C);
  $pdf->Cell(20,10,'Cena služby',0,0,C);
  $pdf->Cell(20,10,'v hotovosti',0,0,C);

$pdf->SetXY(160,46.5);
  $pdf->Cell(7,10,'kg',0,0,C);
  $pdf->Cell(10,10,'g',0,0,C);
  $pdf->Cell(14,10,'Kč',0,0,C);
  $pdf->Cell(5,10,'h',0,0,C);
  $pdf->Cell(19,10,'Kč',0,0,C);
  $pdf->Cell(20,10,'Kč',0,0,C);
  $pdf->Cell(20,10,'Kč',0,0,C);
$pdf->SetXY(195,42);
  $pdf->Cell(22,10,'částka',0,0,C);
$pdf->SetXY(195,33);
  $pdf->Cell(22,10,'Udaná cena',0,0,C);
$pdf->SetXY(234,33);
  $pdf->Cell(22,10,'Placeno',0,0,C);

	
$pdf->SetFont('Arial','',10);
$pdf->SetXY(10,43);
  $pdf->Cell(27,10,'číslo',0,0,C);
  $pdf->Cell(47,10,'(název organizace)',0,0,C);
  $pdf->Cell(35,10,'(PSČ, místo určení)',0,0,C);
  $pdf->Cell(41,10,'Ulice, číslo domu',0,0,C);

$pdf->SetXY(160,51);
  $pdf->Cell(41,10,'',0,0,C);
$pdf->SetXY(255.6,43);
  $pdf->Cell(23,10,'Poznámka',0,0,C);
$pdf->SetXY(255.6,47);
  $pdf->SetFont('Arial','',7);
  $pdf->Cell(23,10,'(doplňkové služby)',0,0,C);

$pdf->SetXY(9.5,35.5);
  $pdf->Cell(269.5,126.3,'',1,0,C);
$pdf->SetXY(9.8,35.7);
  $pdf->Cell(269.0,126.5,'',1,0,C);
	
$pdf->SetXY(10,58);
For ($a=1; $a<=13; $a++)
{
  $pdf->Cell(27,8,'',1,0,C);
  $pdf->Cell(47,8,'',1,0,C);
  $pdf->Cell(35,8,'',1,0,C);
  $pdf->Cell(41,8,'',1,0,C);
  $pdf->Cell(7,8,'',1,0,C);
  $pdf->Cell(10,8,'',1,0,C);
  $pdf->Cell(14,8,'',1,0,C);
  $pdf->Cell(5,8,'',1,0,C);
  $pdf->Cell(0.3,8,'',1,0,C);
  $pdf->Cell(19,8,'',1,0,C);
  $pdf->Cell(20,8,'',1,0,C);
  $pdf->Cell(20,8,'',1,0,C);
  $pdf->Cell(0.2,8,'',1,0,C);
  $pdf->Cell(23,8,'',1,1,C);
  $b=($a*8)+58;
  $pdf->SetXY(10,$b);
}
//konec tabulky	

$pdf->SetFont('Arial','',10);

$pdf->SetXY(156,162);
  $pdf->Cell(40,8,'Převod - úhrn za stránku:         ks',0,0,R);
$pdf->SetXY(156,169);
  $pdf->Cell(40,4,'Převod - úhrn za protokol:         ks',0,0,R);
	
$pdf->SetXY(196.3,161.8);
  $pdf->Cell(59,7,'',1,0,C);
$pdf->SetXY(196.0,162);
  $pdf->Cell(59.6,7,'',1,0,C);

$pdf->SetXY(215.3,161.8);
  $pdf->Cell(20,7,'',1,0,C);


$pdf->SetFont('Arial','B',12);
$pdf->SetXY(10,23);
$pdf->Cell(200,10,'ODESÍLATEL: '.$GLOBALS["CONFIG"]["URAD"].' '.$GLOBALS["CONFIG"]["MESTO"],0,0,'L');

$pdf->SetFont('Arial','',8);
$pdf->SetXY(10,29);
//$pdf->Cell(200,10,'Datum: '.$date('d.M.Y'),0,0,'L');
$pdf->Cell(200,10,'Datum: '.$GLOBALS['datum_od'].' - '.$GLOBALS['datum_do'],0,0,'L');

$pdf->SetFont('Arial','',8);
$pdf->SetXY(10,15);
//$pdf->Cell(200,10,'Datum: '.$date('d.M.Y'),0,0,'L');
$pdf->Cell(200,10,'Česká pošta, s.p., IČ 47114983',0,0,'L');
	
$pdf->SetXY(255.6,15);
$pdf->Cell(23,10,'',1,1,C);
$pdf->SetXY(255.3,14.7);
$pdf->Cell(23.6,10.6,'',1,1,C);

$pdf->SetXY(235,15);
$pdf->Cell(50,5,'Číslo přílohy',0,0,'L');
$pdf->SetXY(235,20);
$pdf->Cell(50,5,'přijímací knihy',0,0,'L');
*/	
?>
