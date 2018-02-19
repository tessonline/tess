<?php
require ("tmapy_config.inc");
require (FileUp2(".admin/run2_.inc"));
require_once (Fileup2("html_header_title.inc"));

if (! isset($GLOBALS['DELETE_ID'])){
  
  $q = new DB_POSTA();
  
  $lastId = 0;
  
  // pokud editujeme zaznam
  if ($GLOBALS['EDIT_ID'] != "")
    $GLOBALS['ID']  = $GLOBALS['EDIT_ID'];
   
  // pokud vkladame zaznam
  if ($GLOBALS['EDIT_ID'] == ""){
    $sql = 'select nextval(\'posta_cis_skartacni_rezimy_id_seq\') as lastid';
    $q->query($sql);
    $q->Next_Record();
    $GLOBALS['ID'] = $q->Record['LASTID'];
  }
  
  
  
  $GLOBALS['JID'] = $GLOBALS['CONFIG']['ID_PREFIX'] . 'REZ' . $GLOBALS['ID'] ;
  $jid = $GLOBALS['CONFIG']['ID_PREFIX'] . 'REZ';
}
Run_(array(
  "showaccess" => true,
  "outputtype" => 3 
));

$require_once(Fileup2("html_footer.inc"));

?>

