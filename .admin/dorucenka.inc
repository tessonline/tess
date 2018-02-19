<?php
require(GetAgendaPath('POSTA',false,false).'/lib/tcpdf/tcpdf.php');

$obalka=array();
$odeslani=array();
while (list($key,$val)=each($GLOBALS["CONFIG"]["TYP_ODESLANI"])) {
  $obalka[$val['VALUE']] = $val['LABEL'];
}   

while (list($key,$val)=each($GLOBALS["CONFIG"]["DRUH_ODESLANI"])) {
  $odeslani[$val['VALUE']] = $val['LABEL'];
}


function ExistujeDorucenka($posta_id=0) {
  $uplobj=Upload(array('create_only_objects'=>true,'agenda'=>'POSTA','noshowheader'=>true));
  $upload_records = $uplobj['table']->GetRecordsUploadForAgenda($posta_id);
  $name_dorucenka = "dorucenka_".$posta_id.".pdf";
  $dorucenka_existuje = false;
  while (list($key,$val)=each($upload_records)) {
    if ($val[NAME]==$name_dorucenka) $dorucenka_existuje=true; 
  }
  return $dorucenka_existuje; 
}


function PripravDorucenku($posta_id=0) {
  global $obalka,$odeslani;
  $sql='select * from posta where id='.$posta_id;
  $q=new DB_POSTA;
  $q->query($sql);
  $q->Next_Record();
  $prichozi_id=$q->Record['DALSI_ID_AGENDA'];
  if ($prichozi_id<0 || !$prichozi_id) return false;
  
  $data['odesilatel']=UkazAdresu($q->Record['ID'],', ');
  $data['datum_odeslani']=$q->Record['DATUM_VYPRAVENI'];
  $data['vec']=$q->Record['VEC'];
  $data['datum_doruceni'] = $q->Record['DATUM_DORUCENI'];

  $doc = LoadSingleton('EedDokument', $posta_id);
  $data['puvodni_cj']=$doc->cislo_jednaci;
  $data['podaci_cislo'] = $doc->barcode;

  $data['obalka']=$obalka[$q->Record['DOPORUCENE']];
  $data['odeslani']=$odeslani[$q->Record['VLASTNICH_RUKOU']];
  $data['soubory']=$soubory;


  $sql='select * from posta where id='.$prichozi_id;
  $q->query($sql);
  $q->Next_Record();
  $data['prijemce']=UkazAdresu($q->Record['ID'],', ');

  $doc_receive = LoadSingleton('EedDokument', $prichozi_id);
  $data['nove_cj']=$doc_receive->cislo_jednaci;
  return $data;

}

Function VytvorDorucenku($posta_id)
{
  if (!$data=PripravDorucenku($posta_id)) return false;
//print_r($data); 

  $file_name='dorucenka.pdf';
  
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
  
  //Instanciation of inherited class
  $pdf = new TCPDF(PDF_PAGE_ORIENTATION, PDF_UNIT, PDF_PAGE_FORMAT, true, 'UTF-8', false, true);

  // set document information
  $pdf->SetCreator(PDF_CREATOR);
  $pdf->SetAuthor('T-WIST');
  $pdf->SetTitle('Doručenka');
  $pdf->SetSubject('Doručenka');


  $pdf->AddPage();
  
  $pdf->SetXy(10, 10);
  $pdf->SetFont('freeserif', '', 18);
  $pdf->Cell(90,10,'Doručenka',0,2,L);

  $pdf->SetXy(120, 10);
  $pdf->write1DBarcode($data['podaci_cislo'], 'C128', '', '', '', 15, 0.34, $style, 'N');


  $pdf->SetXy(10, 30);

  $pdf->SetFont('freeserif', '', 12);

  $html = '<p><table cellpadding="2"  cellspacing="4"> ';
  $html .= '<tr><td width="18%" NOWRAP>K&nbsp;dokumentu:</td><td width="82%"  style="text-decoration:none;background-color:#CCCCCC;color:black;font-weight: bold;">' . TxtEncoding4Soap($data['puvodni_cj']) . '</td></tr>';
  $html .= '<tr><td NOWRAP>Ve věci:</td><td  style="text-decoration:none;background-color:#CCCCCC;color:black;font-weight: bold;">' . TxtEncoding4Soap($data['vec']) . '</td></tr>';
  $html .= '<tr><td NOWRAP>Odesílatel:</td><td  style="text-decoration:none;background-color:#CCCCCC;color:black;font-weight: bold;">' . TxtEncoding4Soap($data['prijemce']) . '</td></tr>';
  $html .= '<tr><td NOWRAP>Číslo&nbsp;jednací:</td><td style="text-decoration:none;background-color:#CCCCCC;color:black;font-weight: bold;">' . TxtEncoding4Soap($data['puvodni_cj']) . '</td></tr>';
  $html .= '<tr><td NOWRAP>Datum&nbsp;odeslání:</td><td style="text-decoration:none;background-color:#CCCCCC;color:black;font-weight: bold;">' . TxtEncoding4Soap($data['datum_odeslani']) . '</td></tr>';
  $html .= '</table>';

  $html .= '<table width="100%"  cellpadding="2"  cellspacing="4"> ';
  $html .= '<tr><td width="18%" NOWRAP>Příjemce:</td><td width="82%"  style="text-decoration:none;background-color:#CCCCCC;color:black;font-weight: bold;">' . TxtEncoding4Soap($data['odesilatel']) . '</td></tr>';
  $html .= '<tr><td>Datum doručení:</td><td style="text-decoration:none;background-color:#CCCCCC;color:black;font-weight: bold;">' . $data['datum_doruceni'] . '</td></tr>';
  $html .= '</table>';

  $html .= '<p><table cellpadding="2"  cellspacing="2"> ';
  $html .= "<tr><td>Dokument byl doručen elektronicky. Dokument příjemce byl založen s číslem jednacím:</td></tr>";
  $html .= '<tr><td style="text-decoration:none;background-color:#CCCCCC;color:black;font-weight: bold;">' . $data['nove_cj'] . '</td></tr>';
  $html .= '</table></p>';


  $pdf->writeHTMLCell(0, 0, '', '', $html, 0, 1, 0, true, '', true);

  $tmp_soubor = $GLOBALS[CONFIG_POSTA][HLAVNI][tmp_adresar]."dorucenka_".$posta_id.".pdf"; 

  $pdf->output($tmp_soubor,'F');
  $GLOBALS['CONVERTED'] = 1; //ze je dokument uz konvertovan
  $uplobj_save=Upload(array('create_only_objects'=>true,'agenda'=>'POSTA','noshowheader'=>true));
  $ret = $uplobj_save['table']->SaveFileToAgendaRecord($tmp_soubor, $posta_id);
  if ($ret[err_msg]<>'') return ShowError($session_id,'COPYFILES','Chyba pri ulozeni souboru dorucenka_'.$posta_id.'.pdf: '.$ret[err_msg]);

}
