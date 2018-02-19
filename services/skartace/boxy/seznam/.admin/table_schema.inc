<?php

function showBox($id) {
  $box = LoadClass('EedArchivacniBox', $id);
  return $box->ev_cislo;
}


function PocetBox($id) {
  $box = LoadClass('EedArchivacniBox', $id);
  return $box->pocet;
}


$TABLE_CONFIG["schema"][] =  array( "field"=>"showBox(ID)", "label"=>"Označení");
$TABLE_CONFIG["schema"][] =  array( "field"=>"NAZEV", "label"=>"Název");
$TABLE_CONFIG["schema"][] =  array( "field"=>"PocetBox(ID)", "label"=>"Počet čj.");


$TABLE_CONFIG['syscolumns'] = array(
 'edit' => array ('theme'=>array('dropdown'=>true, 'column'=>true))
);


