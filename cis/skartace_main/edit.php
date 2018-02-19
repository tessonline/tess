<?php
require("tmapy_config.inc");
require(FileUp2(".admin/edit_.inc"));
require(FileUp2("html_header_title.inc"));

if ($app == 'import') {
  Form_(array("showaccess" => true,"script_extension" => $app . ".php", "method"=>"POST","myform_schema"=>".admin/form_schema_import.inc" ));
  echo '<table height="400"><tr><td><p>&nbsp;</p></td></tr></table>';
  require(FileUp2("html_footer.inc"));
  Die();
}

Form_(array("showaccess" => true));  
require(FileUp2("html_footer.inc"));
?>
