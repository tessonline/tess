<?php
//$GLOBALS["PROPERTIES_DEBUG"]["SHOW_SQL"] = true;
include_once(FileUp2(".admin/db/db_posta.inc"));

$PROPERTIES = array(
  "AGENDA_NAME" => "Synchronizace typ.spisů pracovníků",
  "AGENDA_IDENT" => "POSTA_PLUGINS_UK_PRAC",
  "DB_NAME" => "db_posta",
  "DEFAULT_LANG"=>"cz_utf-8",
  'SECURITY_REGISTRATION' => true,
  "MAIN_WINDOW"=>"synchro.php?insert&cacheid=",
);
