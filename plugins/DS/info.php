<?php
require("tmapy_config.inc");
include(FileUp2(".admin/brow_.inc"));
require_once(FileUp2(".admin/config.inc"));
require_once(FileUp2(".admin/db/db_posta.inc"));
require(FileUp2(".admin/funkce.inc"));
require_once(FileUp2(".admin/oth_funkce.inc"));
require_once(FileUp2("html_header_full.inc"));
require(FileUp2(".admin/soap_funkce.inc"));
require(FileUp2(".admin/nastaveni.inc"));
require(FileUp2(".admin/status.inc"));
//require(FileUp2(".admin/security_.inc"));
require(FileUp2(".admin/isds_.inc"));
$q=new DB_POSTA;
$c=new DB_POSTA;
$a=new DB_POSTA;

$USER_INFO = $GLOBALS["TMAPY_SECURITY"]->GetUserInfo();
$id_user=$USER_INFO["ID"];
$jmeno_uzivatele=$USER_INFO["FNAME"]." ".$USER_INFO["LNAME"];
$LAST_USER_ID=$id_user;
$LAST_TIME=Date('H:i:s');
$LAST_DATE=Date('Y-m-d');

//inicializace NuSOAP

if ($ID)
{
  $schranka=new ISDSbox($GLOBALS[CONFIG_POSTA][DS][ds_user],$GLOBALS[CONFIG_POSTA][DS][ds_passwd],'');
  $zprava_signed=$schranka->SignedSentMessageDownload($ID);
  $podepsano=$zprava_signed['dmSignature']; 
  $ukaz=base64_decode($podepsano);
  print_r($ukaz);
}


require(FileUp2("html_footer.inc"));
