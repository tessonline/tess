<?php
require("tmapy_config.inc");
require(FileUp2(".admin/run2_.inc"));
require_once(Fileup2("html_header_title.inc"));
require_once(Fileup2(".admin/security_.inc"));
require_once(Fileup2(".admin/security_name.inc"));
// if (!$GLOBALS['SUPERODBOR'])
//   $GLOBALS['SUPERODBOR']=VratSuperOdbor();

Run_(array("showaccess"=>true,"outputtype"=>3));
require_once(Fileup2("html_footer.inc"));  

?>

