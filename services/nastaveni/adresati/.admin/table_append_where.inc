<?php
function AddStars(&$str) {
  $str = trim($str);
  if (!$str) return;
  if (strstr($str,"*")) return;
  //if ($str[0]!='*') $str = '%'.$str;
  //if ($str[strlen($str)-1]!='*') $str.= '%';

  $str = str_replace('?','%',$str);
}

//if ($SHOW_ONE) echo "SHOW_ONE ano<br />";
//else echo "SHOW_ONE ne<br />";

$app = "";
if ($SHOW_ONE && !$ZPOCTU) {
  $r = new DB_POSTA;
  //echo $_ODES_TYP."<br />";
  //echo $_ODESL_ADRKOD."<br />";
  if ($_ODES_TYP) $_odes_typ = "and odes_typ = '$_ODES_TYP'";
  else $odes_typ = "and odes_typ = '0'";
  if ($_ODESL_ADRKOD) $_odesl_adrkod = "and odesl_adrkod = $_ODESL_ADRKOD";//číslo
  else $_odesl_adrkod = "and odesl_adrkod = 0";

  if ($_ODESL_PRIJMENI) $_odesl_prijmeni = "and odesl_prijmeni = '$_ODESL_PRIJMENI'";
  else $_odesl_prijmeni = "and (odesl_prijmeni is null or odesl_prijmeni = '')";
  if ($_ODESL_JMENO) $_odesl_jmeno = "and odesl_jmeno = '$_ODESL_JMENO'";
  else $_odesl_jmeno = "and (odesl_jmeno is null or odesl_jmeno = '')";
  if ($_ODESL_ODD) $_odesl_odd = "and odesl_odd = '$_ODESL_ODD'";
  else $_odesl_odd = "and (odesl_odd is null or odesl_odd = '')";
  if ($_ODESL_OSOBA) $_odesl_osoba = "and odesl_osoba = '$_ODESL_OSOBA'";
  else $_odesl_osoba = "and (odesl_osoba is null or odesl_osoba = '')";
  if ($_ODESL_TITUL) $_odesl_titul = "and odesl_titul = '$_ODESL_TITUL'";
  else $_odesl_titul = "and (odesl_titul is null or odesl_titul = '')";
  if ($_ODESL_ULICE) $_odesl_ulice = "and odesl_ulice = '$_ODESL_ULICE'";
  else $_odesl_ulice = "and (odesl_ulice is null or odesl_ulice = '')";
  if ($_ODESL_CP) $_odesl_cp = "and odesl_cp = '$_ODESL_CP'";
  else $_odesl_cp = "and (odesl_cp is null or odesl_cp = '')";
  if ($_ODESL_COR) $_odesl_cor = "and odesl_cor = '$_ODESL_COR'";
  else $_odesl_cor = "and (odesl_cor is null or odesl_cor = '')";
  if ($_ODESL_ICO) $_odesl_ico = "and odesl_ico = '$_ODESL_ICO'";
  else $_odesl_ico = "and (odesl_ico is null or odesl_ico = '')";
  if ($_ODESL_PSC) $_odesl_psc = "and odesl_psc = '$_ODESL_PSC'";
  else $_odesl_psc = "and (odesl_psc is null or odesl_psc = '')";
  if ($_ODESL_POSTA) $_odesl_posta = "and odesl_posta = '$_ODESL_POSTA'";
  else $_odesl_posta = "and (odesl_posta is null or odesl_posta = '')";
  $dotaz2 = "
    select id
    from posta
    where 1=1
    $_odes_typ
    $_odesl_adrkod
    $_odesl_prijmeni
    $_odesl_jmeno
    $_odesl_odd
    $_odesl_osoba
    $_odesl_titul
    $_odesl_ulice
    $_odesl_cp
    $_odesl_cor
    $_odesl_ico
    $_odesl_psc
    $_odesl_posta
  ";
  $r->query($dotaz2);
  while ($r->next_record()) {
    $ids[] = $r->Record["ID"];
  }
  $poc = count($ids);
  if ($ids) {
    $id = implode(",",$ids);
    $app .= " and p.id in(".$id.")";
  }
  //echo $dotaz2." <br>";
}

if ($JEN_AKTIVNI) {
  if ($JEN_AKTIVNI == "N") $app .= " and (p.frozen is null or p.frozen = '".$JEN_AKTIVNI."')";
  else $app .= " and p.frozen = '".$JEN_AKTIVNI."'";
}

 AddStars($ODESL_PRIJMENI);
 AddStars($ODESL_JMENO);
 AddStars($ODESL_ODD);
 AddStars($ODESL_OSOBA);
 AddStars($ODESL_TITUL);
 AddStars($ODESL_ULICE);
 AddStars($ODESL_ICO);
 AddStars($ODESL_POSTA);

?>
