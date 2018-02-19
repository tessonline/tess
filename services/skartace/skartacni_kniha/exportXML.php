<?php
require("tmapy_config.inc");
require(FileUp2('.admin/brow_.inc'));
require(FileUp2('.admin/config.inc'));
require_once(FileUp2("interface/.admin/unispis_funkce.inc"));
require(FileUp2('html_header_full.inc'));
echo '<h1>Generování XML souborů</h1>';

Access();
foreach($_POST as $key => $val)
  $GLOBALS[$key] = $val;

if ($GLOBALS['ODBOR'] == 0) UNSET($GLOBALS['ODBOR']);
$GLOBALS['MAIN_DOC'] = 1;


if ($GLOBALS['SPISOVNA_ID']) $column = 'DOKUMENT_ID'; else $column = 'ID';

if ($_POST['SELECT_ID']) $GLOBALS['ID'] = $_POST['SELECT_ID'];
if ($_POST['SELECT_ID_FILTER']) $GLOBALS['ID'] = $_POST['SELECT_ID_FILTER'];
require(FileUp2('.admin/table_append_where.inc'));

$sql = Table(array( 'return_sql'=>true,
    'appendwhere' => $where . $where2,
));

$IDs = array();
$q->query($sql);
while ($q->Next_Record())
  $IDs[] = $q->Record[$column];


foreach($IDs as $ID) {
  $xml = getXMLDoc($ID);
  echo 'Vytvářím XML soubor '.$ID.'.xml<br/>';
  $tmp_soubor = $GLOBALS[CONFIG_POSTA][HLAVNI][tmp_adresar].$ID.'.xml';
  $fname[] = $ID . '.xml';
  $fp = fopen($tmp_soubor,'w');
  fwrite($fp, $xml);
  fclose($fp);
  $text = 'Dokument <b>' . $ID . '</b> byl exportován do formátu <b>XML dle přílohy č. 1 NSESSS</b>';
  EedTransakce::ZapisLog($ID, $text, 'EXPORT', $id_user);
}

echo 'Jdu vytvořit zip soubor';
@unlink($GLOBALS[CONFIG_POSTA][HLAVNI][tmp_adresar].'XMLpack.zip');
$cmd = 'cd '.$GLOBALS[CONFIG_POSTA][HLAVNI][tmp_adresar].'; zip XMLpack.zip '.implode(' ',$fname);
//echo $cmd;

exec($cmd, $output);

echo '<h1>Hotovo</h1>';
echo '<a href="/ost/posta/exportXMLdownload.php">Klikněte pro stažení souboru</a>';
echo '<p>&nbsp;</p>';
require(FileUp2('html_footer.inc'));
