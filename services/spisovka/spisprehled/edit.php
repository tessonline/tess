<?php
require("tmapy_config.inc");
require(FileUp2(".admin/edit_.inc"));
require(FileUp2("html_header_title.inc"));

Form_(array("showaccess"=>true, "nocaption"=>false));

if ($GLOBALS["ODES_TYP"])
 echo "<script>DruhAdresata('".$GLOBALS[ODES_TYP]."')</script>";



require(FileUp2("html_footer.inc"));
?>
