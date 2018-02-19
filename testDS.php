<?php
require("tmapy_config.inc");
require(FileUp2(".admin/isds_.inc"));
require(FileUp2(".admin/config.inc"));


$dbOwnerInfo = array(
  'dbType'=>'FO',
  'pnLastName' => 'Malý',
  'pnFirstName' => 'Ondřej',
  'biDate' => $datnar

);

if ($GLOBALS[CONFIG_POSTA][DS][ds_cert_id]) $certifikat=VratCestukCertifikatu(0,$GLOBALS[CONFIG_POSTA][DS][ds_cert_id],1); else $certifikat='';
$schranka=new ISDSbox($GLOBALS[CONFIG_POSTA][DS][ds_user],$GLOBALS[CONFIG_POSTA][DS][ds_passwd],$certifikat);
$hodnoty=$schranka->FindPersonalDataBox($dbOwnerInfo);

if (count($hodnoty) == 1) {
  $odesl_datschranka = $hodnoty[0]['dbID'];
  echo "a mame datovku " . $odesl_datschranka;
  
}
elseif (count($hodnoty) > 1) {
    //vypsat hlaseni, ze nalezeno vice datovych schranek
}



/** vlozeni do typoveho spisu IDSTUDIA
 *

