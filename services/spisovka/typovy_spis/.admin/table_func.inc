<?php
Function Ukaz2($UZIVATEL)
{
switch ($UZIVATEL) {
  case "P": 
       $soubor=FileUp2('images/fabrika.gif');$text='Pr�vnick� osoba';
       break;
  case "F": 
       $soubor=FileUp2('images/house.gif');$text='Fyzick� osoba-podnikatel';
       break;
  case "O": 
       $soubor=FileUp2('images/people.gif');$text='Fyzick� osoba-obean';
       break;
  case "A": 
       $soubor=FileUp2('images/people_no.gif');$text='Anonym';
       break;
  }
$res="<img src=\"".FileUp2($soubor)."\" alt=\"$text\">";
return $res;  
}

?>
