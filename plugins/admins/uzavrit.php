<?php
require('tmapy_config.inc');
require_once(FileUp2('.admin/config.inc'));
require_once(FileUp2('.admin/status.inc'));
require_once(FileUp2('.admin/status.inc'));
require_once(FileUp2('html_header_full.inc'));
$doc_id = (int) $_GET['DOC_ID'];
if (!$doc_id) Die('stop');

echo '<h1>Uzavření spisu</h1>';

include_once(FileUp2('services/spisovka/uzavreni_spisu/funkce.inc'));

UzavritSpis($doc_id);

$cj_obj = LoadClass('EedCj', $doc_id);
$cj_info = $cj_obj->GetCjInfo($doc_id);

$text = $cj_info['CELY_NAZEV'] . ' byl uzavřen.';
EedTransakce::ZapisLog($doc_id, $text, 'SPIS');

echo '<p><br/><h2>vše hotovo</h2></p>';
echo '<input type="button" name="" value="Zavřít" class="btn" onclick="window.opener.document.location.reload();">';

require_once(FileUp2('html_footer.inc'));
