<?php
require("tmapy_config.inc");
require(FileUp2(".admin/run2_.inc"));
require_once(Fileup2("html_header_title.inc"));

require(FileUp2("posta/.config/config_czech_point.inc"));

//slouzi pro prvotni import nacteni z config souboru

//print_r($GLOBALS['CONFIG_POSTA_CP']['VALID_USERS']);

$q = new DB_POSTA;

$USER_INFO = $GLOBALS["TMAPY_SECURITY"]->GetUserInfo();
$id_user = $USER_INFO["ID"];
$LAST_TIME = Date('H:i:s');
$LAST_DATE = Date('Y-m-d');


foreach($GLOBALS['CONFIG_POSTA_CP']['VALID_USERS'] as $login => $user) {
  $sql = "select * from posta_czechpoint where login like '" . $login . "'";
  $q->query($sql);
  if ($q->Num_Rows() == 0) {
    echo "pridame uzivatele $login ";

    $sql = 'insert into posta_czechpoint (USER_ID,LOGIN,PASSWD,LAST_USER_ID,OWNER_ID,LAST_DATE,LAST_TIME) VALUES ';
   $sql .= "(".$user['id'].",'$login','".$user['password']."','".$id_user."','".$id_user."','".$LAST_DATE."','".$LAST_TIME."')";
 //  echo $sql.'<br/>';
    $q->query($sql);
    echo ' - pridano<br/>';
  }
}

require_once(Fileup2("html_footer.inc"));

