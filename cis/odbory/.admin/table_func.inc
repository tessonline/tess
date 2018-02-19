<?php

function UkazPrava($text) {
  $kody=explode(':',$text);
  $res=implode(', ',$kody);
  return $res;

}

