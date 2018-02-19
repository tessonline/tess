<?php
NewWindow(array("fname" => "AgendaSpis", "name" => "AgendaSpis", "header" => true, "cache" => false, "window" => "edit"));

Function ShowUrl ($id, $smer) {

  $href = '<a href="brow.php?ID=' . $id . '">ODKAZ</a>';
  return $href;
}

function JeDokumentDr($id, $typ) {
  static $db;
  $href = '<a href="#" onClick="javascript:NewWindowAgendaSpis(\'send.php?ID=' . $id . '&typ=' . $typ.'\');" title="Odeslat do aplikace">Poslat</a>';
  if (!$db) $db = new DB_POSTA;
  $doc = LoadSingleton('EedDokument', $id);
  if ($doc->db->Record['ODESLANA_POSTA'] == 'f') return '';
  $agenda = $doc->db->Record['DALSI_ID_AGENDA'];
  if (!strpos($agenda, 'R-')) return '';

  if ($doc->status == 8 && $typ == 'DOR') return '<i>není staženo</i>';

  if ($typ == 'ODZ') $append="odz>0";
  if ($typ == 'DOR') $append="dorucenka>0";

  $sql = "select * from posta_plugins_dr_app_dorucenky where posta_id=" . $id ." and $append";
  $db->query($sql);
  if ($db->Num_Rows()>0) return 'OK';
  else return $href;
}
function DRJePoslany($id) {
  $doc = LoadSingleton('EedDokument', $id);
  if ($doc->db->Record['ODESLANA_POSTA'] == 't') return '';
  $stav = $doc->db->Record['STAV'];
  if ($stav<1000) return '';
  if (substr($stav, -1)=='1')
    $href = '<a href="#" onClick="javascript:NewWindowAgendaSpis(\'sendPrichozi.php?ID=' . $id . '\');" title="Odeslat do aplikace">Poslat</a>';
  if (substr($stav, -1)=='2')
    $href = 'JE POSLANO';
  return $href;
}