<?php
require('tmapy_config.inc');
require_once(FileUp2('.admin/run2_.inc'));
require_once(Fileup2('html_header_title.inc'));

if ($GLOBALS['DELETE_ID']) {
  require_once(FileUp2('plugins/npu/.config/config_pam_katalog.inc'));

  $sql = 'select * from posta_npu_pam_katalog where id=' . $GLOBALS['DELETE_ID'];
  $q = new DB_POSTA;
  $q->query($sql);
  $q->Next_Record();
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
    echo '<h1>CHYBA</h1>';
    echo '<p>Došlo k chybě při rušení vazby v památkovém katalogu.</p>';
    echo '<input type="button" value="Zavřít" onclick="window.opener.document.location.reload();" class="btn">';
    require(FileUp2('html_footer.inc'));
    Die();
  }
  else {
    Run_(array('outputtype'=>3,'to_history'=>false));
  }


}
require_once(Fileup2('html_footer.inc'));
