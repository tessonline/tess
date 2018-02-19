<?php
require("tmapy_config.inc");
require(FileUp2(".admin/run2_.inc"));
require_once(Fileup2("html_header_title.inc"));
$GLOBALS["AKTIVNI"]=$GLOBALS["AKTIVNI"]?$GLOBALS["AKTIVNI"]:'0';

if ($GLOBALS['DELETE_ID']) {
  $sql = 'delete from  posta_spisovna_boxy_ids where box_id='.$GLOBALS['DELETE_ID'];
  $a = new DB_POSTA;
  $a->query($sql);
}
Run_(array("showaccess"=>true,"outputtype"=>3));
require_once(Fileup2("html_footer.inc"));  

?>

