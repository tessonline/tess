<?php


function ShowAktivni($aktivni) {
  if ($aktivni == 1) $res = 'Ano';
  else $res = 'Ne';
  return $res;
}