<?php
require("tmapy_config.inc");
require(FileUp2(".admin/brow_.inc"));
require(FileUp2("html_header_full.inc"));
require_once(FileUp2(".admin/security_obj.inc"));
require_once(FileUp2(".admin/security_name.inc"));
Table(array("showaccess" => true,"appendwhere"=>$where2,"showedit"=>false,"showdelete"=>false,"setvars"=>true));  
require(FileUp2("html_footer.inc"));
?>
