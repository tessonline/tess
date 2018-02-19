<?php


if ($GLOBALS['EXTERNI_CK']) {
  $GLOBALS['ID'] = PrevedCPnaID($GLOBALS['EXTERNI_CK'],'');
}

if ($GLOBALS['ID']) {
  $sql = "select * from posta_carovekody where ck like '%" . $GLOBALS['ID']."%'";
  $q = new DB_POSTA;
  $q->query($sql);
  $q->Next_Record();
  $id = $GLOBALS['ID'];
  if ($q->Record['DOKUMENT_ID']>0) $GLOBALS['ID'] = array($id,$q->Record['DOKUMENT_ID']);
}

