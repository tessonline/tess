<?php
require("tmapy_config.inc");
require(FileUp2(".admin/brow_.inc"));
include_once($GLOBALS['TMAPY_LIB'] . '/oohforms.inc');
require_once(FileUp2('.admin/el/of_select_.inc'));

require_once(FileUp2('.admin/classes/EedRadar.inc'));

require(FileUp2("html_header_full.inc"));


NewWindow(array("fname" => "AgendaSpis", "name" => "AgendaSpis", "header" => true, "cache" => false, "window" => "edit"));

if ($GLOBALS['CONFIG_POSTA']['RADAR']['adresar']) {
  if (!@$d = dir($GLOBALS['CONFIG_POSTA']['RADAR']['adresar'])) {
    echo "<tr><td><b>Cesta <i>".$cesta."</i> nenalezena!!!</b></td></tr></table>";
    require_once(FileUp2("html_footer.inc"));
    die;

  }
  echo '<h1>Nalezené soubory pro načtení:</h1>';
  echo '<a href="#" class="btn" onClick="javascript:NewWindowAgendaSpis(\'automat.php?show=1\');">Načíst vše</a><br/>';


  while($entry=$d->read()) {
    if ($entry<>'.' && $entry<>'..') {
      $file = pathinfo($entry);
      if (strtolower($file['extension']) == 'xml')
        echo '<a href="#" onClick="javascript:NewWindowAgendaSpis(\'zaloz.php?file='.$entry.'\');">'.$entry.'</a><br/>';
    }
  }

}

echo '<h1>Konfigurace:</h1>';
$kats = getSelectDataEed(new of_select_nastaveni_kategorie(array()));

 $nadpis = $kats['RADAR'];
 $KATEGORIE = 'RADAR';
  $where = '';
	$count = Table(array(
      "agenda" => "POSTA_KONFIGURACE",
			"appendwhere"=>$where,
			"maxnumrows"=>10,
			"caption" => $nadpis,
			"showdelete"=>true,
			"showedit"=>true,
			"showinfo"=>false,
			"showdelete"=>false,
			//         "showinfo"=>$USER_INFO["LOGIN"]!="anonymous",
			"nocaption"=>false,
			//         "sql"=>$q,
			"showaccess"=>true,
			"setvars"=>true,
			"unsetvars"=>true,
	));


$id = EedRadar::getIDKonfigurace();
if (!$id) $id = EedRadar::setIDKonfigurace();;

Access(array('agenda'=>'POSTA'));
$GLOBALS['ID'] = $id;
//  $table = GetAgendaPath('POSTA') . '/.admin/table_schema_simple.inc';

$count = Table(array(
    "agenda" => "POSTA",
//      'schema_file' => $table,
		"caption" => 'Nastavení defaultních hodnot',
		"showdelete"=>true,
		"showedit"=>true,
		"showinfo"=>false,
    "showexport" => false,
		"showdelete"=>false,
		"nocaption"=>false,
		"showaccess"=>true,
		"setvars"=>true,
		"unsetvars"=>true,
));

echo "<p><b>Povolené tagy pro přepis hodnot:</b><br/>
%SUBJEKT_JMENO%,&nbsp;
%SUBJEKT_IC%,&nbsp;
%SUBJEKT_OBEC%,&nbsp;
%SUBJEKT_COBCE%,&nbsp;
%SUBJEKT_ULICE%,&nbsp;
%SUBJEKT_COR%,&nbsp;
%SUBJEKT_CP%,&nbsp;
%SUBJEKT_PSC%,&nbsp;
%SUBJEKT_DS%<br/>
%PRESTUPEK_CJ%,&nbsp;
%PRESTUPEK_RZ%,&nbsp;
%PRESTUPEK_NAMERENA%,&nbsp;
%PRESTUPEK_TOLERANCE%,&nbsp;
%PRESTUPEK_VYPOCTENA%,&nbsp;
%PRESTUPEK_DATUM%</p>";

require(FileUp2("html_footer.inc"));
