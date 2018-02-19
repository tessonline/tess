<?php
session_start();
require("tmapy_config.inc");
require(FileUp2(".admin/edit_.inc"));
require(FileUp2("html_header_title.inc"));
Form_(array("showaccess" => true, 'caption' => ''));




require(FileUp2("html_footer.inc"));
