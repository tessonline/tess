<?php
//anna faris
require("tmapy_config.inc");
include(FileUp2(".admin/brow_.inc"));

include(FileUp2(".admin/config.inc"));
include(FileUp2(".admin/status.inc"));
include_once(FileUp2(".admin/security_name.inc"));
include(FileUp2(".admin/oth_funkce.inc"));
include_once(FileUp2('.admin/oth_funkce_2D.inc'));
include_once(FileUp2('interface/.admin/soap_funkce.inc'));
require_once(Fileup2("html_header.inc"));
//echo Date('d.m.Y H:i:s').'<br/>';

// define(FPDF_FONTPATH,GetAgendaPath('POSTA',false,false).'/lib/pdf/font2/');
// require(GetAgendaPath('POSTA',false,false).'/lib/pdf/fpdf.php');
// require(GetAgendaPath('POSTA',false,false).'/lib/pdf/mc_table.php');

function WriteLogEss($log) {
//echo $log.'<br/>';
/*
  $datum=Date('d.m.Y H:i:s');
  $tmp = '/tmp/logESS.txt';
  $text = $datum . '-'.$log.chr(10);
  $fp = fopen($tmp, 'a');
  fwrite($fp, $text);
  fclose($fp);
*/
}

require(GetAgendaPath('POSTA',false,false).'/lib/tcpdf/mc_table.php');

set_time_limit(0);
$datum = Date("d.m.Y v H:i");


class PDF_Podaci_Kniha extends PDF_MC_Table {
  //Page header
  function Header() {
      global $datum;
      $this->SetFont('freeserif','i',8);
      //$this->Cell(190,8,,0,0,C);
//      $this->Cell(0,3,'Podací deník',0,0,'R');
      $this->Cell(0,3,'Podací deník '.TxtEncoding4Soap($GLOBALS["CONFIG"]["URAD"].' '.$GLOBALS["CONFIG"]["MESTO"]).'              Strana '.$this->PageNo().' / '. $this->getAliasNbPages().', tisk dne '.$datum,0,0,'R');
      $this->Ln(10);
  } 
  //Page footer
  function Footer() {
      global $datum;
//      $this->Cell(0,8,'Podací deník '.$GLOBALS["CONFIG"]["URAD"].' '.$GLOBALS["CONFIG"]["MESTO"].'              Stránka '.$this->PageNo().' / {nb}, tisk dne '.$datum,0,0,'R');
  }

  function Row_Storno($data,$storno) {
    $h = 0;
    for ($i=0 ; $i<count($data) ; $i++) {
    	$hTmp = $this->getStringHeight($this->widths[$i], $data[$i]);
    	$h = max($h, $hTmp);
    }

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
    $this->SetFont('freeserif','B',6);
    $this->Cell(($nov_x-$puv_x),($h/2)-1,strip_tags($storno),0,0,'C');
    $this->SetFont('freeserif','',6);
  	$this->setXY($puv_x,$y);
  	//Go to the next line
  	$this->Ln($h);
  }

    function CheckPageBreak($h)
    {
        //If the height h would cause an overflow, add a new page immediately
        if($this->GetY()+$h>$this->PageBreakTrigger) {
            $this->AddPage();
            $this->Row(array('Směr','Pořad. č. / JID','Datum doručení / Datum vytvoření','Odesílatel/Adresát','Čj. odesilatele','Stručný obsah dokumentu (věc)','Spis.uzel / Zpracovatel','Spis','Způsob vyřízení',
            'Počet listů','Počet příloh a druh','Spis. znak a skart. režim','JID vypravení','Datum vypravení','Spisovna / Vyřazení', 'Poznámka'));
        }
    }

}



//$sql = "SELECT * from posta_view_spisy "; 
$sql = "SELECT max(cislo_spisu1) as max, min(cislo_spisu1) as min from posta_view_spisy ";
//$where = " WHERE ((odeslana_posta = 'f' ) or (odeslana_posta = 't' and (id_puvodni = 0 or id_puvodni is null))) and rok = ".$rok." ORDER by cislo_jednaci1";

$superodbor = "";
if ($GLOBALS['SUPERODBOR']) $superodbor = 'AND SUPERODBOR IN ('.$GLOBALS['SUPERODBOR'].')';
$where = " WHERE cislo_spisu2 = ".$ROK." ";
//$where = " WHERE EXTRACT(YEAR FROM datum_podatelna_prijeti) = ".$ROK." ";

if ($GLOBALS['MESIC']) {
//  $where.= " AND (datum_podatelna_prijeti like '%.".$GLOBALS['MESIC'].".$ROK%' OR datum_podatelna_prijeti like '%.0".$GLOBALS['MESIC'].".$ROK%') ";
  $where.= " AND EXTRACT(MONTH FROM datum_podatelna_prijeti) = ". $GLOBALS['MESIC'];
}

$sql .= $where;
WriteLogEss($sql);
// $q = new DB_POSTA;
// $w = new DB_POSTA;
$q = new DB_POSTA;
$w = new DB_POSTA;

$q->query($sql);
$q->Next_Record();
$celkovy_pocet = $q->Record['MAX'] ? $q->Record['MAX'] : 0;
$od = $GLOBALS['MESIC'] ? $q->Record['MIN'] : 1;

//Die('Celkovy pocet je '. $celkovy_pocet);
//echo '<div id = "upl_wait_message" class = "text" style = "display:block">Hotovo záznamů: 0/'.$celkovy_pocet.'</div>';
Flush();

//$pdf = new PDF_MC_Table('P','mm','A3');
$pdf = new PDF_Podaci_Kniha('L', 'mm', 'A3', true, 'UTF-8', true, true);

$page_format = array(
    'MediaBox' => array ('llx' => 0, 'lly' => 0, 'urx' => 420, 'ury' => 297),
    'Dur' => 3,
    'trans' => array(
        'D' => 1.5,
        'S' => 'Split',
        'Dm' => 'V',
        'M' => 'O'
    ),
    'Rotate' => 0,
    'PZ' => 1,
);


//$pdf->AliasNbPages();
//$pdf->setPageFormat($page_format, 'L');
$pdf->SetMargins(5,5,5);

//$pdf->AddPage($page_format);
$pdf->AddPage();


//$pdf->AddPage($page_format);
//$pdf->AddFont('freeserif','','freeserif.php');
//$pdf->AddFont('freeserif','B','freeserifb.php');

$pdf->SetFont('freeserif','B',40);
$pdf->SetXY(1,80);
$pdf->Cell(280,25,'Podací deník',0,1,'C');
$pdf->SetFont('freeserif','',24);
$pdf->SetXY(1,100);
$pdf->Cell(280,20,'za rok '.$ROK,0,1,'C');
$pdf->SetXY(1,160);
$pdf->Cell(280,20,TxtEncoding4Soap($CONFIG["URAD"]),0,1,'C');
$pdf->SetXY(1,180);
$pdf->Cell(280,20,TxtEncoding4Soap(trim($CONFIG["MESTO"])),0,1,'C');
    $datum = Date("d.m.Y");

$pdf->SetFont('freeserif','',16);
$pdf->SetXY(1,240);
$pdf->Cell(280,20,'dne '.$datum,0,1,'C');
$pdf->SetXY(1,250);
$pdf->Cell(280,20,'celkový počet stránek: ' . $pdf->getAliasNbPages(),0,1,'C');

$pdf->AddPage();
//$pdf->AddPage();
//Table with 20 rows and 4 columns
$pdf->SetWidths(array(7,21,20,56,25,45,25,20,30,13,17,20,22,23,20,42));
//$pdf->SetWidths(array(5,15,15,65,15,55,15,25,34,1,1));
//srand(microtime()*1000000);
$pdf->SetFont('freeserif','B',6);
//$pdf->Row(array('Sm','č.p.','č.j.','datum','Odesílatel/Adresát','Věc','Odbor','Vyřízeno','Skar','rekomando/poąta'));
//$pdf->Row(array('Sm','Pořad. číslo','Datum doručení / Datum vzniku','Odesílatel/Adresát','Čj. odesilatele','Věc','Spis.uzel / Zpracovatel','Způsob vyřízení','Počet listů','Spis. a skar. znak','Spisovna / Vyřazení'));
$pdf->Row(array('Směr','Pořad. č. / JID','Datum doručení / Datum vytvoření','Odesílatel/Adresát','Čj. odesilatele','Stručný obsah dokumentu (věc)','Spis.uzel / Zpracovatel','Spis', 'Způsob vyřízení',
'Počet listů','Počet příloh a druh','Spis. znak a skart. režim','JID vypravení','Datum vypravení','Spisovna / Vyřazení', 'Poznámka'));
$pdf->SetFont('freeserif','',6);

//$cj1 = 1;
//$celkovy_pocet = 100;
for ($cj1 = $od; $cj1<= $celkovy_pocet; $cj1++) {
  if (!$cj1) break;
  WriteLogEss('zpracovavam '.$cj1. '- pocet '.$cj1.'/'.$celkovy_pocet);
  $evidence = 0;
  $stornovano = '';
  $sqla = "select * from posta where cislo_spisu1 = ".$cj1." and cislo_spisu2 = ".$ROK." ".$superodbor." and (kopie=0 or kopie is null) order by podcislo_spisu asc,id";
  $w->query($sqla);
  if ($w->Num_Rows()>0) {
//    $w->Next_Record();
//    echo $cj1.' v spisovce';
    $evidence = 1;
  }
  else {
    $sqla = "select * from posta_h where cislo_spisu1 = ".$cj1." and cislo_spisu2 = ".$ROK." ".$superodbor." order by id asc limit 1";
//echo $sqla.'<br/>';
    WriteLogEss($sqla);
    $q->query($sqla);
    if ($q->Num_Rows()>0) {
      $q->Next_Record();

      $id = $q->Record['ID'] ? $q->Record['ID'] : 0;
      $sqla = "select * from posta where id = ".$id." ".$superodbor." order by id asc limit 1";
//echo $sqla.'<br/>';
      $q->query($sqla);
      if ($q->Num_Rows()>0) {
  
//        echo $cj1.' preevidovano';
        $q->Next_Record();
        $sqla = "select * from posta where id = ".$id." ".$superodbor." order by id asc limit 1";
        $w->query($sqla);
        $evidence = 1;
        $stornovano = "čj. bylo přeevidováno";
        $stornovano = "přeevidováno pod čj. ".$w->Record['CISLO_SPISU1']."/".$w->Record['CISLO_SPISU2'];
      }
    }
  }  
  if ($evidence == 0) {
    $sqla = "select * from posta_stare_zaznamy where cislo_jednaci1 = ".$cj1." and cislo_jednaci2 = ".$ROK." ".$superodbor." order by id asc limit 1";
    WriteLogEss($sqla);
    $w->query($sqla);
    if ($w->Num_Rows()>0) {
      $w->Next_Record();
  //    echo $cj1.' v spisovce';
      $stornovano = "uloženo v historii";
      $evidence = 1;
    }
  }
  if ($evidence ==  1){
    while ($w->Next_Record()) {
//    echo ' - hotovo<br/>';
  
    $data_dokument = $w->Record;

    $main_doc = $data_dokument['ID'];
  
      if ($data_dokument['CISLO_SPISU1'] <> $cj1) {
         $stornovano = "přeevidováno pod čj. ".$data_dokument['CISLO_SPISU1']."/".$data_dokument['CISLO_SPISU2'];
      }


    $id = $data_dokument["ID"];
    $vazba = '';
    $id_puvodni = '';
    $poznamka = TxtEncoding4Soap($data_dokument["POZNAMKA"]);
    $id = $id?$id:0;
 
    $ODESILATEL = TxtEncoding4Soap(UkazAdresu($id,', '));

    $datum_odpovedi = array();
    $id_odpovedi = array();
    if ($data_dokument['ODESLANA_POSTA'] == 'f') {
      $sql = "select * from posta where odeslana_posta='t' and cislo_spisu1 = ".$cj1." and cislo_spisu2 = ".$ROK." ".$superodbor." order by id asc";
      WriteLogEss($sql);
      $q->query($sql);
      while ($q->Next_Record()) {
        if ($q->Record['ODESLANA_POSTA'] == 't') {
          $datum_odpovedi[] = $q->Record['DATUM_VYPRAVENI'];
          $id_odpovedi[] = $GLOBALS['CONFIG']['ID_PREFIX'].$q->Record['ID'];
        }
        $id_puvodni = $GLOBALS['CONFIG']['ID_PREFIX'].$q->Record['ID'];
      }
    }
    $smer = "<";
    If ($data_dokument["ODESLANA_POSTA"] == "f") {$smer = ">"; $vazba = $id_puvodni;}
    If ($data_dokument["ODES_TYP"] == "Z") {$smer = "o";}
    $poradove_cislo = $cj1;
    if ($data_dokument['PODCISLO_SPISU']>0 && $stornovano=='') $poradove_cislo .= '-' . $data_dokument['PODCISLO_SPISU'];
    if ($data_dokument['PODCISLO_SPISU']>0 && $data_dokument['EXEMPLAR']>0 && $stornovano=='') $poradove_cislo .= '-' . $data_dokument['EXEMPLAR'];



    $doc = LoadSingleton('EedSpisovnaSimple', $id);
    $poradove_cislo .= chr(10).chr(13) . $doc->barcode;
    $je_spis = false;

    if ($doc->spis_id <> $id) {
      $spis = $doc->GetCjInfo($id);
      if ($spis['JE_SPIS'] == 1) $je_spis = true;
      $spis_id = $spis['SPIS_ID'];
      $doc = LoadSingleton('EedSpisovnaSimple', $spis_id);
      $id = $spis_id;
    }
     $cj = $doc->GetCjInfo($id);
      $spis = $cj['CELY_NAZEV'];

    $skartace_id = $doc->skartace;

    $VEC = TxtEncoding4Soap($data_dokument["VEC"]);

      //$datum = substr($data_dokument["DATUM_PODATELNA_PRIJETI"],0,strpos($data_dokument["DATUM_PODATELNA_PRIJETI"]," "));
      $datum = $data_dokument["DATUM_PODATELNA_PRIJETI"] ? $data_dokument["DATUM_PODATELNA_PRIJETI"] : ($q->dbdate2str($data_dokument["LAST_DATE"]).' ' . $data_dokument['LAST_TIME']);

    If ($data_dokument["DOBA"]<>"") {$znak .= '/'.$data_dokument["DOBA"];}

    if ($doc->spisZnakKod)
      $znak = $doc->spisZnakKod . "
" . $doc->spisZnakPismeno . "/" . $doc->spisZnakLhuta;

    $rekomando = $data_dokument["ODESL_REKOMANDO"];
    $jejich_cj = TxtEncoding4Soap($data_dokument["JEJICH_CJ"]);
    $odbor = TxtEncoding4Soap($doc->uzel_text.'
'. $doc->referent_text);

    If ($data_dokument["ODESL_POSTAODESL"]<>"") {$rekomando .= '/'.$data_dokument["ODESL_POSTAODESL"];}
    $vyrizeno = '';


    if ($data_dokument["DATUM_VYRIZENI"]) $vyrizeno .= $data_dokument["DATUM_VYRIZENI"];
    if ($data_dokument["VYRIZENO"]) $vyrizeno .= '
' . $data_dokument["VYRIZENO"];

    if ($je_spis) {
      $vyrizeno = $spis['CELY_NAZEV'];
      if($data_dokument["SPIS_VYRIZEN"]) $vyrizeno .= '
uzavřeno ' . $q->dbdate2str($data_dokument["SPIS_VYRIZEN"]);
    }
//    $priloh = ($data_dokument["POCET_PRILOH"] == 0)?'':$data_dokument["POCET_PRILOH"];


    if ($data_dokument['SPISOVNA_ID']>0 || $data_dokument['SPISOVNA_ID'] == '0')
      $spisovna = $doc->JeVeSpisovne();
    else
      $spisovna = array();
    $vyrizeno = TxtEncoding4Soap($vyrizeno);
    $spisovna_text='';
    if ($spisovna['DATUM_PREDANI']<>'')
      $spisovna_text=$q->dbdate2str($spisovna['DATUM_PREDANI']);
    if ($spisovna['DATUM_SKARTACE']<>'')
      $spisovna_text.="
vyřazeno:
".$q->dbdate2str($spisovna['DATUM_SKARTACE']);
    $listu=$doc->spisListu;
    $priloh = $doc->spisPriloh;
    if ($spisovna['ROK_SKARTACE']<>'')
    {
      if ($spisovna['LISTU']) $listu=$spisovna['LISTU'].'
';
      if ($spisovna['DIGITALNI']) $priloh.='Digitálně: '.$spisovna['DIGITALNI'].'
';
      if ($spisovna['PRILOHY']) $priloh.=''.$spisovna['PRILOHY'];


      $priloh=str_replace('<br/>',"
",$priloh);
    }
    else {
      $listu = $data_dokument['POCET_LISTU'];
      $priloh = TxtEncoding4Soap($data_dokument['POCET_PRILOH'].'
' . $data_dokument['DRUH_PRILOH']);
    }

    $znak=$znak."
".$spisovna['ROK_SKARTACE'];

    if ($spisovna['PREEVIDOVANO'])  {
       $spisovna_text = $spisovna['PREEVIDOVANO'];
       $priloh = '';
       $znak = '';
       $stornovano = 'vyřizuje se v '.$spisovna['PREEVIDOVANO'];
    }
    If ($data_dokument["STORNOVANO"]<>'')  $stornovano = TxtEncoding4Soap($data_dokument["STORNOVANO"]);
    if ($stornovano<>'' )
    	$pdf->Row_Storno(array($smer,$poradove_cislo,$datum,$ODESILATEL."\n\r \n\r \n\r",$jejich_cj,$VEC,$odbor,$spis,$vyrizeno,$listu,$priloh,$znak,implode(chr(10).chr(13),$id_odpovedi),implode(chr(10).chr(13),$datum_odpovedi), $spisovna_text, $poznamka),$stornovano);
    else
    	$pdf->Row(array($smer,$poradove_cislo,$datum,$ODESILATEL,$jejich_cj,$VEC,$odbor,$spis,$vyrizeno,$listu, $priloh,$znak,implode(chr(10).chr(13),$id_odpovedi),implode(chr(10).chr(13),$datum_odpovedi), $spisovna_text, $poznamka));

    $spisovna_text = '';
    $priloh = '';
    $znak = '';
    $stornovano = '';
    }

    UNSET($doc); //uvolnime pamet
  }
}
//echo Date('d.m.Y H:i:s').'<br/>';

//echo "<script>document.getElementById('upl_wait_message').innerHTML = '<b>Hotovo záznamů: ".$celkovy_pocet."/".$celkovy_pocet."</b>'</script>";
echo '<script> HiddenTime();</script>';
//include(FileUp2('.admin/upload_fce_.inc'));


$file = $GLOBALS[CONFIG_POSTA][HLAVNI][tmp_adresar].'denik-' . date('Ymdhis').'.pdf';
$filename = basename($file);
//Die();
$pdf->Output($file,'F');
//echo "<script>document.getElementById('upl_wait_message2').style.display = 'none'</script>";
echo TxtEncodingFromSoap("<h1>Vytvořen soubor $filename. <a href='getfile.php?file=$filename'>Klikněte pro jeho stažení</a>.</h1>");
require_once(Fileup2("html_footer.inc"));


