<?php

echo "<h1>Skartační číselník</h1>";
echo "<p>";
$sql = 'select * from s3_spisovy_znak';
$db_from -> query($sql);
while ($db_from->Next_Record()) {

  $id_puv = $db_from->Record['ID'];
  $kod_puv = $db_from->Record['NAZEV'];

  $sql = "select * from cis_posta_skartace where aktivni=1 and kod like '$kod_puv'";
  $db_to->query($sql);
  if ($db_to->Num_Rows() == 0) {
    $sql = "select * from cis_posta_skartace where kod like '$kod_puv'";
    $db_to->query($sql);
  }
  $db_to->Next_Record();
  $tess_id = $db_to->Record['ID'];

  if ($tess_id>0)
    $cis['skartace'][$id_puv] = array('id' => $id_puv, 'kod'=> $kod_puv, 'tess_id' => $tess_id);
  else
    echo "CHYBA - nenalezena hodnota <b>$id_puv</b> v TESS pro <font color='red'>$kod_puv</font><br/>";

}


//RUCNI MAPOVANI
$cis['skartace'][1066] = array('id' => 1066, 'kod'=> $kod_puv, 'tess_id' => 3320);
$cis['skartace'][1275] = array('id' => 1275, 'kod'=> $kod_puv, 'tess_id' => 3210);
$cis['skartace'][1319] = array('id' => 1319, 'kod'=> $kod_puv, 'tess_id' => 3235);


echo "</p>";

//print_r($cis['skartace']);
//$cis['skartace'];



