<?php

if ($_POST['tisk']) $tisk=true; else $tisk=false;
$GLOBALS['stranek_pdf']=0;
set_time_limit(0);

class PDF_Podaci_Kniha extends PDF_MC_Table
{
  //Page header
  function Header()
  {
      global $mesic,$rok;
      $this->SetFont('Arial','I',8);
      //$this->Cell(190,8,,0,0,C);
      $this->Cell(0,3,'PP pro spisovnu',0,0,'R');
      $this->Ln(5);
  } 
  //Page footer
  function Footer()
  {
      $this->SetY(-8);
      $this->SetFont('Arial','',8);
      $datum=Date("d.m.Y v H:m");
      $this->Cell(0,8,'PP pro spisovnu '.$GLOBALS["CONFIG"]["URAD"].' '.$GLOBALS["CONFIG"]["MESTO"].'              Stránka '.$this->PageNo().' / {nb}, tisk dne '.$datum,0,0,'R');
     $GLOBALS['stranek_pdf']=$GLOBALS['stranek_pdf']+1;
  }
  function CheckPageBreak($h)
  {
  	//If the height h would cause an overflow, add a new page immediately
  	if($this->GetY()+$h>$this->PageBreakTrigger)
  	{
    	$this->AddPage($this->CurOrientation);
//      $this->Row(array('jednací číslo','nazev','Rok vzniku','Sk.znak a lhůta','Listů','Místo uložení','Pozn.o trvalém vyřazení'));
      $this->Row(array('jednací číslo','nazev','Datum','Sk.znak a lhůta','Listů','Digitální','Přílohy','Ukl.značka'));
      //$this->Row(array('jednací číslo','nazev','Rok vznikuku','Sk.znak a lhůta','Místo uložení','Pozn.o trvalém vyřazení'));
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
Function VyrizenoNPU($id,$id2,$id3,$smer)
{
  $res="";
  If ($id && $id2 && $id3)
  {
    $sqlxx="select datum_podatelna_prijeti from posta where cislo_spisu1=".$id." and cislo_spisu2=".$id2." and id<>$id3 ORDER BY ev_cislo";
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

FUnction SkartaceNPU($skartace)
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
//    $res=$text." ".$a->Record["SKAR_ZNAK"]."/".$a->Record["DOBA"];
    $res=array($text,$a->Record['SKAR_ZNAK'],$a->Record['DOBA']);

  }
  return $res;
}
/*
$rok=$GLOBALS["ROK"];$mesic=$GLOBALS["MESIC"];
// limit 50,50
$sql="SELECT max(cislo_jednaci1) as max_cj from posta where rok=".$rok;
$q->query($sql);
$q->Next_Record();
 $max_cj=$q->Record["MAX_CJ"];
//$where=" WHERE (odeslana_posta='f' and rok=".$rok." and datum_podatelna_prijeti like '%.".$mesic.".%') or (odeslana_posta='t' and (id_puvodni=0 or id_puvodni is null) and rok=".$rok." and datum_podatelna_prijeti like '%.".$mesic.".%') ORDER by ev_cislo";
*/


//$sql="SELECT * from posta ";
//$where=" WHERE ((odeslana_posta='f' ) or (odeslana_posta='t' and (id_puvodni=0 or id_puvodni is null))) and rok=".$rok." ORDER by cislo_jednaci1";

$superodbor="";
//if ($GLOBALS['SUPERODBOR']) $superodbor='AND SUPERODBOR IN ('.$GLOBALS['SUPERODBOR'].')';
//$where=" WHERE rok=".$ROK." ".$superodbor." ORDER by cislo_jednaci1";

//$sql.=$where;
$sql=$_POST['sql'];
$q=new DB_POSTA;
$a=new DB_POSTA;
//echo $sql;
$q->query($sql);
$celkovy_pocet=$q->Num_Rows();

//$pdf=new PDF_MC_Table('P','mm','A3');
$pdf=new PDF_Podaci_Kniha('P','mm','A4');
$pdf->AliasNbPages();
$pdf->Open();
$pdf->SetMargins(10,15);
$pdf->AddPage();
$pdf->AddFont('arial','','arial.php');
$pdf->AddFont('arial','B','arialb.php');

$pdf->SetFont('Arial','B',20);
$pdf->SetXY(1,25);
$pdf->Cell(200,25,'Předávací protokol dokumentů k uložení do spisovny',0,1,'C');


$protokol = LoadClass('EedProtokol', 0);
if ($tisk) $cislo_protokolu = $protokol->ZalozNovyProtokol('PPSP');
if ($tisk) $protokol_id = $protokol->protokol_id;

$pdf->SetFont('Arial','',12);
$pdf->SetXY(85,20);
$pdf->Cell(80,10,'Číslo protokolu: ', 0, 1, 'L');
if ($tisk) $pdf->Code39(120,20,$cislo_protokolu,1,8);
$pdf->SetXY(120,45);
$pdf->Cell(80,10,'celkový počet stránek: {nb}',0,1,'L');

$znacka = LoadClass('EedZnacka', 0);
//$pdf->AddPage();
//Table with 20 rows and 4 columns
$pdf->SetWidths(array(25,60,15,20,10,10,20,25));
//$pdf->SetWidths(array(5,15,15,65,15,55,15,25,34,1,1));
//srand(microtime()*1000000);
$pdf->SetFont('Arial','B',7);
//$pdf->Row(array('Sm','č.p.','č.j.','datum','Odesílatel/Adresát','Věc','Odbor','Vyřízeno','Skar','rekomando/poąta'));
$pdf->Row(array('Jednací číslo','Název','Datum','Sk.znak a lhůta','Listů','Digitální','Přílohy','Ukl.značka'));
$pdf->SetFont('Arial','',7);
$pocet_digitalnich=0;$prilohy_celkem=array();
while($q->next_record()) {
  $i++;

  $cj=$q->Record["CISLO_JEDNACI1"];
  $pocetl=$q->Record['POCET_LISTU'];
   list($znak,$pismeno,$lhuta)=SkartaceNPU($q->Record["SKARTACE"]);
 //  $znak=Skartace($q->Record["SKARTACE"]);    
  //spocitame pocet listu
  $pocet_listu_celkem=0; $digitalni=0;$pocet_priloh_celkem=array(); $prilohy='';
  $spis1=$q->Record['CISLO_SPISU1'];
  $spis2=$q->Record['CISLO_SPISU2'];
  
  if ($spis1>0) {
    $where_spis="(cislo_spisu1=".$spis1." and cislo_spisu2=".$spis2.")";
    $dalsi_spisy= VyhledejDalsiSpisy($spis1."/".$spis2);
    while (list($key,$val)=each($dalsi_spisy)) {
      list($cj1,$cj2)=explode('/',$val['spis']);
      $where_spis.=" OR (cislo_spisu1=".$cj1." and cislo_spisu2=".$cj2.")";
    }
    if($GLOBALS['CONFIG']['USE_SUPERODBOR']) $sql="select id,typ_dokumentu,skartace,pocet_listu,pocet_priloh,druh_priloh from posta where (".$where_spis.") and superodbor in (".EedTools::VratSuperOdbor().") and stornovano is null order by id asc";
    else $sql="select id,typ_dokumentu,skartace,pocet_listu,pocet_priloh,druh_priloh from posta where (".$where_spis.") and stornovano is null order by id asc";
    $a->query ($sql);
    while($a->next_record()) {

      $pocet_l = $a->Record["POCET_LISTU"];
      $pocet_priloh = $a->Record["POCET_PRILOH"];
      $druh_priloh = $a->Record["DRUH_PRILOH"];
      $skartace[]=$a->Record['ID'];

      if ($tisk) $protokol->VlozIDSDoProtokolu($cislo_protokolu, array($a->Record['ID']));

      //$pocet_listu = $a->Record["POCET_LISTU"];
      $pocet_priloh = $a->Record["POCET_PRILOH"];
      $druh_priloh = trim($a->Record["DRUH_PRILOH"]);
      if ($a->Record['SKARTACE']==2398 || $a->Record['TYP_DOKUMENTU']=='D') {$pocet_l=0; $pocet_priloh=0;}//neni urceno ke skartaci
  //    if ($a->Record['SKARTACE']==2398 || $a->Record['TYP_DOKUMENTU']=='D' || $a->Record['ODES_TYP']=='X') {$pocet_l=0; $pocet_priloh=0;}//neni urceno ke skartaci
      if ($a->Record['TYP_DOKUMENTU']=='D' && $a->Record['SKARTACE']<>2398) {$digitalni++;}//neni urceno ke skartaci

      if ($a->Record["PRILOHY_ZAPOCITAT"]=='1') {
        $pocet_listu_celkem=$pocet_listu_celkem+$pocet_l;
        $pocet_priloh_celkem[$druh_priloh]=$pocet_priloh_celkem[$druh_priloh]+$pocet_priloh;
      }
    }
  }
  else {
   if ($tisk) $protokol->VlozIDSDoProtokolu($cislo_protokolu, array($q->Record['ID']));
  }

  $pocet_digitalnich=$pocet_digitalnich+$digitalni;
  $pocet_listu=$pocet_listu+$pocet_listu_celkem;
  while (list($key,$val)=each($pocet_priloh_celkem)) if ($val>0) {$prilohy.="$key: $val\n"; $prilohy_celkem[$key]=$prilohy_celkem[$key]+$val;}
  //If ($cj<>$oldcj)
  {
    $id=$q->Record["ID"];
    If ($q->Record["ODESLANA_POSTA"]=="f") {$smer=">";}
    $podaci_cislo=$q->Record["EV_CISLO"]."/".$q->Record["ROK"];

    $doc = LoadSingleton('EedDokument', $id);
    $CISLO_JEDNACI = $doc->cislo_jednaci;

    $ODESILATEL=UkazAdresu($id,', ');

    If ($q->Record["ODESLANA_POSTA"]=='t' && $q->Record["ID_PUVODNI"]=='') $ODESILATEL.='
VLASTNÍ DOKUMENT';
    If ($q->Record["ODES_TYP"]=='X') $ODESILATEL.='
VNITŘNÍ POŠTA';
    $VEC=$q->Record["VEC"];
    $datum=substr($q->Record["DATUM_PODATELNA_PRIJETI"],0,strpos($q->Record["DATUM_PODATELNA_PRIJETI"]," "));
//    $datum=$q->Record["DATUM_PODATELNA_PRIJETI"];
    $znak=$znak." - ".$pismeno."/".$lhuta;
    $cj1=$q->Record["CISLO_SPISU1"];
    $cj2=$q->Record["CISLO_SPISU2"];
    $so=$q->Record["SUPERODBOR"];
    If ($q->Record["DOBA"]<>"") {$znak.='/'.$q->Record["DOBA"];}
    $rekomando=$q->Record["ODESL_REKOMANDO"];
    $jejich_cj=$q->Record["JEJICH_CJ"];
    $odbor=UkazOdbor($q->Record["ODBOR"],true).' / '.UkazUsera($q->Record["REFERENT"],true);
    If ($q->Record["ODESL_POSTAODESL"]<>"") {$rekomando.='/'.$q->Record["ODESL_POSTAODESL"];}
    $vyrizeno='';
    $datum_vyr=VyrizenoNPU($cj1,$cj2,$id,$smer);
//    If (!$datum_vyr && $smer==">") $vyrizeno=($q->Record["ZPUSOB_VYRIZENI"]?$q->Record["ZPUSOB_VYRIZENI"]:'vzato na vědomí');
    $priloh=($q->Record["POCET_PRILOH"]==0)?'':$q->Record["POCET_PRILOH"];
    $poradove_cislo=$q->Record["CISLO_JEDNACI1"];
    $znackaNU = $znacka->GetZnackaNameProCJ($id);
//    $pdf->Row(array($CISLO_JEDNACI,$VEC,$datum,$pismeno,$pocetl,'',''));
    $pdf->Row(array($CISLO_JEDNACI,$VEC,$datum,$znak,$pocet_listu_celkem,$digitalni,$prilohy,$znackaNU[0]));
///    	$pdf->Row(array($smer,$poradove_cislo,$cislo_jednaci,$datum,$ODESILATEL,$jejich_cj,$VEC,$odbor,$vyrizeno,$datum_vyr,$priloh,$znak,''));
//    $oldcj=$q->Record["CISLO_JEDNACI1"];
  }
}
$pdf->Row(array('','protokol do spisovny',Date('d.m.Y'),'','{nb}','','',''));
//echo "<script>document.getElementById('upl_wait_message').innerHTML = '<b>Hotovo záznamů: ".($i-1)."/".$celkovy_pocet."</b>'</script>";
//include(FileUp2('.admin/upload_fce_.inc'));
//$dir_arr=GetUploadDir('POSTA',1);
//$filename='denik_'.$GLOBALS['SUPERODBOR'].'-'.$ROK.'.pdf';
//$file = $dir_arr[0].$dir_arr[1].$filename;


$pdf->SetFont('Arial','B',12);
$pdf->Cell(190,4.5,' ','C',1,L);

  $pdf->Cell(190,6,'Celkový počet předaných listů: '.($pocet_listu).' + {nb} ',0,1,L);

  $pdf->Cell(190,6,'Celkový počet předaných el. dokumentů: '.($pocet_digitalnich),0,1,L);

  $prilohy='';
  while (list($key,$val)=each($prilohy_celkem)) if ($val>0) {$prilohy.="$key: $val \n\r"; }
  $pdf->Cell(190,6,'Celkový počet předaných příloh: ',0,1,L);
  $pdf->SetFont('Arial','',12);
  $pdf->MultiCell(190,4.5,"".$prilohy,0,1,L);
  $pdf->SetFont('Arial','B',12);



  
  $pdf->Cell(190,25,'Datum předání: '.Date("d.m.Y"),0,1,L);
  
if ($tisk)
{
  $USER_INFO = $GLOBALS["POSTA_SECURITY"]->GetUserInfo();
  $REFERENT = $USER_INFO["ID"];
  
  $pdf->Cell(95,12,'Předal: '.UkazUsera($REFERENT),0,0,L);
  $pdf->Cell(95,12,'Podpis ...........................................',0,1,L);
  
  $pdf->Cell(95,12,'Převzal ..........................................',0,0,L);
  $pdf->Cell(95,12,'Podpis ...........................................',0,1,L);
  
  $pdf->Cell(95,12,'Schválil ..........................................',0,0,L);
  $pdf->Cell(95,12,'Podpis ...........................................',0,1,L);
  
  $stream=$pdf->Output($file,'S');
  
  //$pdf->Output();
  //echo $stream;
  //echo "<script>document.getElementById('upl_wait_message2').style.display = 'none'</script>";
  //echo "<span class=text>Vytvořen soubor $filename. <a href='getfile.php?file=$filename'>Klikněte pro jeho stažení</a>.</span>";
  //require_once(Fileup2("html_footer.inc"));
  
  $USER_INFO = $GLOBALS["POSTA_SECURITY"]->GetUserInfo();
  $id_user=$USER_INFO["ID"];
  $jmeno=$USER_INFO["FNAME"]." ".$USER_INFO["LNAME"];
  $LAST_USER_ID=$id_user;
  $LAST_TIME=Date('H:i:s');
  $LAST_DATE=Date('Y-m-d');
  
  if($GLOBALS['CONFIG']['USE_SUPERODBOR']) $sql='select * from posta where cislo_spisu1='.$cj1.' and cislo_spisu2='.$cj2.' and superodbor='.$so.' and main_doc=1 order by id asc';
  else $sql='select * from posta where cislo_spisu1='.$cj1.' and cislo_spisu2='.$cj2.' and main_doc=1 order by id asc';
  $a->query($sql);
  $a->Next_Record();$data=$a->Record;
  $data[ODDELENI] = $data[ODDELENI]?$data[ODDELENI]:0;  
  $data[ODBOR] = $data[ODBOR]?$data[ODBOR]:0;  
  $data[REFERENT] = $data[REFERENT]?$data[REFERENT]:0;
  $data[SUPERODBOR] = $data[SUPERODBOR]?$data[SUPERODBOR]:0;
  $data[SPIS_VYRIZEN] = $data[SPIS_VYRIZEN] ? $data[SPIS_VYRIZEN] : Date('Y-m-d');
  $sql="insert into posta (rok,odeslana_posta,odes_typ,typ_dokumentu,cislo_jednaci1,cislo_jednaci2,cislo_spisu1,cislo_spisu2,spis_vyrizen,vec,pocet_listu,odbor,oddeleni,referent,superodbor,datum_podatelna_prijeti,datum_doruceni,last_date,last_time,last_user_id,owner_id,id_puvodni,status)
  values (".Date('Y').",'t','Z','A',$cj1,$cj2,0,0,'$data[SPIS_VYRIZEN]','protokol předání do spisovny',$GLOBALS[stranek_pdf],$data[ODBOR],$data[ODDELENI],$data[REFERENT],$data[SUPERODBOR],'".Date('d.m.Y H:i')."','".Date('d.m.Y H:i')."','".$LAST_DATE."','".$LAST_TIME."',$LAST_USER_ID,$LAST_USER_ID,$data[ID],1)";
  $a->query($sql);
  $NOVEID=$a->getlastid('posta','ID');
  
  $uplobj_save=Upload(array('create_only_objects'=>true,'agenda'=>'POSTA','noshowheader'=>true));
  $val["NAME"] = "predavaci_protokol_do_spisovny.pdf";
  $tmp_soubor = $GLOBALS[CONFIG_POSTA][HLAVNI][tmp_adresar].$val["NAME"];
  $tmp_soubor_x = TxtEncoding4Soap($GLOBALS[CONFIG_POSTA][HLAVNI][tmp_adresar].$val["NAME"]);
  if (is_file($tmp_soubor_x)) unlink($tmp_soubor_x);
  $data=$stream;
  if (strlen($data)<1) return ShowError($session_id,'COPYFILES','Není k dispozici obsah souboru '.$val["NAME"]);
  if (!$fp=fopen($tmp_soubor_x,'w')) return ShowError($session_id,'COPYFILES','Chyba pri ulozeni tmp souboru '.$tmp_soubor);
  fwrite($fp,$data);
  fclose($fp);
  chmod($tmp_soubor_x,0777);
  $GLOBALS['DESCRIPTION'] = $val[FILE_DESC];
  $GLOBALS['LAST_USER_ID'] = $val[LAST_USER_ID];
  //echo "Ukladam ".$tmp_soubor_x." do ".$nove."<br/>";
  $ret = $uplobj_save['table']->SaveFileToAgendaRecord($tmp_soubor, $NOVEID);
  //    print_r($ret);
  if ($ret[err_msg]>0) return ShowError($session_id,'COPYFILES','Chyba pri ulozeni souboru '.$val["NAME"].': '.$ret[err_msg]);

}
else
{
  $pdf->SetFont('Arial','',10);
  $pdf->Cell(190,10,'Toto je náhled protokolu. Pro tisk včetně schvalovací doložky vyberte ve spisové a skartační knize volbu Tisk protokolu',0,1,L);
}
$pdf->Output();


Die('STOP');