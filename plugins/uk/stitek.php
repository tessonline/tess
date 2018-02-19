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
$vyska_bunky = (270-$horniy-$horniy)/$radku;

if ($sk) $sirka_bunky = $sk;
if ($vk) $vyska_bunky = $vk;

//Die($otoceni);
//$pdf = new TCPDF($otoceni,'mm','A4');
$pdf = new TCPDF($otoceni,'mm','A4', true, 'UTF-8', false);
$pdf->SetMargins($hornix,$horniy);
//$pdf = new PDF_Code39();
//$pdf->AddFont('freeserif','','freeserif.php');
//$pdf->AddFont('freeserif','B','freeserifb.php');
//$pdf->AddFont('freeserif','','freeserif.php');
//$pdf->AddFont('freeserif','B','freeserifb.php');

//$pdf->AddFont('freeserif','','freeserif.php');
//$pdf->AddFont('freeserif','B','freeserifbd.php');
$pdf->SetFont('freeserif', '', 11);
//$pdf->AliasNbPages();
$pdf->Ln();
//$pdf->SetFont('freeserif','B',15');

//$pdf->SetFont('freeserif','B',8);

If (!$GLOBALS["DATUM_OD"]) $GLOBALS["DATUM_OD"] = Date('Y-m-d');
If (!$GLOBALS["DATUM_DO"]) $GLOBALS["DATUM_DO"] = Date('Y-m-d');

$where .= " DATUM_PODATELNA_PRIJETI >=  ('".$GLOBALS["DATUM_OD"]." 00:00:00')";
$where .= " AND DATUM_PODATELNA_PRIJETI <=  ('".$GLOBALS["DATUM_DO"]." 23:59:59')";

$where .= " AND stornovano is null";
If ($GLOBALS[EV_CISLO_OD]) $where .= " AND id >=  ".$GLOBALS[EV_CISLO_OD]."";
If ($GLOBALS[EV_CISLO_DO]) $where .= " AND id <=  ".$GLOBALS[EV_CISLO_DO]."";
If ($GLOBALS[CISLO_JEDNACI1_OD]) $where .= " AND cislo_jednaci1 > =  ".$GLOBALS[CISLO_JEDNACI1_OD]."";
If ($GLOBALS[CISLO_JEDNACI1_DO]) $where .= " AND cislo_jednaci1 < =  ".$GLOBALS[CISLO_JEDNACI1_DO]."";
//If ($GLOBALS[PODATELNA_ID]) $where .= " AND podatelna_id IN (".$GLOBALS[PODATELNA_ID].")";
If ($GLOBALS[ODBOR]) $where .= " AND odbor IN (".$GLOBALS["ODBOR"].")"; 
$where .= " AND odes_typ<>'X' and ODESLANA_POSTA = 'f' and main_doc=1 ";
If ($GLOBALS["ID"]) $where  = " id in (".$GLOBALS["ID"].")";
//$pozicex = $hornix;
//$pozicey = $horniy;
$radek = 1;
$sloupec = 1;

If ($GLOBALS["POZICE"])
{
//  $GLOBALS["POZICE"]++;
  $radek = floor($GLOBALS["POZICE"]/$sloupcu);
  If ($GLOBALS["POZICE"]/$sloupcu == floor($GLOBALS["POZICE"]/$sloupcu))
    $sloupec = $sloupcu;
  else
  {
    $sloupec = ($GLOBALS["POZICE"]-($radek*$sloupcu));
    $radek++;
  }
//  $radek = ($radek == 0)?1:$radek;
  $sloupec = ($sloupec == 0)?1:$sloupec;
}
//Die($GLOBALS["POZICE"]." - sl.".$sloupec." x ra.".$radek);
$q = new DB_POSTA;
//$b = new DB_POSTA;
$border_tabulky = 0;
$pdf->AddPage();

$sql = "select * from posta where".$where." order by ev_cislo DESC";
//Die($sql);
$q->query ($sql);
$pocet = $q->Num_Rows();
//Die("a".$pocet);
$a = 0;
If (!$GLOBALS["CELE"]&&!$GLOBALS["ID"]&&$GLOBALS["EV_CISLO_DO"]) {$pocet = $GLOBALS["EV_CISLO_DO"]-$GLOBALS["EV_CISLO_OD"]+1;}

while (($a<$pocet)) {
//  If ($GLOBALS["ID"] or $GLOBALS["CELE"] or (!$GLOBALS["EV_CISLO_DO"]))
  $q->Next_Record();
  If ($radek>$radku) {
    $pdf->AddPage();
    $radek = 1;  
  }

  $doc = LoadSingleton('EedDokument', $q->Record['ID']);
  $cislo_jednaci = $doc->cislo_jednaci;
  $owner_id = $q->Record['OWNER_ID'] ? $q->Record['OWNER_ID'] : $q->Record['LAST_USER_ID'];
  $podaci_cislo = $doc->barcode;
  //VratCarovyKod($GLOBALS['CONFIG']['ID_PREFIX'].$q->Record['ID']);

  //$podaci_cislo = "123456-2007";
  $adresa_uradu = $GLOBALS["CONFIG"]["ADRESA_OBALKA_PDF"];
//  if (!$q->Record[SUPERODBOR]) $q->Record[SUPERODBOR] = VratSuperOdbor($GLOBALS['ODBOR']);
//  $b->query('SELECT name from security_group where id = '.$q->Record[SUPERODBOR]);
//  $b->Next_Record();

  $nazev_uradu = $GLOBALS["CONFIG"]["URAD"];
  $nazev_uradu2 = $GLOBALS["CONFIG"]["URAD2"];

//  $nazev_uradu = iconv('ISO-8859-2', 'WINDOWS-1250', $GLOBALS["CONFIG"]["URAD"]);
  $odbor = $doc->uzel_text;
  $zkratka_odboru = UkazOdbor($q->Record["ODBOR"],true);
  $referent = $doc->referent_text;
  $zkratka_referenta = $doc->referent_zkratka;
  $rekomando = $doc->rekomando;
  $poznamka = $doc->poznamka;
  $dnesni_datum = Date('d.m.Y');
  $datum = $doc->datum_podatelna_prijeti;
  $datum = str_replace(' ', ' v ', $datum);
  $listu = $doc->pocet_listu;
  $priloh = $doc->pocet_priloh;
  $druh_priloh = $doc->druh_priloh;
//  $pdf->SetFont('freeserif','',8);
  $aktualx = $hornix+($sirka_bunky*($sloupec-1))+2;
  $aktualy = $horniy+($vyska_bunky*($radek-1))+1;
  $pdf->SetXY($aktualx,$aktualy);
//  $pdf->Code39_otoc(111+$pozicex,43+$pozicey,$podaci_cislo,1,8);

  $cara = $GLOBALS["CELE"]?1:0;
  If ($sloupec == $sloupcu) {
    $pdf->Cell($sirka_bunky-4,$vyska_bunky-24,'',$cara,1,'L');
    $radek++;
    $sloupec = 0;
  }
  else
    $pdf->Cell($sirka_bunky-4,$vyska_bunky-20+($GLOBALS["STITEK"]==3?4:0),'',$cara,0,'L');
  $sloupec++;
 
  If ($GLOBALS["CELE"]) {
    $pdf->SetXY($aktualx,$aktualy);
    $pdf->Cell($sirka_bunky-4,$vyska_bunky-14-27.5+($GLOBALS["STITEK"]==3?8:0),'',$cara,1,'L');

    $pdf->SetXY($aktualx+48,$aktualy);
    $pdf->Cell($sirka_bunky-4-48,$vyska_bunky-14-19+($GLOBALS["STITEK"]==3?8:0),'',$cara,1,'L');

    $pdf->SetXY($aktualx+48,$aktualy+15);
    $pdf->Cell($sirka_bunky-4-48,$vyska_bunky-14-25+($GLOBALS["STITEK"]==3?8:0),'',$cara,1,'L');

    $pdf->SetFont('freeserif','',6);
    $pdf->SetXY($aktualx+48,$aktualy+6);
    $pdf->Cell($sirka_bunky-4-48,4,'Odbor',0,0,'C');
    $pdf->SetXY($aktualx+48,$aktualy+14);
    $pdf->Cell($sirka_bunky-4-48,4,'Zprac.',0,0,'C');
//    $pdf->SetXY($aktualx+48,$aktualy+21.5);
//    $pdf->Cell($sirka_bunky-4-48,4,'Ukl.znak',0,0,'C');

    $pdf->SetXY($aktualx,$aktualy);
    $pdf->SetFont('freeserif','B',8);
    $pdf->Cell($sirka_bunky-14,0,$nazev_uradu,0,0,'L');
    $pdf->SetXY($aktualx,$aktualy+3);
    $pdf->Cell($sirka_bunky-14,0,$nazev_uradu2,0,0,'L');

    $pdf->SetFont('freeserif','',8);
    $pdf->SetXY($aktualx + 48, $aktualy+1.5);
    $pdf->Cell($sirka_bunky-4-48,3,$owner_id,0,0,'C');

    $pdf->SetFont('freeserif','',9);
    $pdf->SetXY($aktualx,$aktualy+6.5);
    $pdf->Cell($sirka_bunky-4,4,'Došlo:',0,0,'L');
    $pdf->SetXY($aktualx,$aktualy+10);
    $pdf->Cell($sirka_bunky-4,4,'Č.j.:',0,0,'L');
    $pdf->SetXY($aktualx,$aktualy+13.5);
    $pdf->Cell($sirka_bunky-4,4,'Č.dop.:',0,0,'L');
    $pdf->SetXY($aktualx,$aktualy+17);
    $pdf->Cell($sirka_bunky-4,4,'Listů:             Příloh:',0,0,'L');

    $pdf->SetXY($aktualx,$aktualy+20);
    $pdf->Cell($sirka_bunky-4,4,'Druh:',0,0,'L');

    if($GLOBALS["PRAC_KOPIE"]) {
       $pdf->SetFont('freeserif','B',12);
       $pdf->SetXY($aktualx-2,$aktualy+23.5);
       $pdf->setFontSpacing(1.25); 
       $pdf->Text($aktualx, $aktualy+25, "PRACOVNÍ KOPIE");
       $pdf->setFontSpacing(0);
    }
    else {
      $pdf->SetXY($aktualx-2,$aktualy+23.5);
      $pdf->write1DBarcode($podaci_cislo, 'C128', '', '', '', 13, 0.34, $style, 'N');
    }
    
    $pdf->SetFont('freeserif','B',9);
    $pdf->SetXY($aktualx+11,$aktualy+6.5);
    $pdf->Cell($sirka_bunky-4,4,$datum,0,0,'L');
    $pdf->SetFont('freeserif','B',9);
    $pdf->SetXY($aktualx+11,$aktualy+10);
    $pdf->Cell($sirka_bunky-4,4,$cislo_jednaci,0,0,'L');
    $pdf->SetXY($aktualx+11,$aktualy+13.5);
    $pdf->Cell($sirka_bunky-4,4,$rekomando,0,0,'L');
    $pdf->SetFont('freeserif','B',9);
    $pdf->SetXY($aktualx+11,$aktualy+17);
    $pdf->Cell($sirka_bunky-4,4,$listu,0,0,'L');
    $pdf->SetXY($aktualx+27,$aktualy+17);
    $pdf->Cell($sirka_bunky-4,4,$priloh,0,0,'L');
    $pdf->SetXY($aktualx+11,$aktualy+20);
    $pdf->Cell($sirka_bunky-4,4,$druh_priloh,0,0,'L');
  }
  else {
    if($GLOBALS["PRAC_KOPIE"]) {
       $pdf->SetXY($aktualx-2,$aktualy+23.5);
       $pdf->setFontSpacing(1.25);
       $pdf->SetFont('freeserif','B',12);
       $pdf->Text($aktualx, $aktualy+25, "PRACOVNÍ KOPIE");
       $pdf->setFontSpacing(0);
    }
    else {
      $pdf->SetXY($aktualx,$aktualy+2);
      $pdf->write1DBarcode($podaci_cislo, 'C128', '', '', '', 15, 0.34, $style, 'N');
    }
  }
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
