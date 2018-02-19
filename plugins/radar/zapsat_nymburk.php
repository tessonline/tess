<?php
require("tmapy_config.inc");
include(FileUp2(".admin/brow_.inc"));
require_once(FileUp2('.admin/classes/EedRadar.inc'));
require(FileUp2('html_header_full.inc'));

$q = new DB_POSTA;
$a = new DB_POSTA;

$id = EedRadar::getIDKonfigurace();
$sql = 'select id from posta where id_puvodni=' . $id;
$q->query($sql);
while ($q->Next_Record()) {


  $sql = 'select * from posta_transakce where doc_id=' . $q->Record['ID'].' order by id asc';
  $a->query($sql);
  $a->Next_Record();

  $text = $a->Record['TEXT'];
  list ($xxxx, $file) = explode('var/', $text);
  if ($file) {
     $sql = "insert into posta_plugins_radar_ulozeno (posta_id,file) VALUES (" . $q->Record['ID'] .",'" . basename($file) . "')";
     $a->query($sql);
  }

}
