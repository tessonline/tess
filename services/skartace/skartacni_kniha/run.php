<?php
require("tmapy_config.inc");
require(FileUp2(".admin/run2_.inc"));
require(FileUp2(".admin/security_obj.inc"));
require_once(Fileup2("html_header_title.inc"));

$USER_INFO = $GLOBALS["POSTA_SECURITY"]->GetUserInfo();
$id_user=$USER_INFO["ID"];
$q = new DB_POSTA;

if ($GLOBALS['DOKUMENT_ID'] == -1) {

  $skartace = $GLOBALS['SKARTACE_ID'];
  if (!$skartace) {
    $sql = "select min(id) as MINID from cis_posta_skartace";
    $q->query($sql);
    $q->next_Record();
    $skartace = $q->Record['MINID'];
  }

  $GLOBALS['ODBOR'] = $GLOBALS['ODBOR'] ? $GLOBALS['ODBOR'] : 0;
  $text_cj = $GLOBALS['TEXT_CJ'];
  $sql = "insert into posta (ROK,ODES_TYP,CISLO_JEDNACI1,CISLO_SPISU1,VEC,ODBOR,STORNOVANO,STATUS,SKARTACE,TEXT_CJ,MAIN_DOC) VALUES (".$GLOBALS['ROK_PREDANI'].",'Z',-2,0,'" . $GLOBALS['VEC'] . "','" . $GLOBALS['ODBOR'] . "','rucni vypujcka',-3,'$skartace','$text_cj',1)";
//  $sql = 'select min(dokument_id) as doc_id from posta_spisovna ';
  $q->query($sql);
  $GLOBALS['DOKUMENT_ID'] = $q->getLastId('posta','id');
}

if ($GLOBALS['EDIT_ID'] && $GLOBALS['LOKACE_ID']) {
  if (is_array($GLOBALS['EDIT_ID'])) {
    foreach($GLOBALS['EDIT_ID'] as $id) {
       $q->query('select * from posta_spisovna where id=' . $id);
       $q->Next_Record(); $doc_id = $q->Record['DOKUMENT_ID'];
       $lokace_text = EedTools::GetLokace($GLOBALS['LOKACE_ID']);
       $text = 'dokument byl editován ve spisovně, lokace ve spisovně: <b>' . $lokace_text . '</b>';
       EedTransakce::ZapisLog($doc_id, $text, 'DOC', $id_user);
    }
  }
  else {
     $lokace_text = EedTools::GetLokace($GLOBALS['LOKACE_ID']);
     $text = 'dokument byl editován ve spisovně, lokace ve spisovně: <b>' . $lokace_text . '</b>';
     EedTransakce::ZapisLog($GLOBALS['DOKUMENT_ID'], $text, 'DOC', $id_user);
  }
}

Run_(array("showaccess"=>true,"outputtype"=>3,"to_history"=>true));

require_once(Fileup2("html_footer.inc"));  

?>

