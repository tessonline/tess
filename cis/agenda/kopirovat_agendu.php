<?php 
$QUERY_STRING = "insert";
require("tmapy_config.inc");
require(FileUp2(".admin/edit_.inc"));
require(FileUp2("html_header_title.inc"));

$db = new DB_POSTA();
$sql = "SELECT nazev, neaktivni from cis_posta_agenda WHERE ID =".$GLOBALS['id'];
$db->query($sql);
$db->Next_Record();
$GLOBALS['NAZEV'] = $db->Record['NAZEV'];
$GLOBALS['NEAKTIVNI'] = $db->Record['NEAKTIVNI'];
$USER_INFO = $GLOBALS["TMAPY_SECURITY"]->GetUserInfo();
if (!HasRole('spravce'))
$GLOBALS['ID_SUPERODBOR'] = $USER_INFO['PRACOVISTE'];

Form_(array("showaccess" => true, "myform_schema"=>".admin/form_schema_kopie.inc"));
require(FileUp2("html_footer.inc"));
?>