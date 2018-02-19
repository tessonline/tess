<?php
require('tmapy_config.inc');
require(FileUp2('.admin/brow_.inc'));
include_once($GLOBALS['TMAPY_LIB'] . '/oohforms.inc');
require_once(FileUp2('.admin/el/of_select_.inc'));
include_once(FileUp2('plugins/schvalovani/.admin/schvalovani.inc'));
require(FileUp2('html_header_full.inc'));

if (!HasRole('export')) {
	echo '<h1>Chyba</h1><p::Nemáte práva pro export, požádejte správce aplikace</p>';
  require(FileUp2('html_footer.inc'));
	Die();
}
$EddSql = LoadClass('EedSql');


require(FileUp2('.admin/brow_access.inc'));
require(FileUp2('.admin/brow_func.inc'));

$idMain = (int)$GLOBALS['SPISID'];

$EedCj = LoadClass('EedCj', $idMain);
$cj_info = $EedCj->GetCjInfo($idMain);

echo '<h1>' . $cj_info['CELY_NAZEV'] . '</h1>';
$GLOBALS['ID'] = $EedCj->GetDocsInCj($idMain);
// export dokumentu, musime zapsat do trasakcniho protokolu
if ($GLOBALS["EXPORT_ALL_step"] > 0) {
  if ($_POST['SELECT_IDdenik']) $GLOBALS['ID'] = $_POST['SELECT_IDdenik'];
  if ($_POST['SELECT_ID']) $GLOBALS['ID'] = $_POST['SELECT_ID'];
  if ($_POST['SELECT_ID_FILTERdenik']) $GLOBALS['ID'] = $_POST['SELECT_ID_FILTERdenik'];

  $sql = Table(array(
    'tablename' => 'denik',
//    'appendwhere' => $where,
    'return_sql' => true
  ));
  $id_krizvazba = array();
  $aa = NEW DB_POSTA;
  $q->query($sql);
  while ($q->Next_Record()) {
    $id[] = $q->Record['ID'];
    $sql = 'SELECT * FROM POSTA_KRIZOVY_SPIS WHERE NOVY_SPIS=' . $q->Record['ID'];
    $aa->query($sql);
    while ($aa->Next_Record()) {
      $id_kriz = $aa->Record['PUVODNI_SPIS'];
      $doc_temp = LoadClass('EedCj', $id_kriz);
      $dalsi_id = $doc_temp->GetDocsInCj($id_kriz);
      $id = array_merge($id, $dalsi_id);
      $id_krizvazba = array_merge($id_krizvazba, $dalsi_id);
    }
//    $text = 'Dokument <b>' . $id . '</b> byl exportován do formátu <b>' . $_POST['export_output'] . '</b>';
//    EedTransakce::ZapisLog($id, $text, 'EXPORT', $id_user);
  }
  $GLOBALS['ID'] = $id;
  $GLOBALS['KRIZ_VAZBA'] = $id_krizvazba;
}
//Die(print_r($GLOBALS['ID']));

$count = Table(array(
		'tablename' => '',
		'setvars' => true,
		'caption' => $caption,
		'showupload' => false,
		'showhistory' => true,
		'showexportall' => true,
//		'appendwhere' => $where,
		'page_size' => 1000,
		'showinfo' => false,
		'showedit' => false,
		'showdelete' => false,
		
));

echo '<script>ExportAll_();</script>';
require(FileUp2('html_footer.inc'));
