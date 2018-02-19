<?php
session_start();
require("tmapy_config.inc");
require_once(FileUp2(".admin/config.inc"));
require_once(FileUp2(".admin/db/db_posta.inc"));
require(FileUp2(".admin/brow_.inc"));
include_once(FileUp2(".admin/security_.inc")); 

if ($GLOBALS["EXPORT_ALL_step"]<2)
  require(FileUp2("html_header_posta.inc"));
include(FileUp2(".admin/brow_func.inc"));
