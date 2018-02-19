<?php
if ($send)
  Header("Location: ../../edit.php?info&EDIT_ID=".$EDIT_ID."&cacheid=1");
require("tmapy_config.inc");
require(FileUp2(".admin/edit_.inc"));
require(FileUp2("html_header_title.inc"));
if ($app == 'import') {
  Form_(array("showaccess" => true,"script_extension" => "import.php", "method"=>"POST","myform_schema"=>".admin/form_schema.inc" ));
  echo '<p>&nbsp;</p>';
  echo '<p>&nbsp;</p>';
  echo '<p>&nbsp;</p>';
  echo '<p>&nbsp;</p>';
  echo '<p>&nbsp;</p>';
  echo '<p>&nbsp;</p>';
  echo '<p>&nbsp;</p>';
  require(FileUp2("html_footer.inc"));
   Die();
}
Form_(array("showaccess" => true));  
require(FileUp2("html_footer.inc"));
?>
