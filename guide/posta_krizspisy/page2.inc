<?php
include_once(FileUp2('.admin/adresati_func.inc'));
//$where.=" AND CISLO_SPISU1<>0 and spis_vyrizen is null";
$where.=" AND CISLO_SPISU1<>0";
if ($GLOBALS["CONFIG"]["DB"]=="mssql")
  $GLOBALS["ZADEJ_SQL"]="p.*";
else
  $GLOBALS["ZADEJ_SQL"]="DISTINCT ON (cislo_spisu1,cislo_spisu2) p.*";
$GLOBALS["ZADEJ_ORDER_BY"]="cislo_spisu1 ASC, cislo_spisu2 ASC";

$GLOBALS['MAIN_DOC'] = 1;
//echo "smer je $SMER_KRIZ";

Table(array("agenda" => "POSTA", "showselect"=>true, "showedit"=>false,"appendwhere"=>$where,"schema_file" => '.admin/table_schema_simple.inc',
"showdelete"=>false, "showguide"=>true,"setvars"=>true, "nopaging"=>true,"showinfo"=>false,"showhistory"=>false,"action"=>"./guide/posta_krizspisy/page3.php"));
