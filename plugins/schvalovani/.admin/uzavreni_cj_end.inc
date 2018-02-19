<?php

include_once(FileUp2('plugins/schvalovani/.admin/schvalovani.inc'));

$q = new DB_POSTA;
$EedCj = LoadClass('EedCj', $spis_id);
$docIDS = $EedCj->GetDocsInCj($spis_id);


$pole = Skartace_Pole($skartace);
$sql = 'select * from posta where id in (' . implode(',', $docIDS). ') ';
$q->query($sql);
while ($q->Next_Record()) {

  if (JeVeSchvaleni($q->Record['ID'])) {
    $GLOBALS['chyby']['S1'] = 'Dokument <b>' . $q->Record['ID'] . '</b> je ve schvalovacim procesu. Je nutné dokončit schvalovací proces.';
    $chyba[] = 'S1';
  }

}

