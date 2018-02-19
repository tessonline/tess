<?php
require("tmapy_config.inc");
include(FileUp2(".admin/brow_.inc"));
require_once(FileUp2(".admin/config.inc"));
require_once(FileUp2(".admin/db/db_posta.inc"));
require_once(FileUp2(".admin/db/db_npu.inc"));
require_once(FileUp2("html_header_posta.inc"));
//require(FileUp2(".admin/security_.inc"));

$q=new DB_POSTA;
$npu=new DB_NPU;
set_time_limit(0);

function TypSloupce($column) {
  $res = '';
  if ($column['type'] == 'varchar') $res = 'varchar(' . $column['len']. ')';
  else $res = $column['type'];
  return $res;
}

function NazevSloupce($column) {
  $ret = strtolower($column['name']);
  return $ret;
}

function MyAlert($column) {
  $ret = '';
  if ($column['name'] == 'ID' && ereg('int', $column['type'])) $ret = ' -- POZOR, nema byt serial nebo autoincrement? ';
  return $ret;
  
}

$USER_INFO = $GLOBALS["TMAPY_SECURITY"]->GetUserInfo();
$id_user=$USER_INFO["ID"];
$jmeno_uzivatele=$USER_INFO["FNAME"]." ".$USER_INFO["LNAME"];
$LAST_USER_ID=$id_user;
$LAST_TIME=Date('H:m:i');
$LAST_DATE=Date('Y-m-d');

$tables = $npu->table_names();
//$tables = array('POSTA','POSTA_H', 'POSTA_DS', 'POSTA_EPODATELNA');

foreach($tables as $table_array) {
  $table = $table_array['table_name'];
  $metadata_from = $npu->metadata($table);
  $metadata_to = $q->metadata($table);
  $update = array();
  foreach($metadata_from as $sloupec_from) {
    $problem = true;
    foreach($metadata_to as $sloupec_to) {
      if ($sloupec_from['name'] == $sloupec_to['name']) {

        if ($sloupec_from['type'] == $sloupec_to['type'] &&
            $sloupec_from['len'] == $sloupec_to['len']) $problem = false; 

        if ($problem) {
          $update[] = 'ALTER TABLE ' . $table .' ALTER COLUMN ' . NazevSloupce($sloupec_from) . ' TYPE ' . TypSloupce($sloupec_from) . ';  -- puvodne ' . TypSloupce($sloupec_to);
          $problem = false;
        }
      } 
    }
    if ($problem) $update[] = 'ALTER TABLE ' . $table .' ADD ' . NazevSloupce($sloupec_from) . ' ' . TypSloupce($sloupec_from) . ';';

 
    
  }
  if (count($metadata_to)<1) {
    $update = array();
    $create_item = array();
    foreach($metadata_from as $sloupec) {
      $create_item[] = '&nbsp;&nbsp;' . NazevSloupce($sloupec) . ' ' . TypSloupce($sloupec) . ', ' .  MyAlert($sloupec); 
    }
    $create = 'CREATE TABLE ' . $table . '( ';
    $create .= '<br/> '. implode('<br/>', $create_item). '<br/>';
    $create .= ');';
    $update[] = $create;
  }

  if (count($update)>0) {
    echo '<h2>-- table ' . $table . '</h2>';
    echo implode('<br/>', $update);
    
  }
  
}


echo "<script>document.getElementById('upl_wait_message').innerHTML = 'Hotovo'</script>";Flush();



require(FileUp2("html_footer.inc"));
