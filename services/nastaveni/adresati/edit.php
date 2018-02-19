<?php
require("tmapy_config.inc");
require(FileUp2(".admin/edit_.inc"));
include_once(FileUp2('.admin/oth_funkce_2D.inc'));

$co=StrTok($GLOBALS["QUERY_STRING"], '&');

require(FileUp2("html_header_title.inc"));

if ($co == "filter") {
    Form_(array(
      'showaccess' => false,
      'nocaption' => true,
      'myform_schema' => '.admin/form_schema_filter.inc',
      'formname' => '',
      'showbuttons' => true,
    ));
}
else
  Form_(array("showaccess"=>true,));
require(FileUp2("html_footer.inc"));
?>
