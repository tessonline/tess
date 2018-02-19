<?php
$GLOBALS['edit'] = "";
require("tmapy_config.inc");
require(FileUp2(".admin/edit_.inc"));
require(FileUp2("html_header_title.inc"));
Access();
Form_(array("showaccess" => true));  
require(FileUp2("html_footer.inc"));
?>
