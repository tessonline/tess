<?php
  require ("tmapy_config.inc");
  require(FileUp2(".admin/classes//transformace/FullText.inc"));
  $charset = 'UTF-8';
  $ft = new FullText($charset);
  $text_fulltext = $ft->transform($GLOBALS['FULLTEXT']);
  $sql = "SELECT to_tsquery('simple',E'" . $text_fulltext. "') as q";
  $q = new DB_POSTA();
  try {
    $q->query($sql);
    $q->Next_Record();
    echo '0';
  } catch (Exception $e) {
    echo  'Chyba:'.$path.$e->getMessage();
  }
