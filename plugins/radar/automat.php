<?php
require("tmapy_config.inc");
include(FileUp2(".admin/brow_.inc"));
include(FileUp2("interface/.admin/soap_funkce.inc"));
require_once(FileUp2('.admin/classes/EedRadar.inc'));
if ($_GET['show']) require(FileUp2('html_header_full.inc'));

$USER_INFO = $GLOBALS["POSTA_SECURITY"]->GetUserInfo();
$id_user=$USER_INFO["ID"];
$last_date=Date('Y-m-d');
$last_time=Date('H:i:s');
$datum=date('d.m.Y H:m');

$software_id = 'RADAR';
$session_id = md5(uniqid());


if ($GLOBALS['CONFIG_POSTA']['RADAR']['adresar']) {
  if (!@$d = dir($GLOBALS['CONFIG_POSTA']['RADAR']['adresar'])) {
    $text = 'Cesta <i>".$cesta."</i> nenalezena!!!';
    WriteLog($software_id,$text,$session_id,1);
    die;

  }
  echo '<h1>Nalezené soubory pro načtení:</h1>';
  while($entry=$d->read()) {
    if ($entry<>'.' && $entry<>'..') {
      $file = pathinfo($entry);
      if (strtolower($file['extension']) == 'xml')
        $text = '(AUTOMAT) Načítám soubor '.$entry.' .';
        WriteLog($software_id,$text,$session_id,0);
        if (EedRadar::ZalozZaznam($GLOBALS['CONFIG_POSTA']['RADAR']['adresar'] . '/' . $entry)) {
          $text = '(AUTOMAT) Soubor '.$entry.' byl v pořádku načten.';
          WriteLog($software_id,$text,$session_id,0);
        }
        else {
          $text = '(AUTOMAT) Došlo k chybě při uložení '.$entry.' Zkontrolujte LOG.';
          WriteLog($software_id,$text,$session_id,1);
        }
        if ($_GET['show']) echo $text.'<br/>';
     }
  }
}

if ($_GET['show']) {
  echo '<p><input type="button" value="Zavřít" onclick="window.parent.location.reload(); parent.$.fancybox.close();" class="btn"></p>';
  require(FileUp2('html_footer.inc'));
}
