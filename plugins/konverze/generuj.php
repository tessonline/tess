<?php
require('tmapy_config.inc');
require(FileUp2('.admin/brow_.inc'));

$ID = (int) $ID;
if ($ID>0) {
  $replace = '<dsig:Object><root><evidencni_udaje><document_id>'.$ID.'</document_id></evidencni_udaje></root></dsig:Object>';
}
else
  $replace = '';

$forms_unc = GetAgendaPath('POSTA_PLUGINS', false, false).'/konverze/';

if ($type == 'LE')
  $file = $GLOBALS['CONFIG_POSTA_KONVERZE']['forms']['LE'];
else
  $file = $GLOBALS['CONFIG_POSTA_KONVERZE']['forms']['EL'];

$fp = fopen ($forms_unc.$file, 'r');
if (!$fp) Die('Nepovedlo se otevrit XML');
$data = fread($fp, filesize($forms_unc.$file));
fclose($fp);

$data=Str_replace('REPLACE',$replace, $data);

$length = filesize($forms_unc.$file) + strlen($replace);

$content_type = "application/fo";
header("Content-type: $content_type");
header("Content-Disposition: attachment; filename=\"konverze.fo\"");
//header("Content-length: ".(string)($length)."");

echo $data;
