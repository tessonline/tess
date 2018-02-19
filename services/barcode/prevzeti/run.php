<?php
require("tmapy_config.inc");
include(FileUp2(".admin/run2_.inc"));
include(FileUp2(".admin/config.inc"));
include(FileUp2(".admin/status.inc"));
require_once(FileUp2(".admin/security_obj.inc"));
require_once(FileUp2(".admin/security_name.inc"));
require_once(FileUp2(".admin/oth_funkce.inc"));
require_once(FileUp2("html_header_full.inc"));

$q=new DB_POSTA;
$USER_INFO = $GLOBALS["POSTA_SECURITY"]->GetUserInfo();

//echo $_POST['PREBRAL_ID'];
$prebirajici = $GLOBALS["POSTA_SECURITY"]->GetUserInfo($_POST['PREBRAL_ID'],false,true,1);
//print_r($prebirajici);
$id_user=$USER_INFO["ID"];
$LAST_USER_ID=$id_user;
$OWNER_ID=$id_user;
$LAST_TIME=Date('H:i:s');
$LAST_DATE=Date('Y-m-d');
$aktual=Date('d.m.Y H:i:s');


$predana_cisla = explode(',', $_POST['PREDAT_ID']);
//Die(print_r($predana_cisla));

foreach($predana_cisla as $id) {
  if(!$id) continue;
  $sql="update posta set datum_predani".($GLOBALS["SMER"]==1?'':'_ven')."='".$aktual."',last_date='".$LAST_DATE."',last_time='".$LAST_TIME."',last_user_id=".$LAST_USER_ID." where id=".$id;
  $q->query($sql);
  $text = 'Dokument (<b>'.$id.'</b>) převzal(a) '.$prebirajici['LNAME'].' ' .$prebirajici['FNAME'].' dne '.$aktual;
//  echo $text;
  EedTransakce::ZapisLog($id, $text, 'DOC');
  NastavStatus($id, $LAST_USER_ID);
}

echo '<h1>V pořádku</h1>Dokumenty byly převzaty. Pokračujte kliknutím na Přehled.';


require_once(FileUp2("html_footer.inc"));

