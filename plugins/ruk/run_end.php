<?php

//    dokument_id integer,
//    ck character varying(50)

if ($GLOBALS['EXTERNI_CK'] && $GLOBALS['lastid']) {
  $sql = 'select * from posta_carovekody where dokument_id=' . $GLOBALS['lastid'];
  $q = new DB_POSTA;
  $q->query($sql);
  if ($q->Num_Rows() == 0)
    $sql = "insert into posta_carovekody (DOKUMENT_ID,CK) VALUES (".$GLOBALS['lastid'].",'".$GLOBALS['EXTERNI_CK']."')";
  else
    $sql = "update posta_carovekody set ck='".$GLOBALS['EXTERNI_CK']."' where dokument_id=" . $GLOBALS['lastid'];
  $q->query($sql);
}

