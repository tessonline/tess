<?php
echo "<h1>Køí¾ová vazba</h1>";
echo "<p>";

$sql = 'select * from s3_souvisejici_dokument order by dokument_id asc, id asc';
$db_from -> query($sql);
while ($db_from->Next_Record()) {

  $id_puv = $db_from->Record['DOKUMENT_ID'];
  $spojit = $db_from->Record['SPOJIT_S_ID'];

  $user_id = $db_from->Record['USER_ID'];
  $date = $db_from->Record['DATE_ADDED'];


  $prac_id = getCiselnik($user_id, 'users_1');
  if (!$prac_id || $prac_id == 0) $prac_id = getCiselnik($user_id, 'users_2');

  $dalsi_id_agenda = 'SPISOVKA3CERGE:' . $db_from->Record['DOKUMENT_ID'];
  $sql = "select * from posta where dalsi_id_agenda like '" . $dalsi_id_agenda . "'";
  $db_to->query($sql);
  $db_to->Next_Record();
  $posta_id = $db_to->Record['ID'];

  $dalsi_id_agenda = 'SPISOVKA3CERGE:' . $db_from->Record['SPOJIT_S_ID'];
  $sql = "select * from posta where dalsi_id_agenda like '" . $dalsi_id_agenda . "'";
  $db_to->query($sql);
  $db_to->Next_Record();
  $nove_id = $db_to->Record['ID'];

  if ($posta_id>0 && $nove_id>0) {

    $sql = 'insert into posta_krizovy_spis (PUVODNI_SPIS,NOVY_SPIS,LAST_DATE,OWNER_ID,LAST_USER_ID) VALUES';
    $sql .= "($posta_id,$nove_id,'$date',$prac_id,$prac_id)";
    echo $sql.'<br/>';
//    $db_to->query($sql);

  }

}

echo "</p>";
Die();
