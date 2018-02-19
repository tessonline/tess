<?php
require_once(FileUp2("interface/.admin/certifikat_funkce.inc"));

$mail=$GLOBALS["CONFIG_POSTA"]["EPODATELNA"]["imap_adresa"];
//$mbox = imap_open("".$mail."", $username, $passwd);
if (strlen($GLOBALS["CONFIG_POSTA"]["EPODATELNA"]["name_of_eed_folder"])>2)
  $eed_folder=$mail."/".$GLOBALS["CONFIG_POSTA"]["EPODATELNA"]["name_of_eed_folder"];
else
  $eed_folder=$mail;


if (strlen($GLOBALS["CONFIG_POSTA"]["EPODATELNA"]["eed_karantena"])>2)
$eed_folder_karantena = $mail . $GLOBALS["CONFIG_POSTA"]["EPODATELNA"]["eed_karantena"];