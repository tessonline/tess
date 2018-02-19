<?php
require("tmapy_config.inc");
include(FileUp2(".admin/brow_.inc"));
include(FileUp2(".admin/config.inc"));
require_once(FileUp2(".admin/security_obj.inc"));
require_once(FileUp2(".admin/security_name.inc"));
require_once(FileUp2(".admin/oth_funkce.inc"));

require(GetAgendaPath('POSTA',false,false).'/lib/tcpdf/tcpdf.php');

//Instanciation of inherited class
//$pdf = new PDF();
$GLOBALS[OBALKA] = $GLOBALS[OBALKA]?$GLOBALS[OBALKA]:$GLOBALS[obalka];
$GLOBALS[OBALKA] = $GLOBALS[OBALKA]?$GLOBALS[OBALKA]:0;
//ulozime pripadne posledni pozici obalky
If ($GLOBALS["CONFIG"]["POUZIVAT_COOKIES"]) setcookie("TWIST_POSTA_VybranaObalka",$GLOBALS[OBALKA],time()+86400*300, "/"); //30 dnu

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
	'font'  => 'arial',
	'fontsize'  => 8,
	'stretchtext'  => 4
);

$a = new DB_POSTA;
$sqlx = 'select * from posta_cis_obalky where id = '.$GLOBALS[OBALKA];
$a->query($sqlx);
$a->Next_Record();
$velikost = $a->Record["VELIKOST"]?$a->Record["VELIKOST"]:'A4';
$otoceni = $a->Record["OTOCENI"]?$a->Record["OTOCENI"]:'P';

$pdf = new TCPDF($otoceni, 'mm', $velikost, true, 'UTF-8', false);
$pdf->setPrintHeader(false);
$pdf->setPrintFooter(false);

//$pdf = new PDF_Code39();
//$pdf->AliasNbPages();
$pdf->Ln();
//$pdf->SetFont('freeserif','B',15');

$pdf->SetFont('freeserif','B',12);

$dat_do = strtotime($GLOBALS["DATUM_DO"])+86400;
$GLOBALS["DATUM_DO"] = date('d.m.Y',$dat_do);

$where = ' 1=1';
if ($GLOBALS['DATUM_OD']) $where .= " AND DATUM_PODATELNA_PRIJETI >=  ('".$GLOBALS["DATUM_OD"]."')";
if ($GLOBALS['DATUM_DO']) $where .= " AND DATUM_PODATELNA_PRIJETI <=  ('".$GLOBALS["DATUM_DO"]."')";

$where .= " AND referent IN (".$GLOBALS["REFERENT"].") and ODESLANA_POSTA = 't' and vlastnich_rukou<>'9'";
//$where .= "  id>168000 and ODESLANA_POSTA = 't'";
If ($GLOBALS[DOPORUCENE])
  $where .= " AND doporucene IN ('".$GLOBALS[DOPORUCENE]."')";
else
  $where .= " AND doporucene IN ('1','2','3','4','5','P','Z')";

if ($GLOBALS['TYP_POSTY']) $where .= " AND TYP_POSTY='".$GLOBALS["TYP_POSTY"]."' ";
if ($GLOBALS['STATUS']) $where .= " AND STATUS='".$GLOBALS["STATUS"]."' ";

//echo "Odbor ".$GLOBALS["odbor"];
//If ($GLOBALS["ODESLAT"]) Die();
$pozicex = 23.4;
$pozicey = 10;

$q = new DB_POSTA;
$border_tabulky = 0;
If ($GLOBALS["ID"]) $where  = " id in (".$GLOBALS["ID"].")";
If ($GLOBALS["test"]) {$where  = " odeslana_posta = 't' ";$limit = 'LIMIT 10';$border_tabulky = 1;}

$sql = "select * from posta where".$where." order by id desc $limit"; 
$q->query ($sql);
$pocet = $q->Num_Rows();
$pdf->SetFont('freeserif','B',12);

while($q->next_record()) {
  $pdf->AddPage();
  //PRIPRAVIME UDAJE
  $ODESILATEL = '';
  $idcko = $q->Record["ID"];
  $ODESILATEL = UkazAdresu($idcko,chr(13).chr(10));
  $USER_INFO  =  $GLOBALS["POSTA_SECURITY"]->GetUserInfo(); 

  $doc = LoadSingleton('EedDokument', $idcko);
  $cislo_jednaci = $doc->cislo_jednaci;

  $podaci_cislo = $doc->barcode;

  //koukneme, jestli v teto obalce nejsou dalsi cisla jednaci...
    $sql = 'select * from posta_hromadnaobalka where obalka_id = '.$idcko;
    $a->query($sql);
    while ($a->Next_Record()) {
      $cislo_jednaci .= ", ".strip_tags(FormatCJednaci($a->Record["DOKUMENT_ID"]));
    }

  $cislo_spisu = strip_tags(FormatSpis($q->Record["CISLO_SPISU1"],$q->Record["CISLO_SPISU2"],$q->Record["REFERENT"],$q->Record["ODBOR"],$q->Record["NAZEV_SPISU"],$q->Record["PODCISLO_SPISU"]));

  If ($GLOBALS["ODESLAT"]) $odeslat = $GLOBALS["ODESLAT"];
  else  
    $odeslat = $q->Record["DOPORUCENE"];

  $adresa_uradu = $GLOBALS["CONFIG"]["ADRESA_OBALKA_PDF"];
  if (strlen($GLOBALS["CONFIG_POSTA"]["HLAVNI"]["ADRESA_OBALKA_PDF"])>5) $adresa_uradu = str_replace('|',chr(10),$GLOBALS["CONFIG_POSTA"]["HLAVNI"]["ADRESA_OBALKA_PDF"]);
  $vlastni_rukou = 'DO VLASTNÍCH RUKOU'; 
  $jen_adresatovi = 'JEN ADRESÁTOVI'; 

  If ($odeslat>3) $vlastni_rukou = 'DO VLASTNÍCH RUKOU'; else $vlastni_rukou = '';
  If ($odeslat == 4) $jen_adresatovi = 'JEN ADRESÁTOVI'; else $jen_adresatovi = '';

  if ($q->Record["OBALKA_NEVRACET"]>0 || $GLOBALS["test"]) {$nevracet = 'NEVRACET,VLOŽIT DO SCHRÁNKY'; $nevracet2 = 'X';} else {$nevracet = ''; $nevracet2 = '';}
  if ($q->Record["OBALKA_10DNI"]>0 || $GLOBALS["test"]) {$deset = 'ULOŽIT JEN 10 DNÍ'; $deset2 = 'X';} else {$deset = ''; $deset2 = '';}

  $odbor = UkazOdbor($q->Record["ODBOR"]);
  $zkratka_odboru = UkazOdbor($q->Record["ODBOR"],true);
  $referent = UkazUsera($q->Record["REFERENT"]);
  $zkratka_referenta = UkazUsera($q->Record["REFERENT"],true);
  $poznamka = $q->Record["POZNAMKA"];
  $nazev_spisu = $q->Record["NAZEV_SPISU"];
  $znacka = $q->Record["ZNACKA"];
  $dnesni_datum = Date('d.m.Y');

  //UDAJE JSOU PRIPRAVENY

  $sqly = 'select * from posta_cis_obalky_objekty where obalka_id = '.$GLOBALS[OBALKA];
// echo $sqly;
  $a->query($sqly);
  while ($a->Next_Record()) {
    $objekt = $a->Record["OBJEKT"];
    $sourx = $a->Record['SOURX'];
    $soury = $a->Record['SOURY'];
    $velikost_fontu = $a->Record['VELIKOST_FONTU']?$a->Record['VELIKOST_FONTU']:10;
    $velikost = $a->Record['VELIKOST']?$a->Record['VELIKOST']:10;
    $font = $a->Record['FONT']?$a->Record['FONT']:"''";
    $font = 'B';
    $radkovani = $a->Record['RADKOVANI']?$a->Record['RADKOVANI']:5;
    $vlastni_text = $a->Record['TEXT'];
    If ($objekt<1000) {
      $text = '';
      $pdf->SetFont('freeserif',"$font",$velikost_fontu);
      $pdf->SetXY($sourx,$soury);
      if ($objekt == 1) {$text = $adresa_uradu;}
      if ($objekt == 2) {$text = $ODESILATEL;}
      if ($objekt == 3) {$text = $vlastni_rukou;}
      if ($objekt == 4) {$text = $jen_adresatovi;}
      if ($objekt == 5) {$text = $cislo_jednaci;}
      if ($objekt == 6) {$text = $zkratka_referenta;}
      if ($objekt == 7) {$text = $referent;}
      if ($objekt == 8) {$text = $zkratka_odboru;}
      if ($objekt == 9) {$text = $odbor;}
      if ($objekt == 10) {$text = $cislo_spisu;}
      if ($objekt == 11) {$text = $podaci_cislo;}
      if ($objekt == 12) {$text = $poznamka;}
      if ($objekt == 13) {$text = $nazev_spisu;}
      if ($objekt == 14) {$text = $znacka;}
      if ($objekt == 15) {$text = $dnesni_datum;}
      if ($objekt == 16) {$text = $nevracet;}
      if ($objekt == 17) {$text = $deset;}
      if ($objekt == 18) {$text = $nevracet2;}
      if ($objekt == 19) {$text = $deset2;}
      $pdf->MultiCell($velikost,$radkovani,$text,$border_tabulky,L);
      //textove polozky
    }
    If ($objekt>999 && $objekt<2999) {

      $pdf->SetXY($sourx,$soury);
//      if ($objekt == 1000) {$pdf->Code39($sourx,$soury,$podaci_cislo,1,8);} //barcode 3z9 - vodorovne
//      if ($objekt == 1001) {$pdf->Code39_otoc($sourx,$soury,$podaci_cislo,1,8);} //barcode 3z9 - svisle
      if ($objekt == 1100) {
        // barcode 128 - voodorovne
        $pdf->SetXY($sourx,$soury);
        $pdf->write1DBarcode($podaci_cislo, 'C128', '', '', '', 12, 0.34, $style, 'N');
      }
      if ($objekt == 1101) {
        // barcode 128 - svisle
        $pdf->StartTransform();
        $pdf->Rotate(270, $sourx,$soury);
        $pdf->write1DBarcode($podaci_cislo, 'C128', '', '', '', 12, 0.34, $style, 'N');
        $pdf->StopTransform();
      }

      if ($objekt == 2000) {
        // barcode 128 - voodorovnec  - R kod ceske posty
        $cp = LoadClass('EedCeskaPosta', $idcko);
        $kod = $cp->VratCK($idcko);
        if (strlen($kod)>1) {
//          $pdf->SetXY($sourx+5,$soury+5);
          $pdf->image(GetAgendaPath('POSTA',0,0).'/images/R-posta.jpg',$sourx,$soury+0.5,'5.5','17','JPG');
          $pdf->write1DBarcode($kod, 'C128', $sourx+7, $soury+2.5, '', 17, 0.28, $style, 'N');
          $text = $GLOBALS['CONFIG_POSTA']['HLAVNI']['POSTA_NAZEV_POSTY'];
          $pdf->setXy($sourx+8,$soury);
          $pdf->MultiCell(50,5,$text,0,L);
        }
      }

    }

    If ($objekt>2999) {
      $pdf->SetFont('freeserif',"$font",$velikost_fontu);
      $pdf->SetXY($sourx,$soury);
      $pdf->MultiCell($velikost,$radkovani,$vlastni_text,$border_tabulky,L);
    }  
    $pdf->SetFont('freeserif','',10);

  }
}
//  $pdf->Cell(175,2.5,'',0,0,C);
$file_name = 'pokus.pdf';
header("Expires: 0");
header("Cache-Control: must-revalidate, post-check = 0, pre-check = 0");
header("Pragma: public");
//header("Content-Type: text/html");
header("Content-Disposition: attachment; filename = $file_name");
header("Content-Transfer-Encoding: binary");
//header("<meta HTTP-EQUIV = \"Content-Type\" CONTENT = \"text/html; charset = windows-1250\">");


$pdf->Output();
unset($pdf);

