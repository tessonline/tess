<?php
require ("tmapy_config.inc");

if (is_numeric($GLOBALS['SKAR_LHUTA'])===false)
  echo 'neni cislo';

else{
  $q = new DB_POSTA();
  $sql = 'select count(*) as pocet from POSTA_CIS_SKARTACNI_REZIMY where skar_znak=\'' . $GLOBALS['SKAR_ZNAK'] . '\' AND skar_lhuta=' . $GLOBALS['SKAR_LHUTA'];
  $q->query($sql);
  $q->Next_Record();
  $count = $q->Record['POCET'];
  echo $count;
}