<?php

function zapisLog($text, $chyba = 0) {
  global $text_logu, $userInfo;
  if(!$userinfo) $userInfo = $GLOBALS['TMAPY_SECURITY']->getUserInfo();
  $login = $userInfo['LOGIN'];

  if ($chyba > 0)
    $text = Date('Y-m-d H:i:s') . ' ' . $login . ' - CHYBA!: ' . $text . chr(10);
  else
    $text = Date('Y-m-d H:i:s') . ' ' . $login . ' - ' . $text;
  $GLOBALS['text_logu'][] = $text;
}

function commitLog($idf) {
/*  global $text_logu;
  static $dirLog;
  $uplobj = Upload(array(
              'create_only_objects' => true,
              'agenda' => 'POSTA_HROMADNY_IMPORT',
              'noshowheader' => true
            )
          );

  if (!$dirLog) $dirLog = GetCreateAgendaDataDir();
  $tmp_file = $dirLog . '/import_log_'.$idf.' .txt';
  $upload_records = $uplobj['table']->GetRecordsUploadForAgenda($idf);
  if (count($upload_records)>0) {
    while (list($key, $val) = each($upload_records)) {
      if ($val['NAME'] == basename($tmp_file)) {
        $id_file = $val['ID'];
        $datafile = $uplobj['table']->GetUploadFiles($val);
      }
    }
  }
//  $tmp_file = '/tmp/import_log.txt';
  $fp = fopen($tmp_file, 'w');
  fwrite($fp, $datafile);
  fwrite($fp, implode(chr(10), $GLOBALS['text_logu']));
  fwrite($fp, chr(10));
  fclose ($fp);

  if ($id_file>0) {
    $uplobj['table']->deleteAllUploadForAgendaRecord($idf, array($id_file));
  }
  unset($uplobj);
  $uplobj = Upload(array(
              'create_only_objects' => true,
              'agenda' => 'POSTA_HROMADNY_IMPORT',
              'noshowheader' => true
            )
          );

  $tmp = $uplobj['table']->SaveFileToAgendaRecord($tmp_file, $idf);
  unlink($tmp_file);*/
}


