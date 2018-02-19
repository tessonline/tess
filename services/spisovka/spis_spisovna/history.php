<?php
require("tmapy_config.inc");
require(FileUp2(".admin/history_.inc"));
require(FileUp2(".admin/upload_.inc"));
require(FileUp2("html_header_full.inc"));


$uplobj=Upload(array('create_only_objects'=>true,'noshowheader'=>true));


History(array());


require(FileUp2("html_footer.inc")); 
?>
