<?php
require("tmapy_config.inc");
require(FileUp2(".admin/edit_.inc"));
require(FileUp2("html_header_title.inc"));

Form_(array("showaccess"=>true, "nocaption"=>true,"caption"=>"Smazat spis?","showbuttons"=>false));
require(FileUp2("html_footer.inc"));
?>
