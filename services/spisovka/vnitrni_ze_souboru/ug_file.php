<?php
require("tmapy_config.inc");
require(FileUp2(".admin/upload_.inc"));
Header("Pragma: cache");
Header("Cache-Control: public"); 
Upload(array());
?>
