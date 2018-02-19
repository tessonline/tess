<?php
include_once(FileUp2('.admin/db/db_posta.inc'));

$PROPERTIES = array(
  'AGENDA_NAME' => 'Verze aplikace',
  'AGENDA_TABLE' => 'posta_version',
  'AGENDA_ID' => 'ID',
  'AGENDA_IDENT' => 'POSTA_VERSION',
  'DEFAULT_LANG'=>'cz_utf-8',

  'DB_NAME'=>'db_posta',

  'BROW_PAGE_SIZE' => 100,
    
  'HISTORY_SHOW'=>false,

  //po insertu se refreshne okno main
  'INSERT_REFRESH' => true,

  'BROW_ORDER_BY' => 'datum desc',

  'EDIT_WIDTH' => 790,
  'EDIT_HEIGHT' => 420,
  'EDIT_LEFT' => 10,
  'EDIT_TOP' => 50,

  'DELETE_WIDTH' => 700,
  'DELETE_HEIGHT' => 250,
  'DELETE_LEFT' => 50,
  'DELETE_TOP' => 50

);

include_once(FileUp2(".admin/access_.inc"));


$je_ceu = strpos($_SERVER['SCRIPT_FILENAME'], 'ost/ceu');
if (!(HasRole('spravce')) && $je_ceu === false) {
  if (!$USER_INFO) $USER_INFO = $GLOBALS["POSTA_SECURITY"]->GetUserInfo();
  $EedUser = LoadClass('EedUser', $USER_INFO['ID']);

  $text = 'uživatel <b>' . $EedUser->cele_jmeno . '</b> (' . $EedUser->id_user. '), spustil akci Konfigurace EED, na které nemá dostatečná práva';
  EedTransakce::ZapisLog(0, $text, 'SECURITY', $user_id);
  echo '<h1>CHYBA:</h1><p>Pro tuto operaci nemáte oprávnění.</p>';
  require(FileUp2('html_footer.inc'));
  Die();
}
