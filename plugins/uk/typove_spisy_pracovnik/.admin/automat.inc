<?php

function VlozDokumentDoTypSpisu($doc_id, $studium_id, $znak) {
  $nazev = '%/' . $studium_id.'%';
  if (!$ids = EedTools::VratTypovySpisZNazvu($nazev)) return 'Chyba - není založen odpovídající typový spis. ';
  if (count($ids)>1) return 'Chyba - nalezeno více typových spisů. ';
  else
    $typovy_spis_id = $ids[0];

  $vhodna_soucast = array(); //soucast, ktera splnuje zadani;


  $vhodna_soucast = EedTools::VratSoucastDleSkartaceTypovehoSpisu($typovy_spis_id, $znak);

  if (count($vhodna_soucast) == 0) return 'Nenalezena prave jedna soucast';

  if (count($vhodna_soucast) == 1) $vybrana_soucast = $vhodna_soucast[0];

  $cj = LoadClass('EedCj', $typovy_spis_id)
  $cj->dejDokumentDoTypSpisu($doc_id, $typovy_spis_id, $soucast['ID']);

}