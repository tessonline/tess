<?php
$TABLE_CONFIG["schema"][] =  array( "field"=>"ID", "label"=>"ID","add"=>"align=center");
$TABLE_CONFIG["schema"][] =  array( "field"=>"NAME", "label"=>"Odbory/oddělení","add"=>"align=left");
$TABLE_CONFIG["schema"][] =  array( "field"=>"ZKRATKA", "label"=>"Zkratka","add"=>"align=center");
$TABLE_CONFIG["schema"][] =  array( "field"=>"UkazPrava(PRAVA)", "label"=>"Kody");

$TABLE_CONFIG['syscolumns'] = array(
 'upload' => array ('theme'=>array('dropdown'=>true, 'column'=>true)),
 'edit' => array ('theme'=>array('dropdown'=>true, 'column'=>true)),
 'delete' => array ('theme'=>array('dropdown'=>true, 'column'=>true))
);