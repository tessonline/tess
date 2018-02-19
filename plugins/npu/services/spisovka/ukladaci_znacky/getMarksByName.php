<?php
require("tmapy_config.inc");
require(FileUp2(".admin/brow_.inc"));

///nutno mit nejake pravo na cteni
Access();
if(!HasSubRole('read')) exit;


$json = array();

if($_GET['term']) {

    $q = new DB_MONUMNIS;
    
    $term = iconv('UTF-8', 'ISO-8859-2', str_replace(';', '', $_GET['term']));
    
//    $q->query('SELECT idznacka, txthled FROM npu_spisuklznac WHERE txthled ILIKE \'%' . $term . '%\' ORDER BY txthled LIMIT 100');
//    $q->query('SELECT idznacka, txtznacka FROM npu_spisuklznac WHERE txtznacka ILIKE \'%' . $term . '%\' ORDER BY txtznacka LIMIT 100');
    $q->query('SELECT idznacka, txtznacka, replace(txtznacka,\' \',\'\') as znackadupl FROM SpisUklZnac WHERE txthled LIKE \'%' . $term . '%\' AND STATUS<4 GROUP BY znackadupl ORDER BY txtznacka LIMIT 0,1000');
    while($q->next_record()) {
    
        $id = $q->Record['IDZNACKA'];
//        $tx = str_replace('"', '\"', $q->Record['TXTHLED']);
        $tx = str_replace('"', '\"', $q->Record['TXTZNACKA']);
        //echo "ID: $id $tx <br>\n";
        
        $json[] = '{"id":"' . $id . '","label":"' . $tx . '","value":"' . $tx . '"}';
    }
}

echo iconv('ISO-8859-2', 'UTF-8', '[' . implode(',', $json) . ']');
