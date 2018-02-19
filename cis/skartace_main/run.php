<?php
require("tmapy_config.inc");
require(FileUp2(".admin/run2_.inc"));
require_once(Fileup2("html_header_title.inc"));
$GLOBALS["AKTIVNI"]=$GLOBALS["AKTIVNI"]?$GLOBALS["AKTIVNI"]:'0';

if (!$GLOBALS['EDIT_ID'] && !$GLOBALS['DELETE_ID']) {
	$text = 'Vytvoření nového spisového plánu <b>(ID)</b>';
}
if ($GLOBALS['EDIT_ID'] && !$GLOBALS['DELETE_ID']) {
	$text = 'Editace spisového plánu <b>(ID)</b>';
}

$text .='<br/>
Název: <b>' . $GLOBALS['NAZEV']. '</b></br>
Platnost od: <b>' . $GLOBALS['PLATNOST_OD']. '</b></br>
Platnost do: <b>' . $GLOBALS['PLATNOST_DO']. '</b></br>
Aktivni: <b>' . $GLOBALS['AKTIVNI'] . '</b>';

if (!$GLOBALS['EDIT_ID'] && $GLOBALS['DELETE_ID']) {
	$text = 'Smazání spisového plánu <b>' . $GLOBALS['DELETE_ID'] . '</b>';
}

$id = Run_(array("showaccess"=>true,"outputtype"=>1));

$text = str_replace('(ID)', '(' . $id . ')', $text);
$USER_INFO = $GLOBALS["POSTA_SECURITY"]->GetUserInfo();
$LAST_USER_ID = $USER_INFO['ID'];

EedTransakce::ZapisLog(0, $text, 'SPISZNAK', $LAST_USER_ID);

echo '
<script language="JavaScript" type="text/javascript">
  if (window.opener.document) {
    window.opener.document.location.reload();
  }
//  window.close();
</script>
';
require_once(Fileup2("html_footer.inc"));  

