<?php

function NactiVytvoreneSpisy($so = 0, $kod = 'C') {
  static $q;
  if (!$q) $q = new DB_POSTA;
  $sql = 'SELECT * from posta where superodbor in (' . $so . ') and text_cj ilike (\''. $kod . '%\') AND ID IN (select spis_id from cis_posta_spisy where typovy_spis>0)';
  $res = array();
  $q->query($sql);
  while($q->Next_Record()) {
    $kod = $q->Record['TEXT_CJ'];
    $whois = substr($kod, 1, strpos($kod,'/')-1);
    $res[$whois] = $whois;
  }
  return $res;
}

