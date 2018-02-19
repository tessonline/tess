<?php
if (($GLOBALS['ODES_TYP'] == 'C' || $GLOBALS['ODES_TYP'] == 'G') && $GLOBALS['ODES_TYP_WHOIS']<>$GLOBALS['ODES_TYP']) {
  $sql = 'update posta set odes_typ=\'O\' where id=' . $GLOBALS['lastid'];
  $q = new DB_POSTA;
  $q->query($sql);
}


if ($GLOBALS['WHOIS_TYPOVYSPISID']>0 && $GLOBALS['WHOIS_TYPOVYSPISSOUCAST']>0 && $GLOBALS['lastid']) {

  $cj_obj = LoadClass('EedCj',$GLOBALS['lastid']);
  $docs = $cj_obj->GetDocsInTypSpis($GLOBALS['WHOIS_TYPOVYSPISID']);
  print_r($docs);
  //pokud jeste neni zalozen, tak zalozime
  if (!in_array($GLOBALS['lastid'], $docs))
    $cj_obj->dejDokumentDoTypSpisu($GLOBALS['lastid'], $GLOBALS['WHOIS_TYPOVYSPISID'], $GLOBALS['WHOIS_TYPOVYSPISSOUCAST']);
}



