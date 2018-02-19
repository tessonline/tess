<?php

$adresa_ds="https://www.czebox.cz/DS/df";
//$adresa_ds="https://www.czebox.cz/DS/dz";
$username="aaritj";
//$username="aariti";
$password="Ww5Lu3Ya4H";
//$password="Xv9Mv7Ch8Q";

Function ShowText($text)
{
  echo '<div id="upl_wait_message" class="text" style="display:block"><br>'.$text;
  //<br><img src="'.FileUpUrl('images/progress.gif').'" title="nahrávám ..." alt="nahrávám ..."></div>';
  Flush();
}
