<?
require('tmapy_config.inc');
include_once(FileupUrl('.admin/db/db_default.inc'));

$db_name = $GLOBALS['PROPERTIES']['DB_NAME'] ? $GLOBALS['PROPERTIES']['DB_NAME'] : 'DB_DEFAULT';
$db = new $db_name;
$img_ok = FileUpUrl('images/ok_check.gif');
$img_ko = FileUpUrl('images/ko_check.gif');

if (isset($_POST['id'])){
	$id = $_POST['id'];
}
$sql = 'SELECT * FROM posta_adresati WHERE ID = '.$id;
$db->query($sql);
$db->Next_Record();
if ($db->Record['FROZEN'] == 'N') {
	$sqla = "UPDATE posta_adresati SET FROZEN = 'A' WHERE ID = ".$id; 
	if($db->query($sqla)){
		$result = '<img src="'.$img_ko.'"/ title="Neplatn&#225; adresa">';	
	}	 
} else {
	$sqln = "UPDATE posta_adresati SET FROZEN = 'N' WHERE ID = ".$id; 
	if($db->query($sqln)){  
		$result = '<img src="'.$img_ok.'" title="Platn&#225; adresa"/>';
	} 
}
//$str=iconv("UTF-8","iso-8859-2",$result);

echo $result;
?>