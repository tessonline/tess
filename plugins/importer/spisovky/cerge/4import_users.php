<?php

echo "<h1>Uživatelé číselník</h1>";

echo "<p>";
$sql = 'SELECT * FROM  `s3_osoba_to_user` u LEFT JOIN s3_osoba o ON u.osoba_id = o.id ';
$db_from -> query($sql);
while ($db_from->Next_Record()) {

  $id_user = $db_from->Record['USER_ID'];
  $prijmeni = iconv('iso-8859-2', 'UTF-8', $db_from->Record['PRIJMENI']);
  $jmeno = iconv('iso-8859-2', 'UTF-8', $db_from->Record['JMENO']);

  $sql = "select * from security_user where fname ilike '$jmeno' and lname ilike '$prijmeni'";
  $db_to->query($sql);
  if ($db_to->Num_Rows() == 0) {
    $sql = "select * from security_user where fname ilike '%$jmeno%' and lname ilike '%$prijmeni%'";
    $db_to->query($sql);
  }
  if ($db_to->Num_Rows() == 0) {
    echo "CHYBA - nenalezena hodnota <b> $id_user </b> v TESS pro <font color='red'>$jmeno $prijmeni</font><br/>";

  }
  else
  while ($db_to->Next_Record()) {

    if ($db_to->Record['PRACOVISTE'] == 126)
      $cis['users_2'][$id_user] = array('label' => $jmeno .' ' . $prijmeni, 'tess_id' => $db_to->Record['ID']);
    if ($db_to->Record['PRACOVISTE'] == 102148)
      $cis['users_1'][$id_user] = array('label' => $jmeno .' ' . $prijmeni, 'tess_id' => $db_to->Record['ID']);

  }
}

