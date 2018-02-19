<?php
require("tmapy_config.inc");
require(FileUp2(".admin/upload_.inc"));
include_once(FileUp2(".admin/has_access.inc"));
Header("Pragma: cache");
Header("Cache-Control: public"); 
Upload(array());
?>
