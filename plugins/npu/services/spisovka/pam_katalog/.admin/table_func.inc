<?php

function Url($url) {
  //global $znacka_id
  static $img_search;
  if (!$img_search) $img_search = FileUpImage('images/search');
  if (strlen($url)>5)
    $ret = '<a href="' . $url . '" target="PK"><img src="'.$img_search.'" title="Otevřít v památkovém katalogu"></a>';
  return $ret;
  
}

function Img($img) {
  static $img_eye;
  if (!$img_eye) $img_eye = FileUpImage('images/eye');
  if (strlen($img)>5)
    $ret = '<a href="' . $img . '" target="PK2"><img src="'.$img_eye.'" title="Ukázat fotografii"></a>';
  return $ret;

}