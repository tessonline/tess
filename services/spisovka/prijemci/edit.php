<?php
session_start();
require("tmapy_config.inc");
require(FileUp2(".admin/edit_.inc"));
require(FileUp2("html_header_title.inc"));
if (!$GLOBALS["ODES_TYP"]) $GLOBALS["ODES_TYP"]='O';
Form_(array("showaccess" => true,"formname"=>"prijemce"));  
echo "<script>DruhAdresata('".$GLOBALS["ODES_TYP"]."')</script>";
require(FileUp2("html_footer.inc"));
?>
