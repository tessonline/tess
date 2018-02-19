<?php
$TABLE_CONFIG["schema"][] = array("field"=>"JID", "label"=>"id",  "width"=>"1%","add"=>"align=center",'is_html' => true);
$TABLE_CONFIG["schema"][] = array("field"=>"NAZEV", "label"=>"Entita",  "width"=>"80%","add"=>"align=left NOWRAP",'is_html' => true);
$TABLE_CONFIG["schema"][] = array("field"=>"VEC", "label"=>"Věc",  "width"=>"80%","add"=>"align=left NOWRAP",'is_html' => true);
$TABLE_CONFIG["schema"][] = array("field"=>"'<b>'...CZDate(DATUM_OTEVRENI)...'</b>", "label"=>"Datum otevření",  "width"=>"20%","add"=>"align=left NOWRAP",'is_html' => true);
$TABLE_CONFIG["schema"][] = array("field"=>"'<b>'...CZDate(DATUM_UZAVRENI)...'</b>", "label"=>"Datum uzavření",  "width"=>"20%","add"=>"align=left NOWRAP",'is_html' => true);
$TABLE_CONFIG["schema"][] = array("field"=>"Stav", "label"=>"STATUS",  "width"=>"10%","add"=>"align=left NOWRAP",'is_html' => true);
