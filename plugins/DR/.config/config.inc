<?php
$dbx = new DB_POSTA;
$sql = 'select * from posta_plugins_dr_app';
$dbx->query($sql);

while ($dbx->Next_Record()) {
  $idDRR = 1000 + ($dbx->Record['ID']*10);
  $GLOBALS['CONFIG_POSTA']['of_select_add']['of_select_vita'][($idDRR+1)] = array('value' => ($idDRR+1), 'label' => 'Dokument by se měl vyřídit v DR: '. $dbx->Record['NAZEV'], 'fullselect' =>0);
  $GLOBALS['CONFIG_POSTA']['of_select_add']['of_select_vita'][($idDRR+2)] = array('value' => ($idDRR+2), 'label' => 'Dokument se vyřizuje v DR: '. $dbx->Record['NAZEV'], 'fullselect' =>1);
}

