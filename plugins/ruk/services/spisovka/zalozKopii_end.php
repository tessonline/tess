<?php

  $sql = 'select * from posta_carovekody where dokument_id=' . $GLOBALS['ID'];
  $q = new DB_POSTA;
  $q->query($sql);
  $q->Next_Record();
  $GLOBALS['EXTERNI_CK'] = $q->Record['CK'] ? $q->Record['CK'] : $GLOBALS['CONFIG']['ID_PREFIX'] . str_pad($GLOBALS['ID'], 10, '0', STR_PAD_LEFT);

  $sql = 'select * from posta_carovekody where dokument_id=' . $GLOBALS['noveID'];
  $q = new DB_POSTA;
  $q->query($sql);
  if ($q->Num_Rows() == 0)
    $sql = "insert into posta_carovekody (DOKUMENT_ID,CK) VALUES (".$GLOBALS['noveID'].",'".$GLOBALS['EXTERNI_CK']."')";
  else
    $sql = "update posta_carovekody set ck='".$GLOBALS['EXTERNI_CK']."' where dokument_id=" . $GLOBALS['noveID'];
  $q->query($sql);

  $sql = "select * from cis_posta_skartace where text like 'ZI %' and vyber=1";
  echo $sql.'<br/>';
  $q = new DB_POSTA;
  $q->query($sql);
  $q->Next_Record();
  $skartace = $q->Record['ID'] ? $q->Record['ID'] : 0;

  if ($skartace>0) {
    $sql = 'update posta set skartace=' . $skartace . ' where id=' . $GLOBALS['noveID'];
  echo $sql.'<br/>';
    $q->query($sql);
  }

