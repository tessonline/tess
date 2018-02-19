<?php
require("tmapy_config.inc");
require(FileUp2(".admin/brow_.inc"));
require_once(FileUp2(".admin/security_obj.inc"));
require_once(FileUp2(".admin/security_name.inc"));
require_once(FileUp2(".admin/unispis_funkce.inc"));
require_once(FileUp2(".admin/config.inc"));
require_once(FileUp2(".config/config_rzp.inc"));

$q = new DB_POSTA;
$id = 1000462171;
$id = 1000462159;


while($q->Next_Record()) {
  $IDs[] = $q->Record['DOKUMENT_ID'];
}
//print_r($IDs);
//Die();

foreach($IDs as $ID) {
  $xml = GetPoleDokument($id);
  echo 'Vytvářím XML soubor '.$ID.'.xml<br/>';
  $tmp_soubor = $GLOBALS[CONFIG_POSTA][HLAVNI][tmp_adresar].$ID.'.xml';
  $fname[] = $ID.'.xml';
  $fp = fopen($tmp_soubor,'w');
  fwrite($fp, $xml);
  fclose($fp);
}

//print_r($doc);