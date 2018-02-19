<?php

function JmenoZnacky($id)
{
  //global $znacka_id
  if ($id>0)
    $ret=$GLOBALS['znacka_obj']->GetNameForZnackaId($id);
  return $ret;
  
}