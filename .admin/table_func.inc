<?php

require_once(FileUp2('.admin/oth_funkce_2D.inc'));
include_once($GLOBALS['TMAPY_LIB'] . '/oohforms.inc');
require_once(FileUp2('.admin/el/of_select_.inc'));

$GLOBALS['odes_typ'] = getSelectDataEed(new of_select_odes_typ(array()));
$GLOBALS['status'] = getSelectDataEed(new of_select_status(array()));
$GLOBALS['jine'] = getSelectDataEed(new of_select_jine(array()));
$GLOBALS['typ_posty'] = getSelectDataEed(new of_select_typ_posty(array('selectfull'=>true)));

$USER_INFO = $GLOBALS["POSTA_SECURITY"]->GetUserInfo();

function ChangeClassPosta($t) {
  switch($GLOBALS['STATUS']) {
    case '1':
      $color = 'silver';
      break;
    case '2':
      $color = 'green';
      break;
    case '3':
      $color = 'blue';
      break;
    case '4':
      $color = 'black';
      break;
    case '5':
      $color = 'red';
      break;
    case '6':
      $color = 'red';
      break;
    case '7':
      $color = 'orange';
      break;
    case '8':
      $color = 'violet';
      break;
    case '11':
      $color = 'black';
      break;
    case '12':
      $color = 'violet';
      break;
    default:
      $color = 'silver';
      break;

  }
  static $i;
  if ($i){
    $t->classname = 'brow_'.$color;
    $i = 0;
  }
  else{
    $t->classname = 'browdark_'.$color;
    $i = 1;
  }
}



function tableBarcode($id) {
  $doc = LoadSingleton('EedDokument', $id);
  $ret = $doc->barcode;
  if ($GLOBALS['STATUS'] == -1) $ret = '<strike>' . $ret  . '</strike>';
  return $ret;
}

function tableFormatCJednaci($id, $hrefBude = 0) {
  if (!$id) return false;
  $doc = LoadSingleton('EedDokument', $id);
  $cjObject = LoadClass('EedCj', $id);
  $cj = $cjObject->GetCjInfo($id);
  $cislo_jednaci = $doc->cislo_jednaci;
  If ($hrefBude > 0) {
    $ret = '<b><a class="pages" href="/ost/posta';
//    $ret = '<b><a class="pages" href="/' . GetAgendaPath('POSTA',true,true);
    $ret .= '/brow_spis.php?cislo_spisu1=' . $cj['CISLO_SPISU1'] . '&cislo_spisu2=' . $cj['CISLO_SPISU2'];
    $ret .= '&doc_id=' . $id . '">';
    $ret .= $cislo_jednaci . '</a></b>';
  }
  else $ret = '<b> ' . $cislo_jednaci . '</b>';

  if($cj['JE_SPIS'] && $cj['SPIS_ID'] == $id) {
    $ret .= '<br/>spis <a class="pages" href="/ost/posta';
    $ret .= '/brow_spis.php?cislo_spisu1=' . $cj['CISLO_SPISU1'] . '&cislo_spisu2=' . $cj['CISLO_SPISU2'];
    $ret .= '&doc_id=' . $id . '">';
    $ret .= ''.$cj['CELE_CISLO'].'</a></b>';
  }
  elseif($cj['JE_SPIS'] && $cj['SPIS_ID'] <> $id) {
    $ret .= '<br/>ve spisu <a class="pages" href="/ost/posta';
    $ret .= '/brow_spis.php?cislo_spisu1=' . $cj['CISLO_SPISU1'] . '&cislo_spisu2=' . $cj['CISLO_SPISU2'];
    $ret .= '&doc_id=' . $id . '">';
    $ret .= ''.$cj['CELE_CISLO'].'</a></b>';
  }
//  elseif($cj['JE_ARCH'] && $cj['SPIS_ID'] == $id) {
//  	$ret .= '<br/>'.$cj['CELY_NAZEV'].'';
//  }
//  elseif($cj['JE_ARCH'] && $cj['SPIS_ID'] <> $id) {
//  	$ret .= '<br/>'.$cj['CELY_NAZEV'].'';
//  }
  else {
    $ret .= '<br/>&nbsp;';
  }

  if ($cj['TYPOVY_SPIS_MAINID'] == $id) {
    $ret = '<b><a class="pages" href="/ost/posta';
//    $ret = '<b><a class="pages" href="/' . GetAgendaPath('POSTA',true,true);
    $ret .= '/brow_typspis.php?';
    $ret .= '&doc_id=' . $id . '">';
    $ret .= $cislo_jednaci . '</a></b>';
    $ret .= '<br/>typový spis';
  }
  if($cj['NAZEV_SPISU'] && $cj['JE_SPIS']) {
   $ret .= ',<br/><i>' . wordwrap($cj['NAZEV_SPISU'],35, "<br />", true) . '</i>';
  }
  
  if ($GLOBALS['KOPIE'] == 1) $ret .= '<br/><b>KOPIE</b>';
  if ($GLOBALS['STATUS'] == -1) $ret = '<strike>' . $ret  . '</strike>';

  return $ret;
}

function tableFormatJenCJ($id, $hrefBude = 1) {
  if (!$id) return false;
  $doc = LoadSingleton('EedDokument', $id);
  $cjObject = LoadClass('EedCj', $id);
  $cj = $cjObject->GetCjInfo($id);
  $cislo_jednaci = $doc->cislo_jednaci;
  $hrefBude = 1;
  If ($hrefBude > 0) {
    $ret = '<b><a class="pages" href="/ost/posta';
//    $ret = '<b><a class="pages" href="/' . GetAgendaPath('POSTA',true,true);
    $ret .= '/brow_spis.php?cislo_spisu1=' . $cj['CISLO_SPISU1'] . '&cislo_spisu2=' . $cj['CISLO_SPISU2'];
    $ret .= '&doc_id=' . $id . '">';
    $ret .= $cislo_jednaci . '</a></b>';
  }
  else $ret = '<b> ' . $cislo_jednaci . '</b>';

  if ($GLOBALS['KOPIE'] == 1) $ret .= '<br/><b>KOPIE</b>';
  if ($GLOBALS['STATUS'] == -1) $ret = '<strike>' . $ret  . '</strike>';

  return $ret;
}

function tableFormatJenSpis($id, $hrefBude = 1) {
  if (!$id) return false;
  $doc = LoadSingleton('EedDokument', $id);
  $cjObject = LoadClass('EedCj', $id);
  $cj = $cjObject->GetCjInfo($id);
  $cislo_jednaci = $doc->cislo_jednaci;
  $hrefBude = 1;
  If ($cj['JE_SPIS']>0) {
    $ret = '<b><a class="pages" href="/ost/posta';
//    $ret = '<b><a class="pages" href="/' . GetAgendaPath('POSTA',true,true);
    $ret .= '/brow_spis.php?cislo_spisu1=' . $cj['CISLO_SPISU1'] . '&cislo_spisu2=' . $cj['CISLO_SPISU2'];
    $ret .= '&doc_id=' . $id . '">';
    $ret .= ''.$cj['CELE_CISLO'].'</a></b>';
  }

  if($cj['NAZEV_SPISU'] && $cj['JE_SPIS']) {
   $ret .= ',<br/><i>' . wordwrap($cj['NAZEV_SPISU'],35, "<br />", true) . '</i>';
  }

  if ($GLOBALS['KOPIE'] == 1) $ret .= '<br/><b>KOPIE</b>';
  if ($GLOBALS['STATUS'] == -1) $ret = '<strike>' . $ret  . '</strike>';

  return $ret;
}


function tableVec($id) {
  $doc = LoadSingleton('EedDokument', $id);
  $ret =  str_replace(",", ", ", $doc->vec);
  $ret = wordwrap($ret, 80, "<br />", true);
  if ($GLOBALS['STATUS'] == -1) $ret = '<strike>' . $ret  . '</strike>';
  return $ret;
}

function tableSpisACJ($id, $hrefBude = 1) {
  $cjObject = LoadClass('EedCj', $id);
  $cj = $cjObject->GetCjInfo($id);
  $nazev = $cj['JE_SPIS'] ? 'spis ' . $cj['CELE_CISLO'] : $cjObject->cislo_jednaci_zaklad;
//  $nazev = wordwrap($nazev, 80, "<br />", true);

  If ($hrefBude > 0) {
    $ret = '<b><a class="pages" href="/ost/posta';
    $ret .= '/brow_spis.php?cislo_spisu1=' . $cj['CISLO_SPISU1'] . '&cislo_spisu2=' . $cj['CISLO_SPISU2'];
    $ret .= '&doc_id=' . $id . '">';
    $ret .= $nazev . '</a></b>';
  }
  else $ret = '<b> ' . $nazev . '</b>';

  if ($GLOBALS['STATUS'] == -1) $ret = '<strike>' . $ret  . '</strike>';
  return $ret;
}


function tableSpisVec($id) {
  $cjObject = LoadClass('EedCj', $id);
  $cj = $cjObject->GetCjInfo($id);
  $ret = $cj['NAZEV_SPISU'] ? $cj['NAZEV_SPISU'] : $cjObject->vec;
  $ret = wordwrap($ret, 80, "<br />", true);
  if ($GLOBALS['STATUS'] == -1) $ret = '<strike>' . $ret  . '</strike>';
  return $ret;
}

function tableZpracovatel($id) {
  global $USER_INFO;
  $doc = LoadSingleton('EedDokument', $id);
  $ret = $doc->referent_text;
  if ($USER_INFO['ID'] == $doc->referent_id) $ret = "<b>" . $ret . "</b>";
  if ($GLOBALS['STATUS'] == -1) $ret = '<strike>' . $ret  . '</strike>';
  return $ret;
}

function tableSpisUzel($id) {
  $doc = LoadSingleton('EedDokument', $id);
  $ret = $doc->uzel_text;
  if ($GLOBALS['STATUS'] == -1) $ret = '<strike>' . $ret  . '</strike>';
  return $ret;
}

function tableVraceni($id) {
  $doc = LoadSingleton('EedDokument', $id);
  $ret = $doc->odmitnuti;
  $html = '';
  $htmlArray = array();
  if (is_array($ret) && count($ret)>0 && $doc->referent_id<1) {
    foreach($ret as $odmitnuti) {
      $htmlArray[] = $odmitnuti['last_date'].'-'.$odmitnuti['user_text'].': '.$odmitnuti['duvod'];
    }
   $html = '<img src="'.FileUpImage('images/import').'" title="Vrácení:'.chr(10).implode(chr(10), $htmlArray).'"  style="background:#ccc;">';
  }
  if ($GLOBALS['STATUS'] == -1) $ret = '<strike>' . $ret  . '</strike>';
  return $html;
}



function spisovaZnacka($id) {
//  $spisovna = LoadSingleton('EedSpisovnaSimple', $id);
  $spisovna = LoadSingleton('EedDokument', $id);

  if ($spisovna->spisZnakKod)
    $ret = $spisovna->spisZnakKod . '<br/>' . $spisovna->spisZnakPismeno . '/' . $spisovna->spisZnakLhuta;
  else
    $ret = ''; 
  if ($GLOBALS['STATUS'] == -1) $ret = '<strike>' . $ret  . '</strike>';
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
  if ($GLOBALS['STATUS'] == -1) $ret = '<strike>' . $ret  . '</strike>';
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

Function Vyrizeno($jak, $kdy, $spis) {
   $ret .= ',<br/><i>' . wordwrap($cj['NAZEV_SPISU'],35, "<br />", true) . '</i>';

  $res = str_replace(' ','&nbsp;', $jak);
  $res = wordwrap($res, 35, '<br />', true);
  $res .= '<br />'; 
  if ($kdy && !$spis) {
    $temp=substr($kdy,0,strpos($kdy," "));
    If ($temp=='') $res.= CzDate($kdy); else $res.=CzDate($temp);
  }
  if ($spis) $res .= CzDate($spis);
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

function tableDatovaZprava($id) {
  return EedTools::getIDDZ($id);
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
Function ShowOdesTyp($typ_id) {
  $ret = $GLOBALS['odes_typ'][$typ_id];
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

function vybranaSablona($typ_posty) {
  if (isset($typ_posty)) {
    $db = new DB_POSTA;
    $sql = "select id from posta_cis_sablony where typ_posty= ".$typ_posty;
    $db->query($sql);
    $db->Next_record();
  return $db->Record['ID'];
  } else
    return null;
}

