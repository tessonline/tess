<?php
session_start();
require("tmapy_config.inc");
require(FileUp2(".admin/brow_.inc"));
require(FileUp2("html_header_full.inc"));

//echo "vybrano ".$GLOBALS["SELECT_ID"];

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

echo " $kod $ulice $cisdom $cor $mesto $psc";

?>
<script language="JavaScript" type="text/javascript">
<!--
  //window.opener.document.frm_edit.ODESL_ADRKOD.value = '<?php echo $kod;?>';

  
  window.opener.document.frm_edit.ODESL_PRIJMENI.value = '<?php echo $prijmeni;?>';
  window.opener.document.frm_edit.ODESL_PRIJMENI.style.color='red';
  window.opener.document.frm_edit.ODESL_JMENO.value = '<?php echo $jmeno;?>';
  window.opener.document.frm_edit.ODESL_JMENO.style.color='red';
  window.opener.document.frm_edit.ODESL_TITUL.value = '<?php echo $titul;?>';
  window.opener.document.frm_edit.ODESL_TITUL.style.color='red';
  window.opener.document.frm_edit.ODESL_ICO.value = '<?php echo $ico;?>';
  window.opener.document.frm_edit.ODESL_ICO.style.color='red';
  window.opener.document.frm_edit.ODESL_ODD.value = '<?php echo $odd;?>';
  window.opener.document.frm_edit.ODESL_ODD.style.color='red';
  window.opener.document.frm_edit.ODESL_OSOBA.value = '<?php echo $osoba;?>';
  window.opener.document.frm_edit.ODESL_OSOBA.style.color='red';
  
  
  window.opener.document.frm_edit.ODESL_ULICE.value = '<?php echo $ulice;?>';
  window.opener.document.frm_edit.ODESL_ULICE.style.color='red';

  window.opener.document.frm_edit.ODESL_CP.value = '<?php echo $cp;?>';
  window.opener.document.frm_edit.ODESL_CP.style.color='red';

  window.opener.document.frm_edit.ODESL_COR.value = '<?php echo $cor;?>';
  window.opener.document.frm_edit.ODESL_COR.style.color='red';

  window.opener.document.frm_edit.ODESL_POSTA.value = '<?php echo $mesto;?>';
  window.opener.document.frm_edit.ODESL_POSTA.style.color='red';

  window.opener.document.frm_edit.ODESL_PSC.value = '<?php echo $psc;?>';
  window.opener.document.frm_edit.ODESL_PSC.style.color='red';

  window.close();
//-->
</script>
