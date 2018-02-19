<?php

include_once(FileUp2('.admin/table_func_pracovnik.inc'));

//$TABLE_CONFIG["schema"][] = array("field"=>"ID_ZAMESTNANI", "label"=>"ID",  "width"=>"1%","add"=>"align=center");
$TABLE_CONFIG["schema"][] = array("field"=>"CISLO_UK", "label"=>"WHOIS",  "width"=>"1%","add"=>"align=center");
$TABLE_CONFIG["schema"][] = array("field"=>"PRIJMENI...' ' ...JMENO", "label"=>"příjmení jméno",  "width"=>"60%","add"=>"align=left NOWRAP");
if ($GLOBALS['SHOW_FAKULTA']) $TABLE_CONFIG["schema"][] = array("field"=>"getPracoviste(ID_ORG)", "label"=>"fakulta",  "width"=>"40%","add"=>"align=left NOWRAP");

$TABLE_CONFIG["schema"][] = array("field"=>"getTypPomeru(ZAMESTNANI_TYP)", "label"=>"Typ",  "width"=>"40%","add"=>"align=left NOWRAP");
$TABLE_CONFIG["schema"][] = array("field"=>"getDatum(DATUM_OD)", "label"=>"poměr OD",  "width"=>"40%","add"=>"align=left NOWRAP");
$TABLE_CONFIG["schema"][] = array("field"=>"getDatum(DATUM_DO)", "label"=>"poměr DO",  "width"=>"40%","add"=>"align=left NOWRAP");

