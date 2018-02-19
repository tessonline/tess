<?php
require('tmapy_config.inc');
require(FileUp2('.admin/brow_.inc'));
if (!$_SERVER['HTTPS'] == 'on') Die();
require(FileUp2('html_header_full.inc'));

echo "<h1>Vítejte v ePodatelně</h1>";
$path_to_upload = GetAgendaPath($name, false, true);
NewWindow(array("fname" => "Obecne", "name" => "Obecne", "header" => true, "cache" => false, "window" => "edit"));

echo '<p>Na výběr máte dvě možnosti</p>
<h2>1. Import XML dat z jiné ESS</h2>';
echo "<input type='button' onclick=\"NewWindowObecne('$path_to_upload/edit.php?insert&app=import&cacheID=');\" name='' value='Nahrát soubor' class='btn' title=\"Nahrát soubor\">&nbsp;&nbsp;&nbsp;";
echo '
<h2>2. Načíst e-maily z ePodatelny</h2>';
echo '<a href="prichozi.php" class="btn">Načíst emaily</a>';
//echo "<input type='button' onclick=\"NewWindowObecne('$path_to_upload/edit.php?insert&app=rucne&cacheID=');\" name='' value='Nahrát soubor' class='btn' title=\"Nahrát soubor\">&nbsp;&nbsp;&nbsp;";

require(FileUp2("html_footer.inc"));