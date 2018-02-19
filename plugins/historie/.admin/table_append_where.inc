<?php
function AddStars(&$str) {
  $str = trim($str);
  if (!$str) return;
  if (strstr($str,"*")) return;
  if ($str[0]!='*') $str = '*'.$str;
  if ($str[strlen($str)-1]!='*') $str.= '*';
}

//if ($SHOW_ONE) echo "SHOW_ONE ano<br />";
//else echo "SHOW_ONE ne<br />";


AddStars($ODESL_PRIJMENI);
AddStars($ODESL_JMENO);
AddStars($ODESL_ODD);
AddStars($ODESL_OSOBA);
AddStars($ODESL_TITUL);
AddStars($ODESL_ULICE);
AddStars($ODESL_ICO);
AddStars($ODESL_POSTA);

?>
