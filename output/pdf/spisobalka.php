<?php
require("tmapy_config.inc");
include(FileUp2(".admin/brow_.inc"));
include(FileUp2(".admin/config.inc"));
define(FPDF_FONTPATH,GetAgendaPath('POSTA',false,false).'/lib/pdf/font2/');
require(GetAgendaPath('POSTA',false,false).'/lib/pdf/fpdf.php');
require(GetAgendaPath('POSTA',false,false).'/.admin/classes/EedCj.inc');
require("tmapy_config.inc");
include_once(FileUp2(".admin/security_name.inc"));
include(FileUp2(".admin/oth_funkce.inc"));

reset ($GLOBALS["CONFIG_POSTA"]["PLUGINS"]);
foreach($GLOBALS["CONFIG_POSTA"]["PLUGINS"] as $plug_name => $plug) {
  if ($plug['enabled']){
    $file = FileUp2('plugins/'.$plug['dir'].'/output/pdf/spisobalka_start.php');
		if (File_Exists($file)) include($file);
  }
}




$pdf_enter = chr(10);
//$pdf_enter = "<br />";
$pdf_enter = "\n";

set_time_limit(0);
/*
$sql="select * from posta where cislo_spisu1=".$cislo_spisu1." and cislo_spisu2=".$cislo_spisu2." and stornovano is null order by id asc ";
//echo $sql;
$a->query($sql);
$a->Next_Record();
$skartace=$a->Record["SKARTACE"];

$sql="select * from posta where cislo_spisu1=".$cislo_spisu1." and cislo_spisu2=".$cislo_spisu2." and stornovano is null order by id asc ";

//echo $sql;
$a->query($sql);
$a->Next_Record();
//nacteme prvotniho adresata
$id=$a->Record[ID];
*/
$id = $SPIS_ID;
if (!$id) Die('neni co tisknout.');

$pom=new DB_POSTA;
$a=new DB_POSTA;


$sql="select * from posta where id=".$id." ";
//echo $sql;
$a->query($sql);
$a->Next_Record();

$skartace = $a->Record['SKARTACE'];
$odeslana = $a->Record['ODESLANA_POSTA'];
$cj=new EedCj($id);
$cj_predchozi_text=array();
$nasledujici_cj_text=array();
$vypravene_doc=array();
$predchozi_cj=$cj->GetPredchoziCJ($id);

$vypravene_doc=$cj->GetVypraveneDoc($id);

if (count($predchozi_cj)>0) {
  reset($predchozi_cj);
  while (list($key,$val)=each($predchozi_cj)) {
    $cj_predchozi_text[]=$cj->FormatCisloJednaci($val);
  }
}

$nasledujici_cj=$cj->GetNasledujiciCJ($id);
//print_r($nasledujici_cj);
//Die();
if (count($nasledujici_cj)>0)  {
  reset($nasledujici_cj);
  while (list($key,$val)=each($nasledujici_cj)) {
    $nasledujici_cj_text[]=$cj->FormatCisloJednaci($val);
  }
}


$dalsi_dokumenty=$cj->GetDocsInCj($id);
$seznam_schvalovatelu=array();
$seznam_spolupracujici=array();
while (list($key,$val)=each($dalsi_dokumenty)) {
  $schvalujici=$cj->SeznamSchvalovatelu($val);
  while (list($key1,$val1)=each($schvalujici)) {
    if (!in_array($val1,$seznam_schvalovatelu)) $seznam_schvalovatelu[]=$val1;
  }  
  //zkontrolujeme, jestli jde o vcnitrni postu
  $doc=$cj->GetDocInfo($val);
  if ($doc['ODES_TYP']=='X' and $doc['ODESLANA_POSTA']=='f' and $doc['REFERENT']>0) 
    if (!in_array($doc['REFERENT'],$seznam_spolupracujici)) $seznam_spolupracujici[]=$doc['REFERENT'];
}

while(list($key,$val)=each($seznam_schvalovatelu))
  $schvalovatele_jmeno.=UkazUsera($val).'
';
while(list($key,$val)=each($seznam_spolupracujici))
  $spolupracujici_jmeno.=UkazUsera($val).'
';

while (list($key,$val)=each($vypravene_doc))
{
  //zkontrolujeme, jestli jde o vcnitrni postu
  $doc=$cj->GetDocInfo($val);
  $vypraveno_text.=$doc['DATUM_VYPRAVENI'].'
';
}

$dalsi_cj=$cj->SeznamCJvSpisu($id);

if (count($dalsi_cj)>0) {
  while (list ($key, $val) = each ($dalsi_cj))  {
    $cj_obj_temp = new EedCj($val);
    $cj_obj_info = $cj_obj_temp->GetCjInfo($val,1);
    $text[] = $cj_obj_info['TEXT_CJ'];
  }
  $cj_ve_spisu = implode(', ',$text);
}

$spolupracujici=$spolupracujici_jmeno;
$schvalovatele=$schvalovatele_jmeno;

$sql="select * from posta_spisobal where posta_id=".$id." ";
$pom->query($sql);
$pom->Next_Record();
if ($pom->Record['OBEH_PRED']<>'') $pred_vypravenim = $pom->Record['OBEH_PRED'];
//if ($pom->Record['OBEH_PO']<>'')

 $po_vypraveni = $pom->Record['OBEH_PO'];

$drivejsi_spisy=implode(', ',$cj_predchozi_text);
$dalsi_cj=implode(', ',$nasledujici_cj_text);
$ODESILATEL=UkazAdresu($id,', ');

$cj_obj = LoadClass('EedCj',$id);
$cj_info = $cj_obj->GetCjInfo($id);

$nazev_spisu = $cj_info['NAZEV_SPISU'];
$cislo_spisu = $cj_info['CELE_CISLO'];
$skartace_pole = $cj_obj->SpisZnak($id);

$prijemci=substr($a->Record["DALSI_PRIJEMCI"],1,-1);

if ($odeslana == 't')
$ODESILATEL = 'dokument z vlastního podnětu';
$prvotni_adresat=StrTr($ODESILATEL, $tr_from, $tr_to);

$vec_dopisu = $nazev_spisu <>'' ? $nazev_spisu : $a->Record["VEC"];
$vec_dopisu=StrTr($vec_dopisu, $tr_from, $tr_to);
$jejich_cj=StrTr($a->Record["JEJICH_CJ"], $tr_from, $tr_to);
$poznamka=StrTr($a->Record["POZNAMKA"], $tr_from, $tr_to);
//$zkratka_odboru=UkazOdbor($a->Record["ODBOR"],true);

$zkratka_odboru = $cj_obj->uzel_text;
//$referent=StrTr(UkazUsera($a->Record['REFERENT'], $tr_from, $tr_to));
$referent=StrTr(UkazUsera($a->Record['REFERENT']),$tr_from,$tr_to);

$USER_INFO = $GLOBALS["POSTA_SECURITY"]->GetUserInfo($a->Record['REFERENT']);
$telefon = $USER_INFO["PHONE"]; 

$spis_vyrizen=$a->Record['SPIS_VYRIZEN'];
$datum_vyrizeni=$a->Record['DATUM_VYRIZENI'];
$doslo=$a->Record['DATUM_PODATELNA_PRIJETI'];
$DALSI_ADRESATI=array();
$DALSI_ADRESATI_JSOU=array();
$DALSI_ADRESATI_JSOU[]=$a->Record["ODESL_PRIJMENI"];
while ($a->Next_Record())
{
  $ODESILATEL='';
  $psc=substr($a->Record["ODESL_PSC"],0,3)." ".substr($a->Record["ODESL_PSC"],3,2);
  If (($a->Record["ODES_TYP"]<>"A") and ($a->Record["ODES_TYP"]<>"P"))
  {
    $ODESILATEL=$a->Record["ODESL_PRIJMENI"]." ".$a->Record["ODESL_JMENO"]." ".$a->Record["ODESL_TITUL"].", ".$a->Record["ODESL_ULICE"]." ".$a->Record["ODESL_CP"]."".$a->Record["ODESL_COR"].", ".$psc." ".$a->Record["ODESL_POSTA"];
  }
  If (($a->Record["ODES_TYP"]=="P"))
  {
    $ODESILATEL=$a->Record["ODESL_PRIJMENI"].", ";
    $ODESILATEL.=$a->Record["ODESL_ULICE"]." ".$a->Record["ODESL_CP"]."".$a->Record["ODESL_COR"].", ".$psc." ".$a->Record["ODESL_POSTA"];
  }
  $ODESILATEL=UkazAdresu($a->Record["ID"],', ');
  //pridame jenom ty, co tam jeste nejsou
  If (!in_array($ODESILATEL,$DALSI_ADRESATI_JSOU) && $a->Record['ODES_TYP']<>'X') 
  {
    $DALSI_ADRESATI[]=$ODESILATEL;
    $DALSI_ADRESATI_JSOU[]=$ODESILATEL;
  }

}
//$DALSI_ADRESATI.= $ODESILATEL."\\par ";
sort($DALSI_ADRESATI,SORT_STRING);
$DALSI_ADRESATI=StrTr(implode(chr(10).chr(13),$DALSI_ADRESATI), $tr_from, $tr_to);

$zkratka_odboru=StrTr($zkratka_odboru, $tr_from, $tr_to);
$DALSI_ADRESATI=StrTr($DALSI_ADRESATI, $tr_from, $tr_to);
$prvotni_adresat=StrTr($prvotni_adresat, $tr_from, $tr_to);


If (!$skartace) $skartace=0;
if ($skartace>0)
{
  $sql='select * from cis_posta_skartace where id='.$skartace;
  $a->query($sql);
  $a->Next_Record();

  $skartace_text = "
";
  
//  $skartace_text=substr($a->Record["TEXT"],0,strpos($a->Record["TEXT"],' ')).", ;
  if (count($ukl_znacka_array)>0) 
    $ukl_znacka_text = implode($pdf_enter, $ukl_znacka_array);
    
//  $skartace_text .= $a->Record["TEXT"];
  $skartace_text .= $skartace_pole['text'];

//  $skartace_lhuta_text .= $a->Record["SKAR_ZNAK"] . "/" . $a->Record["DOBA"];
  $skartace_lhuta_text = $skartace_pole['znak'] . "/" . $skartace_pole['doba'];

  if (!$spis_vyrizen) { 
    $datum=$datum_vyrizeni;
    $date1 = substr($datum,0,strpos($datum," "));
    $datumkod=explode(".",$date1);
    $rok=$datumkod[2];
  }
  else
  {
    $date1=explode("-",$spis_vyrizen);
    $rok=$date1[0];
  }
  $rok=$rok+$skartace_pole['doba']+1;
  if ($rok>1900)
    $skartace_lhuta_text.=', '.$rok;

}
else
  $skartace="    ";



//$pdf=new PDF_MC_Table('P','mm','A3');
$page_width = 210;
$margins = 15;
$content_width = $page_width - 2 * $margins;
$column_width = $content_width / 2;
$main_font_size = 8;
$padding_left = 5;
$padding_right = $padding_left;
$padding_top = 5;
$line_height = 8;
$dots = ' ............ ';
$text = 'asdfg asg asg asfg asg   asgf asfg as gas g asg a s gasgasdfg asg asg asfg asg   asgf asfg aasdfg asg asg asfg asg   asgf asfg as gas g asg a s gasgasdfg asg asg asfg asg   asgf asfg as gas g asg a s gasg';
$text = '';
//$format = 'A3';
//$pdf=new FPDF('P','mm','A4');
//$pdf->SetMargins($margins,$margins,$margins);

if ($format == 'A3')
{
  $pdf=new FPDF('L','mm','A3');
  $pdf->SetMargins(220,15,15);
  $padding_left = 5;
  $padding_right = 5;
}
else
{
  $pdf=new FPDF('P','mm','A4');
  $pdf->SetMargins($margins,$margins,$margins);
}

$pdf->AliasNbPages();
$pdf->AddFont('arial','','arial.php');
$pdf->AddFont('arial','B','arialb.php');
$pdf->AddPage();

// 1.radek
$cell_height = 20;
$pdf->Cell($column_width,$cell_height,'',RB,0,L);
//$pdf->Image(FileUP2('images/logo/npu.jpg'), $pdf->GetX() - $column_width - 3, $pdf->GetY() + 4, 21, 13);
$pdf->SetFont('Arial','B',13);
$title = strtoupper($CONFIG["URAD"]);
$tile_width = $pdf->GetStringWidth($title);
$pdf->Text($pdf->GetX() - $tile_width - 4,$pdf->GetY() + $padding_top + 4, $title);


$pdf->Cell($column_width,$cell_height,'',LB,1,L);
$pdf->SetFont('Arial','',$main_font_size);
$label = 'Označení spěšnosti / důvěrnosti spisu: ';
$label_width = $pdf->GetStringWidth($label);
$pdf->Text($pdf->GetX() + $column_width + $padding_left,$pdf->GetY() + $padding_top - $cell_height + 4, $label);
$pdf->SetFont('Arial','B',$main_font_size);
$value = $oznaceni_spisu;
$pdf->Text($pdf->GetX() + $column_width + $padding_left + $label_width,$pdf->GetY() + $padding_top - $cell_height + 4, $value);

// 2.radek
$cell_height = 20;
$pdf->Cell($column_width,$cell_height,'',RB,0,L);
$pdf->SetFont('Arial','',$main_font_size);
$label = 'Číslo jednací:';
$pdf->Text($pdf->GetX() - $column_width,$pdf->GetY() + $padding_top, $label);
$label = 'Odbor, oddělení (sekce):';
$label_width = $pdf->GetStringWidth($label);
$pdf->Text($pdf->GetX() - $label_width - $padding_right,$pdf->GetY() + $padding_top, $label);
$pdf->SetFont('Arial','B',10);
$value = $cislo_spisu;
$pdf->Text($pdf->GetX() - $column_width, $pdf->GetY() + $padding_top + $line_height + 3, $value);
$value = $zkratka_odboru;
$value_width = $pdf->GetStringWidth($value);
$pdf->Text($pdf->GetX() - $value_width - $padding_right, $pdf->GetY() + $padding_top + $line_height + 3, $value);


$pdf->Cell($column_width,$cell_height,'',LB,1,L);
$pdf->SetFont('Arial','',$main_font_size);
$label = 'Referent: ';
$label_width = $pdf->GetStringWidth($label);
$pdf->Text($pdf->GetX() + $column_width + $padding_left,$pdf->GetY() - $cell_height / 3 * 2, $label);
$pdf->SetFont('Arial','B',$main_font_size);
$value = $referent;
$pdf->Text($pdf->GetX() + $column_width + $padding_left + $label_width,$pdf->GetY() - $cell_height / 3 * 2, $value);

$pdf->SetFont('Arial','',$main_font_size);
$label = 'Telefon: ';
$label_width = $pdf->GetStringWidth($label);
$pdf->Text($pdf->GetX() + $column_width + $padding_left,$pdf->GetY() - $cell_height / 3 + 1, $label);
$pdf->SetFont('Arial','B',$main_font_size);
$value = $telefon;
$pdf->Text($pdf->GetX() + $column_width + $padding_left + $label_width,$pdf->GetY() - $cell_height / 3 + 1, $value);

// 3.radek
$cell_height = 35;
$entire_line_width = 0;
$pdf->Cell($column_width,$cell_height,'',RB,0,L);

$pdf->SetFont('Arial','',$main_font_size);
$label = 'Došlo: ';
$label_width = $pdf->GetStringWidth($label);
$entire_line_width = $label_width;
$pdf->Text($pdf->GetX() - $column_width,$pdf->GetY() + $padding_top, $label);
$pdf->SetFont('Arial','B',$main_font_size);
$value = $doslo;
$pdf->Text($pdf->GetX() - $column_width + $entire_line_width,$pdf->GetY() + $padding_top, $value);
$entire_line_width += $pdf->GetStringWidth($value);

$pdf->SetFont('Arial','',$main_font_size);
$label = '       č. j.: ';
$pdf->Text($pdf->GetX() - $column_width + $entire_line_width,$pdf->GetY() + $padding_top, $label);
$entire_line_width += $pdf->GetStringWidth($label);
$pdf->SetFont('Arial','B',$main_font_size);
$value = $jejich_cj;
$pdf->Text($pdf->GetX() - $column_width + $entire_line_width,$pdf->GetY() + $padding_top, $value);
/*
$pdf->SetFont('Arial','',$main_font_size);
$label = ' ';
$label_width = $pdf->GetStringWidth($label);
$pdf->Text($pdf->GetX() - $column_width,$pdf->GetY() + $padding_top + $line_height, $label);
$pdf->SetFont('Arial','B',$main_font_size);
$value = $datum;
$pdf->Text($pdf->GetX() - $column_width + $label_width,$pdf->GetY() + $padding_top + $line_height, $value);
*/
$pdf->SetFont('Arial','',$main_font_size);
$y = $pdf->GetY();
$label = 'Od: ';
$label_width = $pdf->GetStringWidth($label);
$pdf->Text($pdf->GetX() - $column_width, $pdf->GetY() + $padding_top + ($line_height/2) , $label);
$pdf->SetFont('Arial','B',$main_font_size);
$value = $prvotni_adresat;
//$pdf->Text($pdf->GetX() - $column_width + $label_width, $pdf->GetY() + $padding_top + $line_height, $value);
$x = $pdf->GetX() - $column_width ;
//$y = $pdf->GetY() + $padding_top + $line_height;
$pdf->SetXY($x, $y + $padding_top + $line_height);
$pdf->MultiCell($column_width, $line_height / 2, $value);
$pdf->SetXY($x + $column_width, $y);


$pdf->Cell($column_width,$cell_height,'',LB,1,L);
$pdf->SetFont('Arial','',$main_font_size);
$label = 'Zároveň se vyřizují č. j.: ';
$label_width = $pdf->GetStringWidth($label);
$pdf->Text($pdf->GetX() + $column_width + $padding_left,$pdf->GetY() - $cell_height + $padding_top, $label);
$pdf->SetFont('Arial','B',$main_font_size);
$value = $cj_ve_spisu;
$x = $pdf->GetX();
$y = $pdf->GetY();
$pdf->SetXY($pdf->GetX() + $column_width + $padding_left,$pdf->GetY() - $cell_height + $padding_top + 2);
$pdf->MultiCell(0, 5, $value, 0, L);

// 4.radek
$cell_height = 20;
$pdf->SetXY($x, $y);
$pdf->Cell($content_width ,$cell_height,'',B,1,L);
$pdf->SetFont('Arial','B',$main_font_size);
$label = 'Věc: ';
$label_width = $pdf->GetStringWidth($label);
$pdf->Text($pdf->GetX(),$pdf->GetY() + $padding_top - $cell_height, $label);
$pdf->SetFont('Arial','B',$main_font_size);
$value = $vec_dopisu ;
$x = $pdf->GetX();
$y = $pdf->GetY();
$pdf->SetXY($pdf->GetX() + $label_width,$pdf->GetY() - $cell_height + 1.8);
$pdf->MultiCell(0, 5, $value, 0, L);

// 5.radek
$cell_height = 23;
$pdf->SetXY($x, $y);
$pdf->SetFont('Arial','',$main_font_size);
$pdf->Cell($column_width,$cell_height,'',RB,0,L);
$label = 'Dřívější spisy č.j.:';
$pdf->Text($pdf->GetX() - $column_width,$pdf->GetY() + $padding_top, $label);
$pdf->SetFont('Arial','B',$main_font_size);
$value = $drivejsi_spisy;
$x = $pdf->GetX();
$y = $pdf->GetY();
$pdf->SetXY($pdf->GetX() - $column_width,$pdf->GetY() + $padding_top + 2);
$pdf->MultiCell($column_width - $padding_right, 5, $value, 0, L);


$pdf->SetXY($x, $y);
$pdf->SetFont('Arial','',$main_font_size);
$pdf->Cell($column_width,$cell_height,'',LB,1,L);
$label = 'Poznámka:';
$pdf->Text($pdf->GetX() + $column_width + $padding_left,$pdf->GetY() - $cell_height + $padding_top, $label);
$pdf->SetFont('Arial','B',$main_font_size);
$value = $dalsi_cj;
$x = $pdf->GetX();
$y = $pdf->GetY();
$pdf->SetXY($pdf->GetX() + $column_width + $padding_left,$pdf->GetY() - $cell_height + $padding_top + 2);
$pdf->MultiCell(0, 5, $value, 0, L);

// 6.radek
$cell_height = 10;
$pdf->SetXY($x, $y);
$pdf->SetFont('Arial','B',$main_font_size);
$pdf->Cell($content_width ,$cell_height,'Do spisu nahlédne:','',1,C);

// 7.radek
$cell_height = 70;

if (!$pred_vypravenim)
{
  $pdf->SetFont('Arial','',$main_font_size);
  $pdf->Cell($column_width,$cell_height,'',RB,0,L);
  $label = 'Před vypravením:';
  $pdf->Text($pdf->GetX() - $column_width,$pdf->GetY() + $padding_top, $label);
  $label = 'Spolupracující:';
  $pdf->Text($pdf->GetX() - $column_width,$pdf->GetY() + $padding_top + $line_height, $label);
  $pdf->SetFont('Arial','B',$main_font_size);
  $value = $spolupracujici;
  $x = $pdf->GetX();
  $y = $pdf->GetY();
  $pdf->SetXY($pdf->GetX() - $column_width,$pdf->GetY() + $padding_top + 2 + $line_height);
  $pdf->MultiCell($column_width - $padding_right, 5, $value, 0, L);
  
  $pdf->SetFont('Arial','',$main_font_size);
  $label = 'Schvalovatelé:';
  $pdf->Text($pdf->GetX(),$pdf->GetY() + $padding_top, $label);
  $pdf->SetFont('Arial','B',$main_font_size);
  $value = $schvalovatele;
  $pdf->SetXY($x - $column_width,$pdf->GetY() + $padding_top + 2);
  $pdf->MultiCell($column_width - $padding_right, 5, $value, 0, L);
}
else
{
  $pdf->SetFont('Arial','',$main_font_size);
  $pdf->Cell($column_width,$cell_height,'',RB,0,L);
  $label = 'Před vypravením:';
  $pdf->Text($pdf->GetX() - $column_width,$pdf->GetY() + $padding_top, $label);
  $pdf->SetFont('Arial','B',$main_font_size);
  $value = $pred_vypravenim;
  $x = $pdf->GetX();
  $y = $pdf->GetY();
  $pdf->SetXY($pdf->GetX() - $column_width,$pdf->GetY() + $padding_top + 4 );
  $pdf->MultiCell($column_width - $padding_right, 0, $value, 0, L);
 
}


$pdf->SetXY($x, $y);
$pdf->SetFont('Arial','',$main_font_size);
$pdf->Cell($column_width,$cell_height,'',LB,1,L);
$label = 'Po vypravení:';
$pdf->Text($pdf->GetX() + $column_width + $padding_left,$pdf->GetY() - $cell_height + $padding_top, $label);
$pdf->SetFont('Arial','B',$main_font_size);
$value = $po_vypraveni;
$x = $pdf->GetX();
$y = $pdf->GetY();
$pdf->SetXY($pdf->GetX() + $column_width + $padding_left,$pdf->GetY() - $cell_height + $padding_top + 2);
$pdf->MultiCell(0, 5, $value, 0, L);

// 8.radek
$cell_height = 60;
$pdf->SetXY($x, $y);
$pdf->SetFont('Arial','',$main_font_size);
$pdf->Cell($column_width,$cell_height,'',R,0,L);
$label = 'Ukládací značka: ';
$label_width = $pdf->GetStringWidth($label);
$pdf->Text($pdf->GetX() - $column_width,$pdf->GetY()  - $cell_height + $padding_top + $line_height * 8, $label);
$label = 'Spisový znak: ';
$label_width = $pdf->GetStringWidth($label);
$pdf->Text($pdf->GetX() - $column_width,$pdf->GetY()  - $cell_height + $padding_top + $line_height * 8 + 24, $label);
$label = 'Skartační lhůta: ';
$label_width = $pdf->GetStringWidth($label);
$pdf->Text($pdf->GetX() - $column_width,$pdf->GetY()  - $cell_height + $padding_top + $line_height * 8 + 40, $label);


$pdf->SetFont('Arial','B',$main_font_size);
$value = $skartace_text;

$pdf->SetXY($x, $y + $padding_top + 5);
$pdf->MultiCell($column_width, 3, $ukl_znacka_text , 0);
$pdf->SetXY($x, $y + 25 + $padding_top);
$pdf->MultiCell($column_width, 4, $skartace_text , 0);
$pdf->SetXY($x, $y + 45 + $padding_top);
$pdf->MultiCell($column_width, 4, $skartace_lhuta_text, 0);
$pdf->SetXY($x + $column_width, $y);

$pdf->SetFont('Arial','B',$main_font_size);
$pdf->Cell($column_width,$cell_height,'',L,1,L);
$label = 'Výpravna:';
$pdf->Text($pdf->GetX() + $column_width + $padding_left,$pdf->GetY() - $cell_height + $padding_top, $label);

$pdf->SetFont('Arial','',$main_font_size);
$label = 'Vypraveno: ';
$label_width = $pdf->GetStringWidth($label);
$pdf->Text($pdf->GetX() + $column_width + $padding_left,$pdf->GetY() - $cell_height + $padding_top + $line_height, $label);
$pdf->SetFont('Arial','B',$main_font_size);
$value = $vypraveno_text;
$pdf->Text($pdf->GetX() + $column_width + $padding_left + $label_width, $pdf->GetY() - $cell_height + $padding_top + $line_height, $value);

$pdf->SetFont('Arial','',$main_font_size);
$label = 'Převzal: ';
$label_width = $pdf->GetStringWidth($label);
$pdf->Text($pdf->GetX() + $column_width + $padding_left,$pdf->GetY() - $cell_height + $padding_top + $line_height * 2, $label);
$pdf->SetFont('Arial','B',$main_font_size);
$value = $prevzal;
$pdf->Text($pdf->GetX() + $column_width + $padding_left + $label_width, $pdf->GetY() - $cell_height + $padding_top + $line_height * 2, $value);

$pdf->SetFont('Arial','B',$main_font_size);
$label = 'Spisovna:';
$pdf->Text($pdf->GetX() + $column_width + $padding_left,$pdf->GetY() - $cell_height + $padding_top + $line_height * 3, $label);

$pdf->SetFont('Arial','',$main_font_size);
$label = 'Založeno: ';
$label_width = $pdf->GetStringWidth($label);
$pdf->Text($pdf->GetX() + $column_width + $padding_left,$pdf->GetY() - $cell_height + $padding_top + $line_height * 4, $label);
$pdf->SetFont('Arial','B',$main_font_size);
$value = $zalozeno;
$pdf->Text($pdf->GetX() + $column_width + $padding_left + $label_width, $pdf->GetY() - $cell_height + $padding_top + $line_height * 4, $value);

$pdf->SetFont('Arial','',$main_font_size);
$label = 'Popis spisu: ';
$label_width = $pdf->GetStringWidth($label);
$pdf->Text($pdf->GetX() + $column_width + $padding_left,$pdf->GetY() - $cell_height + $padding_top + $line_height * 5, $label);
$pdf->SetFont('Arial','B',$main_font_size);
$value = $popis_spisu;
$pdf->Text($pdf->GetX() + $column_width + $padding_left + $label_width, $pdf->GetY() - $cell_height + $padding_top + $line_height * 5, $value);

$pdf->SetFont('Arial','',$main_font_size);
$label = 'ref. archů: ';
$label_width = $pdf->GetStringWidth($label);
$pdf->Text($pdf->GetX() + $column_width + $padding_left + 45,$pdf->GetY() - $cell_height + $padding_top + $line_height * 5, $label);
$pdf->SetFont('Arial','B',$main_font_size);
$value = $ref_arch;
$pdf->Text($pdf->GetX() + $column_width + $padding_left + 45 + $label_width, $pdf->GetY() - $cell_height + $padding_top + $line_height * 5, $value);

$pdf->SetFont('Arial','',$main_font_size);
$label = 'exh., přil.: ';
$label_width = $pdf->GetStringWidth($label);
$pdf->Text($pdf->GetX() + $column_width + $padding_left + 45,$pdf->GetY() - $cell_height + $padding_top + $line_height * 6, $label);
$pdf->SetFont('Arial','B',$main_font_size);
$value = $nevim;
$pdf->Text($pdf->GetX() + $column_width + $padding_left + 45 + $label_width, $pdf->GetY() - $cell_height + $padding_top + $line_height * 6, $value);

/*
$pdf->SetXY(15,30);
$pdf->SetFont('Arial','',16);
$pdf->Cell(20,6,'Spisová značka: ',0,0,'L',0);
$pdf->SetXY(15,36);
$pdf->SetXY(15,36);
$pdf->SetFont('Arial','B',26);
$pdf->Cell(180,10,$cislo_spisu,0,1,'C',1); //cj

$pdf->SetXY(15,60);
$pdf->SetFont('Arial','',16);
$pdf->Cell(22,6,'Předmět řízení: ',0,0,'L',0);
$pdf->SetXY(15,66);
$pdf->SetFont('Arial','B',20);
$pdf->SetXY(15,67);
$pdf->MultiCell(180,8,$vec_dopisu,0,'C',1); //vec

$pdf->SetXY(15,100);
$pdf->SetFont('Arial','',16);
$pdf->Cell(20,6,'Odbor: ',0,0,'L',0);
$pdf->SetXY(15,106);
$pdf->SetFont('Arial','B',20);
$pdf->Cell(80,10,$zkratka_odboru,0,1,'L',1); //oddelni

$pdf->SetXY(105,100);
$pdf->SetFont('Arial','',16);
$pdf->Cell(20,6,'Skartační znak, lhůta, rok: ',0,0,'L',0);
$pdf->SetXY(105,106);
$pdf->SetFont('Arial','B',20);
$pdf->Cell(90,10,$skartace_text,0,1,'L',1); //skart. lhuta

$pdf->SetXY(15,140);
$pdf->SetFont('Arial','',16);
$pdf->Cell(22,6,'Prvotní adresát: ',0,0,'L',0);
$pdf->SetFont('Arial','B',12);
$pdf->SetXY(15,147);
//$pdf->Cell(180,10,$prvotni_adresat,0,1,'L',1);
$pdf->MultiCell(180,6,$prvotni_adresat,0,'L',1); //od

$pdf->SetXY(15,165);
$pdf->SetFont('Arial','',16);
$pdf->SetFillColor(225,225,225);
$pdf->Cell(22,6,'Účastníci řízení: ',0,0,'L',0);

$pdf->SetXY(15,171);
//$pdf->Cell(180,109,'',0,0,'C',1);
$pdf->SetFont('Arial','',8);
$pdf->SetXY(15,170);
$pdf->MultiCell(180,4,$DALSI_ADRESATI,0,'L',1);
$pdf->SetFillColor(255,255,255);




//Table with 20 rows and 4 columns
//$pdf->SetWidths(array(5,15,15,65,15,55,15,25,34,1,1));
//srand(microtime()*1000000);
$pdf->SetFont('Arial','B',6);
//$pdf->Row(array('Sm','č.p.','č.j.','datum','Odesílatel/Adresát','Věc','Odbor','Vyřízeno','Skar','rekomando/poąta'));
*/


$pdf->Output('spisobalka.pdf','D');
