<?php
Function Ukaz3($UZIVATEL)
{
switch ($UZIVATEL) {
  case "P": 
       $soubor=FileUp2('images/fabrika.gif');$text='Právnická osoba';
       break;
  case "F": 
       $soubor=FileUp2('images/house.gif');$text='Fyzická osoba-podnikatel';
       break;
  case "O": 
       $soubor=FileUp2('images/people.gif');$text='Fyzická osoba-obean';
       break;
  case "A": 
       $soubor=FileUp2('images/people_no.gif');$text='Anonym';
       break;
  }
$res="<img src=\"".FileUp2($soubor)."\" alt=\"$text\">";
return $res;  
}

?>
