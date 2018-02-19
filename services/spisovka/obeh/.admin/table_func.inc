<?php

Function UkazXDXX()
{

  $novaadresa=$GLOBALS["ODESL_PRIJMENI"].$GLOBALS["ODESL_JMENO"].$GLOBALS["ODESL_ULICE"].$GLOBALS["ODESL_CP"].$GLOBALS["ODESL_PSC"].$GLOBALS["ODESL_POSTA"];
  If ($GLOBALS["CELA_ADRESA"]<>$novaadresa)
  {
  $GLOBALS["CELA_ADRESA"]=$novaadresa;
  return $novaadresa;
  }
}
?>
