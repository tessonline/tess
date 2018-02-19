<?php
require("tmapy_config.inc");
if (strpos($GLOBALS['EDIT_ID'],",")>0) {
  $GLOBALS['EDIT_ID'] = explode(',',$GLOBALS['EDIT_ID']);
}
require(FileUp2(".admin/edit_.inc"));
require(FileUp2("html_header_title.inc"));


Form_(array("showaccess" =>"true", 
  "method"=>"POST",
  "myform_schema"=>".admin/form_schema.inc", 
));


require(FileUp2("html_footer.inc"));
?>
