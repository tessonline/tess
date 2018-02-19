<?php
session_start();
//require("tmapy_config.inc");
require(FileUp2("html_header_full.inc"));
//require(FileUp2(".admin/form_func_ev.inc"));

//echo "vybrano ".$GLOBALS["SELECT_ID"];

if ($GLOBALS["SELECT_ID"]<0) $tabulka='posta_adresati'; else $tabulka='posta';
$sql="SELECT * from ".$tabulka." where id=".abs($GLOBALS["SELECT_ID"]);


//echo $sql;
$q=new DB_POSTA;
$q->query($sql);
$q->Next_Record();
$kod=$q->Record["ODESL_UIRADR"];
$typ=$q->Record["ODES_TYP"];
$osloveni=$q->Record["ODESL_OSLOVENI"];
$prijmeni=$q->Record["ODESL_PRIJMENI"];
$jmeno=$q->Record["ODESL_JMENO"];
$titul=$q->Record["ODESL_TITUL"];
$ico=$q->Record["ODESL_ICO"];
$odd=$q->Record["ODESL_ODD"];
$osoba=$q->Record["ODESL_OSOBA"];
$email=$q->Record["ODESL_EMAIL"];
$ulice=$q->Record["ODESL_ULICE"];
$cp=$q->Record["ODESL_CP"];
$cor=$q->Record["ODESL_COR"];
$psc=$q->Record["ODESL_PSC"];
$mesto=$q->Record["ODESL_POSTA"];
//$datnar=CZDate($q->Record["ODESL_DATNAR"]);
$ds=$q->Record["ODESL_DATSCHRANKA"];

//echo " $kod $ulice $cisdom $cor $mesto $psc";

echo "
<script language=\"JavaScript\" type=\"text/javascript\">
<!--
  window.opener.document.frm_edit.ODESL_ADRKOD.value = '".$kod."';

//   window.opener.document.frm_edit.ODES_TYP.value = '".$typ."';
//   window.opener.document.frm_edit.ODES_TYP.style.color='red';
";
if ($typ=='U' || $typ=='P')  
echo "
  window.opener.document.frm_edit.ODESL_PRIJMENI_FIRMA.value = '".$prijmeni."';
  window.opener.document.frm_edit.ODESL_PRIJMENI_FIRMA.style.color='red';
";
else
echo "
  window.opener.document.frm_edit.ODESL_OSLOVENI.value = '".$osloveni."';
  window.opener.document.frm_edit.ODESL_OSLOVENI.style.color='red';
  window.opener.document.frm_edit.ODESL_PRIJMENI.value = '".$prijmeni."';
  window.opener.document.frm_edit.ODESL_PRIJMENI.style.color='red';
  window.opener.document.frm_edit.ODESL_JMENO.value = '".$jmeno."';
  window.opener.document.frm_edit.ODESL_JMENO.style.color='red';
//  window.opener.document.frm_edit.ODESL_TITUL.value = '".$titul."';
//  window.opener.document.frm_edit.ODESL_TITUL.style.color='red';
      window.opener.document.frm_edit.ODESL_DATNAR.value = '".$datnar."';
      window.opener.document.frm_edit.ODESL_DATNAR.style.color='red';
";

echo "
  window.opener.document.frm_edit.ODESL_ICO.value = '".$ico."';
  window.opener.document.frm_edit.ODESL_ICO.style.color='red';
  window.opener.document.frm_edit.ODESL_ODD.value = '".$odd."';
  window.opener.document.frm_edit.ODESL_ODD.style.color='red';
  window.opener.document.frm_edit.ODESL_OSOBA.value = '".$osoba."';
  window.opener.document.frm_edit.ODESL_OSOBA.style.color='red';
  
  
  window.opener.document.frm_edit.ODESL_ULICE.value = '".$ulice."';
  window.opener.document.frm_edit.ODESL_ULICE.style.color='red';

  window.opener.document.frm_edit.ODESL_CP.value = '".$cp."';
  window.opener.document.frm_edit.ODESL_CP.style.color='red';

  window.opener.document.frm_edit.ODESL_COR.value = '".$cor."';
  window.opener.document.frm_edit.ODESL_COR.style.color='red';

  window.opener.document.frm_edit.ODESL_EMAIL.value = '".$email."';
  window.opener.document.frm_edit.ODESL_EMAIL.style.color='red';

  window.opener.document.frm_edit.ODESL_POSTA.value = '".$mesto."';
  window.opener.document.frm_edit.ODESL_POSTA.style.color='red';

  window.opener.document.frm_edit.ODESL_PSC.value = '".$psc."';
  window.opener.document.frm_edit.ODESL_PSC.style.color='red';

  window.opener.document.frm_edit.ODESL_DATSCHRANKA.value = '".$ds."';
  window.opener.document.frm_edit.ODESL_DATSCHRANKA.style.color='red';

  window.opener.document.frm_edit.FROZEN.value = 'A';

  parent.$.fancybox.close();

//-->
</script>
";
?>
