<?php

If (HasRole('spravce')||HasRole('podatelna')||HasRole('podatelna-odbor')) {
  $dropdownListFunc[] = array(
    'name' => 'Vytvoření ELO záznamů',
//    'href' => GetAgendaPath('POSTA_ELO', false, true) . '/edit.php?insert'
    'href' => GetAgendaPath('POSTA_PLUGINS', false, true) . '/elo/edit.php?insert&cacheid='
  );

  $dropdownListFunc[] = array(
    'name' => 'Kontrola ELO záznamů',
//    'href' => GetAgendaPath('POSTA_ELO', false, true) . '/kontrola.php'
    'href' => GetAgendaPath('POSTA_PLUGINS', false, true) . '/elo/kontrola.php'
  );

}
