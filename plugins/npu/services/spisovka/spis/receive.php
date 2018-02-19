<?php
require("tmapy_config.inc");
require(FileUp2(".admin/brow_.inc"));

///nutno mit nejake pravo na cteni
Access();
if(!HasSubRole('read')) exit;



$q = new DB_MONUMNIS;

echo "<script>alert('ident je ".$ident."');</script>";
//    $q->query('SELECT idznacka, txthled FROM npu_spisuklznac WHERE txthled ILIKE \'%' . $term . '%\' ORDER BY txthled LIMIT 100');
//    $q->query('SELECT idznacka, txtznacka FROM npu_spisuklznac WHERE txtznacka ILIKE \'%' . $term . '%\' ORDER BY txtznacka LIMIT 100');
$q->query('SELECT idznacka, txtznacka FROM SpisUklZnac WHERE txtznacka LIKE \'%' . $term . '%\' ORDER BY txtznacka LIMIT 100');    
while($q->next_record()) {

    $id = $q->Record['IDZNACKA'];
//        $tx = str_replace('"', '\"', $q->Record['TXTHLED']);
    $tx = str_replace('"', '\"', $q->Record['TXTZNACKA']);
    //echo "ID: $id $tx <br>\n";
    
    $json[] = '{"id":"' . $id . '","label":"' . $tx . '","value":"' . $tx . '"}';
}
?>
