<?php
require("tmapy_config.inc");
require(FileUp2(".admin/run2_.inc"));
require_once(Fileup2("html_header_title.inc"));
if (!$GLOBALS['KLIENT_AUTHEN']) $GLOBALS['KLIENT_AUTHEN'] = 0;
if (!$GLOBALS['KLIENT_MUZO']) $GLOBALS['KLIENT_MUZO'] = 0;

Run_(array("showaccess"=>true,"outputtype"=>3));
require_once(Fileup2("html_footer.inc"));  

?>

