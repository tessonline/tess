<?php
$text = file_get_contents($GLOBALS['path_content']);
$text = nl2br($text);

echo '<b>Soubor: '.basename($GLOBALS['path_content']).'</b><br />';

//echo $text;
