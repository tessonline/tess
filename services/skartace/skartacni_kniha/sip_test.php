<?php
require('tmapy_config.inc');
require(FileUp2('.admin/brow_.inc'));
require(FileUp2('sip/sip.inc'));
require(FileUp2('html_header_full.inc'));
echo '<h1>Generování SIP balíčků</h1>';
//print_r($IDs);
//Die();

$ID = '1000506609';
//  if ($ID<>30569133) continue;
  $xml = generateSIP($ID);
  echo 'Vytvářím XML soubor '.$ID.'.xml<br/>';
  $tmp_soubor = $GLOBALS[CONFIG_POSTA][HLAVNI][tmp_adresar].abs($ID).'.xml';
  $fname[] = abs($ID).'.xml';
  $fp = fopen($tmp_soubor,'w');
  fwrite($fp, $xml);
  fclose($fp);
echo 'Jdu vytvořit zip soubor<br/>';
@unlink($GLOBALS[CONFIG_POSTA][HLAVNI][tmp_adresar].'pack.zip');
$cmd = 'cd '.$GLOBALS[CONFIG_POSTA][HLAVNI][tmp_adresar].'; zip pack.zip '.implode(' ',$fname);
echo $cmd;

echo "<br/>";
exec($cmd, $output);

echo '<h1>Hotovo</h1>';
echo '<a href="sip_download.php">Klikněte pro stažení souboru</a>';
require(FileUp2('html_footer.inc'));
