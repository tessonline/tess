<?php
require('tmapy_config.inc');
require_once(FileUp2('.admin/run2_.inc'));
include_once(FileUp2(".admin/setting_.inc"));
require_once(Fileup2('html_header_title.inc'));


$GLOBALS['SKRYT_STORNOVANO'] = $GLOBALS['SKRYT_STORNOVANO'] ? $GLOBALS['SKRYT_STORNOVANO'] : 0;
$GLOBALS['SKRYT_VYRAZENE'] = $GLOBALS['SKRYT_VYRAZENE'] ? $GLOBALS['SKRYT_VYRAZENE'] : 0;
$GLOBALS['SKRYT_VE_SPISOVNE'] = $GLOBALS['SKRYT_VE_SPISOVNE'] ? $GLOBALS['SKRYT_VE_SPISOVNE'] : 0;
$GLOBALS['UKAZOVAT_OBALKY'] = $GLOBALS['UKAZOVAT_OBALKY'] ? $GLOBALS['UKAZOVAT_OBALKY'] : 0;
$GLOBALS['UKAZAT_FILTR_V_DETAILU'] = $GLOBALS['UKAZAT_FILTR_V_DETAILU'] ? $GLOBALS['UKAZAT_FILTR_V_DETAILU'] : 0;

$GLOBALS['UKAZAT_BAREVNY_FILTR'] = $GLOBALS['UKAZAT_BAREVNY_FILTR'] ? $GLOBALS['UKAZAT_BAREVNY_FILTR'] : 0;
$GLOBALS['NEZASILAT_EMAILY'] = $GLOBALS['NEZASILAT_EMAILY'] ? $GLOBALS['NEZASILAT_EMAILY'] : 0;

if (is_array($GLOBALS['TABLE']))
  $sloupce = array_keys($GLOBALS['TABLE']);
else
  $sloupce = array();

if (is_array($GLOBALS['TABLE_SPIS']))
  $sloupce_spis = array_keys($GLOBALS['TABLE_SPIS']);
else
  $sloupce_spis = array();

$set = array();
$set['POSTA']['USER_CONFIG'] = array(
  'SKRYT_STORNOVANO' => $GLOBALS['SKRYT_STORNOVANO'],
  'SKRYT_VYRAZENE' => $GLOBALS['SKRYT_VYRAZENE'],
  'SKRYT_VE_SPISOVNE' => $GLOBALS['SKRYT_VE_SPISOVNE'],
  'NA_STRANKU' => $GLOBALS['NA_STRANKU'],
  'UKAZOVAT_OBALKY' => $GLOBALS['UKAZOVAT_OBALKY'],
  'UKAZAT_FILTR_V_DETAILU' => $GLOBALS['UKAZAT_FILTR_V_DETAILU'],
  'UKAZAT_BAREVNY_FILTR' => $GLOBALS['UKAZAT_BAREVNY_FILTR'],
  'NEZASILAT_EMAILY' => $GLOBALS['NEZASILAT_EMAILY'],
  'DEFAULT_STAV' => $GLOBALS['DEFAULT_STAV'],
  'DEFAULT_TABLE_SCHEMA' => $sloupce,
  'DEFAULT_TABLE_SCHEMA_SPIS' => $sloupce_spis,




);

$sett = new SETTING_OBJ;

if ($GLOBALS['SET_DEFAULT'] == 1) {
  $set = array();
  $set['POSTA']['USER_CONFIG'] = array();
}

$a = $sett->set($set, $USER_INFO['ID']);
echo '
<script language="JavaScript" type="text/javascript">
  window.opener.document.location.reload();
  window.close();
</script>

';

require_once(Fileup2('html_footer.inc'));
