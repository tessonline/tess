<?php
require("tmapy_config.inc");
require(FileUp2(".admin/brow_.inc"));
require(FileUp2("html_header_full.inc"));
IF ($GLOBALS["TEXT"]) {$GLOBALS["TEXT"]="*".$GLOBALS["TEXT"]."*";}
Table(array("showaccess" => true));  
require(FileUp2("html_footer.inc"));
?>
