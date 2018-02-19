<?php
require("tmapy_config.inc");
require(FileUp2(".admin/brow_.inc"));
require(FileUp2("html_header_full.inc"));

If ($GLOBALS["ODESL_PRIJMENI"]) {$GLOBALS["ODESL_PRIJMENI"]='*'.$GLOBALS["ODESL_PRIJMENI"].'*';}

Table(array("showaccess" => true,"showselect"=>true,"setvars"=>true));  



require(FileUp2("html_footer.inc"));
?>
