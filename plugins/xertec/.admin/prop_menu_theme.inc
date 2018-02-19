<?php

If (HasRole('spravce')||HasRole('podatelna')) {
  $dropdownListFunc[] = array(
    'name' => 'Vážit na XERTECu',
    'href' => GetAgendaPath('POSTA_XERTEC', false, true) . '/edit.php?insert&cacheid='
  );
  $dropdownListFunc[] = array(
    'name' => 'Načíst soubor z XERTECu',
    'href' => GetAgendaPath('POSTA_XERTEC', false, true) . '/xertec.php?povoleni=1'
  );
}
