<?php
function DatumHistorie($datumFull) {
  list($datumF,$casF) = explode(' ', $datumFull);
  $datumArr = explode('-', $datumF);
  $datum = $datumArr['2'].'.'.$datumArr['1'].'.'.$datumArr['0'];
  list($cas,$mikro) = explode('.', $casF);
  $res = $datum.' '.$cas;
  return $res;
}

$TABLE_CONFIG["schema"][] =  array( "field"=>"JMENO", "label"=>"Kdo:");
$TABLE_CONFIG["schema"][] =  array( "field"=>"DatumHistorie(LAST_TIME)", "label"=>"Kdy:");
$TABLE_CONFIG["schema"][] =  array( "field"=>"TEXT", "label"=>"Co:","is_html"=>true);


