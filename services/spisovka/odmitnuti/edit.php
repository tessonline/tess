<?php
require("tmapy_config.inc");

require(FileUp2(".admin/edit_.inc"));
require(FileUp2("html_header_title.inc"));
require(FileUp2(".admin/brow_.inc"));

EedTools::MaPristupKDokumentu($GLOBALS['POSTA_ID'], 'odmitnuti dokumentu');

$cj_obj = LoadClass('EedCj',$GLOBALS['POSTA_ID']);
$cj_info = $cj_obj->GetCjInfo($GLOBALS['POSTA_ID']);
$caption = $cj_info['CELE_CISLO'];
echo '<h1 align="center">'.$caption.'</h1>';


// $id_zal = $GLOBALS['ID'];
//
// $GLOBALS['ID'] = $GLOBALS['POSTA_ID']; $GLOBALS['ukaz_ovladaci_prvky'] = false;
// $table = GetAgendaPath("POSTA")."/.admin/table_schema_simple.inc";
// Table(
//   array(
//     "agenda"=>POSTA,
//     "schema_file"=>$table,
//     "appendwhere"=>"AND p.ID IN (".$GLOBALS['POSTA_ID'].")",
//     "showinfo"=>false,
//     "showedit"=>false,
//     "setvars"=>true,
//     "unsetvars"=>true,
//     "showhistory"=>false,
//     "caption"=>"Schvalovací proces pro dokument",
//     "showdelete"=>false));
//
// $GLOBALS['ID'] = $id_zal;

Form_(array("showaccess"=>true, "nocaption"=>false, "showbuttons"=>true));
require(FileUp2("html_footer.inc"));

?>
