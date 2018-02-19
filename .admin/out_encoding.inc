<?php 
function enc($source) {
  return iconv('utf-8','cp1250',$source);
}


function enc_array($source_arr) {
  foreach($source_arr as &$source){
    $source = iconv('utf-8','cp1250',$source);
  }
  return $source_arr;
}