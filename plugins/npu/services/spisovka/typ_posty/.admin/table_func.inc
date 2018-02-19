<?php
function KlasifikaceAFaze($typ_posty_id, $jine_id) {
  $typ_posty = $GLOBALS['typ_posty'][$typ_posty_id];
  if (!$typ_posty) $typ_posty = $typ_posty_id;

  $jine = $GLOBALS['jine'][$jine_id];
  if (!$jine) $jine = $jine_id;

  $res = 'Klasifikace: <b>' . $typ_posty . '</b><br/>';
  $res .= 'Fáze: <b>' . $jine . '</b>';
  return $res;
}

