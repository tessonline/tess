<?php
  include_once(FileUp2(".admin/security_name.inc"));
	$zkratka=UkazOdbor($ODBOR,true);
  If ($CISLO_JEDNACI3) $CISLO_JEDNACI1=$CISLO_JEDNACI3;
  If ($CISLO_JEDNACI3) $CISLO_JEDNACI2=$CISLO_JEDNACI4;
  If ($NAZEV_SPISU2) $NAZEV_SPISU=$NAZEV_SPISU2;
  $text_spisu=$CISLO_JEDNACI1."/".$CISLO_JEDNACI2;
  If ($NAZEV_SPISU) $text_spisu.=" - ".$NAZEV_SPISU;
  $text_spisu.=" ";

?> 
<script language="JavaScript" type="text/javascript">
<!--
  window.opener.document.getElementById('OBJEKT_KOD_SPAN').innerHTML = '<?php echo $text_spisu ?>';
  window.opener.document.frm_edit.CISLO_SPISU1.value = '<?php echo $CISLO_JEDNACI1;?>';
  window.opener.document.frm_edit.CISLO_SPISU2.value = '<?php echo $CISLO_JEDNACI2;?>';
//  window.opener.document.frm_edit.ODBOR_SPISU.value = '<?php echo $zkratka;?>';
  window.opener.document.frm_edit.NAZEV_SPISU.value = '<?php echo $NAZEV_SPISU;?>';
  window.opener.document.frm_edit.PODCISLO_SPISU.value = -1;

  window.close();
//-->
</script>
