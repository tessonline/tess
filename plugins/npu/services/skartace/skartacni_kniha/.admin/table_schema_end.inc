<?php
$znackaClass = LoadClass('EedZnacka', 0);

function ShowUkladaciZnacka($id) {
  global $znackaClass;
  if (!$znackaClass) $znackaClass = LoadClass('EedZnacka', 0);
  $znackaNU = $znackaClass->GetZnackaNameProCJ($id);
  return $znackaNU[0];
}

if (!$GLOBALS['SPISOVNA_ID'] && !$GLOBALS['SHOW_BOX'] && !$GLOBALS['HISTORY_ID'] && !$GLOBALS['SKARTACNI_RIZENI_ID']) {
  $TABLE_CONFIG["schema"][]= array( field=>"ShowUkladaciZnacka(ID)", "label"=>"Značka", width=>"10%");
}
else {
  $TABLE_CONFIG["schema"][]= array( field=>"ShowUkladaciZnacka(DOKUMENT_ID)", "label"=>"Značka", width=>"10%");
}