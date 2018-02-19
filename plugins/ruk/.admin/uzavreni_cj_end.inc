<?php
include_once(FileUp2(".admin/upload_.inc"));
$uplobj = Upload(array('create_only_objects'=>true,'agenda'=>'POSTA','noshowheader'=>true));

$GLOBALS['chyby']['R1'] = 'Není vyplněn spisový znak. Opravte to prosím.';

$q = new DB_POSTA;
$EedCj = LoadClass('EedCj', $spis_id);
$docIDS = $EedCj->GetDocsInCj($spis_id);

$skartace = $EedCj->skartace_id;
$text_inicializacni = 'inicializační dokument';

if (!$skartace || $skartace == 0) {
  $chyba[] = 'R1';
}
else {
  $pole = Skartace_Pole($skartace);

  $sql = 'select * from posta_spisovna where dokument_id='.$spis_id;
  $q->query($sql); $q->Next_Record();
  $skartace_id = $q->Record['SKARTACE_ID'] ? $q->Record['SKARTACE_ID'] : 0;
  if ($skartace_id>0) {
    $text_inicializacni = 'celé čj./spis';
    $pole = Skartace_Pole($skartace_id);
  }


  $sql = 'select * from posta where id in (' . implode(',', $docIDS). ') and typ_dokumentu like \'D\'';
  $q->query($sql);

  if ($pole['znak']=='A' or $pole['znak']=='V') {
    if ($q->Num_Rows()>0 && $pole['doba']>9) {
      $idcka = array();
      while($q->Next_Record()) $idcka[] = $q->Record['ID'];
      $GLOBALS['chyby']['R2'] = 'ČJ je označeno skartačním písmenem A nebo V s dobou 10 let a více'
                                .' ( = všechny dokumenty musí být tedy označeny příznakem analogové). '
                                .'Dokumenty: <b>' . implode('</b>, <b>', $idcka) . '</b> jsou ale digitální. Prosím opravte to';
      $chyba[] = 'R2';
    }
  }

/*
  $sql = 'select * from posta where id in (' . implode(',', $docIDS). ') and typ_dokumentu like \'D\'';
  $q->query($sql);
  while ($q->Next_Record()) {
    $listu = $q->Record['POCET_PRILOH'];
    $listu = (int) $listu;
    $upload_records = $uplobj['table']->GetRecordsUploadForAgenda($q->Record['ID']);
    $pocet_upload = count($upload_records);
    if ($listu <> $pocet_upload) {
       $GLOBALS['chyby']['C'.$q->Record['ID']] = 'Dokument <b>' . $q->Record['ID'] . '</b> je digitální dokument a nesouhlasí počet příloh (<b>'.$listu.'</b>) s počtem souborů v uploadu (<b>'.$pocet_upload.'</b>). Prosím opravte počet příloh.';
       $chyba[] = 'C'.$q->Record['ID'];
    }

  }
*/

  $sql = 'select * from posta where id in (' . implode(',', $docIDS). ')';
  $q->query($sql);

  while ($q->Next_Record()) {
    $poleID = Skartace_Pole($q->Record['SKARTACE']);
    if ($poleID['doba'] > $pole['doba']) {
      $GLOBALS['chyby']['A'.$q->Record['ID']] = 'Dokument <b>'.$q->Record['ID'].'</b> má delší archivační dobu (<b>'.$poleID['doba'].'</b>) než '.$text_inicializacni.' (<b>'.$pole['doba'].'</b>).';
      $chyba[] = 'A'.$q->Record['ID'];
    } else {
      if ($pole['znak'] == 'S' and ($poleID['znak']=='A' || $poleID['znak']=='V')) {
        $GLOBALS['chyby']['B'.$q->Record['ID']] = 'Dokument <b>' . $q->Record['ID'] . '</b> je označen důležitějším písmenem (<b>'.$poleID['znak'].'</b>) než '.$text_inicializacni.' (<b>S</b>)';
        $chyba[] = 'B'.$q->Record['ID'];
      }
      if ($pole['znak'] == 'V' and $poleID['znak']=='A') {
        $GLOBALS['chyby']['B'.$q->Record['ID']] = 'Dokument <b>' . $q->Record['ID'] . '</b> je označen důležitějším písmenem (<b>A</b>) než '.$text_inicializacni.' (<b>S</b>)';
        $chyba[] = 'B'.$q->Record['ID'];
      }
    }
  }

}

