<?php
session_start();
require("tmapy_config.inc");
require(FileUp2(".admin/brow_.inc"));
require(FileUp2("html_header_full.inc"));
$q=new DB_POSTA;
$sql="SELECT psc,nazev FROM ui_posta WHERE psc like '%".$GLOBALS[SELECT_ID]."%'";
$q->query($sql);
$pocet=$q->Num_Rows();
$q->next_record();
$psc=$q->Record["PSC"];  
$posta=$q->Record["NAZEV"];
 
 ?>
<script language="JavaScript" type="text/javascript">
<!--
  window.opener.document.frm_edit.ODESL_POSTA.value = '<?php echo StrTr($posta,$tr_from,$tr_to);?>';
  window.opener.document.frm_edit.ODESL_POSTA.style.color='red';
  window.opener.document.frm_edit.ODESL_PSC.value = '<?php echo StrTr($psc,$tr_from,$tr_to);?>';
  window.opener.document.frm_edit.ODESL_PSC.style.color='red';

  window.close();
//-->
</script>
