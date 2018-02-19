<?php
//$TABLE_CONFIG["callback"]="ChangeClassBarva";
//$TABLE_CONFIG["schema"][] =  array( "field"=>"JIDVS(ID)", "label"=>"JID VS");
$TABLE_CONFIG["schema"][] =  array( "field"=>"JID", "label"=>"JID VS");

$TABLE_CONFIG["schema"][] =  array( "field"=>"TEXT", "label"=>"Kod");
$TABLE_CONFIG["schema"][] =  array( "field"=>"ShowSkartaceVS(SKAR_ZNAK,DOBA,TYP)", "label"=>"Skartace");
$TABLE_CONFIG["schema"][] =  array( "field"=>"ExportXMLVS(ID,TYP)", "label"=>"","class"=>"image");

$TABLE_CONFIG['syscolumns'] = array(
 'edit' => array ('theme'=>array('dropdown'=>true, 'column'=>true)),
 'delete ' => array ('theme'=>array('dropdown'=>true, 'column'=>true)),
);

