<?php
echo '<h1>Import souborů</h1>';
include_once(FileUp2('.admin/upload_.inc'));

$uplobj=Upload(array('create_only_objects'=>true,'agenda'=>'POSTA','noshowheader'=>true));
$main_dir = '/var/www/html/virtuals/ders-uk.tmapserver.cz/data/spis3/client/';


// $sql = "select id from posta where dalsi_id_agenda like 'SPISOVKA3CERGE:%'";
// $db_to->query($sql);
// while ($db_to->Next_Record()) {
//   echo "mazu " . $db_to->Record['ID'].'<br/>';
//   $ret = $uplobj['table']->deleteAllUploadForAgendaRecord($db_to->Record['ID'], array());
//   print_r($ret);
// }

//$sql = 'SELECT * FROM  s3_dokument_to_file d LEFT JOIN s3_file f ON d.file_id = f.id  order by f.id asc';
$sql = 'SELECT * FROM  s3_dokument_to_file d LEFT JOIN s3_file f ON d.file_id = f.id  where dokument_id>2462 order by f.id asc';


echo $sql;
$db_from2->query($sql);
while ($db_from2->Next_Record()) {

  $doc_id = $db_from2->Record['DOKUMENT_ID'];
  $user = $db_from2->Record['USER_ID'];
  $nazev = $db_from2->Record['NAZEV'];
  $popis = $db_from2->Record['POPIS'];
  if ($popis<>'') $nazev .= '(' . $popis .')';
  $file = $db_from2->Record['REAL_PATH'];

  $dalsi_id_agenda = 'SPISOVKA3CERGE:' . $db_from2->Record['DOKUMENT_ID'];

  //zjistime, jestli uz je zalozeno ve spisovce
  $sql = "select * from posta where dalsi_id_agenda like '" . $dalsi_id_agenda . "'";
  $db_to->query($sql);
  $db_to->Next_Record();
  if ($db_to->Record['ID']>0) {
  echo $sql.'<br/>';
    $id_posta = $db_to->Record['ID'];
    $GLOBALS['DESCRIPTION'] = iconv('ISO-8859-2','UTF-8', $nazev);
    $GLOBALS['LAST_USER_ID'] = $db_to->Record['REFERENT'];
    $GLOBALS['LAST_DATE'] = $db_to->Record['LAST_DATE'];

    $file = $main_dir . $file;

    if (file_exists($file))   $ret = $uplobj['table']->SaveFileToAgendaRecord($file, $id_posta);
    else echo 'Soubor ' . $file . ' nenalezen<br/>';


  }
}

