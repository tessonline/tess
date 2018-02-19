<?php
require('tmapy_config.inc');
require(FileUp2('.admin/brow_.inc'));
require_once(Fileup2('html_header_title.inc'));

$db_name = $GLOBALS['PROPERTIES']['DB_NAME'] ? $GLOBALS['PROPERTIES']['DB_NAME'] : 'DB_DEFAULT';
$db = new $db_name;
if (isset($_GET['id'])) {
	$id = $_GET['id'];
}
$sql = 'SELECT * FROM posta_adresati WHERE ID ='.$id;
$db->query($sql);
$db->Next_Record();
if ($db->Record['FROZEN'] = 'N') {
	$sqla = "UPDATE posta_adresati SET FROZEN = 'A' WHERE ID = ".$id; 
	if($db->query($sqla)){
		/*javascript*/
		
	}		
} 
if ($db->Record['FROZEN'] = 'A' || $db->Record['FROZEN'] = '') {
	$sqln = "UPDATE posta_adresati SET FROZEN = 'N' WHERE ID = ".$id; 
	if($db->query($sqln)){
		echo "aktualizovánoN";
		/*javascript*/
	}	
}

