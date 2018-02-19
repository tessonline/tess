<?php

If (HasRole('spravce')||HasRole('podatelna')) {
  $dropdownListFunc[] = array(
    'name' => 'Načíst obálky z Neopostu (2D kod)',
    'href' => GetAgendaPath('POSTA_PLUGINS', false, true) . '/neopost/run.php?cacheid='
  );
}
