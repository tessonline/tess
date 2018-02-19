<?php

Function Ukaz2()
{

$novaadresa=$GLOBALS["ODESL_PRIJMENI"].$GLOBALS["ODESL_JMENO"].$GLOBALS["ODESL_ULICE"].$GLOBALS["ODESL_CP"].$GLOBALS["ODESL_PSC"].$GLOBALS["ODESL_POSTA"];
If ($GLOBALS["CELA_ADRESA"]<>$novaadresa)
{
$GLOBALS["CELA_ADRESA"]=$novaadresa;
return $novaadresa;
}
else
{
$res="-------------------------";
return $res;
}

//If ($GLOBALS["STAV=='t') 
//{$res="<img src=\"".FileUp2('images/odchozi.gif')."\" alt=\"Odchozí pošta\">";}
//else {$res="<img src=\"".FileUp2('images/prichozi.gif')."\" alt=\"Příchozí pošta\">";}

//$res=$GLOBALS["barva_sipky"];

}

/*
Function Ukaz2($UZIVATEL)
{
switch ($UZIVATEL) {
  case "P": 
       $soubor='images/fabrika.gif';$text='Právnická osoba';
       break;
  case "F": 
       $soubor='images/house.gif';$text='Fyzická osoba-podnikatel';
       break;
  case "O": 
       $soubor='images/people.gif';$text='Fyzická osoba-občan';
       break;
  case "A": 
       $soubor='images/people_no.gif';$text='Anonym';
       break;
  case "V": 
       $soubor='images/rodina.gif';$text='Veřejnost';
       break;
  }
$res="<img src=\"".FileUp2($soubor)."\" alt=\"$text\">";
return $res;  
  
}
*/
?>
