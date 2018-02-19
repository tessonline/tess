<?php
require("tmapy_config.inc");
require(FileUp2(".admin/brow_.inc"));
if (!$_SERVER['HTTPS'] == 'on') Die();

require(FileUp2("html_header_full.inc"));
include_once($GLOBALS['TMAPY_LIB'] . '/oohforms.inc');
require_once(FileUp2('.admin/el/of_select_.inc'));

$kats = getSelectDataEed(new of_select_nastaveni_kategorie(array()));

$where = 'AND 1=2';

if ($GLOBALS['CONFIG']['USE_SUPERODBOR']) {
  if (HasRole('spravce') && !$_GET['omez_zarizeni']) $where = " AND superodbor is NULL or SUPERODBOR=0";
  if (HasRole('lokalni-spravce')) $where = " AND superodbor=" . EedTools::VratSuperOdbor();

  if (HasRole('spravce')) {
    include_once(FileUp2('.admin/brow_superodbor.inc'));
  }

  if ($GLOBALS['omez_zarizeni']) $where = " AND superodbor=" . $GLOBALS['omez_zarizeni'];

}

$where .= ' AND odbor is null ';

foreach ($kats as $KATEGORIE => $nadpis) {
	if ((isset($_GET['KATEGORIE']) && $_GET['KATEGORIE']==$KATEGORIE) || !isset($_GET['KATEGORIE']))
	$count = Table(array(
			"appendwhere"=>$where,
      'tablename' => $KATEGORIE,
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
	
}

if ($GLOBALS['omez_zarizeni']) {

  $KATEGORIE = '';
  $where = " AND superodbor=" . $GLOBALS['omez_zarizeni'];
  $where .= ' AND odbor is not null ';
	$count = Table(array(
			"appendwhere"=>$where,
      'tablename' => 'SPISODBOR',
			"maxnumrows"=>10,
      'agenda' => 'POSTA_KONFIGURACE_ODBORY',
			"caption" => 'Přenastavení pro spisové uzly',
			"showdelete"=>true,
			"showedit"=>true,
			"showinfo"=>false,
			//         "showinfo"=>$USER_INFO["LOGIN"]!="anonymous",
			"nocaption"=>false,
			//         "sql"=>$q,
			"showaccess"=>true,
			"setvars"=>true,
			"unsetvars"=>true,
	));

  NewWindow(array('fname' => 'AgendaSpis', 'name' => 'AgendaSpis', 'header' => true, 'cache' => false, 'window' => 'edit'));
  echo "<a  class=\"btn btn-loading\" href=\"#\" onClick=\"javascript:NewWindowAgendaSpis('odbory/edit.php?insert&SUPERODBOR=".$GLOBALS['omez_zarizeni']."&cacheid=')\">Přidat parametr</a>";


}


require(FileUp2("html_footer.inc"));

?>
