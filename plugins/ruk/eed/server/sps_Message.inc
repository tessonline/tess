<?php

function NastavPopis($type,$kod,$msg='',$errSql='') {
  $res = array('Kod'=>'9999', 'Popis'=>'Neexistuje popis', 'ErrSql'=>'');
  
  if ($msg) $msg = strip_tags($msg);
  if ($errSql) $errSql = strip_tags($errSql);
  
  //Synchroni
  if ($type=='DokumentZalozeni') {
    if ($kod=='0000') $res = array('Kod'=>$kod, 'Popis'=>'OK - Dokument byl vytvoren', 'ErrSql'=>$errSql);
    if ($kod=='1000') $res = array('Kod'=>$kod, 'Popis'=>'Chyba - Dokument jiz existuje nebo uzivatel neni drzitelem dokumentu', 'ErrSql'=>$errSql);
    if ($kod=='1001') $res = array('Kod'=>$kod, 'Popis'=>'Chyba - Nepodarilo se vytvorit dokument', 'ErrSql'=>$errSql);
    if ($kod=='1002') $res = array('Kod'=>$kod, 'Popis'=>'Chyba - Dokument neexistuje', 'ErrSql'=>$errSql);
    if ($kod=='2000') $res = array('Kod'=>$kod, 'Popis'=>'Chyba - Chyba v UdalostiPredchazejici', 'ErrSql'=>$errSql);
  }

  if ($type=='ProfilDOkumentuZadost') {
    if ($kod=='0000') $res = array('Kod'=>$kod, 'Popis'=>'OK - Dokument byl zobrazen', 'ErrSql'=>$errSql);
    if ($kod=='1000') $res = array('Kod'=>$kod, 'Popis'=>'Chyba - Dokument neexistuje nebo uzivatel neni drzitelem dokumentu', 'ErrSql'=>$errSql);
  }
  
  if ($type=='SpisZalozeni') {
    if ($kod=='0000') $res = array('Kod'=>$kod, 'Popis'=>'OK - Spis byl zalozen', 'ErrSql'=>$errSql);
    if ($kod=='1000') $res = array('Kod'=>$kod, 'Popis'=>'Chyba - Spis jiz existuje', 'ErrSql'=>$errSql);
    if ($kod=='1001') $res = array('Kod'=>$kod, 'Popis'=>'Chyba - Nepodarilo se vytvorit spis', 'ErrSql'=>$errSql);
    if ($kod=='1002') $res = array('Kod'=>$kod, 'Popis'=>'Chyba - Nepodarilo se vytvorit spis ('.$msg.')', 'ErrSql'=>$errSql);
    if ($kod=='2000') $res = array('Kod'=>$kod, 'Popis'=>'Chyba - Chyba v UdalostiPredchazejici', 'ErrSql'=>$errSql);
  }
  
  if ($type=='Udalosti') {
    if ($kod=='1000') $res = array('Kod'=>$kod, 'Popis'=>'Chyba - Asynchroni funkce '.$msg.' neexistuje', 'ErrSql'=>$errSql);
  }
  
  //Asynchroni
  if ($type=='ermsAsyn') {
    if ($kod=='1000') $res = array('Kod'=>$kod, 'Popis'=>'Chyba - Asynchroni funkce '.$msg.' neexistuje', 'ErrSql'=>$errSql);
  }
  
  if ($type=='DokumentOtevreni') {
    if ($kod=='0000') $res = array('Kod'=>$kod, 'Popis'=>'OK - Otevreni dokumentu, ktery byl vyrizen (vyrizenim spisu)', 'ErrSql'=>$errSql);
    if ($kod=='1000') $res = array('Kod'=>$kod, 'Popis'=>'Chyba - Dokument neexistuje nebo uzivatel neni drzitelem dokumentu nebo neni otevreny', 'ErrSql'=>$errSql);
    if ($kod=='1001') $res = array('Kod'=>$kod, 'Popis'=>'Chyba - Nepovedlo se otevrit dokumentu, ktery byl vyrizen (vyrizenim spisu)', 'ErrSql'=>$errSql);
  }
  
  if ($type=='DokumentUprava') {
    if ($kod=='0000') $res = array('Kod'=>$kod, 'Popis'=>'OK - Byl zmenen profil dokumentu', 'ErrSql'=>$errSql);
    if ($kod=='1000') $res = array('Kod'=>$kod, 'Popis'=>'Chyba - Dokument neexistuje nebo uzivatel neni drzitelem dokumentu', 'ErrSql'=>$errSql);
    if ($kod=='1001') $res = array('Kod'=>$kod, 'Popis'=>'Chyba - Nebyl zmenen profil dokumentu', 'ErrSql'=>$errSql);
  }
  
  if ($type=='DokumentVlozeniDoSpisu') {
    if ($kod=='0000') $res = array('Kod'=>$kod, 'Popis'=>'OK - Do spisu byl vlozen dokument', 'ErrSql'=>$errSql);
    if ($kod=='1000') $res = array('Kod'=>$kod, 'Popis'=>'Chyba - Spis neexistuje nebo uzivatel neni drzitelem spisu nebo je uzavren', 'ErrSql'=>$errSql);
    if ($kod=='1001') $res = array('Kod'=>$kod, 'Popis'=>'Chyba - Do spisu se nepodarilo vlozit dokument', 'ErrSql'=>$errSql);
    if ($kod=='1002') $res = array('Kod'=>$kod, 'Popis'=>'Chyba - Do spisu se nepodarilo vlozit dokument ('.$msg.')', 'ErrSql'=>$errSql);
  }
  
  if ($type=='DokumentVraceni') {
    if ($kod=='0000') $res = array('Kod'=>$kod, 'Popis'=>'OK - Dokument byl predan z AIS do ESS', 'ErrSql'=>$errSql);
    if ($kod=='1000') $res = array('Kod'=>$kod, 'Popis'=>'Chyba - Dokument neexistuje nebo neni v drzeni agendy nebo je ve spisu', 'ErrSql'=>$errSql);
    if ($kod=='1001') $res = array('Kod'=>$kod, 'Popis'=>'Chyba - Dokument nebyl predan', 'ErrSql'=>$errSql);
  }
  
  if ($type=='DokumentVyjmutiZeSpisu') {
    if ($kod=='0000') $res = array('Kod'=>$kod, 'Popis'=>'OK - Vyjmutí dokumentu ze spisu', 'ErrSql'=>$errSql);
    if ($kod=='1000') $res = array('Kod'=>$kod, 'Popis'=>'Chyba - Spis neexistuje nebo uzivatel neni drzitelem spisu nebo je uzavren', 'ErrSql'=>$errSql);
    if ($kod=='1001') $res = array('Kod'=>$kod, 'Popis'=>'Chyba - Dokument neexistuje nebo uzivatel neni drzitelem dokumentu', 'ErrSql'=>$errSql);
    if ($kod=='1002') $res = array('Kod'=>$kod, 'Popis'=>'Chyba - Vyjmutí dokumentu ze spisu se nepovedlo', 'ErrSql'=>$errSql);
  }
  
  if ($type=='DokumentZmenaZpracovatele') {
    if ($kod=='0000') $res = array('Kod'=>$kod, 'Popis'=>'OK - Predan dokument novemu zpracovateli', 'ErrSql'=>$errSql);
    if ($kod=='1000') $res = array('Kod'=>$kod, 'Popis'=>'Chyba - Dokument neexistuje nebo je ve spisu', 'ErrSql'=>$errSql);
    if ($kod=='1001') $res = array('Kod'=>$kod, 'Popis'=>'Chyba - Dokument se nepodarilo predat novemu zpracovateli', 'ErrSql'=>$errSql);
  }
  
  if ($type=='DokumentZruseni') {
    if ($kod=='0000') $res = array('Kod'=>$kod, 'Popis'=>'OK - Dokument byl strornovan', 'ErrSql'=>$errSql);
    if ($kod=='1000') $res = array('Kod'=>$kod, 'Popis'=>'Chyba - Dokument neexistuje nebo uzivatel neni drzitelem dokumentu nebo vypraveni dokumentu neni ve stavu nevypraveno nebo stornovano', 'ErrSql'=>$errSql);
    if ($kod=='1001') $res = array('Kod'=>$kod, 'Popis'=>'Chyba - Dokument se nepodarilo stornovat', 'ErrSql'=>$errSql);
  }
  
  if ($type=='DoruceniUprava') {
    if ($kod=='0000') $res = array('Kod'=>$kod, 'Popis'=>'OK - Byly zmeneny informace o doruceni prichoziho dokumentu', 'ErrSql'=>$errSql);
    if ($kod=='1000') $res = array('Kod'=>$kod, 'Popis'=>'Chyba - Dokument neexistuje nebo se nejdna o prichozi dokument nebo uzivatel neni drzitelem dokumentu', 'ErrSql'=>$errSql);
    if ($kod=='1001') $res = array('Kod'=>$kod, 'Popis'=>'Chyba - Nebyly zmeneny informace o doruceni prichoziho dokumentu', 'ErrSql'=>$errSql);
  }
  
  if ($type=='SouborZalozeni') {
    if ($kod=='0000') $res = array('Kod'=>$kod, 'Popis'=>'OK - Byl pripojen el. obsah souboru k dokumentu', 'ErrSql'=>$errSql);
    if ($kod=='1000') $res = array('Kod'=>$kod, 'Popis'=>'Chyba - Dokument neexistuje nebo uzivatel neni drzitelem dokumentu', 'ErrSql'=>$errSql);
    if ($kod=='1001') $res = array('Kod'=>$kod, 'Popis'=>'Chyba - Nebyl pripojen el. obsah souboru k dokumentu'.($msg ? ' ('.$msg.')' : ''), 'ErrSql'=>$errSql);
  }
  
  if ($type=='SouborNovaVerze') {
    if ($kod=='0000') $res = array('Kod'=>$kod, 'Popis'=>'OK - Byl nahrazen stavajici el. obsah souboru novou verzi dat', 'ErrSql'=>$errSql);
    if ($kod=='1000') $res = array('Kod'=>$kod, 'Popis'=>'Chyba - Dokument neexistuje nebo uzivatel neni drzitelem dokumentu', 'ErrSql'=>$errSql);
    if ($kod=='1001') $res = array('Kod'=>$kod, 'Popis'=>'Chyba - Nebyl nahrazen stavajici el. obsah souboru novou verzi dat'.($msg ? ' ('.$msg.')' : ''), 'ErrSql'=>$errSql);
  }
  
  if ($type=='SouborZruseni') {
    if ($kod=='0000') $res = array('Kod'=>$kod, 'Popis'=>'OK - Byl odebran el. obsahu souboru z dokumentu', 'ErrSql'=>$errSql);
    if ($kod=='1000') $res = array('Kod'=>$kod, 'Popis'=>'Chyba - Dokument neexistuje nebo uzivatel neni drzitelem dokumentu nebo el. obsah je soucasti vypraveni, ktere je predano k vypraveni a je ve stavu vypraveno nebo doruceno', 'ErrSql'=>$errSql);
    if ($kod=='1001') $res = array('Kod'=>$kod, 'Popis'=>'Chyba - Nebyl odebran el. obsahu souboru z dokumentu'.($msg ? ' ('.$msg.')' : ''), 'ErrSql'=>$errSql);
  }
    
  if ($type=='SouborVlozitKVypraveni') {
    if ($kod=='0000') $res = array('Kod'=>$kod, 'Popis'=>'OK - Byl pripojen el. obsah souboru k vypraveni', 'ErrSql'=>$errSql);
    if ($kod=='1000') $res = array('Kod'=>$kod, 'Popis'=>'Chyba - Dokument neexistuje nebo uzivatel neni drzitelem dokumentu', 'ErrSql'=>$errSql);
    if ($kod=='1001') $res = array('Kod'=>$kod, 'Popis'=>'Chyba - Vypraveni neexistuje nebo neni ve stavu nevypraveno', 'ErrSql'=>$errSql);
    if ($kod=='1002') $res = array('Kod'=>$kod, 'Popis'=>'Chyba - Nebyl pripojen el. obsah souboru k vypraveni'.($msg ? ' ('.$msg.')' : ''), 'ErrSql'=>$errSql);
  }
  
  if ($type=='SouborVyjmoutZVypraveni') {
    if ($kod=='0000') $res = array('Kod'=>$kod, 'Popis'=>'OK - Byl odebran el. obsahu souboru z vypraveni', 'ErrSql'=>$errSql);
    if ($kod=='1000') $res = array('Kod'=>$kod, 'Popis'=>'Chyba - Dokument neexistuje nebo uzivatel neni drzitelem dokumentu', 'ErrSql'=>$errSql);
    if ($kod=='1001') $res = array('Kod'=>$kod, 'Popis'=>'Chyba - Vypraveni neexistuje nebo neni ve stavu nevypraveno', 'ErrSql'=>$errSql);
    if ($kod=='1002') $res = array('Kod'=>$kod, 'Popis'=>'Chyba - Nebyl odebran el. obsahu souboru z vypraveni'.($msg ? ' ('.$msg.')' : ''), 'ErrSql'=>$errSql);
  }
  
  if ($type=='SpisOtevreni') {
    if ($kod=='0000') $res = array('Kod'=>$kod, 'Popis'=>'OK - Spis byl znovu otevren', 'ErrSql'=>$errSql);
    if ($kod=='1000') $res = array('Kod'=>$kod, 'Popis'=>'Chyba - Spis neexistuje nebo uzivatel neni drzitelem spisu nebo neni uzavren', 'ErrSql'=>$errSql);
    if ($kod=='1001') $res = array('Kod'=>$kod, 'Popis'=>'Chyba - Spis nebyl znovu otevren', 'ErrSql'=>$errSql);
  }
  
  if ($type=='SpisVraceni') {
    if ($kod=='0000') $res = array('Kod'=>$kod, 'Popis'=>'OK - Spis byl predan z AIS do ESS', 'ErrSql'=>$errSql);
    if ($kod=='1000') $res = array('Kod'=>$kod, 'Popis'=>'Chyba - Spis neexistuje nebo neni v drzeni agendy', 'ErrSql'=>$errSql);
    if ($kod=='1001') $res = array('Kod'=>$kod, 'Popis'=>'Chyba - Spis nebyl predan', 'ErrSql'=>$errSql);
  }
  
  if ($type=='SpisVyrizeni') {
    if ($kod=='0000') $res = array('Kod'=>$kod, 'Popis'=>'OK - Spis byl uzavren', 'ErrSql'=>$errSql);
    if ($kod=='1000') $res = array('Kod'=>$kod, 'Popis'=>'Chyba - Spis neexistuje nebo uzivatel neni drzitelem spisu nebo je jiz uzavren', 'ErrSql'=>$errSql);
    if ($kod=='1001') $res = array('Kod'=>$kod, 'Popis'=>'Chyba - Spis nebyl uzavren', 'ErrSql'=>$errSql);
  }
  
  if ($type=='SpisZmenaZpracovatele') {
    if ($kod=='0000') $res = array('Kod'=>$kod, 'Popis'=>'OK - Predan cely spis novemu zpracovateli', 'ErrSql'=>$errSql);
    if ($kod=='1000') $res = array('Kod'=>$kod, 'Popis'=>'Chyba - Spis neexistuje', 'ErrSql'=>$errSql);
    if ($kod=='1001') $res = array('Kod'=>$kod, 'Popis'=>'Chyba - Nepodarilo se predat cely spis novemu zpracovateli', 'ErrSql'=>$errSql);
  }
  
  if ($type=='SpisZruseni') {
    if ($kod=='0000') $res = array('Kod'=>$kod, 'Popis'=>'OK - Spis byl zrusen', 'ErrSql'=>$errSql);
    if ($kod=='1000') $res = array('Kod'=>$kod, 'Popis'=>'Chyba - Spis neexistuje nebo uzivatel neni drzitelem spisu', 'ErrSql'=>$errSql);
    if ($kod=='1001') $res = array('Kod'=>$kod, 'Popis'=>'Chyba - Spis nebyl zrusen', 'ErrSql'=>$errSql);
  }
  
  if ($type=='VypraveniDoruceno') {
    if ($kod=='0000') $res = array('Kod'=>$kod, 'Popis'=>'OK -  Vypraveni byla doplnena informace o doruceni', 'ErrSql'=>$errSql);
    if ($kod=='1000') $res = array('Kod'=>$kod, 'Popis'=>'Chyba - Dokument neexistuje', 'ErrSql'=>$errSql);
    if ($kod=='1001') $res = array('Kod'=>$kod, 'Popis'=>'Chyba - Vypraveni neexistuje nebo neni ve stavu vypraveno', 'ErrSql'=>$errSql);
    if ($kod=='1002') $res = array('Kod'=>$kod, 'Popis'=>'Chyba - Vypraveni nebyla doplnena informace o doruceni', 'ErrSql'=>$errSql);
  }
  
  if ($type=='VypraveniPredatVypravne') {
    if ($kod=='0000') $res = array('Kod'=>$kod, 'Popis'=>'OK - Vypraveni bylo predano do podatelny k vypraveni', 'ErrSql'=>$errSql);
    if ($kod=='1000') $res = array('Kod'=>$kod, 'Popis'=>'Chyba - Vypraveni neexistuje nebo neni ve stavu nevypraveno', 'ErrSql'=>$errSql);
    if ($kod=='1001') $res = array('Kod'=>$kod, 'Popis'=>'Chyba - Vypraveni nebylo predano do podatelny k vypraveni', 'ErrSql'=>$errSql);
  }
  
  if ($type=='VypraveniUprava') {
    if ($kod=='0000') $res = array('Kod'=>$kod, 'Popis'=>'OK - Dokumentu bylo zmeneno vypraveni', 'ErrSql'=>$errSql);
    if ($kod=='1000') $res = array('Kod'=>$kod, 'Popis'=>'Chyba - Dokument neexistuje nebo uzivatel neni drzitelem dokumentu', 'ErrSql'=>$errSql);
    if ($kod=='1001') $res = array('Kod'=>$kod, 'Popis'=>'Chyba - Vypraveni neexistuje nebo neni ve stavu nevypraveno', 'ErrSql'=>$errSql);
    if ($kod=='1002') $res = array('Kod'=>$kod, 'Popis'=>'Chyba - Dokumentu nebylo zmeneno vypraveni', 'ErrSql'=>$errSql);
  }
  
  if ($type=='VypraveniVypraveno') {
    if ($kod=='0000') $res = array('Kod'=>$kod, 'Popis'=>'OK -  Vypraveni byla doplnena informace o vypraveni', 'ErrSql'=>$errSql);
    if ($kod=='1000') $res = array('Kod'=>$kod, 'Popis'=>'Chyba - Dokument neexistuje', 'ErrSql'=>$errSql);
    if ($kod=='1001') $res = array('Kod'=>$kod, 'Popis'=>'Chyba - Vypraveni neexistuje nebo neni ve stavu nevypraveno nebo predano k vypraveni', 'ErrSql'=>$errSql);
    if ($kod=='1002') $res = array('Kod'=>$kod, 'Popis'=>'Chyba - Vypraveni nebyla doplnena informace o vypraveni', 'ErrSql'=>$errSql);
  }
  
  if ($type=='VypraveniZalozeni') {
    if ($kod=='0000') $res = array('Kod'=>$kod, 'Popis'=>'OK - Dokumentu bylo nastaveno nove vypraveni', 'ErrSql'=>$errSql);
    if ($kod=='1000') $res = array('Kod'=>$kod, 'Popis'=>'Chyba - Dokument neexistuje nebo se nejedna o vystupni dokument nebo uzivatel neni drzitelem dokumentu', 'ErrSql'=>$errSql);
    if ($kod=='1001') $res = array('Kod'=>$kod, 'Popis'=>'Chyba - Vypraveni jiz existuje', 'ErrSql'=>$errSql);
    if ($kod=='1002') $res = array('Kod'=>$kod, 'Popis'=>'Chyba - Dokumentu nebylo nastaveno nove vypraveni', 'ErrSql'=>$errSql);
  }
  
  if ($type=='VypraveniZruseni') {
    if ($kod=='0000') $res = array('Kod'=>$kod, 'Popis'=>'OK - Vypraveni bylo zruseno / zneplatneno', 'ErrSql'=>$errSql);
    if ($kod=='1000') $res = array('Kod'=>$kod, 'Popis'=>'Chyba - Dokument neexistuje nebo uzivatel neni drzitelem dokumentu', 'ErrSql'=>$errSql);
    if ($kod=='1001') $res = array('Kod'=>$kod, 'Popis'=>'Chyba - Vypraveni neexistuje', 'ErrSql'=>$errSql);
    if ($kod=='1002') $res = array('Kod'=>$kod, 'Popis'=>'Chyba - Vypraveni nebylo zruseno / zneplatneno', 'ErrSql'=>$errSql);
  }
  
  //********************************* IN *******************************************
  
  if ($type=='DokumentPostoupeni') {
    if ($kod=='0000') $res = array('Kod'=>$kod, 'Popis'=>'OK - Dokument byl predan z ESS do AIS', 'ErrSql'=>$errSql);
    if ($kod=='1000') $res = array('Kod'=>$kod, 'Popis'=>'Chyba - Dokument neexistuje nebo neni v drzeni ESS nebo je ve spisu', 'ErrSql'=>$errSql);
    if ($kod=='1001') $res = array('Kod'=>$kod, 'Popis'=>'Chyba - Nektery z dokumentu neni v drzeni ESS', 'ErrSql'=>$errSql);
    if ($kod=='1002') $res = array('Kod'=>$kod, 'Popis'=>'Chyba - Dokument nebyl predan', 'ErrSql'=>$errSql);
  }
  
  if ($type=='SpisPostoupeni') {
    if ($kod=='0000') $res = array('Kod'=>$kod, 'Popis'=>'OK - Spis byl predan z ESS do AIS', 'ErrSql'=>$errSql);
    if ($kod=='1000') $res = array('Kod'=>$kod, 'Popis'=>'Chyba - Spis neexistuje nebo neni v drzeni ESS', 'ErrSql'=>$errSql);
    if ($kod=='1001') $res = array('Kod'=>$kod, 'Popis'=>'Chyba - Nektery z dokumentu ve spisu neni v drzeni ESS', 'ErrSql'=>$errSql);
    if ($kod=='1002') $res = array('Kod'=>$kod, 'Popis'=>'Chyba - Spis nebyl predan', 'ErrSql'=>$errSql);
  }

  return $res;
}

function NastavText($type,$kod) {
  if ($type=='DokumentZalozeni') {
    if ($kod=='001') $res = 'prirazeni cj.';
  }
  
  if ($type=='DokumentZruseni') {
    if ($kod=='001') $res = 'ISRZP zruseni / zneplatneni dokumentu';
  }
  
  if ($type=='SpisZruseni') {
    if ($kod=='001') $res = 'ISRZP zruseni / zneplatneni spisu';
  }
  
  if ($type=='VypraveniZruseni') {
    if ($kod=='001') $res = 'ISRZP  zruseni / zneplatneni vypraveni';
  }
  
  return $res;
}
?>
