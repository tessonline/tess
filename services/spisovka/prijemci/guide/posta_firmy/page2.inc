<?php
session_start();
//require("tmapy_config.inc");
//require(FileUp2(".admin/brow_.inc"));
require(FileUp2("html_header_full.inc"));

echo "vybrano ".$GLOBALS["SELECT_ID"];


$sql="SELECT * from posta where id=".$GLOBALS["SELECT_ID"];


echo $sql;
$q=new DB_POSTA;
$q->query($sql);
$q->Next_Record();
$kod=$q->Record["ODESL_UIRADR"];
$typ=$q->Record["ODES_TYP"];
$prijmeni=$q->Record["ODESL_PRIJMENI"];
$jmeno=$q->Record["ODESL_JMENO"];
$titul=$q->Record["ODESL_TITUL"];
$ico=$q->Record["ODESL_ICO"];
$odd=$q->Record["ODESL_ODD"];
$osoba=$q->Record["ODESL_OSOBA"];
$ulice=$q->Record["ODESL_ULICE"];
$cp=$q->Record["ODESL_CP"];
$cor=$q->Record["ODESL_COR"];
$psc=$q->Record["ODESL_PSC"];
$mesto=$q->Record["ODESL_POSTA"];

//echo " $kod $ulice $cisdom $cor $mesto $psc";

echo "
<script language=\"JavaScript\" type=\"text/javascript\">
<!--
//  window.opener.document.frm_edit_prijemce.ODESL_ADRKOD.value = '".$kod."';

//   window.opener.document.frm_edit_prijemce.ODES_TYP.value = '".$typ."';
//   window.opener.document.frm_edit_prijemce.ODES_TYP.style.color='red';
";
if ($typ=='U' || $typ=='P')  
echo "
  window.opener.document.frm_edit_prijemce.ODESL_PRIJMENI_FIRMA.value = '".$prijmeni."';
  window.opener.document.frm_edit_prijemce.ODESL_PRIJMENI_FIRMA.style.color='red';
  window.opener.document.frm_edit_prijemce.ODES_TYP.value = '".$typ."';
  window.opener.document.frm_edit_prijemce.ODES_TYP.style.color='red';
";
else
echo "
  window.opener.document.frm_edit_prijemce.ODES_TYP.value = '".$typ."';
  window.opener.document.frm_edit_prijemce.ODES_TYP.style.color='red';
  window.opener.document.frm_edit_prijemce.ODESL_PRIJMENI.value = '".$prijmeni."';
  window.opener.document.frm_edit_prijemce.ODESL_PRIJMENI.style.color='red';
  window.opener.document.frm_edit_prijemce.ODESL_JMENO.value = '".$jmeno."';
  window.opener.document.frm_edit_prijemce.ODESL_JMENO.style.color='red';
  window.opener.document.frm_edit_prijemce.ODESL_TITUL.value = '".$titul."';
  window.opener.document.frm_edit_prijemce.ODESL_TITUL.style.color='red';
";

echo "
  window.opener.document.frm_edit_prijemce.ODESL_ICO.value = '".$ico."';
  window.opener.document.frm_edit_prijemce.ODESL_ICO.style.color='red';
  window.opener.document.frm_edit_prijemce.ODESL_ODD.value = '".$odd."';
  window.opener.document.frm_edit_prijemce.ODESL_ODD.style.color='red';
  window.opener.document.frm_edit_prijemce.ODESL_OSOBA.value = '".$osoba."';
  window.opener.document.frm_edit_prijemce.ODESL_OSOBA.style.color='red';
  
  
  window.opener.document.frm_edit_prijemce.ODESL_ULICE.value = '".$ulice."';
  window.opener.document.frm_edit_prijemce.ODESL_ULICE.style.color='red';

  window.opener.document.frm_edit_prijemce.ODESL_CP.value = '".$cp."';
  window.opener.document.frm_edit_prijemce.ODESL_CP.style.color='red';

  window.opener.document.frm_edit_prijemce.ODESL_COR.value = '".$cor."';
  window.opener.document.frm_edit_prijemce.ODESL_COR.style.color='red';

  window.opener.document.frm_edit_prijemce.ODESL_POSTA.value = '".$mesto."';
  window.opener.document.frm_edit_prijemce.ODESL_POSTA.style.color='red';

  window.opener.document.frm_edit_prijemce.ODESL_PSC.value = '".$psc."';
  window.opener.document.frm_edit_prijemce.ODESL_PSC.style.color='red';

  window.opener.document.frm_edit_prijemce.FROZEN.value = 'N';

  window.close();
//-->
</script>
";
?>
