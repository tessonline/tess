<?php

If (HasRole('spravce')||HasRole('podatelna')) {
  $dropdownListFunc[] = array(
    'name' => 'Načtení ze scanneru',
    'href' => GetAgendaPath('POSTA', false, true) . '/plugins/skenlinka/nacist.php?insert'
  );
}
