<?php

function getAktivniText($hodnota) {
  $res = "XX";
  if ($hodnota == 1) $res = 'ANO'; else $res = "NE";
  return $res;
}

function getHodnota($id) {
  static $db;
  if (!$db) $db = new DB_POSTA;
  $sql="select * from posta_deniky_".$id."_seq";
  $db->query($sql);
  $db->Next_Record();
  return $db->Record[LAST_VALUE];
}