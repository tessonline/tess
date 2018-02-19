<?php
include_once(FileUpUrl('.admin/table_funkce.inc'));
$qqq = new DB_POSTA;
$TABLE_CONFIG["schema"][] = array("field"=>"ID", "label"=>"id",  "width"=>"10%","add"=>"align=center");
$TABLE_CONFIG["schema"][] = array("field"=>"UkazUsera(OWNER_ID)", "label"=>"Kdo",  "width"=>"30%","add"=>"align=center");
$TABLE_CONFIG["schema"][] = array("field"=>"LAST_DATE...'&nbsp;v&nbsp;'...LAST_TIME", "label"=>"dne",  "width"=>"20%","add"=>"align=center");
//$TABLE_CONFIG["schema"][] = array("field"=>"SESSION_ID", "label"=>"session",  "width"=>"10%","add"=>"align=center");
$TABLE_CONFIG["schema"][] = array("field"=>"TEXT", "label"=>"Akce",  "width"=>"50%","add"=>"align=left");
?>
