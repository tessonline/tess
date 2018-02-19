<?php
require("tmapy_config.inc");
Header("Pragma: cache");
Header("Cache-Control: public"); 
require(FileUp2(".admin/upload_.inc"));
Upload(array());
