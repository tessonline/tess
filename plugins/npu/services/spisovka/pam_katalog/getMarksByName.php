<?php
require("tmapy_config.inc");
require(FileUp2(".admin/brow_.inc"));

///nutno mit nejake pravo na cteni
Access();
if(!HasSubRole('read')) exit;

require(FileUp2('.admin/classes/PagisServiceFulltext.inc'));

$json = array();

if($_GET['term']) {

    $pk = new PagisServiceFulltext;
    //$term = iconv('UTF-8', 'ISO-8859-2', str_replace(';', '', $_GET['term']));
    $term = str_replace(';', '', $_GET['term']);

    $res = $pk->fulltext($term);

    
//    $q->query('SELECT idznacka, txthled FROM npu_spisuklznac WHERE txthled ILIKE \'%' . $term . '%\' ORDER BY txthled LIMIT 100');
//    $q->query('SELECT idznacka, txtznacka FROM npu_spisuklznac WHERE txtznacka ILIKE \'%' . $term . '%\' ORDER BY txtznacka LIMIT 100');
    while (list($key, $val) = each($res)) {
      $id = $val['id'];
      $tx = $val['jmeno'];
        $json[] = '{"id":"' . $id . '","label":"' . $tx . '","value":"' . $tx . '"}';
    }
}
//echo iconv('ISO-8859-2', 'UTF-8', '[' . implode(',', $json) . ']');
echo '[' . implode(',', $json) . ']';
