<?php
session_start();
require("tmapy_config.inc");
require(FileUp2(".admin/brow_.inc"));
require(FileUp2("html_header_full.inc"));
 $q = new DB_POSTA;

 $sql='SELECT nazev FROM ui_posta WHERE psc='.$PSC;
 
 $q->query($sql);
 $q->next_record();
 
 $posta=$q->Record["NAZEV"];
 
 If ($posta=='') {
?>
<script language="JavaScript" type="text/javascript">
<!--
  window.alert('Pošta nenalezena');
  window.close();
//-->
</script>
  
 <?php
 }
 else
 {
 ?>
<script language="JavaScript" type="text/javascript">
<!--
  window.opener.document.frm_edit.ODESL_POSTA.value = '<?php echo $posta;?>';
  window.opener.document.frm_edit.ODESL_POSTA.style.color='red';

  window.close();
//-->
</script>
  
 <?php
 }
  

?>


