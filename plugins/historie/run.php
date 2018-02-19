<?php
require("tmapy_config.inc");
require(FileUp2(".admin/run2_.inc"));
require_once(Fileup2("html_header_title.inc"));
Flush();
include_once(FileUp2(".admin/security_obj.inc")); 
$USER_INFO = $GLOBALS["POSTA_SECURITY"]->GetUserInfo();
$id_user=$USER_INFO["ID"];

if (!$EDIT_ID && !$DELETE_ID) $is_insert = true;
if ($EDIT_ID) $is_edit = $EDIT_ID;
if ($DELETE_ID) $is_delete = $DELETE_ID;

require_once(Fileup2("html_footer.inc"));  

?>

