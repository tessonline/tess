<?php
require("tmapy_config.inc");
require(FileUp2(".admin/brow_.inc"));
include_once($GLOBALS['TMAPY_LIB'] . '/oohforms.inc');
require_once(FileUp2('.admin/el/of_select_.inc'));
require(FileUp2(".admin/security_name.inc"));
include_once(FileUp2('.admin/oth_funkce_2D.inc'));


require(FileUp2("html_header_full.inc"));

$path = GetAgendaPath('POSTA_NASTAVENI_ADRESATI', false, true);
$link_self = $path."/index.php?frame&SHOW_ONE=1&ID=&_ODES_TYP='...ODES_TYP...'&_ODESL_ADRKOD='...ODESL_ADRKOD...'&_ODESL_PRIJMENI='...ODESL_PRIJMENI...'&_ODESL_JMENO='...ODESL_JMENO...'&_ODESL_ODD='...ODESL_ODD...'&_ODESL_OSOBA='...ODESL_OSOBA...'&_ODESL_TITUL='...ODESL_TITUL...'&_ODESL_ULICE='...ODESL_ULICE...'&_ODESL_CP='...ODESL_CP...'&_ODESL_COR='...ODESL_COR...'&_ODESL_ICO='...ODESL_ICO...'&_ODESL_PSC='...ODESL_PSC...'&_ODESL_POSTA='...ODESL_POSTA...'&XXX1='...XXX1...'&XXX=1";
include(FileUp2(".admin/table_append_where.inc"));

access();
if (!(HasRole('spravce') || HasRole('podatelna') || HasRole('podatelna'))) {
//  $GLOBALS['ODBOR']=VratOdbor();
}

if (!$GLOBALS['TYP_VIEW']) $GLOBALS['TYP_VIEW'] = 1;
$temp = $_GET;
unset($GLOBALS['FROZEN']);

if ($GLOBALS['TYP_VIEW'] == 2)
$count = Table(array(
  "agenda"=>"POSTA_NASTAVENI_ADRESATI_NEW",
  "tablename"=>"adresati",
  "appendwhere"=>$app,
//  "showself"=>true,
//  "showselfurl"=>$link_self,
  //"maxnumrows"=>10,
//   "showdelete"=>false,
//   "showedit"=>false,
  "showinfo"=>false,	 
  "showaccess"=>true,
  "setvars"=>true,
  "unsetvars"=>true,
));

foreach ($temp as $key => $val) $GLOBALS[$key] = $val;
$_GET = $temp;
//print_r($_GET);


if ($GLOBALS['TYP_VIEW'] == 1)
$count = Table(array(
//  "agenda"=>"POSTA_NASTAVENI_ADRESATI",
  "tablename"=>"posta",
  "appendwhere"=>$app,
  "caption" => 'Souhrnný přehled adres v EED a v ručně zadaných adresátech',
//  "showselfurl"=>$link_self,
  //"maxnumrows"=>10,
   "showdelete"=>false,
   "showedit"=>false,
  "showinfo"=>false,
  "showaccess"=>true,
  "setvars"=>true,
));


/*
if ($count == 1 && $GLOBALS["SHOW_ONE"]) {
  //echo $GLOBALS["SHOW_ONE"]." |<br />";
  //echo $app."<br />";
  //$app1 = "";
  Table(array(
    "agenda"=>"POSTA",
    "tablename"=>"posta",
    "appendwhere"=>$app,
    "showself"=>false,
    //"maxnumrows"=>10,
    "showdelete"=>false, 
    "showedit"=>false,
    "showinfo"=>true,	 
    "showaccess"=>true,
    "setvars"=>true, 
  ));
}
*/
require(FileUp2("html_footer.inc"));

?>
