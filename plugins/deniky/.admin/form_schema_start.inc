<?php

if (!$GLOBALS['EDIT_ID'] && $GLOBALS['MAIN_DOC']>100) {
  $q = new DB_POSTA;
  $sql = 'select * from posta_cis_deniky where id=' . $GLOBALS['MAIN_DOC'];
  $q->query($sql);
  $q->Next_Record();

  $GLOBALS['LHUTA'] = $q->Record['LHUTA'];
  $GLOBALS['TYP_POSTY'] = $q->Record['TYP_POSTY'];
  $GLOBALS['ODBOR'] = $q->Record['ODBOR'];
  $GLOBALS['VEC'] = $q->Record['VEC'];
  $GLOBALS['SKARTACE'] = $q->Record['SKARTACE'];

  $GLOBALS['STAV'] = $q->Record['STAV'];
  $GLOBALS['VYRIZENO'] = $q->Record['VYRIZENO'];
  if ($q->Record['DATUM_VYRIZENI']) $GLOBALS['DATUM_VYRIZENI'] = Date('d.m.Y H:i:s');
  if ($q->Record['SPIS_VYRIZEN']) $GLOBALS['SPIS_VYRIZEN'] = Date('d.m.Y H:i:s');
}

