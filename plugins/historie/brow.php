<?php
require("tmapy_config.inc");
require(FileUp2(".admin/brow_.inc"));
require(FileUp2(".admin/security_name.inc"));
require(FileUp2(".admin/brow_func.inc"));
require(FileUp2("html_header_full.inc"));
  $GLOBALS[SUPERODBOR]=VratSuperOdbor();

$path = GetAgendaPath('POSTA_NASTAVENI_ADRESATI', false, true);
$link_self = $path."/index.php?frame&SHOW_ONE=1&ID=&_ODES_TYP='...ODES_TYP...'&_ODESL_ADRKOD='...ODESL_ADRKOD...'&_ODESL_PRIJMENI='...ODESL_PRIJMENI...'&_ODESL_JMENO='...ODESL_JMENO...'&_ODESL_ODD='...ODESL_ODD...'&_ODESL_OSOBA='...ODESL_OSOBA...'&_ODESL_TITUL='...ODESL_TITUL...'&_ODESL_ULICE='...ODESL_ULICE...'&_ODESL_CP='...ODESL_CP...'&_ODESL_COR='...ODESL_COR...'&_ODESL_ICO='...ODESL_ICO...'&_ODESL_PSC='...ODESL_PSC...'&_ODESL_POSTA='...ODESL_POSTA...'&XXX1='...XXX1...'&XXX=1";
include(FileUp2(".admin/table_append_where.inc"));
/*
if (!HasRole('podatelna'))
  $app=$app.$where;
*/
Table(array(
  "agenda"=>"STARA_POSTA",
  "tablename"=>"posta",
//  "appendwhere"=>$app,
  "showself"=>false,
  //"maxnumrows"=>10,
  "showdelete"=>false, 
  "showedit"=>false,
  "showinfo"=>true,	 
  "showaccess"=>true,
  "setvars"=>true, 
  "showhistory"=>true,
  "showupload"=>true,

  "unsetvars"=>array("except"=>array("ID")),
  "showselect"=>true,
  "multipleselect"=>true,
  "multipleselectsupport"=>true,
));

require(FileUp2("html_footer.inc"));
?>
