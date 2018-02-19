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

  $znak = $pole['znak'];
  $doba = $pole['doba'];
  $sql = 'select * from posta where id in (' . implode(',', $docIDS). ')';
  $q->query($sql);

  while ($q->Next_Record()) {
    $poleID = Skartace_Pole($q->Record['SKARTACE']);
    if ($poleID['doba'] > $doba) {
        $skartace_id = $q->Record['SKARTACE'];
        $pole = $poleID;
        $doba = $poleID['doba'];
    }
    if ($znak == 'S' and ($poleID['znak']=='A' || $poleID['znak']=='V')) {
      $skartace_id = $q->Record['SKARTACE'];
      $znak = $poleID['znak'];
      $pole = $poleID;
    }
    if ($znak == 'V' and $poleID['znak']=='A') {
      $skartace_id = $q->Record['SKARTACE'];
      $znak = $poleID['znak'];
      $pole = $poleID;
    }
  }

  if ($skartace_id <> $skartace && $skartace_id>0) {
     // jdeme ulozit novy skartacni znak ke spisu.
    $sql = 'select * from posta_spisovna where dokument_id='.$spis_id;
    $q->query($sql); 
    if ($q->Num_Rows()>0) {
      $q->Next_Record();
      $sql = 'update posta_spisovna set skartace_id='.$skartace_id.',skar_znak=\''.$znak.'\',lhuta='.$doba.' where id='.$q->Record['ID'];
    }
    else {
      $sql = 'insert into posta_spisovna (DOKUMENT_ID,SKARTACE_ID,SKAR_ZNAK,LHUTA) VALUES ('.$spis_id.','.$skartace.',\''.$znak.'\','.$doba.')';
    }
    $q->query($sql);

    //a znak opravime u inicializacniho dokumentu
//    $sql = 'update posta set skartace='.$skartace_id.' where id='.$spis_id;
//    $q->query($sql);

  }
}

