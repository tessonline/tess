<?php
require("tmapy_config.inc");
require(FileUp2('.admin/brow_.inc'));
require(FileUp2('.admin/config.inc'));
require_once(FileUp2("interface/.admin/unispis_funkce.inc"));
require(FileUp2('html_header_full.inc'));
echo '<h1>Generování XML souborů</h1>';

Access();

foreach($_POST as $key => $val)
{
  $GLOBALS[$key] = $val;
  $_GET[$key] = $val;
}

$omez_stav_part = "";

require(FileUp2('posta/.admin/brow_func.inc'));

if (is_array($GLOBALS['omez_stav'])) {
  $where.= " AND (";
  foreach ($GLOBALS['omez_stav'] as $omez) {
    $part = getOmezStavPart($omez);
    $omez_stav_part.=$part." AND ";
    if ($omez == 1 || $omez == 4) {
      // pro tisk predavaciho protokolu
        $show_predani = true;
        $multipleedit = true;
    }
    if ($omez == -7 || $omez == -5)
      $multipleedit = true;
  }
  $omez_stav_part.=" 1=1)";
  $where.=$omez_stav_part;
//  $where.=" 0=1)";
} else {

  if ($GLOBALS['omez_stav']) {
    if ($GLOBALS['omez_stav']==201)
    {
      $multipleedit = true;
      $GLOBALS['ODESLANA_POSTA'] == 'f';
    }
    $omez_stav_part.=" AND ".getOmezStavPart($GLOBALS['omez_stav']);
  }
  $where.=$omez_stav_part;


  if ($GLOBALS['omez_stav'] == 1 || $GLOBALS['omez_stav'] == 4) {
    // pro tisk predavaciho protokolu
      $show_predani = true;
      $multipleedit = true;
  }

  if ($GLOBALS['omez_stav'] == -7 || $GLOBALS['omez_stav'] == -5)
    $multipleedit = true;

}
if ($GLOBALS['omez_uzel']>0 ) {

  $EddSql = LoadClass('EedSql');
  $GLOBALS['omez_uzel'] = is_array($GLOBALS['omez_uzel']) ? $GLOBALS['omez_uzel'] : explode(',',$GLOBALS['omez_uzel']) ;
  foreach ($GLOBALS['omez_uzel'] as $uzel) {
    $where_app = $EddSql->WhereOdborAndPrac($uzel);
    //  $where.= " AND (".$where_app."  OR referent in (".$USER_INFO['ID']."))";
    $where.= " AND (".$where_app."  )";
  }

}


if ($GLOBALS['omez_rok'] && !$_GET['VYHLEDAVANI']) { $where.=" AND cislo_spisu2 in (" . $GLOBALS['omez_rok'] . ")";}
//if ($GLOBALS['omez_zarizeni']) { $where.=" AND superodbor in (" . $GLOBALS['omez_zarizeni'] . ")";}
if ($GLOBALS['omez_zarizeni']) { $where.=" AND superodbor in (" . $GLOBALS['omez_zarizeni'] . ")";}

if ($GLOBALS['ODBOR'] == 0) UNSET($GLOBALS['ODBOR']);
$GLOBALS['MAIN_DOC'] = 1;

if ($_POST['SELECT_ID']) $GLOBALS['ID'] = $_POST['SELECT_ID'];
if ($_POST['SELECT_IDdenik']) $GLOBALS['ID'] = $_POST['SELECT_IDdenik'];


$sql = Table(array( 'return_sql'=>true,
    'appendwhere' => $where,
));

$IDs = array();
$q->query($sql);
while ($q->Next_Record())
  $IDs[] = $q->Record['ID'];


foreach($IDs as $ID) {
  $xml = getXMLDoc($ID);
  echo 'Vytvářím XML soubor '.$ID.'.xml<br/>';
  $tmp_soubor = $GLOBALS[CONFIG_POSTA][HLAVNI][tmp_adresar].$ID.'.xml';
  $fname[] = $ID.'.xml';
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
echo '<a href="exportXMLdownload.php">Klikněte pro stažení souboru</a>';
echo '<p>&nbsp;</p>';
require(FileUp2('html_footer.inc'));
