<?php
require('tmapy_config.inc');
require(FileUp2('.admin/config.inc'));
require(FileUp2('.admin/status.inc'));
require(FileUp2('.admin/upload_.inc'));
require(FileUp2('.admin/run2_.inc'));
require(FileUp2('html_header_full.inc'));

echo '<h1>Smazání doručenek u DZ</h1>';
$doc_id = (int) $_GET['DOC_ID'];
if (!$doc_id) Die('stop');
$cj_obj = LoadClass('EedCj',$doc_id);
$docs = $cj_obj->GetDocsInCj($doc_id);

$USER_INFO = $GLOBALS["POSTA_SECURITY"]->GetUserInfo();
$LAST_USER_ID = $USER_INFO['ID'];
$OWNER_ID = $USER_INFO['ID'];
$LAST_TIME = Date('H:i:s');
$LAST_DATE = Date('Y-m-d');

$q = new DB_POSTA;

$uplobj = Upload(array('create_only_objects'=>true,'agenda'=>'POSTA','noshowheader'=>true));

foreach($docs as $doc) {
  echo "Provádím výmaz doručenek u DZ $doc - ";
  $upload_records = $uplobj['table']->GetRecordsUploadForAgenda($doc);
  $soubor=array();
  while (list($key,$val)=each($upload_records)) {
    if ($val['NAME']=='dorucenka.zfo') {
      $uplobj['table']->deleteAllUploadForAgendaRecord($doc, array($val['ID']));
      $sql = 'update posta_DS set datum_precteni=NULL where posta_id=' . $doc;
      $q->query($sql);
      echo " - smazáno - ";
    }
  }
  echo "hotovo.<br/>";
}

echo '<p><br/><h2>vše hotovo</h2></p>';
echo '<input type="button" name="" value="Zavřít" class="btn" onclick="window.opener.document.location.reload();">';

require(FileUp2('html_footer.inc'));
