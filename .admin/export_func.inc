<?php
function exportSmer($smer) {
  $ret = 'příchozí';
  if ($GLOBALS['ODESLANA_POSTA'] == 't') $ret = 'odchozí';
  if ($GLOBALS['ODES_TYP'] == 'S') $ret = 'vlastní';
  return $ret;
}

function exportFormatCJednaci($id) {
  if (!$id) return false;
  $doc = LoadSingleton('EedDokument', $id);
  $cjObject = LoadClass('EedCj', $id);
  $cj = $cjObject->GetCjInfo($id);
  $cislo_jednaci = $doc->cislo_jednaci;
  $ret = $cislo_jednaci;
  return $ret;
}

function exportFormatSpis($id, $nazev = false) {
  if (!$id) return false;
  $doc = LoadSingleton('EedDokument', $id);
  $cjObject = LoadClass('EedCj', $id);
  $cj = $cjObject->GetCjInfo($id);
  $cislo_jednaci = $doc->cislo_jednaci;
  if($cj['JE_SPIS']) {
    $ret = $cj['CELE_CISLO'].'';
    if ($nazev) $ret = $cj['NAZEV_SPISU'];
  }

  return $ret;
}

Function exportVyrizeno($jak, $kdy, $spis) {
  $res = str_replace(' ','&nbsp;', $jak);
  $res .= ' - ';
  if ($kdy && !$spis) {
    $temp=substr($kdy,0,strpos($kdy," "));
    If ($temp=='') $res.= $kdy; else $res.=$temp;
  }
  if ($spis) $res .= CzDate($spis);
  return $res;
}


function exportSpisovaZnacka($id) {
  $spisovna = LoadSingleton('EedSpisovnaSimple', $id);

  if ($spisovna->spisZnakKod)
    $ret = $spisovna->spisZnakKod . ' - ' . $spisovna->spisZnakPismeno . '/' . $spisovna->spisZnakLhuta;
  else
    $ret = '';
  return $ret;
}

function exportZpracovatel($id) {
  global $USER_INFO;
  $doc = LoadSingleton('EedDokument', $id);
  $ret = $doc->referent_text;
  return $ret;
}

function KrizVazba($id) {
  if (@in_array($id, $GLOBALS['KRIZ_VAZBA'])) return '1'; else return '0';
}