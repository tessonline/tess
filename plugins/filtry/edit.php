<?php
require("tmapy_config.inc");
require(FileUp2(".admin/edit_.inc"));
require(FileUp2("html_header_title.inc"));

$eid = $GLOBALS['EDIT_ID'];
$co=StrTok($GLOBALS["QUERY_STRING"], '&');

if ($co == 'insertfrom') $eid='';

Form_(array("showaccess"=>true, "caption"=>"Filtry", 'formvars'=>array('eid'=>$eid)));
require(FileUp2("html_footer.inc"));
?>
