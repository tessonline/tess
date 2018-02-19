<?php
require('tmapy_config.inc');
require(FileUp2('.admin/brow_.inc'));
require(FileUp2('sip/sip.inc'));
require(FileUp2('html_header_full.inc'));
$q = new DB_POSTA;

if ($_POST['typ'] == 'A') {

  $_POST['sql'] = str_replace( "ORDER BY ", " AND (skar_znak like 'A' or skar_znak_alt like 'A') ORDER BY ",$_POST['sql']);
  $caption_add = ' - finální seznam archivace ';
}

echo '<h1>Generování SIP balíčků ' . $caption_add . '</h1>';

$q->query($_POST['sql']);
while($q->Next_Record()) {
  $IDs[] = $q->Record['DOKUMENT_ID'];
}

if (count($IDs) == 0) {
  echo '<h1>Nejsou záznamy s A</h1>';
echo "
<input type='button' onclick='document.location.href=\"brow.php?SKARTACNI_RIZENI_ID=$rizeni_id\";' value='   Vrátit se   ' class='button btn'>";
  require(FileUp2('html_footer.inc'));
Die();
}
//print_r($IDs);
//Die();

foreach($IDs as $ID) {
//  if ($ID<>30569133) continue;

  $xml = generateSIP($ID);
  echo 'Vytvářím XML soubor '.$ID.'.xml<br/>';
  $tmp_soubor = $GLOBALS[CONFIG_POSTA][HLAVNI][tmp_adresar].abs($ID).'.xml';
  $fname[] = abs($ID).'.xml';
  $fp = fopen($tmp_soubor,'w');
  fwrite($fp, $xml);
  fclose($fp);
}
echo 'Jdu vytvořit zip soubor';
@unlink($GLOBALS[CONFIG_POSTA][HLAVNI][tmp_adresar].'pack.zip');
$cmd = 'cd '.$GLOBALS[CONFIG_POSTA][HLAVNI][tmp_adresar].'; zip pack.zip '.implode(' ',$fname);
echo $cmd;

exec($cmd, $output);

echo '<h1>Hotovo</h1>';
echo '<a href="sip_download.php">Klikněte pro stažení souboru</a>';
require(FileUp2('html_footer.inc'));
