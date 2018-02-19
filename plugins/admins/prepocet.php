<?php
require('tmapy_config.inc');
require(FileUp2('.admin/config.inc'));
require(FileUp2('.admin/status.inc'));
require(FileUp2('html_header_full.inc'));

echo '<h1>Přepočet stavu</h1>';
$doc_id = (int) $_GET['DOC_ID'];
if (!$doc_id) Die('stop');
$cj_obj = LoadClass('EedCj',$doc_id);
$docs = $cj_obj->GetDocsInCj($doc_id);

$USER_INFO = $GLOBALS["POSTA_SECURITY"]->GetUserInfo();

foreach($docs as $doc) {
  echo "Provádím přepočet $doc - ";
  NastavStatus($doc, $USER_INFO['ID']);
  echo "hotovo.<br/>";
}

echo '<p><br/><h2>vše hotovo</h2></p>';
echo '<input type="button" name="" value="Zavřít" class="btn" onclick="window.opener.document.location.reload();">';

require(FileUp2('html_footer.inc'));
