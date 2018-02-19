<?php
require("tmapy_config.inc");
require(FileUp2(".admin/edit_.inc"));
require(FileUp2("html_header_title.inc"));

if ($GLOBALS["smer"])
  Form_(array("showaccess" => true,"script_extension"=>"pp.php","caption"=>"Předávací protokol"));  
else
  Form_(array("showaccess" => true,"noshowclose"=>true));
require(FileUp2("html_footer.inc"));
?>
