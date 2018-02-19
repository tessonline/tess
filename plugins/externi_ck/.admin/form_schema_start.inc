<?php

if ($GLOBALS['EDIT_ID']) {
  $sql = 'select * from posta_carovekody where dokument_id=' . $GLOBALS['EDIT_ID'];
  $q = new DB_POSTA;
  $q->query($sql);
  $q->Next_Record();
  $GLOBALS['EXTERNI_CK'] = $q->Record['CK'];
}

$FORM_CONFIG["schema"][] = array("elements"=>array(
        array( "type"=>"text", "name"=>"EXTERNI_CK","size"=>40),
        ),
        "label"=>"Externí čárový kód:");

