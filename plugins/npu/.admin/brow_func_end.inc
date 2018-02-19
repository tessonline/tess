<?php
if ($GLOBALS['ZNACKA_ID']) {
  $GLOBALS['ID'][]=-1;

  require_once(GetAgendaPath('POSTA',false,false).'/.admin/classes/EedZnacka.inc');
  $znacka_obj = new EedZnacka(0);
//print_r($GLOBALS['ZNACKA_ID']);
  $res = $znacka_obj->_GetSpisIDProIDZnacka($GLOBALS['ZNACKA_ID']);
//print_r($res);
  if (count($res)>0) $GLOBALS['ID'] = $res;
  $GLOBALS['MAIN_DOC'] = 1;
}

if ($GLOBALS['PAMATKA_REJSTRC_TEXT'] || $GLOBALS['PAMATKA_IDREG_TEXT']) {
  $GLOBALS['ID'][]=-1;

//  require_once(GetAgendaPath('POSTA',false,false).'/.admin/classes/EedZnacka.inc');
  $GLOBALS['IDREG'] = $GLOBALS['PAMATKA_IDREG_TEXT'];
  $GLOBALS['REJSTC'] = $GLOBALS['PAMATKA_REJSTRC_TEXT'] . '%';

  $sql = table(
    array(
      'agenda' => 'POSTA_SPIS',
      'return_sql' => true
    )
  );
//echo $sql;
  $pam = new DB_MONUMNIS;
  $pam -> query($sql);
  while ($pam->Next_Record()) {
    $GLOBALS['ID'][] = $pam->Record['SPIS_ID'];
  }
//print_r($res);
}
