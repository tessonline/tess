<?php
function showBox($id) {
  $box = LoadClass('EedArchivacniBox', $id);
  return $box->ev_cislo;
}

function nameBox($id) {
  $box = LoadClass('EedArchivacniBox', $id);
  return $box->nazev;
}

$TABLE_CONFIG["schema"][] =  array( "field"=>"showBox(BOX_ID)", "label"=>"Označení");
$TABLE_CONFIG["schema"][] =  array( "field"=>"nameBox(BOX_ID)", "label"=>"Název");



$TABLE_CONFIG['syscolumns'] = array(
 'edit' => array ('theme'=>array('dropdown'=>true, 'column'=>true))
);


