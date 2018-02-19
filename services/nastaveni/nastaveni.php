<?php
require("tmapy_config.inc");
require_once(FileUp2(".admin/config.inc"));
require(FileUp2(".admin/brow_.inc"));
require_once(Fileup2("html_header_title.inc"));

//vypiseme nastaveni
echo "<table class=brow align=center>";
while ( list($key,$val)=each($GLOBALS["CONFIG"]) )
{
  If ($val=='') $val='</b><i>vypnuto</i><b>';
  If ($val==1) $val='zapnuto';
  $a=$a?false:true;
  If ($a) $dark=''; else $dark='dark';
  echo '<tr class=brow><td class=brow'.$dark.'>'.$key.'&nbsp;</td><td class=brow'.$dark.'><b>';
  If (is_array($val)) 
  {
     while(list($a,$b)=each($val))
    echo "".$a."=>".$b."</br>";
  }
  else 
    echo $val;
  echo '</b></tr>';
}
echo "</table><p align=center><a class='body' href='menu.php'>Zpět</a></p>";
require(FileUp2("html_footer.inc"));
?>
