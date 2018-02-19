<?php
require("tmapy_config.inc");
include(FileUp2(".admin/brow_.inc"));
include(FileUp2("interface/.admin/soap_funkce.inc"));
require_once(FileUp2('.admin/classes/EedRadar.inc'));
require(FileUp2('html_header_full.inc'));

$USER_INFO = $GLOBALS["POSTA_SECURITY"]->GetUserInfo();
$id_user=$USER_INFO["ID"];
$last_date=Date('Y-m-d');
$last_time=Date('H:i:s');
$datum=date('d.m.Y H:m');


//$data = EedRadar::loadXML($_GET['file']);
if (EedRadar::ZalozZaznam($GLOBALS['CONFIG_POSTA']['RADAR']['adresar'].'/'.$_GET['file'])) {
  echo 'Záznam byl v pořádku uložen.';
}
else
  echo '<b>POZOR: Došlo k chybě při uložení! Zkontrolujte LOG.</b>';

echo '<p><input type="button" value="Zavřít" onclick="window.parent.location.reload(); parent.$.fancybox.close();" class="btn"></p>';

require(FileUp2('html_footer.inc'));

//print_r($data);