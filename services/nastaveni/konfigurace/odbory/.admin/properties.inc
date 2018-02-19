<?php
if (!$_SERVER['HTTPS'] == 'on') Die();
//$GLOBALS["PROPERTIES_DEBUG"]["SHOW_SQL"] = true;
include_once(FileUp2("posta/.admin/properties.inc"));
include_once(FileUp2(".admin/db/db_posta.inc"));
include_once(FileUp2(".admin/db/db_default.inc"));

$PROPERTIES = array(
  "AGENDA_NAME" => "Konfigurace Evidence dokumentů",
  "AGENDA_TABLE" => "POSTA_KONFIGURACE",
  "AGENDA_ID" => "ID",
  "AGENDA_IDENT" => "POSTA_KONFIGURACE_ODBORY",
  "DB_NAME" => "db_posta",
  "DEFAULT_LANG"=>"cz_utf-8",

  "INSERT_REFRESH"=>true,
  "BROW_ORDER_BY"=>"kategorie, parametr",

  "EDIT_LEFT"=>20,
  "EDIT_TOP"=>20,
  "EDIT_HEIGHT"=>200,
  "EDIT_WIDTH"=>750,

  "DELETE_HEIGHT" => 300,
  "DELETE_WIDTH" => 600,
  "DELETE_LEFT" => 50,
  "DELETE_TOP" => 50
);

include_once(FileUp2(".admin/access_.inc"));

$je_ceu = strpos($_SERVER['SCRIPT_FILENAME'], 'ost/ceu');
if (!(HasRole('spravce') || HasRole('lokalni-spravce')) && $je_ceu === false) {
  if (!$USER_INFO) $USER_INFO = $GLOBALS["POSTA_SECURITY"]->GetUserInfo();
  $EedUser = LoadClass('EedUser', $USER_INFO['ID']);

  $text = 'uživatel <b>' . $EedUser->cele_jmeno . '</b> (' . $EedUser->id_user. '), spustil akci Konfigurace EED, na které nemá dostatečná práva';
  EedTransakce::ZapisLog(0, $text, 'SECURITY', $user_id);
  echo '<h1>CHYBA:</h1><p>Pro tuto operaci nemáte oprávnění.</p>';
  require(FileUp2('html_footer.inc'));
  Die();
}
