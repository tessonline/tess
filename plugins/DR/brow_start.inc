<?php


if ($GLOBALS['STAV']>1000) {
  $app_id = floor(($GLOBALS['STAV']-1000)/10);
  $last_digit = substr($GLOBALS['STAV'], -1);

  if ($last_digit == '2') $where .= " AND (stav in (".$GLOBALS['STAV'].",".($GLOBALS['STAV']+1).") OR dalsi_id_agenda like 'DR-".$app_id."-%')";
  elseif ($last_digit == '1') $where .= " AND (stav in (".$GLOBALS['STAV']."))";

  $GLOBALS['STAV_select'] = $GLOBALS['STAV'];
  UNSET($GLOBALS['STAV']);
}