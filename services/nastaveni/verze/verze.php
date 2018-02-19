<?php
require('tmapy_config.inc');
require(FileUp2('.admin/brow_.inc'));
require(FileUp2('html_header_full.inc'));

if (!HasRole('spravce')) {
	echo '<h1>Chyba</h1><p::Nemáte oprávnění správce, požádejte správce aplikace</p>';
  require(FileUp2('html_footer.inc'));
	Die();
}

function OrezText($text) {
//  $text = mb_substr($text,1);
//  if (mb_substr($text, -1) == '"') $text = mb_substr($text, 0, -1);
//  if (trim($text) == '"') $text = '';
  $text = iconv('WINDOWS-1250', 'UTF-8', $text);
  $text = nl2br($text);
  return $text;
}

$file = FileUpUrl('.admin/changelog/EED_changelog.csv');
$fp = fopen($file, 'r');
$data = fread($fp, filesize($file));
fclose($fp);


$radky = explode('~', $data);
$sett = array();
foreach($radky as $key => $val) {
  $temp = explode('|', $val);
  $key = str_replace(' ','', $temp[1]);
  $key = str_replace(':','', $key);
  $key = str_replace('-','', $key);
  $sett[$key]['VERZE'] = $temp[0];
  $sett[$key]['DATUM'] = $temp[1];
  $sett[$key]['PLUGIN'] = $temp[2];
  $sett[$key]['POPIS'] = OrezText($temp[3]);
  $sett[$key]['OPRAVY'] = OrezText($temp[4]);

  if( $sett[$key]['POPIS'] == '' && $sett[$key]['OPRAVY'] == '') unset($sett[$key]);
}
//print_r($sett);
krsort($sett);

include_once $GLOBALS["TMAPY_LIB"]."/db/db_array.inc";
echo '<h1>Historie verzí TESS</h1>';
$verze = '';
foreach($sett as $key => $val) {
  if ($verze <> $val['VERZE']) {
    $verze = $val['VERZE'];

    $verze_pole = array();
    foreach($sett as $key1 => $val1) {
      if ($val1['VERZE'] == $verze) {
        if ($val1['PLUGIN'] == '')
          $verze_pole[] = $val1;
        if ($GLOBALS["CONFIG_POSTA"]["PLUGINS"][$val1['PLUGIN']]['enabled'] == true)
          $verze_pole[] = $val1;
      }
    }
    $db_arr = new DB_Sql_Array;
    $db_arr->Data = $verze_pole;

    if (count($verze_pole)>0)
      Table(array(
        "db_connector" => &$db_arr,
        "showaccess" => true,
        "tablename" => 'table'.$verze,
        "showedit"=>false,
        "showdelete"=>false,
        "showselect"=>false,
        "multipleselect"=>false,
        "caption" => $verze,
        "showinfo"=>false,
        'schema_file' => '.admin/table_schema_vypis.inc',
        "multipleselectsupport"=>false
      ));

      echo '<a class="btn" href="/ost/posta/brow.php">Návrat zpět</a>';


  }
}

require(FileUp2('html_footer.inc'));
