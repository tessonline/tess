<?php
require("tmapy_config.inc");
require(FileUp2(".admin/edit_.inc"));
require(FileUp2("html_header_full.inc"));

require(FileUp2(".admin/brow_.inc"));

$odb = $GLOBALS['ODBOR']; 
$ref = $GLOBALS['REFERENT']; 
UNSET($GLOBALS['ODBOR']); 
UNSET($GLOBALS['REFERENT']); 
$GLOBALS['ukaz_ovladaci_prvky'] = false;
$GLOBALS['FROM_EVIDENCE'] = 1;
$table = GetAgendaPath("POSTA")."/.admin/table_schema_simple.inc";
Table(
  array(
    "agenda"=>POSTA,
    "schema_file"=>$table,
    "appendwhere"=>"AND (ID_PUVODNI IN (".$GLOBALS['POSTA_ID'].") or p.ID IN (".$GLOBALS['POSTA_ID'].") )and odeslana_posta='f'",
    "showinfo"=>false,
    "showedit"=>false,
    "setvars"=>true,
    "unsetvars"=>true,
    "showhistory"=>false,
    "caption"=>"Seznam vyřizujích útvarů a zpracovatelů",
    "showdelete"=>false));

$GLOBALS['ODBOR'] = $odb;
$GLOBALS['REFERENT'] = $ref; 

//where odeslana_posta ='f' and id_puvodni = ".$GLOBALS['ID']

Form_(array("showaccess"=>true, "nocaption"=>false));
require(FileUp2("html_footer.inc"));
?>
