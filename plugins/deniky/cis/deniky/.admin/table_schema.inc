<?php

$TABLE_CONFIG['schema'][] = array(
  'field' => 'NAZEV',
  'label' => 'Název evidence',
);

$TABLE_CONFIG['schema'][] = array(
  'field' => 'ZKRATKA',
  'label' => 'Zkratka'
);

$TABLE_CONFIG['schema'][] = array(
  'field' => 'getHodnota(ID)',
  'label' => 'Aktuální hodnota'
);

$TABLE_CONFIG['schema'][] = array(
  'field' => 'getAktivniText(AKTIVNI)',
  'label' => 'Aktivní'
);

