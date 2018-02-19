<?php
require("tmapy_config.inc");
require(FileUp2(".admin/brow_.inc"));
require(FileUp2("posta/.admin/properties.inc"));
include(FileUp2(".admin/security_obj.inc"));
$USER_INFO = $GLOBALS["POSTA_SECURITY"]->GetUserInfo();
$id_user=$USER_INFO["ID"];
$jmeno=$USER_INFO["FNAME"]." ".$USER_INFO["LNAME"];
$LAST_USER_ID=$id_user;
$OWNER_ID=$id_user;
$LAST_TIME=Date('H:m:i');
$LAST_DATE=Date('Y-m-d');
$dnes=Date('d.m.Y');

//echo "$LAST_USER_ID, $OWNER_ID, $LAST_TIME, $LAST_DATE<br />";

$ttt=new DB_POSTA;
/*
$sqlaa="update posta SET frozen='".$frozen."' where id IN (".$idaa.")";
$ttt->query($sqlaa);
//die($sqlaa);
echo $sqlaa;
*/

//echo "$idaa, $frozen<hr />";

$r = new DB_POSTA;
$dotaz1 = "
  select odes_typ,odesl_adrkod,odesl_prijmeni,odesl_jmeno,odesl_odd,odesl_osoba,
  odesl_titul,odesl_ulice,odesl_cp,odesl_cor,odesl_ico,odesl_psc,odesl_posta,referent
  from posta
  where id = $idaa
";
$r->query($dotaz1);
//echo "$dotaz1<hr />";
while ($r->next_record()) {
  //$frozen = $r->Record["FROZEN"];
  $odes_typ = $r->Record["ODES_TYP"];
  $odesl_adrkod = $r->Record["ODESL_ADRKOD"];
  $odesl_prijmeni = $r->Record["ODESL_PRIJMENI"];
  $odesl_jmeno = $r->Record["ODESL_JMENO"];
  $odesl_odd = $r->Record["ODESL_ODD"];
  $odesl_osoba = $r->Record["ODESL_OSOBA"];
  $odesl_titul = $r->Record["ODESL_TITUL"];
  $odesl_ulice = $r->Record["ODESL_ULICE"];
  $odesl_cp = $r->Record["ODESL_CP"];
  $odesl_cor = $r->Record["ODESL_COR"];
  $odesl_ico = $r->Record["ODESL_ICO"];
  $odesl_psc = $r->Record["ODESL_PSC"];
  $odesl_posta = $r->Record["ODESL_POSTA"];
  $referent = $r->Record["REFERENT"];
}

if (!$odes_typ) $odes_typ = " 0";//mezeru nechat :-[
if ($odes_typ) $_odes_typ = "and odes_typ = trim('$odes_typ')";//not null
if ($odesl_adrkod) $odesl_adrkod = "and odesl_adrkod = $odesl_adrkod";//číslo
else $odesl_adrkod = "and odesl_adrkod is null";

if ($odesl_prijmeni) $_odesl_prijmeni = "and odesl_prijmeni = '$odesl_prijmeni'";
else $_odesl_prijmeni = "and (odesl_prijmeni is null or odesl_prijmeni = '')";
if ($odesl_jmeno) $_odesl_jmeno = "and odesl_jmeno = '$odesl_jmeno'";
else $_odesl_jmeno = "and (odesl_jmeno is null or odesl_jmeno = '')";
if ($odesl_odd) $_odesl_odd = "and odesl_odd = '$odesl_odd'";
else $_odesl_odd = "and (odesl_odd is null or odesl_odd = '')";
if ($odesl_osoba) $_odesl_osoba = "and odesl_osoba = '$odesl_osoba'";
else $_odesl_osoba = "and (odesl_osoba is null or odesl_osoba = '')";
if ($odesl_titul) $_odesl_titul = "and odesl_titul = '$odesl_titul'";
else $_odesl_titul = "and (odesl_titul is null or odesl_titul = '')";
if ($odesl_ulice) $_odesl_ulice = "and odesl_ulice = '$odesl_ulice'";
else $_odesl_ulice = "and (odesl_ulice is null or odesl_ulice = '')";
if ($odesl_cp) $_odesl_cp = "and odesl_cp = '$odesl_cp'";
else $_odesl_cp = "and (odesl_cp is null or odesl_cp = '')";
if ($odesl_cor) $_odesl_cor = "and odesl_cor = '$odesl_cor'";
else $_odesl_cor = "and (odesl_cor is null or odesl_cor = '')";
if ($odesl_ico) $_odesl_ico = "and odesl_ico = '$odesl_ico'";
else $_odesl_ico = "and (odesl_ico is null or odesl_ico = '')";
if ($odesl_psc) $_odesl_psc = "and odesl_psc = '$odesl_psc'";
else $_odesl_psc = "and (odesl_psc is null or odesl_psc = '')";
if ($odesl_posta) $_odesl_posta = "and odesl_posta = '$odesl_posta'";
else $_odesl_posta = "and (odesl_posta is null or odesl_posta = '')";

if ($odesl_posta) $_odesl_referent = "and referent = $referent";
else $_odesl_referent = "and referent is null";

//frozen = 'A'
$dotaz2 = "
  select frozen,id
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
  $_odesl_referent
";
//echo "$dotaz2<hr />";
//$frozen = "N";
$r->query($dotaz2);
//unset($ids);
while ($r->next_record()) {
  //$frozen = $r->Record["FROZEN"];
  $ids[] = $r->Record["ID"];
  //$id = $r->Record["ID"];
}
$poc = count($ids);
//echo "pocet: $poc<br />";
if ($ids) $id = implode(",",$ids);

if ($LAST_USER_ID) $up_last_user_id = ", last_user_id = ".$LAST_USER_ID;
if ($LAST_TIME) $up_last_time = ", last_time = '".$LAST_TIME."'";
if ($LAST_DATE) $up_last_date = ", last_date = '".$LAST_DATE."'";

$upd = "update posta set frozen='".$frozen."' $up_last_user_id $up_last_time $up_last_date where id in (".$id.")";
//die($upd);
$r -> query($upd);


echo "      <script language=\"JavaScript\" type=\"text/javascript\">
  window.opener.location.reload();
  window.close();
         
      //-->
      </script>
";
?>
