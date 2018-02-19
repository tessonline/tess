<?php
require('tmapy_config.inc');
require_once(FileUp2('.admin/run2_.inc'));
require_once(FileUp2('.admin/status.inc'));
require_once(Fileup2('html_header_title.inc'));
$id_posta = $GLOBALS['POSTA_ID'];

$podatelna = 0;
$puvSO = $GLOBALS['PUVODNI_SUPERODBOR'];

if ($GLOBALS['PODATELNA']==1) {
  $GLOBALS['DUVOD'] = 'Vrácení na podatelnu:' . $GLOBALS['DUVOD'];
  $podatelna = 1;
} elseif ($GLOBALS['PODATELNA']==1 && $puvSO>0) {
  $GLOBALS['DUVOD'] = 'Vrácení na předchozí podatelnu:' . $GLOBALS['DUVOD'];
  $podatelna = 1;
} else
  $GLOBALS['DUVOD'] = 'Vrácení od zpracovatele na spisový uzel:' . $GLOBALS['DUVOD'];


$text = $GLOBALS['DUVOD'];

Run_(array('outputtype'=>3,'to_history'=>false));

$USER_INFO = $GLOBALS["POSTA_SECURITY"]->GetUserInfo();
$id_user=$USER_INFO["ID"];
$LAST_USER_ID=$id_user;
$OWNER_ID=$id_user;
$LAST_TIME=Date('H:m:i');
$LAST_DATE=Date('Y-m-d');

$q = new DB_POSTA;

$next = '';
if ($podatelna==1) $next = ',odbor=NULL,datum_predani=NULL';
if ($puvSO>0) $next .=", superodbor=" . $puvSO;
$sql = "update posta set referent = NULL".$next.",last_date='$LAST_DATE',last_time='$LAST_TIME',last_user_id=$LAST_USER_ID where id = ".$id_posta;

$q->query($sql);
NastavStatus($id_posta);

EedTransakce::ZapisLog($id_posta, $text, 'DOC');

require_once(Fileup2('html_footer.inc'));
