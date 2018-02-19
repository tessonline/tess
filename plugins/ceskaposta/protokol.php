<?php
require("tmapy_config.inc");
//require(FileUp2(".admin/run2_.inc"));
//require(FileUp2(".admin/brow_.inc"));

require("tmapy_config.inc");
include(FileUp2(".admin/brow_.inc"));
include(FileUp2(".admin/config.inc"));
include(FileUp2(".admin/security_obj.inc"));
include_once(FileUp2(".admin/oth_funkce.inc"));
define(FPDF_FONTPATH,GetAgendaPath('POSTA',false,false).'/lib/pdf/font2/');
require(GetAgendaPath('POSTA',false,false).'/lib/pdf/fpdf.php');
set_time_limit(0);
$file_name='pokus.pdf';
header("Expires: 0"); 
header("Cache-Control: must-revalidate, post-check=0, pre-check=0"); 
header("Pragma: public"); 
//header("Content-Type: text/html"); 
header("Content-Disposition: attachment; filename=$file_name"); 
header("Content-Transfer-Encoding: binary"); 
//header("<meta HTTP-EQUIV=\"Content-Type\" CONTENT=\"text/html; charset=windows-1250\">");


Function ShowCell($x,$y,$width,$text)
{
//MultiCell(float w, float h, string txt [, mixed border [, string align [, int fill]]]) 

}

class PDF extends FPDF
{
  //Page header
  function Header()
  {
     $this->SetFont('Arial','B',11);
      //Move to the right
     $this->SetXY(119,11);
     $this->Cell(48,4,"POŠTOVNÍ PODACÍ ARCH",0,0,C);
     $this->Ln(20);
  } 
  
  //Page footer
  function Footer()
  {
      //Position at 1.0 cm from bottom
      $this->SetY(-6);
      //Arial italic 8
      $this->SetFont('Arial','',6);
      //Page number
      $datum=Date("d.m.Y H:m");
      $this->Cell(0,3,'vytištěno v programu Evidence dokumentů, (c) T-MAPY spol. s r.o., www.tmapy.cz',0,0,'L');
      $this->Cell(0,3,'Stránka '.$this->PageNo().'/{nb}, tisk dne '.$datum,0,0,'R');
  }
}

//Instanciation of inherited class
$pdf=new PDF();
$pdf->AddFont('arial','','arial.php');
$pdf->AddFont('arial','B','arialb.php');
$pdf->AliasNbPages();
$pdf->AddPage('L');

$pdf->Ln();
//$pdf->SetFont('Arial','B',15');

$q=new DB_POSTA;
//$sql='select * from posta where id in (select pisemnost_id from posta_cis_ceskaposta_id where protokol_id='.$GLOBALS[PROTOKOL].') ORDER BY doporucene,cislo_spisu2,cislo_spisu1,datum_podatelna_prijeti';

//$sql='select * from posta where id in (select pisemnost_id from posta_cis_ceskaposta_id where protokol_id='.$GLOBALS[PROTOKOL].') ORDER BY doporucene,odbor,cislo_jednaci2,cislo_jednaci1,datum_podatelna_prijeti';
//$sql='select * from posta where id in (select pisemnost_id from posta_cis_ceskaposta_id where protokol_id='.$GLOBALS[PROTOKOL].') ORDER BY doporucene,hmotnost,odbor,cislo_jednaci2,cislo_jednaci1,datum_podatelna_prijeti';
$sql='select * from posta_cis_ceskaposta where id='.$GLOBALS[ID].'';
//Die($sql);
$q->query($sql);
$q->Next_Record(); $obyc1=$q->Record['OBYC1'];
$GLOBALS['datum_od']=$q->Record['DATUM_OD'];
$GLOBALS['datum_do']=$q->Record['DATUM_DO'];
$protokol=$q->Record['PROTOKOL'];

include('pdf_inc/tabulka.inc');
$pdf->SetXY(255.3,14.7);
$pdf->SetFont('Arial','',14);
$pdf->Cell(23.6,10.6,$GLOBALS[PROTOKOL],1,1,C);

$pdf->SetFont('Arial','',8);

/*
//Uprava datumu
$where="";
//$where.=" odbor IN (".$GLOBALS["ODBOR"].")";
$where.=" (DATUM_PODATELNA_PRIJETI) >= ('".$GLOBALS["DATUM_OD"]."',) AND (DATUM_PODATELNA_PRIJETI) <= ('".$GLOBALS["DATUM_DO"]."',)";

//jen odeslane pisemnosti
$where.=" AND odeslana_posta='t'";
//jen pisemnosti na ceskou postu
$where.=" AND vlastnich_rukou='1'";
//jen dokuemnty, ktere jsou zvazene?parametr v configu
If ($GLOBALS["CONFIG"]["CPOST_VAZIT"]) $where.=" AND hmotnost is not null";
//a ktere tedy obalky, hle obycejne se tam neeviduji
$where2=" AND ((doporucene='2') or (doporucene='3') or (doporucene='4') or (doporucene='5'))";
$where3=" AND (doporucene='Z')";

If ($GLOBALS["ODBOR"]<>'')
  $where.=" AND odbor IN (".$GLOBALS["ODBOR"].")";
	
UNSET($GLOBALS["ODBOR"]);
$q=new DB_POSTA;

If ($GLOBALS["CONFIG"]["CPOST_VAZIT"]) 
  $sql='select * from posta where '.$where.$where2.' ORDER BY xertec_id';
else
  $sql='select * from posta where '.$where.$where2.' ORDER BY doporucene,datum_podatelna_prijeti';
*/

//echo $sql;
//Die();
//$q->query($sql);
$a=1;
$cena_celkem=0;
$hmotnostCD0=0;
$hmotnostCD1=0;
$hmotnostCD2=0;
$hmotnostCD3=0;
$hmotnostCD4=0;
$hmotnostCD5=0;
$hmotnostCD6=0;

//Die($GLOBALS['datum_od']);
$sql="select * from posta where id in (select pisemnost_id from posta_cis_ceskaposta_id where protokol_id=".$protokol.") and doporucene<>'1' ORDER BY xertec_id,doporucene,cislo_jednaci2,cislo_jednaci1 asc";
//Die($sql);
$q->query($sql);

    $pdf->SetXY(185,185);
    $pdf->Cell(15,4,$zasilek,0,0,L);

If ($GLOBALS[c1]) {$pocitame=true; $cislood=$GLOBALS[c1];}
$stranka=1;
//vypiseme postu, ktera neni zahranici, ta musi byt az na konci
while ($q->Next_Record())
{
	If (($a>13)or($puvodni<>$q->Record["DOPORUCENE"] && $puvodni=='C')or($puvodni<>$q->Record["DOPORUCENE"] && $q->Record["DOPORUCENE"]=='C' && $stranka>1))
//	If ($a>15)
	{
	  //dalsi stranka
    $pdf->SetFont('Arial','B',10);
    $cena_souhrn=$cena_souhrn+$cena_celkem;
    $zasilek=$zasilek+$a-1;
  
    $pdf->SetXY(185,169);
    $pdf->Cell(15,4,$zasilek,0,0,L);
    $pdf->SetXY(196.3,169);
    $pdf->Cell(19,4,' ',0,0,C);
     
    if ($cena_souhrn==0)
      $pdf->Cell(20,4,'',0,0,C);
    else     
      $pdf->Cell(20,4,number_format($cena_souhrn,2,',',''),0,0,C);

    $pdf->SetXY(185,162);
    $pdf->Cell(15,8,$a-1,0,0,L);
    $pdf->SetXY(205,162);
    
    if ($cena_celkem==0)
      $pdf->Cell(41,8,'',0,0,C);
    else
      $pdf->Cell(41,8,number_format($cena_celkem,2,',',''),0,0,C);
    $pdf->SetFont('Arial','B',10);


    $pdf->Cell(20,8,' ',0,0,C);
    $pdf->AddPage('L');
		$pdf->Ln();
		include('pdf_inc/tabulka.inc');
    $pdf->SetXY(255.3,14.7);
	  $stranka++;
    $pdf->Cell(23.6,10.6,$GLOBALS[PROTOKOL].' (str. '.$stranka.')',1,1,C);
	  $a=1;
    $pdf->SetXY(10,51);
    $pdf->SetFont('Arial','',8);
		$cena_celkem=0;
	}


  $b=($a*8)+50;
  //zjistime, zda nepresahl pocet na dorucenky, pokud jo, pak nastavime na c3
  If ($cislood>$GLOBALS[c2] && $GLOBALS[c2]) $cislood=$GLOBALS[c3];

  $pdf->SetXY(10,$b);

  If ($GLOBALS[c1] && $q->Record["DOPORUCENE"]<>'C') $pdf->Cell(27,8,$cislood,1,0,C);
  else
  $pdf->Cell(27,8,'',1,0,C);
  $pdf->SetXY(37,$b+1);
  $pdf->MultiCell(47,3,$q->Record["ODESL_PRIJMENI"].' '.$q->Record["ODESL_JMENO"],'L','L');
  $pdf->SetXY(84,$b+1);
  $pdf->MultiCell(35,3,substr($q->Record["ODESL_PSC"],0,3).' '.substr($q->Record["ODESL_PSC"],3,2).'  '.$q->Record["ODESL_POSTA"],'L','L');
  $pdf->SetXY(119,$b+1);
  $ulice=$q->Record["ODESL_ULICE"]." ";
  If ($q->Record["ODESL_CP"] && $q->Record["ODESL_COR"]) $ulice.=$q->Record["ODESL_CP"].'/'.$q->Record["ODESL_COR"];
  If ($q->Record["ODESL_CP"] && !$q->Record["ODESL_COR"]) $ulice.=$q->Record["ODESL_CP"];
  If (!$q->Record["ODESL_CP"] && $q->Record["ODESL_COR"]) $ulice.=$q->Record["ODESL_COR"];
  
  $pdf->MultiCell(41,3,$ulice,'L','L');

	$hmotnost=$q->Record["HMOTNOST"];
  $pdf->SetXY(160,$b);
	$hmotnost_kg=floor($hmotnost/1000);
	$hmotnost_g=$hmotnost-($hmotnost_kg*1000);

  if ($hmotnost_kg==0)
    $pdf->MultiCell(7,8,'',0,'C');
  else
    $pdf->MultiCell(7,8,$hmotnost_kg,0,'C');
  
  $pdf->SetXY(167,$b);
  if ($hmotnost_g==0)
    $pdf->MultiCell(10,8,'',0,'C');
  else
    $pdf->MultiCell(10,8,$hmotnost_g,0,'C');
	
  $pdf->SetXY(177,$b);
  $pdf->MultiCell(14,8,'',0,'C');
  $pdf->SetXY(191,$b);
  $pdf->MultiCell(7,8,'');
  $pdf->SetXY(196.3,$b);
  $pdf->Cell(19,8,' ',1,0,C);
	$cena=$q->Record["CENA"];
	$cena_celkem=$cena_celkem+$cena;
  if ($cena==0)
      $pdf->Cell(20,8,'',0,0,C);
  else
    $pdf->Cell(20,8,number_format($cena,2,',',''),0,0,C);
  $pdf->Cell(20,8,' ',1,0,C);
  
  If ($q->Record["DOPORUCENE"]=='C') {$text='';$cislood--;}
  If ($q->Record["DOPORUCENE"]=='2') $text='R';
  If ($q->Record["DOPORUCENE"]=='3') $text='D';
  If ($q->Record["DOPORUCENE"]=='4') $text='DR';
  If ($q->Record["DOPORUCENE"]=='5') $text='DZ';

  If ($q->Record["OBALKA_NEVRACET"]>0) $text.=' SA';
  If ($q->Record["OBALKA_10DNI"]>0) $text.=' UX';

  
  $doc = LoadSingleton('EedDokument', $q->Record['ID']);
  $cj = $doc->cislo_jednaci;

  $pdf->SetFont('Arial','B',8);
  $pdf->Cell(23.6,4,$text,0,0,C);
  $pdf->SetXY(255.3,$b+4);
  $pdf->SetFont('Arial','',6);
  $pdf->Cell(23.6,4,$cj,0,0,C);
  $pdf->SetFont('Arial','',8);

  
  $cislood++;
  
  $puvodni=$q->Record["DOPORUCENE"];
  
  $a++;
}

$pdf->SetFont('Arial','B',10);
  $b=($a*8)+50;
  $pdf->SetXY(37,$b+1);
  $pdf->MultiCell(47,3,$obyc1.' obyčejných zásilek','L','L');


$cena_souhrn=$cena_souhrn+$cena_celkem;
$zasilek=$zasilek+$a-1;
$pdf->SetXY(185,169);
$pdf->Cell(15,4,$zasilek,0,0,L);
$pdf->SetXY(196.3,169);
$pdf->Cell(19,4,' ',0,0,C);
$pdf->Cell(20,4,number_format($cena_souhrn,2,',',''),0,0,C);

$pdf->SetXY(185,162);
$pdf->Cell(15,8,$a-1,0,0,L);
$pdf->SetXY(205,162);
$pdf->Cell(41,8,number_format($cena_celkem,2,',',''),0,0,C);


$pdf->SetFont('Arial','',8);
$pdf->SetXY(10,178);
$pdf->Cell(41,3,'Formální správnost dokladu - vyplňuje pracovník, pokladny:  __________________________',0,0,L);
$pdf->SetXY(10,184);
$pdf->Cell(41,3,'Datum, jméno, příjmení, funkce a podpis správce fin. plánu: __________________________',0,0,L);
$pdf->SetXY(150,178);
$pdf->Cell(41,3,'Datum, jméno, příjmení, funkce a podpis náměstka ekon.úseku:  __________________________',0,0,L);
$pdf->SetXY(150,184);
$pdf->Cell(41,3,'Datum, jméno, příjmení, funkce a podpis příkazce operace: _____________________________',0,0,L);

$pdf->SetXY(185,178);
//else
//  $pdf->Cell(20,8,'',0,0,C);
//$pdf->Cell(20,8,$cena_celkem,0,0,C);

//number_format($number, 2, ',', ' ');
$pdf->Cell(20,8,' ',0,0,C);

//echo $sql;
/*
//v novem roce se jiz nepouyiva

//spocitame obycejny obalky
$where="";
$q->query("select * from posta_cis_ceskaposta where protokol=".$GLOBALS["PROTOKOL"]);
$q->Next_Record();

$datum_od=$q->Record["DATUM_OD"];
$datum_do=$q->Record["DATUM_DO"];
$odbor=$q->Record["ODBOR"];
If ($GLOBALS["CONFIG"]["DB"]=='psql')
{
  $where.=" (DATUM_PODATELNA_PRIJETI) >= ('".$datum_od."',)";
  $where.=" AND (DATUM_PODATELNA_PRIJETI) <= ('".$datum_do."',)";
}
If ($GLOBALS["CONFIG"]["DB"]=='mssql')
{
  $where.=" CONVERT(datetime,datum_podatelna_prijeti,104)>CONVERT(datetime,'".$datum_od." 00:00',104)";
  $where.=" AND CONVERT(datetime,datum_podatelna_prijeti,104)<CONVERT(datetime,'".$datum_do." 23:59',104)";
}
$where.=" AND stornovano is null";
//jen odeslane pisemnosti
$where.=" AND odeslana_posta='t'";
//jen pisemnosti na ceskou postu
$where.=" AND vlastnich_rukou='1'";
//jen dokuemnty, ktere jsou zvazene?parametr v configu
If ($GLOBALS["CONFIG"]["CPOST_VAZIT"]) $where.=" AND hmotnost is not null";

$sql='select * from posta where '.$where;
//Die($sql);
$q->query($sql);
$a=1;
while ($q->Next_Record())
{
	$hmotnost=$q->Record["HMOTNOST"];
  $druh_zasilky=$q->Record["DRUH_ZASILKY"];  

  If ($q->Record["DOPORUCENE"]=='1')
  { 
  	If ($hmotnost<21 && $druh_zasilky==3) $hmotnostCO1++; //psani za obyc cenu
  	If ($hmotnost<21 && $druh_zasilky<>3) $hmotnostCO1a++; //drazi psani
  	If ($hmotnost>20 && $hmotnost<51) $hmotnostCO2++;
  	If ($hmotnost>50 && $hmotnost<201) $hmotnostCO3++;
  	If ($hmotnost>200 && $hmotnost<501) $hmotnostCO4++;
  	If ($hmotnost>500 && $hmotnost<1001) $hmotnostCO5++;
  	If ($hmotnost>1000) $hmotnostCO6++;
  	$hmotnostCO0++;
  }
  elseif ($q->Record["DOPORUCENE"]=='Z') 
  {
   	If ($hmotnost<11) $hmotnostZD1++;
  	If ($hmotnost>10 && $hmotnost<21) $hmotnostZD2++;
  	If ($hmotnost>20 && $hmotnost<51) $hmotnostZD3++;
  	If ($hmotnost>50 && $hmotnost<201) $hmotnostZD5++;
   	If ($hmotnost>200 && $hmotnost<501) $hmotnostZD6++;
  	If ($hmotnost>500 && $hmotnost<1001) $hmotnostZD7++;
  	If ($hmotnost>1000) $hmotnostZD8++;
  	$hmotnostZD0++;
  }
  else
  {
  	If ($hmotnost<21) $hmotnostCD1++;
  	If ($hmotnost>20 && $hmotnost<51) $hmotnostCD2++;
  	If ($hmotnost>50 && $hmotnost<201) $hmotnostCD3++;
  	If ($hmotnost>200 && $hmotnost<501) $hmotnostCD4++;
  	If ($hmotnost>500 && $hmotnost<1001) $hmotnostCD5++;
  	If ($hmotnost>1000) $hmotnostCD6++;
  	$hmotnostCD0++;
  }  
  

}


$hmotnostCO1=$hmotnostCO1+$GLOBALS[OBYC1];
$hmotnostCO1a=$hmotnostCO1a+$GLOBALS[OBYC2];

$pdf->AddPage('P');
$pdf->Ln();

$pdf->SetXY(10,20);

$pdf->SetFont('Arial','B',14);
$pdf->Cell(180,10,'Výkaz o počtu a skladbě podaných zásilek',0,1,'C');

$pdf->SetFont('Arial','',8);
//$pdf->Cell(200,10,'Datum: '.$date('d.M.Y'),0,0,'L');
$pdf->Cell(150,6,'Česká pošta, s.p., IČ 47114983',0,0,'L');
$pdf->Cell(30,6,'Datum: '.date('d.m.Y'),0,1,'L');
$pdf->Cell(180,6,'Podací pošta: '.$GLOBALS["CONFIG"]["MESTO"],0,1,'L');
$pdf->SetFont('Arial','B',10);
$pdf->Cell(180,6,'Uživatel: '.$GLOBALS["CONFIG"]["URAD"].' '.$GLOBALS["CONFIG"]["MESTO"],0,1,'L');
$pdf->SetFont('Arial','',8);
$pdf->Cell(180,6,'Způsob úhrady: ..................................',0,1,'L');

$pdf->Cell(180,6,'',0,1,'L');


$pdf->Cell(170,0.3,'',1,1,C);
$pdf->SetFont('Arial','B',10);
$pdf->Cell(50,6,'Vnitrostátní zásilky',1,0,C);
$pdf->Cell(20,6,'ks',1,0,C);
$pdf->Cell(50,6,'Mezinárodní zásilky',1,0,C);
$pdf->Cell(15,6,'Evropa',1,0,C);
$pdf->Cell(35,6,'ostatní země',1,1,C);

$pdf->SetFont('Arial','',6);
$pdf->Cell(50,4,'Počet zásilek',1,0,C);
$pdf->Cell(20,4,'ks',1,0,C);
$pdf->Cell(50,4,'Počet zásilek',1,0,C);
$pdf->Cell(15,4,'ks',1,0,C);
$pdf->Cell(15,4,'ks - prioritní',1,0,C);
$pdf->Cell(20,4,'ks - ekonomické',1,1,C);

$pdf->Cell(170,0.3,'',1,1,C);

$pdf->SetFont('Arial','',8);
$pdf->Cell(50,8,'Obyč. standard.psaní do 20g',1,0,L);
$pdf->SetFont('Arial','B',12);
$pdf->Cell(20,8,$hmotnostCO1,1,0,C);
$pdf->SetFont('Arial','',8);
$pdf->Cell(50,8,'Obyčejná zásilka do 10g',1,0,L);
$pdf->Cell(15,8,'',1,0,C);
$pdf->Cell(15,8,'',1,0,C);
$pdf->Cell(20,8,'',1,1,C);

$pdf->Cell(50,8,'Ostatní obyč.psaní do 20g',1,0,L);
$pdf->SetFont('Arial','B',12);
$pdf->Cell(20,8,$hmotnostCO1a,1,0,C);
$pdf->SetFont('Arial','',8);
$pdf->Cell(50,8,'                            do 20g',1,0,L);
$pdf->Cell(15,8,'',1,0,C);
$pdf->Cell(15,8,'',1,0,C);
$pdf->Cell(20,8,'',1,1,C);

$pdf->Cell(50,8,'Obyčejné psaní do 50g',1,0,L);
$pdf->SetFont('Arial','B',12);
$pdf->Cell(20,8,$hmotnostCO2,1,0,C);
$pdf->SetFont('Arial','',8);
$pdf->Cell(50,8,'                            do 50g',1,0,L);
$pdf->Cell(15,8,'',1,0,C);
$pdf->Cell(15,8,'',1,0,C);
$pdf->Cell(20,8,'',1,1,C);

$pdf->Cell(50,8,'                          do 200g',1,0,L);
$pdf->SetFont('Arial','B',12);
$pdf->Cell(20,8,$hmotnostCO3,1,0,C);
$pdf->SetFont('Arial','',8);
$pdf->Cell(50,8,'                            do 100g',1,0,L);
$pdf->Cell(15,8,'',1,0,C);
$pdf->Cell(15,8,'',1,0,C);
$pdf->Cell(20,8,'',1,1,C);

$pdf->Cell(50,8,'                          do 500g',1,0,L);
$pdf->SetFont('Arial','B',12);
$pdf->Cell(20,8,$hmotnostCO4,1,0,C);
$pdf->SetFont('Arial','',8);
$pdf->Cell(50,8,'                            do 250g',1,0,L);
$pdf->Cell(15,8,'',1,0,C);
$pdf->Cell(15,8,'',1,0,C);
$pdf->Cell(20,8,'',1,1,C);

$pdf->Cell(50,8,'                          do 1kg',1,0,L);
$pdf->SetFont('Arial','B',12);
$pdf->Cell(20,8,$hmotnostCO5,1,0,C);
$pdf->SetFont('Arial','',8);
$pdf->Cell(50,8,'                            do 500g',1,0,L);
$pdf->Cell(15,8,'',1,0,C);
$pdf->Cell(15,8,'',1,0,C);
$pdf->Cell(20,8,'',1,1,C);

$pdf->Cell(50,8,'                          do 2kg',1,0,L);
$pdf->SetFont('Arial','B',12);
$pdf->Cell(20,8,$hmotnostCO6,1,0,C);
$pdf->SetFont('Arial','',8);
$pdf->Cell(50,8,'                            do 1kg',1,0,L);
$pdf->Cell(15,8,'',1,0,C);
$pdf->Cell(15,8,'',1,0,C);
$pdf->Cell(20,8,'',1,1,C);

$pdf->Cell(50,8,'',1,0,L);
$pdf->Cell(20,8,'',1,0,C);
$pdf->Cell(50,8,'                            do 2kg',1,0,L);
$pdf->Cell(15,8,'',1,0,C);
$pdf->Cell(15,8,'',1,0,C);
$pdf->Cell(20,8,'',1,1,C);

$pdf->Cell(170,0.3,'',1,1,C);

$pdf->Cell(50,12,'Obyčejné psaní celkem',1,0,L);
$pdf->SetFont('Arial','B',12);
$pdf->Cell(20,12,$hmotnostCO0,1,0,C);
$pdf->SetFont('Arial','',8);
$pdf->Cell(50,12,'Obyčejné psaní celkem',1,0,L);
$pdf->Cell(15,12,'',1,0,C);
$pdf->Cell(15,12,'',1,0,C);
$pdf->Cell(20,12,'',1,1,C);

$pdf->Cell(50,8,'',1,0,L);
$pdf->Cell(20,8,'',1,0,C);
$pdf->Cell(50,8,'Obyčejný tiskovinový pytel',1,0,L);
$pdf->Cell(15,8,'',1,0,C);
$pdf->Cell(15,8,'',1,0,C);
$pdf->Cell(20,8,'',1,1,C);

$pdf->Cell(170,0.3,'',1,1,C);

//druhá sloka

$pdf->Cell(50,8,'Doporučená zásilka do 20g',1,0,L);
$pdf->SetFont('Arial','B',12);
$pdf->Cell(20,8,$hmotnostCD1,1,0,C);
$pdf->SetFont('Arial','',8);
$pdf->Cell(50,8,'Doporučená zásilka do 10g',1,0,L);
$pdf->SetFont('Arial','B',12);
$pdf->Cell(15,8,$hmotnostZD1,1,0,C);
$pdf->SetFont('Arial','',8);
$pdf->Cell(15,8,'',1,0,C);
$pdf->Cell(20,8,'',1,1,C);

$pdf->Cell(50,8,'                                 do 50g',1,0,L);
$pdf->SetFont('Arial','B',12);
$pdf->Cell(20,8,$hmotnostCD2,1,0,C);
$pdf->SetFont('Arial','',8);
$pdf->Cell(50,8,'                                 do 20g',1,0,L);
$pdf->SetFont('Arial','B',12);
$pdf->Cell(15,8,$hmotnostZD2,1,0,C);
$pdf->SetFont('Arial','',8);
$pdf->Cell(15,8,'',1,0,C);
$pdf->Cell(20,8,'',1,1,C);

$pdf->Cell(50,8,'                                 do 200g',1,0,L);
$pdf->SetFont('Arial','B',12);
$pdf->Cell(20,8,$hmotnostCD3,1,0,C);
$pdf->SetFont('Arial','',8);
$pdf->Cell(50,8,'                                 do 50g',1,0,L);
$pdf->SetFont('Arial','B',12);
$pdf->Cell(15,8,$hmotnostZD3,1,0,C);
$pdf->SetFont('Arial','',8);
$pdf->Cell(15,8,'',1,0,C);
$pdf->Cell(20,8,'',1,1,C);

$pdf->Cell(50,8,'                                 do 500g',1,0,L);
$pdf->SetFont('Arial','B',12);
$pdf->Cell(20,8,$hmotnostCD4,1,0,C);
$pdf->SetFont('Arial','',8);
$pdf->Cell(50,8,'                                 do 100g',1,0,L);
$pdf->SetFont('Arial','B',12);
$pdf->Cell(15,8,$hmotnostZD4,1,0,C);
$pdf->SetFont('Arial','',8);
$pdf->Cell(15,8,'',1,0,C);
$pdf->Cell(20,8,'',1,1,C);

$pdf->Cell(50,8,'                                 do 1kg',1,0,L);
$pdf->SetFont('Arial','B',12);
$pdf->Cell(20,8,$hmotnostCD5,1,0,C);
$pdf->SetFont('Arial','',8);
$pdf->Cell(50,8,'                                 do 250g',1,0,L);
$pdf->SetFont('Arial','B',12);
$pdf->Cell(15,8,$hmotnostZD5,1,0,C);
$pdf->SetFont('Arial','',8);
$pdf->Cell(15,8,'',1,0,C);
$pdf->Cell(20,8,'',1,1,C);

$pdf->Cell(50,8,'                                 do 2kg',1,0,L);
$pdf->SetFont('Arial','B',12);
$pdf->Cell(20,8,$hmotnostCD6,1,0,C);
$pdf->SetFont('Arial','',8);
$pdf->Cell(50,8,'                                 do 500g',1,0,L);
$pdf->SetFont('Arial','B',12);
$pdf->Cell(15,8,$hmotnostZD6,1,0,C);
$pdf->SetFont('Arial','',8);
$pdf->Cell(15,8,'',1,0,C);
$pdf->Cell(20,8,'',1,1,C);

$pdf->Cell(50,8,'',1,0,L);
$pdf->Cell(20,8,'',1,0,C);
$pdf->Cell(50,8,'                                 do 1kg',1,0,L);
$pdf->SetFont('Arial','B',12);
$pdf->Cell(15,8,$hmotnostZD7,1,0,C);
$pdf->SetFont('Arial','',8);
$pdf->Cell(15,8,'',1,0,C);
$pdf->Cell(20,8,'',1,1,C);

$pdf->Cell(50,8,'',1,0,L);
$pdf->Cell(20,8,'',1,0,C);
$pdf->Cell(50,8,'                                 do 2kg',1,0,L);
$pdf->SetFont('Arial','B',12);
$pdf->Cell(15,8,$hmotnostZD8,1,0,C);
$pdf->SetFont('Arial','',8);
$pdf->Cell(15,8,'',1,0,C);
$pdf->Cell(20,8,'',1,1,C);

$pdf->Cell(170,0.3,'',1,1,C);

$pdf->Cell(50,12,'Doporučené psaní celkem',1,0,L);
$pdf->SetFont('Arial','B',12);
$pdf->Cell(20,12,$hmotnostCD0,1,0,C);
$pdf->SetFont('Arial','',8);
$pdf->Cell(50,12,'Doporučené psaní celkem',1,0,L);
$pdf->SetFont('Arial','B',12);
$pdf->Cell(15,12,$hmotnostZD0,1,0,C);
$pdf->SetFont('Arial','',8);
$pdf->Cell(15,12,'',1,0,C);
$pdf->Cell(20,12,'',1,1,C);

$pdf->Cell(50,8,'',1,0,L);
$pdf->Cell(20,8,'',1,0,C);
$pdf->Cell(50,8,'Doporučený tiskovinový pytel',1,0,L);
$pdf->Cell(15,8,'',1,0,C);
$pdf->Cell(15,8,'',1,0,C);
$pdf->Cell(20,8,'',1,1,C);

$pdf->Cell(170,0.3,'',1,1,C);

$pdf->Cell(170,30,'',0,1,C);

$pdf->SetFont('Arial','',8);
$pdf->Cell(170,3,'................................................................',0,1,R);
$pdf->Cell(150,3,'razítko, podpis',0,1,R);

$pdf->SetXY(9.8,60);
$pdf->Cell(170.4,179.3,'',1,0,C);

$pdf->SetXY(79.8,60);
$pdf->Cell(0.2,179.3,'',1,0,C);
*/

$pdf->Output();

?>

