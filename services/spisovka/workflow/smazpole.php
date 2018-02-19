<?php 
require("tmapy_config.inc");
require(FileUp2(".admin/brow_.inc"));
require(FileUp2("html_header_title.inc"));

include_once(FileUp2(".admin/db/db_posta.inc"));

$q = new DB_POSTA;
$sql="DELETE FROM posta_workflow_pole WHERE promenna = '".$_GET['promenna']."' AND id_posta=".$_GET['id_posta'];
$q->query($sql); 
?>

