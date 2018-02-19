<?php
require_once(FileUp2('.admin/oth_funkce_2D.inc'));
include_once($GLOBALS['TMAPY_LIB'] . '/oohforms.inc');
require_once(FileUp2('.admin/el/of_select_.inc'));

$GLOBALS['pracoviste'] = getSelectDataEed(new of_select_superodbor_prefix(array()));


function getPracoviste($prac_id) {
  $ret = $GLOBALS['pracoviste'][$prac_id];
  if (!$ret) $ret = $prac_id;
  return $ret;
}

function getDatum($date) {
  if ($date=='03.03.3333') $ret = 'trvá';
  else $ret = $date;
  return $ret;
}

function getTypPomeru ($typ) {
  $ret = 'neuvedeno';
  if ($typ == 1) $ret = 'prac.smlouva';
  if ($typ == 2) $ret = 'DPČ';
  if ($typ == 3) $ret = 'DPP';
  return $ret;
}

