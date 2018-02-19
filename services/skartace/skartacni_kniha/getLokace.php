<?php
require("tmapy_config.inc");
require(FileUp2(".admin/brow_.inc"));

///nutno mit nejake pravo na cteni
Access();
if(!HasSubRole('read')) exit;


$json = array();

if($_GET['term']) {
    $q = new DB_POSTA;
    $b = new DB_POSTA;

    $sql = 'select * from posta_cis_spisovna';
    $q->query($sql);
    while($q->next_record()) {
      $spisovna_array[$q->Record['ID']] = $q->Record['SPISOVNA'];
    }

    $spisovna = '';
    if ($_GET['spisovna_id']) $spisovna = " and spisovna_id=" . $_GET['spisovna_id'];
    $q->query('SELECT * FROM posta_spisovna_cis_lokace WHERE (plna_cesta ILIKE \'%' . $term . '%\') ' . $spisovna . ' ORDER BY plna_cesta limit 100');
    while($q->next_record()) {
        $id = $q->Record['ID'];
        //$nadrazene_id = $q->Record['ID_PARENT'] ? $q->Record['ID_PARENT'] : $id;
        $spisovna_id = $q->Record['SPISOVNA_ID'];
        $sqlx = 'select * from posta_spisovna_cis_lokace WHERE id_parent=' . $id;
        $b->query($sqlx);
        if ($b->Num_Rows() == 0)
        {
          $tx = $spisovna_array[$spisovna_id].'-'.str_replace('"', '\"', $q->Record['PLNA_CESTA']);
          $json[] = '{"id":"' . $id . '","label":"' . $tx . '","value":"' . $tx . '"}';
        }
    }
}

echo '[' . implode(',', $json) . ']';
