<?php
require("tmapy_config.inc");
$GLOBALS['BOX_ID'] = $GLOBALS['ID'];
$GLOBALS['PROPERTIES']['AGENDA_ID'] = 'BOX_ID';
require(FileUp2(".admin/delete_.inc"));
?>
