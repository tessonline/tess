<?php
require('tmapy_config.inc');
require_once(FileUp2('.admin/run2_.inc'));
require_once(Fileup2('html_header_title.inc'));
include_once(FileUp2(".admin/db/db_monumnis.inc"));

require_once(FileUp2('plugins/npu/.config/config_pam_katalog.inc'));

require_once(FileUp2('plugins/npu/.admin/classes/PKident.inc'));
require_once(FileUp2('plugins/npu/.admin/classes/PagisServiceStavBind.inc'));

$PK = new PagisServiceStavBind;
$ident = new PKIdent(array());

$a = new DB_POSTA;

$login = 'malyo';
$last_date = Date('Y-m-d');
$last_time = Date('H:i:s');

$sql = 'select * from EssPam order by idpam desc limit 0,100';
$q = new DB_MONUMNIS;
$q->query($sql);
$pocet = $q->Num_Rows();
while ($q->Next_Record()) {
  $spis_id = $q->Record['SPIS_ID'];
  $pk_id = $q->Record['IDREG'];
  $sqlx = 'select id from posta where id='.$pk_id;
  $a->query($sqlx);
  $pocet = $a->Num_Rows();
  if ($pocet>0) {
    if ($ident->getCountOfIdent($spis_id) == 0 ) {
      if ($PK->createBind($spis_id, $pk_id, $login)) {
       // if ($PK->deleteBind($spis_id, $pk_id, $login)) echo ' a vazba smazana';
        $sql = "insert into posta_npu_pam_katalog (JID,TYP_ID,PK_ID,OWNER_ID,LAST_DATE,LAST_TIME) VALUES ($spis_id, 8,$pk_id,-1,'$last_date','$last_time')";
        $a->query($sql);
      }
      else {
        echo "Vazba pro JID $spis_id - navázáno na stav $pk_id nebyla provedena <br/>";
      }

    }
  }
  else {
    echo "Dokument $spis_id nenalezen<br/>";
  }

}

require_once(Fileup2('html_footer.inc'));

/*
ID právního stavu

  $spis_id = $q->Record['JID'];
  $typ = $q->Record['TYP_ID'];
  $hodnota= $q->Record['PK_ID'];

  $USER_INFO = $GLOBALS["POSTA_SECURITY"]->GetUserInfo();
  $login = $USER_INFO['LOGIN'];

  $sql = "insert into posta_npu_pam_katalog (JID,TYP_ID,PK_ID) VALUES ($spis_id, $typ,$hodnota)";

  $bind = $GLOBALS['PK_CIS'][$typ]['bind'];
  $cesta = 'plugins/npu/.admin/classes/' . $bind . '.inc';
  include_once(FileUp2($cesta));
  $vazbaWS = new $bind;
  if (!$res = $vazbaWS->deleteBind($spis_id, $hodnota, $login)) {
  */