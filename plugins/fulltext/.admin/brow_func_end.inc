<?php

require(FileUp2(".admin/classes/transformace/FullText.inc"));

if ($GLOBALS['FULLTEXT_SEARCH']) {

//   $sql = "SELECT ts_rank(tsv, q.q) AS rank, p.*
//   FROM posta p, (SELECT to_tsquery('cs','jan:* & test:*') as q) q
//   WHERE p.tsv @@ q.q
//   ORDER BY rank DESC";

  $charset = 'UTF-8';
  $ft  = new FullText($charset);
  $text_fulltext = $ft->transform($GLOBALS['FULLTEXT_SEARCH']);
  
  /* ladici info 
  $fulltext = new DB_POSTA;
  $sql = "SELECT to_tsquery('cs',E'" . $text_fulltext. "') as q";
  $fulltext->query($sql);
  $fulltext->Next_Record(); 
  echo $sql.'<br />';
  echo $fulltext->Record[0].'<br />';*/
  
  
  $sql_fulltext = "SELECT p.*
    FROM posta p, (SELECT to_tsquery('simple',E'" . $text_fulltext. "') as q) q
  WHERE p.tsv @@ q.q LIMIT 1000";

  $fulltext = new DB_POSTA;
  $fulltext->query($sql_fulltext); 
  while ($fulltext->Next_Record()) {
    $GLOBALS['ID'][] = $fulltext->Record['ID'];
  }

}