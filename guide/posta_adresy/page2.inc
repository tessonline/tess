<?php
session_start();
require("tmapy_config.inc");
require(FileUp2(".admin/brow_.inc"));
require(FileUp2("html_header_full.inc"));

//echo "vybrano ".$GLOBALS["SELECT_ID"];
//If ($GLOBALS["ULICE"]<>"") 
//{
$sql="SELECT a.STAV, a.ADRESA_KOD as KOD, a.CISOR_HOD,j.objekt_kod as OBJEKT_KOD,o.okres_kod AS OKRES_KOD, a.PSC as PSC, u.NAZEV as ULICE, j.CISDOM_HOD, o.NAZEV as MESTO FROM ui_adresa a, ui_objekt j,ui_cobce c,ui_obec o,ui_ulice u";
$where.=" WHERE u.ulice_kod = a.ulice_kod AND a.adresa_kod=".$GLOBALS["SELECT_ID"];
//}
//else
//{
//$sql="SELECT a.STAV, a.ADRESA_KOD as KOD, a.CISOR_HOD, a.PSC as PSC, j.CISDOM_HOD, o.NAZEV as MESTO FROM ui_adresa a, ui_objekt j,ui_cobce c,ui_obec o";
//$where.=" WHERE a.adresa_kod=".$GLOBALS["SELECT_ID"];
//} 
$where.=" AND o.obec_kod = c.obec_kod";
$where.=" AND j.cobce_kod = c.cobce_kod";
$where.=" AND a.objekt_kod = j.objekt_kod";

$sql.=$where;
//echo $sql;
$q=new DB_POSTA;
$q->query($sql);
If ($q->Num_Rows()==0)
{
$where="";
$sql="SELECT a.STAV, a.ADRESA_KOD as KOD,j.objekt_kod as OBJEKT_KOD,o.okres_kod AS OKRES_KOD, a.CISOR_HOD, a.PSC as PSC, j.CISDOM_HOD, o.NAZEV as MESTO FROM ui_adresa a, ui_objekt j,ui_cobce c,ui_obec o";
$where.=" WHERE a.adresa_kod=".$GLOBALS["SELECT_ID"];
$where.=" AND o.obec_kod = c.obec_kod";
$where.=" AND j.cobce_kod = c.cobce_kod";
$where.=" AND a.objekt_kod = j.objekt_kod";
$sql.=$where;
//Die('Jsme tam '.$sql);

$q->query($sql);
}
$q->Next_Record();
$kod=$q->Record["KOD"];
$objekt=$q->Record["OBJEKT_KOD"];
$okres=$q->Record["OKRES_KOD"];
$ulice=$q->Record["ULICE"];
$cisdom=$q->Record["CISDOM_HOD"];
$cor=$q->Record["CISOR_HOD"];
$mesto=$q->Record["MESTO"];
$psc=$q->Record["PSC"];

//echo " $kod $objekt $okres $ulice $cisdom $cor $mesto $psc";
//Die();
?>
<script language="JavaScript" type="text/javascript">
<!--
  window.opener.document.frm_edit.ODESL_ADRKOD.value = '<?php echo $kod;?>';
  window.opener.document.frm_edit.OBJEKT_KOD.value = '<?php echo $objekt;?>';
  window.opener.document.frm_edit.OKRES_KOD.value = '<?php echo $okres;?>';

  window.opener.document.frm_edit.ODESL_ULICE.value = '<?php echo $ulice;?>';
  window.opener.document.frm_edit.ODESL_ULICE.style.color='red';

  window.opener.document.frm_edit.ODESL_CP.value = '<?php echo $cisdom;?>';
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
