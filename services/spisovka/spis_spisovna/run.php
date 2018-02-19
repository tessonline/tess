<?php
require('tmapy_config.inc');
require_once(FileUp2('.admin/run2_.inc'));
require_once(FileUp2('.admin/status.inc'));
require_once(Fileup2('html_header_title.inc'));
require_once(FileUp2(".admin/security_obj.inc"));

$dokument_id_puv = $GLOBALS['DOKUMENT_ID']; //nevim proc, pri insertu se smaze
if (!$GLOBALS['VYHRAZENO']) $GLOBALS['VYHRAZENO'] = '';
if ($GLOBALS['SKARTACE_ID']>0 && ($GLOBALS['SKARTACE_ID']<>$GLOBALS['SKARTACE_ID_PUV'])) {
  $USER_INFO = $GLOBALS["POSTA_SECURITY"]->GetUserInfo();
  $id_user=$USER_INFO["ID"];
  $jmeno=$USER_INFO["FNAME"]." ".$USER_INFO["LNAME"];
  $LAST_USER_ID=$id_user;
  $OWNER_ID=$id_user;
  $LAST_TIME=Date('H:i:s');
  $LAST_DATE=Date('Y-m-d');
  $dnes=Date('d.m.Y H:i');
  $id_puvodni=$ID;

  $q=new DB_POSTA;
  $sql="update posta set skartace='".$GLOBALS['SKARTACE_ID']."',last_date='$LAST_DATE',last_time='$LAST_TIME',last_user_id=$LAST_USER_ID where id=".$GLOBALS['DOKUMENT_ID'];
  $q->query($sql);
}
if (!$GLOBALS['DATUM_ARCHIVACE_ODHAD']) $GLOBALS['DATUM_ARCHIVACE_ODHAD']=0;
$lastid = Run_(array('outputtype'=>1,'unsetvars'=>true,'to_history'=>true));

$tran = LoadClass('EedTransakce');
$tran->ZapisZHistorieTable($lastid, $GLOBALS['DOKUMENT_ID'], 'posta_spisovna', ' v Údaje o čj./spisu');

$GLOBALS['DOKUMENT_ID'] = $GLOBALS['DOKUMENT_ID'] ? $GLOBALS['DOKUMENT_ID'] : $dokument_id_puv;
NastavStatus($GLOBALS['DOKUMENT_ID']);

$cj_obj = LoadClass('EedCj',$GLOBALS['DOKUMENT_ID']);
$docs = $cj_obj->GetDocsInCj($GLOBALS['DOKUMENT_ID'],1);
  while (list($key,$doc)=each($docs))
    NastavStatus($doc);

echo '
<script language="JavaScript" type="text/javascript">
  if (window.opener.document) {
    window.opener.document.location.reload();
  }
//  window.close();
</script>
';


require_once(Fileup2('html_footer.inc'));
