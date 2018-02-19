<?php
require("tmapy_config.inc");
require(FileUp2(".admin/edit_.inc"));
require(FileUp2("html_header_title.inc"));
Form_(array("showaccess" => true));  

if ($GLOBALS["TYP"] && !$is_filter) {
	echo "<script>DruhSkartaceFilter('".$GLOBALS[TYP]."')</script>";

}
require(FileUp2("html_footer.inc"));

