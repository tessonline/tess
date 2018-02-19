<?php
require("tmapy_config.inc");
require(FileUp2(".admin/run2_.inc"));
require_once(Fileup2("html_header_title.inc"));

$GLOBALS['AKTIVNI'] = $GLOBALS['AKTIVNI'] ? $GLOBALS['AKTIVNI'] : '0';
$GLOBALS['VYBER'] = $GLOBALS['VYBER'] ? $GLOBALS['VYBER'] : '0';
$GLOBALS['SHOW_VS'] = $GLOBALS['SHOW_VS'] ? $GLOBALS['SHOW_VS'] : '0';

if (!$GLOBALS['EDIT_ID'] && !$GLOBALS['DELETE_ID']) {
	$text = 'Nový záznam: (CO) <b>(ID)</b>';
}
if ($GLOBALS['EDIT_ID'] && !$GLOBALS['DELETE_ID']) {
	$text = 'Editace (CO) <b>(ID)</b>';
}
$text .='<br/>
Nadřazené ID: <b>' . $GLOBALS['NAZEV']. '</b></br>
Kod: <b>' . $GLOBALS['KOD']. '</b></br>
Text: <b>' . $GLOBALS['TEXT']. '</b></br>
Znak: <b>' . $GLOBALS['SKAR_ZNAK']. '</b></br>
Doba: <b>' . $GLOBALS['DOBA']. '</b></br>
Viditelné: <b>' . $GLOBALS['SHOW_VS']. '</b></br>
Aktivni: <b>' . $GLOBALS['AKTIVNI'] . '</b>';

if ($GLOBALS['TYP'] == 1) $text = str_replace('(CO)', ' věcné skupiny', $text);
else $text = str_replace('(CO)', 'spisového znaku', $text);

if (!$GLOBALS['EDIT_ID'] && $GLOBALS['DELETE_ID']) {
	$text = 'Smazání věcné skupiny/spis. znaku <b>' . $GLOBALS['DELETE_ID'] . '</b>';
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
