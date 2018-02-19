<?php

If (HasRole('spravce')||HasRole('podatelna')||HasRole('podatelna-odbor')) {
  $dropdownListFunc[] = array(
    'name' => 'Předávací protokol pro Českou poštu',
    'href' => GetAgendaPath('POSTA_CPOST', false, true) . '/brow.php?cacheid='
  );

  $dropdownListFunc[] = array(
    'name' => 'Měsíční výkaz pro Českou poštu',
    'href' => GetAgendaPath('POSTA_CPOST', false, true) . '/edit_mesic.php?edit&MESICNI_VYKAZ=1&cacheid='
  );
}
