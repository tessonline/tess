<?php
?>
<script language="JavaScript" type="text/javascript">
<!--
<?php
if ($nula=='ne')
{
?>
  window.opener.document.getElementById('CJEDNACI_TEXT_SPAN').innerHTML = 'Číslo jednací bude vytvořeno při uloení<input class=\"button\" type=\"button\" value=\"Nevytvářet číslo jednací\" onclick=\"window.open(\'services/spisovka/c_jednaci/nula.php?nula=ano\', \'guide2\', \'height=10px,width=10px,scrollbars,resizable\');\">';
  window.opener.document.frm_edit.CISLO_JEDNACI1.value = '';
<?php
}
else
{
?>
  window.opener.document.getElementById('CJEDNACI_TEXT_SPAN').innerHTML = '<input class=\"button\" type=\"button\" value=\"Vytvořit číslo jednací\" onclick=\"window.open(\'services/spisovka/c_jednaci/nula.php?nula=ne\', \'guide2\', \'height=10px,width=10px,scrollbars,resizable\');\">';
  window.opener.document.frm_edit.CISLO_JEDNACI1.value = '0';
<?php
}
?>

          
  window.close();
//-->
</script>
