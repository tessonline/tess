<?php
require("tmapy_config.inc");
require(FileUp2(".admin/edit_.inc"));
require(FileUp2("html_header_title.inc"));
require(FileUp2(".admin/brow_.inc"));

$id_zal = $GLOBALS['EDIT_ID'];

$GLOBALS['ID'] = $GLOBALS['EDIT_ID']; 

EedTools::MaPristupKDokumentu($GLOBALS['ID'], 'elekotrnicky podpis');
//UNSET($GLOBALS['EDIT_ID']);
$table = GetAgendaPath("POSTA")."/.admin/table_schema_simple.inc";
Table(
  array(
    "agenda"=>POSTA,
    "schema_file"=>$table,
//    "appendwhere"=>"AND ID IN (".$GLOBALS['POSTA_ID'].")",
    "showinfo"=>false,
    "showedit"=>false,
    "setvars"=>true,
    "showhistory"=>false,
    "caption"=>"Elektronický podpis pro dokument",
    "showdelete"=>false));

$GLOBALS['ID'] = $id_zal;
Form_(array("showaccess" => true,"nocaption"=>true));  


$url = $_SERVER[REQUEST_URI];
//$url = str_replace('https', 'http', $url);
$url = str_replace('edit', 'run_ff', $url);


echo "<script>
if (navigator.userAgent.indexOf(\"Firefox\") > 0) {
  var url = '" . $url . "';
   $('form[name=\"frm_edit\"]').attr('action', url);
}

</script>
";
require(FileUp2("html_footer.inc"));
?>
