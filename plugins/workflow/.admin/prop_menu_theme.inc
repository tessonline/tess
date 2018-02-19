<?php

foreach ($dropdownListFunc as &$singleFunc) {
  if ($singleFunc['name'] == 'Dokumentace') {
     $singleFunc['href'] = GetAgendaPath('POSTA_DOKUMENTACE', false, true).'/brow.php';
     unset($singleFunc);
     break;
  }
}
// $dropdownListFunc[] = "POSTA_DOKUMENTACE";