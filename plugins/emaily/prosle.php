<?php
require('tmapy_config.inc');
require(FileUp2('.admin/brow_.inc'));
require(FileUp2('.admin/config.inc'));
@include(FileUp2('.admin/table_funkce_denik.inc'));
require(FileUp2('html_header_full.inc'));
chdir(getAgendaPath('POSTA', 0, 0) . '/plugins/epodatelna');
include_once(getAgendaPath('POSTA', 0, 0) . '/plugins/emaily/.admin/emaily_html_funkce.inc');


function FormatText($text, $delka) {
  $text = mb_substr($text, 0, $delka);
  $text = str_pad($text, $delka, " ");
  return $text;
}

$eedSql = LoadClass('EedSql');

$q = new DB_POSTA;
$a = new DB_POSTA;
$sql = 'select referent from posta where status=6 and referent>0 GROUP BY REFERENT';
$q->query($sql);
while ($q->Next_Record()) {

  $id_user = $q->Record['REFERENT'];
  $login = $q->Record['LOGIN_NAME'];
  $EedUser = LoadClass('EedUser',$id_user);

  $sql = 'select * from posta where status=6 and referent=' . $id_user . ' order by id asc';
  $a->query($sql);
  

$mail = '<pre>
' . FormatText($GLOBALS['CONFIG']['CISLO_SPISU'], 13) . '   | Vyřídit do | Věc                                                | Vyřizuje                  | Stav
----------------+------------+----------------------------------------------------+---------------------------+---------
';
  $mail_send = false;
  while($a->Next_Record()) {
    $mail_send = true;
    $doc = LoadClass('EedDokument', $a->Record['ID']);
    $mail .= FormatText($doc->cislo_jednaci, 15) . ' | ' . FormatText(CZDate($a->Record['LHUTA_VYRIZENI']), 10) . ' | ' . FormatText($a->Record['VEC'],50) . ' | ' . FormatText($doc->referent_text,27) . ' | PO LHUTE
';
  }
  $mail .= '</pre>';
  $final_mail = str_replace('$SEZNAM_DOKUMENTU$', $mail, $GLOBALS['CONFIG_POSTA']['HLAVNI']['EMAIL_PO_TERMINU']);
  $final_mail = str_replace('$AKTUALNI_DATUM$', Date('d.m.Y'), $final_mail);
  $final_mail = str_replace('$AKTUALNI_CAS$', Date('H:i:s'), $final_mail);

  $final_mail = '<html><body>' . $final_mail . '</body></html>';

  if ($EedUser->email<> '' ) {
    if ($send_real == 1 && $mail_send) {

      echo "<h1>".$EedUser->cele_jmeno." - email ".$EedUser->email."</h1>posilam email:";
      OdesliHTMLEmail($EedUser->email, $final_mail, $datum, 'Dokumenty po lhute', array(),array());
      echo ' - HOTOVO</hr>';
    }
    elseif ($mail_send) echo "<h1>login $login - email ".$EedUser->email."</h1>posilam email:<pre>" . ($final_mail) . '</pre></hr>';
    else echo "<h1>login $login - email ".$EedUser->email."</h1> - neni nic po terminu, mail neposilam.<hr/>";
  }
}

if (!$send_real) {
  echo '<form method="GET" action="prosle.php">';
  echo '<input type="hidden" name="send_real" value="1">';
  echo '<input type="submit" value="Skutečně poslat" class="btn">';
  echo '</font>';
}
else
  echo '<p><br/><h1>Vše hotovo</h1></p>';
require(FileUp2('html_footer.inc'));
