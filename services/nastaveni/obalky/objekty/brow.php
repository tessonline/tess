<?php
require("tmapy_config.inc");
require(FileUp2(".admin/brow_.inc"));
require(FileUp2("html_header_full.inc"));

$count=Table(array("showaccess" => true,"showself"=>true));  

require(FileUp2("html_footer.inc"));
?>
