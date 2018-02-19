<?php

If (HasRole('spravce')||HasRole('podatelna')) {
    $dropdownListFunc[] = array(
      'name' => 'Generovat soubor pro EVROFIN',
      'href' => GetAgendaPath('POSTA_EVROFIN', false, true) . '/edit.php?insert&cacheid='
    );
}

