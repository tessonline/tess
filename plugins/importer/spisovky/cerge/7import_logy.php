<?php
echo "<h1>Transakèní log</h1>";
echo "<p>";
/*
echo "smazeme jiz vytvoreny log ";
$sql = "delete from posta_transakce where doc_id in (select id from posta where dalsi_id_agenda like 'SPISOVKA3CERGE:%')";
$db_to->query($sql);
echo ".... hotovo <br/>";

$sql = 'select * from s3_log_dokument order by dokument_id asc, id asc';
$db_from -> query($sql);
while ($db_from->Next_Record()) {

  $id_puv = $db_from->Record['DOKUMENT_ID'];
  $date = $db_from->Record['DATE'];
  $text = iconv('ISO-8859-2','UTF-8', $db_from->Record['POZNAMKA']);

  $dalsi_id_agenda = 'SPISOVKA3CERGE:' . $db_from->Record['DOKUMENT_ID'];

  //zjistime, jestli uz je zalozeno ve spisovce
  $sql = "select * from posta where dalsi_id_agenda like '" . $dalsi_id_agenda . "'";
  $db_to->query($sql);
  $db_to->Next_Record();
  if ($db_to->Record['ID']>0) {

    $so = $db_to->Record['SUPERODBOR'];
    $doc_id = $db_to->Record['ID'];
    $user = LoadClass('EedUser', $db_to->Record['REFERENT']);
    $jmeno = $user->cele_jmeno;
    $typ = 'DOC';
    $user_id = $db_to->Record['REFERENT'];

    $doc_id = $db_to->Record['ID'];

    $sql = 'insert into posta_transakce (DOC_ID, JMENO, TEXT, TYP,LAST_USER_ID,ID_SUPERODBOR,LAST_TIME) VALUES';
    $sql .= "($doc_id,'$jmeno','$text','$typ',$user_id,$so,'$date')";
    $db_to->query($sql);

  }

}
//    $cis['skartace'][1275] = array('id' => 1275, 'kod'=> $kod_puv, 'tess_id' => -1);

echo "</p>";

//print_r($cis['skartace']);
//$cis['skartace'];
*/
