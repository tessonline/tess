<?php
echo "<h1>Konfig hodnoty</h1>";

$db_from = new DB_IMPORTER;
$db_from2 = new DB_IMPORTER;
$db_to = new DB_POSTA;

echo "<p>Směr kopírování:<br/>";
echo "Z - ";
echo "<font color='green'>" .$db_from->type. " - host:" .$db_from->Host. " -  DB:" . $db_from->Database . "</font>";
echo "<br/>";

echo "Do - ";
echo "<font color='green'>" .$db_to->type. " - host:" .($db_to->Host ? $db_to->Host : 'localhost'). " -  DB:" . $db_to->Database . "</font>";
echo "</p>";

function getCiselnik ($hodnota, $ciselnik) {
  global $cis;
  $ret = $cis[$ciselnik][$hodnota]['tess_id'];
  if (!$ret && $hodnota) {
    echo "<font color=red>nenaelzeno <b>$hodnota</b> v ciselniku <b>$ciselnik</b></font> <br/>";
    $ret = 0;
  }
  return $ret;
}