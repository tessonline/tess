<?php
require('tmapy_config.inc');
require(FileUp2('.admin/brow_.inc'));
require(FileUp2('html_header_full.inc'));
require(FileUp2('.admin/nastaveni.inc'));
require(FileUp2('.admin/funkce.inc'));

$chyba = false;
if (strlen($eed_folder) < 5 ) {  
  $chyba = true;
}

if (!$mbox_eed = @imap_open($eed_folder, $GLOBALS["CONFIG_POSTA"]["EPODATELNA"]["username"], $GLOBALS["CONFIG_POSTA"]["EPODATELNA"]["passwd"])) {
  $chyba = true;
}

if ($chyba) {
  echo '<h3>Nastala chyba při komunikaci s mailovou schránkou!</h3>';
  if (HasRole('spravce')) echo 'Pokračujte prosím odkazem Nastavení ePodatelny vpravo nahoře.</span>';
  else echo 'Kontaktujte prosím vašeho správce.</span>';
  require(FileUp2("html_footer.inc"));
  Die();
}
echo '<p><div class="form darkest-color"> <div class="form-body"> <div class="form-row">';


echo '<span class="text">Filtr ePodatelny:</span><div class="form dark-color"><div class="form-body"><div class="form-row">

<a href="?statusEP=1" class="'.($GLOBALS["statusEP"]==1?'':'btn').'">nové e-maily</a>&nbsp;
<a href="?statusEP=50" class="'.($GLOBALS["statusEP"]==50?'':'btn').'">všechny e-maily ve složce</a>&nbsp;
</div></div></div>';

echo '</div> </div> </div><p>';

if (!$statusEP) $statusEP = 1;
$q = new DB_POSTA;
$jiz_nactene = array();

if ($statusEP < 10) {
  $sql = "select record_uid from posta_epodatelna where smer = 'f'";
  $q->query($sql);
  while ($q->Next_Record()) $jiz_nactene[] = $q->Record[RECORD_UID];
}
$sorted = imap_sort($mbox_eed, SORTARRIVAL,  1); // setridime zpravy
$count = count($headers);

while (list($key, $val) = each($sorted)) {
  unset($email);
  $email = VratEmailPole($mbox_eed, $val, 0);
  
  if (!in_array($email[message_id], $jiz_nactene)) {
    $href = '<a title="Uložit dokument do EED" href="receive.php?ID_DOSLE=' . $val;
    $href .= '&vytvorit_cj=1&statusEP=$statusEP"><img src="' . FileUp2("images/ok_check.gif") . '"';
    $href .= 'border="0"></a><br/>';
//     $href .= '<a title="Uložit dokument do EED bez ČJ" ';
//     $href .= '"receive . php?ID_DOSLE=' . $val . '&vytvorit_cj=0&statusEP=$statusEP">';
//     $href .= '<img src="' . FileUp2("images/ko_check.gif") . '" border="0"></a>';    
    $EMAIL_DATA[] = array(
      'ID' => $val, 
      'datum' => $email[datum], 
      'from' => $email[from], 
      'vec' => $email[vec], 
      'odkaz' => $href
    );
  }
}

include_once $GLOBALS['TMAPY_LIB'] . '/db/db_array.inc';
$db_arr = new DB_Sql_Array;
$db_arr->Data = $EMAIL_DATA;

if (count($EMAIL_DATA)>0) {
  Table(
    array(
      'db_connector' => &$db_arr, 
      'showaccess' => true, 
      'tablename' => 'epodatelna',
      'select_id' => 'ID',
      'appendwhere' => $where2, 
      'showedit' => false, 
      'showdelete' => false, 
      'showselect' => true,
       'multipleselect' => true, 
       'showinfo' => true, 
       'multipleselectsupport' => true, 
       'showinfo' => false
     )
  );  
}
else {
  echo '<span class="caption">Příchozí emaily</span><span class="text"><br/>V dané složce není žádný email k načtení.</span>';
}
require(FileUp2("html_footer.inc"));
