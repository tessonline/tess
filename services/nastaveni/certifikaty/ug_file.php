<?php
require("tmapy_config.inc");
header("Cache-Control: public, must-revalidate");
header("Pragma: hack");
require(FileUp2(".admin/upload_.inc"));
Upload(array());
