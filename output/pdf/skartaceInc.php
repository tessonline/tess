<?php
define(FPDF_FONTPATH,GetAgendaPath('POSTA',false,false).'/lib/pdf/font2/');
require(GetAgendaPath('POSTA',false,false).'/lib/pdf/fpdf.php');
require(GetAgendaPath('POSTA',false,false).'/lib/pdf/mc_table.php');

  class PDF_Podaci_Kniha extends PDF_MC_Table
  {
    //Page header
    function Header()
    {
        global $mesic,$rok;
        $this->SetFont('Arial','',8);
        //$this->Cell(190,8,,0,0,C);
        $this->Cell(0,8,'Protokol pro skartační řízení '.$GLOBALS["CONFIG"]["URAD"].' '.$GLOBALS["CONFIG"]["MESTO"],0,0,'R');
        $this->Ln(5);
    }
    //Page footer
    function Footer() {
        $this->SetY(-8);
        $this->SetFont('Arial','',8);
        $datum=Date("d.m.Y v H:i:s");
        $this->Cell(0,8,'Stránka '.$this->PageNo().' / {nb}, tisk dne '.$datum,0,0,'R');
    }
    function CheckPageBreak($h)
    {
    	//If the height h would cause an overflow, add a new page immediately
    	if($this->GetY()+$h>$this->PageBreakTrigger)
    	{
      	$this->AddPage($this->CurOrientation);
        //$this->Row(array('jednací číslo','nazev','Rok vznikuku','Sk.znak a lhůta','Místo uložení','Pozn.o trvalém vyřazení'));
        $this->Row(array('','čj.','Název','Rok uzavření','Pův.znak','Lhůta','Listů','přílohy','Dig.'));
      }
    }
    function Row_Storno($data,$storno)
    {
    	//Calculate the height of the row
    	$nb=0;
    	for($i=0;$i<count($data);$i++)
    		$nb=max($nb,$this->NbLines($this->widths[$i],$data[$i]));
    	$h=3*$nb;
    	$puv_x=$this->GetX();
    	//Issue a page break first if needed
    	$this->CheckPageBreak($h);
    	//Draw the cells of the row
    	for($i=0;$i<count($data);$i++)
    	{
    		$w=$this->widths[$i];
    		$a=isset($this->aligns[$i]) ? $this->aligns[$i] : 'L';
    		//Save the current position
    		$x=$this->GetX();
    		$y=$this->GetY();
    		//Draw the border
    		$this->Rect($x,$y,$w,$h);
    		//Print the text
    		$this->MultiCell($w,3,$data[$i],0,$a);
    		//Put the position to the right of the cell
    		$this->SetXY($x+$w,$y);
    	}
    	$nov_x=$this->GetX();
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
    $res="";
    If ($id && $id2 && $id3)
    {
      $sqlxx="select datum_podatelna_prijeti from posta where cislo_jednaci1=".$id." and cislo_jednaci2=".$id2." and id<>$id3 ORDER BY ev_cislo";
      $b=new DB_POSTA;
      $b->query ($sqlxx);
      while($b->next_record())
      {
         $DATUM=$b->Record["DATUM_PODATELNA_PRIJETI"];
      }
    }
    else
    {
      $DATUM='neni';
    }
    $res=$DATUM;
    return $res;
  }

  FUnction Skartace($skartace)
  {
    $res="";
    If ($skartace>0)
    {
      $a=new DB_POSTA;
      $sql='select skar_znak, doba, text from cis_posta_skartace where id='.$skartace;
      $a->query($sql);
      $a->Next_Record();
      $text_skartace=str_replace('STARE - ','',$a->Record["TEXT"]);
      $text=substr($text_skartace,0,strpos($text_skartace,' '));
      //$res=$text." ".$a->Record["SKAR_ZNAK"]."/".$a->Record["DOBA"];
      $res=array($text,$a->Record['SKAR_ZNAK'],$a->Record['DOBA']);
    }
    return $res;
  }




function GenerujSkartacniProtokol($_POST, $text='') {

  if (!strpos($_POST['sql'], 'FROM posta_spisovna s LEFT JOIN cis_posta_skartace k' ))
    $_POST['sql'] = str_replace('SELECT s.* FROM posta_spisovna s ', 'SELECT s.* FROM posta_spisovna s LEFT JOIN cis_posta_skartace k ON s.skartace_id = k.id ',$_POST['sql']);

  $sqla0=str_replace('WHERE ','WHERE (k.skar_znak like \'%A%\' OR (k.skar_znak like \'%V%\' and s.skar_znak_alt like \'%A%\')) AND ',$_POST['sql']);
  $sqls0=str_replace('WHERE ','WHERE (k.skar_znak like \'%S%\' OR (k.skar_znak like \'%V%\' and s.skar_znak_alt like \'%S%\')) AND ',$_POST['sql']);
  $sqlv0=str_replace('WHERE ','WHERE k.skar_znak like \'%V%\' AND ',$_POST['sql']);

  $sqla=substr($sqla0,0,strpos($sqla0,'ORDER BY'));
  $sqla=$sqla." ORDER BY s.skartace_id ASC, s.cislo_spisu2 ASC, s.cislo_spisu1 ASC";
  $sqla2=substr($sqla0,0,strpos($sqla0,'ORDER BY'));
  $sqla2=$sqla2." ORDER BY s.cislo_spisu2 ASC, s.cislo_spisu1 ASC";

  $sqls=substr($sqls0,0,strpos($sqls0,'ORDER BY'));
  $sqls=$sqls." ORDER BY s.skartace_id ASC, s.cislo_spisu2 ASC, s.cislo_spisu1 ASC"; //dle skartace
  $sqls2=substr($sqls0,0,strpos($sqls0,'ORDER BY'));
  $sqls2=$sqls2." ORDER BY s.cislo_spisu2 ASC, s.cislo_spisu1 ASC"; //dle cisel jednacich

  $sqlv=substr($sqlv0,0,strpos($sqlv0,'ORDER BY'));
  $sqlv=$sqlv." ORDER BY s.skartace_id ASC, s.cislo_spisu2 ASC, s.cislo_spisu1 ASC"; //dle skartace
  $sqlv2=substr($sqlv0,0,strpos($sqlv0,'ORDER BY'));
  $sqlv2=$sqlv2." ORDER BY s.cislo_spisu2 ASC, s.cislo_spisu1 ASC"; //dle cisel jednacich

  set_time_limit(0);

  $superodbor="";
  //if ($GLOBALS['SUPERODBOR']) $superodbor='AND SUPERODBOR IN ('.$GLOBALS['SUPERODBOR'].')';
  //$where=" WHERE rok=".$ROK." ".$superodbor." ORDER by cislo_jednaci1";

  //$sql.=$where;
  //echo $sql;
  //Die();
  $sql=$_POST['sql'];
  $q=new DB_POSTA;

  //$pdf=new PDF_MC_Table('P','mm','A3');
  $pdf=new PDF_Podaci_Kniha('P','mm','A4');
  $pdf->AliasNbPages();
  $pdf->Open();
  $pdf->SetMargins(10,5);
  //$pdf->AddPage();
  $pdf->AddFont('arial','','arial.php');
  $pdf->AddFont('arial','B','arialb.php');

  if ($_POST['pismeno'] == 'S') $sql = $sqls;
  if ($_POST['pismeno'] == 'A') $sql = $sqla;
  if ($_POST['pismeno'] == 'V') $sql = $sqlv;

  $q->query($sql);

  $pismeno = $_POST['pismeno'];

  $celkovy_pocet=$q->Num_Rows();

  if ($celkovy_pocet>0) {
    $pdf->AddPage();
    $pdf->SetFont('Arial','B',14);
    if (strlen($text)>1)
      $pdf->Cell(150,10, $text, 0,1);
    else
      $pdf->Cell(150,10,'Seznam navrhovaných dokumentů skupiny '.$pismeno.' dle spisových znaků:',0,1);
    $pdf->SetFont('Arial','',7);
    $pdf->SetWidths(array(8,33,56,20,15,12,12,20,12));
    $i=0;
    $skartace_id=0; $prvni=true;
    $pocet_listu_celkem=0;
    while($q->next_record()) {
      if ($skartace_id<>$q->Record['SKARTACE_ID']) {
        if (!$prvni) {
          $pdf->SetFont('Arial','B',9);
          $pdf->Cell(150,5,'Celkový počet předaných listů: '.$pocet_listu_celkem,0,1);
          $pocet_listu_celkem=0;
        }
        $prvni=false;
        $skar_pole=Skartace_Pole($q->Record['SKARTACE_ID']);
        $pdf->SetFont('Arial','B',9);
        $pdf->Cell(150,5,'',0,1);
        $pdf->Cell(150,5,$skar_pole['text'],0,1);
        $pdf->SetFont('Arial','B',8);
        $pdf->Row(array('','čj.','Název','Rok uzavření','Znak','Lhůta','Listů','přílohy','Dig.'));
        $pdf->SetFont('Arial','',8);
      }
      $i++;
      $id=$q->Record["ID2"];

      $TABLE_CONFIG["schema"][] =  array( "field"=>"DATUM_PREDANI", "label"=>"Datum předání", "width"=>"4%");
      $cj_obj = LoadClass('EedCj', $q->Record['DOKUMENT_ID']);
      $cj = $cj_obj->cislo_jednaci;

      $VEC=$q->Record["VEC"];

      $pdf->Row(array($i.'.',$cj,$VEC,$q->Record['ROK_PREDANI'],$q->Record['SKAR_ZNAK'],$q->Record['LHUTA'],$q->Record['LISTU'],str_replace('<br/>',chr(10).chr(13),$q->Record['PRILOHY']),$q->Record['DIGITALNI']));
      $skartace_id=$q->Record['SKARTACE_ID'];
      $pocet_listu_celkem=$pocet_listu_celkem+$q->Record['LISTU'];
    }
    $pdf->SetFont('Arial','B',9);
  //  $pdf->Cell(150,5,'Celkový počet předaných listů: '.$pocet_listu_celkem,0,1);

  }
  return $pdf;

}

