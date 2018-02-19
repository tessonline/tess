<?php
require("tmapy_config.inc");
require(FileUp2(".admin/db_index.inc"));
$_SESSION["CENA_OBYC"]=$GLOBALS["CENA_OBYC"];
Die($GLOBALS["CENA_OBYC"]);

?>

