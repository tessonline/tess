<?php
require("tmapy_config.inc");
require(FileUp2(".admin/brow_.inc"));
require(FileUp2("html_header_full.inc"));

if (!HasRole('admin-typspis')) {

  require_once(FileUp2(".admin/security_obj.inc"));
  $USER_INFO = $GLOBALS["POSTA_SECURITY"]->GetUserInfo();

	$EedUser = LoadClass('EedUser', $USER_INFO['ID']);

	$text = 'uživatel <b>' . $EedUser->cele_jmeno . '</b> (' . $EedUser->id_user. '), spustil akci Administrace typových spisů, na které nemá dostatečná práva';
	EedTransakce::ZapisLog(0, $text, 'SECURITY', $user_id);
  require(FileUp2("html_footer.inc"));
  Die('Na tuto operaci nemáte dostatečná práva');
}


//if ($GLOBALS['CONFIG']['USE_SUPERODBOR']) $where = " AND id_superodbor is null or id_superodbor=" . EedTools::VratSuperOdbor();
if (HasRole('spravce'))  {
  $where = ' AND id_superodbor is null';
  if (!$GLOBALS['ID'])
    include_once(FileUp2('.admin/brow_superodbor.inc'));
}
if (HasRole('lokalni-spravce'))  $where = ' AND id_superodbor=' . EedTools::VratSuperOdbor();

if ($GLOBALS['omez_zarizeni']) $where = " AND id_superodbor=" . $GLOBALS['omez_zarizeni'];

if ($GLOBALS['ID']) $where = '';

$count = Table(array(
  'showself' => true,
  'appendwhere' => $where,
));

if ($count == 1 && $GLOBALS['ID']) {

  $id = $GLOBALS['ID'];
  UNSET($GLOBALS[ID]);
  $GLOBALS['SPIS_ID'] = $id;
  $count = Table(array(
    'agenda' => 'POSTA_CIS_TYPOVY_SPIS_SOUCAST',
    'showself' => false,
    'tablename' => 'POSTA_CIS_TYPOVY_SPIS_SOUCAST',
  ));

  NewWindow(array('fname' => 'AgendaSpis', 'name' => 'AgendaSpis', 'header' => true, 'cache' => false, 'window' => 'edit'));

  echo "<a  class=\"btn btn-loading\" href=\"#\" onClick=\"javascript:NewWindowAgendaSpis('soucast/edit.php?insert&SPIS_ID=".$id."&cacheid=')\">Přidat součást</a>";

}



require(FileUp2("html_footer.inc"));
