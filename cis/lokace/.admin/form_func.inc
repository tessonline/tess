<?php

/**
 * Funkce pro update vsech potomku pri zmene nazvu rodice
 * 
 * @param &DB_POSTA q db konektor
 * @param string staryNazev stary nazev v uplne ceste
 * @param string novyNazev novy nazev v uplne ceste
 * @param int idParent identifikator predka
 */
function updateAllChildren($q, $staryNazev, $novyNazev, $idParent) {
  $sql = 'SELECT * FROM posta_spisovna_cis_lokace WHERE id_parent='.$idParent;
  $q->query($sql);
  while ($q->next_record()) {
    $children[] = $q->Record;
  }
  if (count($children) < 1) return 1;
  foreach ($children as $child) {
    $novaCesta = str_replace($staryNazev, $novyNazev, $child['PLNA_CESTA']);
    $sql = "UPDATE posta_spisovna_cis_lokace SET plna_cesta='".$novaCesta."' WHERE id=".$child['ID'];
    $q->query($sql);
    updateAllChildren($q, $child['PLNA_CESTA'], $novaCesta, $child['ID']);
  }
}

/**
 * Funkce pro vytvoreni lokacni cesty
 * 
 * @param string nazev Nazev aktulani lokace
 * @param int idParent ID nadrazene lokace
 * @param string delimiter Oddelovac cesty
 * @return string Slozena cesta pro PLNA_CESTA
 */
function makeFullWay($nazev, $idParent, $delimiter) {
  $idParent = intval($idParent);
  $id = intval($id);
  $q = new DB_POSTA;
  $sql = "SELECT plna_cesta FROM posta_spisovna_cis_lokace WHERE id = ".$idParent;
  $q->query($sql);
  $cesta = "";
  if($q->next_record()) {
    $cesta .= $q->Record["PLNA_CESTA"] . $delimiter;
  }
  $cesta .= $nazev;
  return $cesta;
}

/**
 * Funkce pro ziskani ID z cesty
 * 
 * @param string cesta Uplna cesta k lokaci
 * @param string delimiter Oddelovac cesty
 * @return int ID nadrazene lokace nebo false, kdyz nema rodice
 */
function getParentFromFullWay($cesta, $delimiter) {
  $rozdelCesta = explode($delimiter, $cesta);
  $count = count($rozdelCesta);
  $hledanaCesta = "";
  for($i=0; $i<$count-1; $i++) {
    if($i!=0) $hledanaCesta .= $delimiter;
    $hledanaCesta .= $rozdelCesta[$i];
  }
  if($hledanaCesta) {
    $q = new DB_POSTA;
    if($hledanaCesta)
    $sql = "SELECT * FROM posta_spisovna_cis_lokace WHERE plna_cesta = '".$hledanaCesta."'";
    $q->query($sql);
    if($q->next_record()) {
      return $q->Record["ID"];
    }
  }
  return false;
}