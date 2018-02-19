<?php

if ($GLOBALS['EDIT_ID'] && !$is_multiedit) {
  $sql = 'select * from posta_carovekody where dokument_id=' . $GLOBALS['EDIT_ID'];
  $q = new DB_POSTA;
  $q->query($sql);
  $q->Next_Record();
  $GLOBALS['EXTERNI_CK'] = $q->Record['CK'];

  if ($is_new) $GLOBALS['EXTERNI_CK'] = '';
}

$FORM_CONFIG["schema"][] = array("elements"=>array(
        array( "type"=>"text", "name"=>"EXTERNI_CK","size"=>40),
        ),
        "visible"=>!$is_multiedit && ($GLOBALS['ODESLANA_POSTA']=='t' || $is_new || $is_insert),
        "label"=>"PID:");

$FORM_CONFIG["schema"][] = array("elements"=>array(
        array( "type"=>"text", "name"=>"EXTERNI_CK","frozen"=>true,"value"=>($GLOBALS['EXTERNI_CK'] ? $GLOBALS['EXTERNI_CK'] : $GLOBALS['CONFIG']['ID_PREFIX'].$GLOBALS['EDIT_ID'])),
        ),
        "visible"=>!$is_multiedit && !$is_filter && $is_edit && $GLOBALS['ODESLANA_POSTA']<>'t',
        "label"=>"PID:");

