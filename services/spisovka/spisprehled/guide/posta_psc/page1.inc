<?php
include_once(FileUp2('.admin/convert.inc'));
require(FileUp2("html_header_full.inc"));
$q = new DB_POSTA;

If ($GLOBALS[PSC]) $sql="SELECT psc,nazev FROM ui_posta WHERE psc like '%".$PSC."%'";
else
  $sql="SELECT psc,nazev FROM ui_posta WHERE nazev like '%".$GLOBALS[MESTO]."%'";
$q->query($sql);
$pocet=$q->Num_Rows();
If ($pocet==0)
{
?>
<script language="JavaScript" type="text/javascript">
<!--
  window.alert('Pošta nenalezena');
  window.close();
//-->
</script>
  
 <?php
 }
 
If ($pocet==1) 
{
  $q->next_record();
  $psc=$q->Record["PSC"];  
  $posta=$q->Record["NAZEV"];
 
 ?>
<script language="JavaScript" type="text/javascript">
<!--
  window.opener.document.frm_edit.ODESL_POSTA.value = '<?php echo $posta;?>';
  window.opener.document.frm_edit.ODESL_POSTA.style.color='red';
  window.opener.document.frm_edit.ODESL_PSC.value = '<?php echo StrTr($psc,$tr_from,$tr_to);?>';
  window.opener.document.frm_edit.ODESL_PSC.style.color='red';

  window.close();
//-->
</script>
  
 <?php
}
//$GLOBALS[GUIDE_DIRECTION]='1';

If ($pocet>1) 
{
  Table(array("showedit"=>false,
  "sql"=>$sql,
  "showdelete"=>false,
  "showinfo"=>false,
  "showhistory"=>false,
  "schema_file"=>"./guide/posta_psc/table_schema_psc.inc",
  "formvars"=>array("GUIDE_DIRECTION"),
  "select_id"=>"PSC",
  "showselect"=>true,
  "nopaging"=>true,
  "nocaption"=>true,
  "action"=>"./guide/posta_psc/page2.inc",
));
//echo "<input type='hidden' name='ONMA' value='1'>"; 
}


?>
