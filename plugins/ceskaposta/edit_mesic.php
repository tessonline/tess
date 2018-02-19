<?php
require("tmapy_config.inc");
require(FileUp2(".admin/edit_.inc"));
require(FileUp2("html_header_title.inc"));

Form_(array("showaccess"=>true, "caption"=>"Česká pošta","script_extension"=>"mesicni_vykaz.php"));
require(FileUp2("html_footer.inc"));
?>
