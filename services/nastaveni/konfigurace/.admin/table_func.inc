<?php

function showHodnota($hodnota, $parametr) {
  $heslo = strpos($parametr, 'assw');
  if ($heslo) $hodnota = '**********';
  return $hodnota;

}