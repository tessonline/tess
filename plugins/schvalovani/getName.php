<?php
require("tmapy_config.inc");
require(FileUp2(".admin/brow_.inc"));
require_once(FileUp2(".admin/oth_funkce_2D.inc"));

///nutno mit nejake pravo na cteni
Access();
if(!HasSubRole('read')) exit;


$json = array();

if($_GET['term']) {

    $q = new DB_POSTA;
    
//    $term = iconv('UTF-8', 'ISO-8859-2', str_replace(';', '', $_GET['term']));
    $term = $_GET['term'];

//    $q->query('SELECT idznacka, txthled FROM npu_spisuklznac WHERE txthled ILIKE \'%' . $term . '%\' ORDER BY txthled LIMIT 100');
//    $q->query('SELECT idznacka, txtznacka FROM npu_spisuklznac WHERE txtznacka ILIKE \'%' . $term . '%\' ORDER BY txtznacka LIMIT 100');
    $q->query('SELECT id,fname,lname FROM security_user WHERE (lname ILIKE \'%' . $term . '%\' or fname ILIKE \'%' . $term . '%\') AND active ORDER BY lname asc,fname asc LIMIT 100');
    while($q->next_record()) {
    
        $id = $q->Record['ID'];
        $prac = PopisPracovnika($id);
        $odbor = UkazOdbor($prac['odbor']);
        $tx = str_replace('"', '\"', $q->Record['TXTHLED']);
        $odbor = str_replace('"', '\"', $odbor);
        if ($odbor)  $odbor = '(' . $odbor . ')';
        $tx = str_replace('"', '\"', $q->Record['FNAME'].' '.$q->Record['LNAME'] .' ' . $odbor .'');
        //echo "ID: $id $tx <br>\n";
        
        $json[] = '{"id":"' . $id . '","label":"' . $tx . '","value":"' . $tx . '"}';
    }
}

//echo iconv('ISO-8859-2', 'UTF-8', '[' . implode(',', $json) . ']');
echo '[' . implode(',', $json) . ']';
