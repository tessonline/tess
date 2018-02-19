<?php
include_once($GLOBALS['TMAPY_LIB'] . '/oohforms.inc');
require_once(FileUp2('.admin/el/of_select_.inc'));

$GLOBALS['status'] = getSelectData(new of_select_status(array()));
$GLOBALS['jine'] = getSelectData(new of_select_jine(array()));
$GLOBALS['typ_posty'] = getSelectData(new of_select_typ_posty(array('selectfull'=>true)));


function tableBarcode($id) {
  $doc = LoadSingleton('EedDokument', $id);
  $ret = $doc->barcode;
  return $ret;
}

function tableFormatCJednaci($id, $url) {
  $doc = LoadSingleton('EedDokument', $id);
  $cj = $doc->cislo_jednaci;
  If ($url) { 
    $ret = '<b><a class="pages" href="/' . GetAgendaPath('POSTA',true,true);
    $ret .= '/brow_spis.php?cislo_spisu1=' . $doc->cj1 . '&cislo_spisu2=' . $doc->cj2;
    $ret .= '&doc_id=' . $doc->id_dokument . '">';
    $ret .= $cj . '</a></b>';
  }
  else $ret = '<b>' . $cj . '</b>';

  return $ret;
}

function tableVec($id) {
  $doc = LoadSingleton('EedDokument', $id);
  $ret =  str_replace(",", ", ", $doc->vec);
  return $ret;
}

function tableZpracovatel($id) {
  $doc = LoadSingleton('EedDokument', $id);
  $ret = $doc->referent_text;
  return $ret;
}

function tableSpisUzel($id) {
  $doc = LoadSingleton('EedDokument', $id);
  $ret = $doc->uzel_text;
  return $ret;
}


function spisovaZnacka($id) {
  $spisovna = LoadSingleton('EedSpisovna', $id);

  if ($spisovna->spisZnakKod)
    $ret = $spisovna->spisZnakKod . '<br/>' . $spisovna->spisZnakPismeno . '/' . $spisovna->spisZnakLhuta;
  else
    $ret = ''; 
  return $ret;
}

function UlozenoVeSpisovne($id) {
  $spisovna = LoadSingleton('EedSpisovna', $id);

  if ($spisovna->JeVeSpisovne()) {
    $spis = $spisovna->NazevSpisovny();
    $ret = str_replace(' ', '&nbsp;', $spis['SPISOVNA']) . '<br/>'
         . str_replace(' ', '&nbsp;', $spis['PREVZAL_JMENO']) . ' '
         . CzDate($spis['PREDANO']);
  }
  else
    $ret = ''; 
  return $ret;
}

Function UklZnacka($spis_id,$delic='<br/>') {
  $vysl_znacky = array();
  $znacka = LoadClass('EedZnacka', $spis_id);

  $vysl_znacky = $znacka->GetZnackaNameProCJ($spis_id);
  if (count($vysl_znacky)>0) $ret = implode($delic,$vysl_znacky);
  else $ret = '&nbsp;';

  return $ret;
} 

Function Vyrizeno($jak, $kdy) {
  $res = str_replace(' ','&nbsp;', $jak);
  $res .= '<br />'; 
  $res .= CzDate($kdy);
  return $res;
}

function spisForma($id) {
  $spisovna = LoadSingleton('EedSpisovna', $id);

  $res = $spisovna->spisForma;
  return $res;
}

function spisListu($id) {
  $spisovna = LoadSingleton('EedSpisovna', $id);

  $res = $spisovna->spisListu;
  return $res;
}

function spisDigitalnich($id) {
  $spisovna = LoadSingleton('EedSpisovna', $id);

  $res = $spisovna->spisDigitalnich;
  return $res;
}

function spisListuADigitalnich($id) {
  $spisovna = LoadSingleton('EedSpisovna', $id);

  $res = $spisovna->spisListu . '&nbsp;/&nbsp;' . $spisovna->spisDigitalnich;
  return $res;
}


function spisVyber($id) {
  $spisovna = LoadSingleton('EedSpisovna', $id);

  $res = $spisovna->spisZnakPismeno;
  $res .= $spisovna->spisVyrazeno ? ('(' . CzDate($spisovna->spisVyrazeno) . ')') : '';
  return $res;
}


Function ShowStatus($stat_id) {
  $ret = $GLOBALS['status'][$stat_id];
  if (!$ret) $ret = $stat_id;
  return $ret;
}

Function ShowJine($jine_id) {
  $ret = $GLOBALS['jine'][$jine_id];
  if (!$ret) $ret = $jine_id;
  return $ret;
}

Function ShowTypPosty($typ_id) {
  $ret = $GLOBALS['typ_posty'][$typ_id];
  if (!$ret) $ret = $typ_id;
  return $ret;
}
Function czdate2eng($engdatum)
{
 $date1 = substr($engdatum,0,strpos($engdatum," "));
// Odstranime cas...
  $datumkod=explode(".",$date1);
  if (strlen($datumkod[0])<2) $datumkod[0]="0".$datumkod[0];
  if (strlen($datumkod[1])<2) $datumkod[1]="0".$datumkod[1];
  $odeslano=$datumkod[2]."-".$datumkod[1]."-".$datumkod[0]; 
//  $odeslano=strtotime ($datumkod[2]."-".$datumkod[1]."-".$datumkod[0]); 

  return $odeslano;
}

