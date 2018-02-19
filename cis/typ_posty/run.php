<?php
require("tmapy_config.inc");
require(FileUp2(".admin/run2_.inc"));
require_once(Fileup2("html_header_title.inc"));
require_once(Fileup2(".admin/odbory.inc"));

$odbory = getOdboryFromForm(array_merge($_GET, $_POST));

if ($DELETE_ID) {
  deleteOdbory($DELETE_ID) ;
}
else if ($EDIT_ID) {
  
  editOdbory($EDIT_ID, $odbory);
}


$lastid = Run_(array("showaccess"=>true,"outputtype"=>3));


if (!$DELETE_ID && !$EDIT_ID) {
  insertOdbory($lastid, $odbory);
}

require_once(Fileup2("html_footer.inc"));  

?>

