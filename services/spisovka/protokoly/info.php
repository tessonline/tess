<?php
require("tmapy_config.inc");
require(FileUp2(".admin/brow_.inc"));
require(FileUp2("html_header.inc"));

$q = new DB_POSTA;
//$sql = "SELECT * from posta_view_spisy ";
$sql = "SELECT count(*) as max from posta ";
//$where = " WHERE ((odeslana_posta = 'f' ) or (odeslana_posta = 't' and (id_puvodni = 0 or id_puvodni is null))) and rok = ".$rok." ORDER by cislo_jednaci1";

$superodbor = "";
$sql .= " WHERE cislo_spisu2 = ".$_GET['ROK']." ";
//$sql .= " WHERE EXTRACT(YEAR FROM datum_podatelna_prijeti) = ".$_GET['ROK']." ";
if ($GLOBALS['SUPERODBOR']) $superodbor = 'AND SUPERODBOR IN ('.$GLOBALS['SUPERODBOR'].')';
if ($GLOBALS['MAIN_DOC']) $sql .= 'AND MAIN_DOC='. $GLOBALS['MAIN_DOC'].' ';
else $sql .= "AND MAIN_DOC=1";

if ($_GET['MESIC'])   $sql .= " AND EXTRACT(MONTH FROM datum_podatelna_prijeti) = ". $_GET['MESIC'];


$q->query($sql);
$q->Next_Record();
$celkovy_pocet = $q->Record['MAX'] ? $q->Record['MAX'] : 1;

$doba_sekund = $celkovy_pocet/10;
$doba_minut = $doba_sekund / 60;
$doba_hodin = floor ($doba_minut / 60);

$zbytek_minut = $doba_minut - ($doba_hodin * 60);

if ($doba_hodin>0) $cas = $doba_hodin ." hod a ";
if (!$_GET['MESIC']) $_GET['MESIC'] = 0;
$cas .= floor($zbytek_minut) ." min. ";
echo "<center><p>Celkový počet jednacích čísel: <b>$celkovy_pocet</b><br/>Skript bude trvat přibližně <b>$cas</b>";
echo '</p><p>
<input name="StartGeneruj" type="button" class="btn" value="Skutečně spustit" onclick="Start('.$_GET['ROK'].','.$_GET['MESIC'].','.floor($doba_sekund).'000)"></p>
</center>';

require(FileUp2("html_footer.inc"));

