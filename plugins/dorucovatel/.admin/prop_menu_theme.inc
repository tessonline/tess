<?php

If (HasRole('spravce')||HasRole('podatelna')||HasRole('podatelna-odbor')) {
  $dropdownListFunc[] = array(
    'name' => 'Předávací protokol pro doručovatele',
    'href' => GetAgendaPath('POSTA_DORUCOVATEL', false, true) . '/brow.php?cacheid='
  );

}
