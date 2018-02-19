<?php
require("tmapy_config.inc");
require(FileUp2(".admin/run2_.inc"));
require_once(Fileup2("html_header_title.inc"));

include_once(FileUp2(".admin/security_obj.inc"));
$USER_INFO = $GLOBALS["POSTA_SECURITY"]->GetUserInfo();
$id_user=$USER_INFO["ID"];

$sql = "update posta_spisovna set SKAR_ZNAK_ALT='".$znak."',last_date='".Date('Y-m-d')."',last_time='".Date('H:i:s')."',last_user_id=".$id_user." where id=".$GLOBALS['doc_id'];
$q = new DB_POSTA;
$q->query($sql);
require_once(Fileup2("html_footer.inc"));

