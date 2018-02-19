<?php
require("tmapy_config.inc");
require(FileUp2(".admin/brow_.inc"));
require("tmapy_config.inc");
include_once(FileUp2(".admin/brow_.inc"));
include_once(FileUp2(".admin/config.inc"));
include_once(FileUp2(".admin/status.inc"));
include_once(FileUp2(".admin/security_name.inc"));

include_once(FileUp2(".admin/oth_funkce.inc"));

include_once(FileUp2("skartaceInc.php"));

$stream = GenerujSkartacniProtokol($_POST);

$stream->Output();
