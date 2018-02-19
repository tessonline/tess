<?php
require("tmapy_config.inc");
require(FileUp2(".admin/run2_.inc"));
//include(Fileup2(".admin/functions.inc"));

header("Location: ".GetAgendaPath('POSTA',false,true)."/output/pdf/obalka.php?DATUM_OD=".$GLOBALS["DATUM_OD"]);
//include('../../../output/pdf/obalky.php');

//echo "hotovo";
?>
