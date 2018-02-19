<iframe id="ifrm_get_value" name="ifrm_get_value" style="position:absolute;z-index:0;left:10;top:10;visibility:hidden"></iframe>
<iframe id="ifrm_get_value2" name="ifrm_get_value2" style="position:absolute;z-index:0;left:0;top:0;visibility:hidden"></iframe>
<script language="JavaScript" type="text/javascript">
<!--
var vall;


function UkazPracovnika(ODBOR,vysledek,hodnota) {
	var selectedValues = $('[name="'+ODBOR.name+'"]').val();
	newwindow = window.open('<?php echo GetAgendaPath('POSTA',false,true);?>/services/spisovka/oddeleni/get_value_prac.php?ODBOR='+selectedValues+'&vysledek='+vysledek+'&hodnota='+hodnota+'','ifrm_get_value2','height=600px,width=600px,left=1,top=1,scrollbars,resizable');
  newwindow.focus();
  document.frm_.ODBOR.value = selectedValues;
}

function REFERENT_ON(ref) {
  document.frm_.REFERENT.value = ref.value;
  return false;
}

function TYPSPIS_ON(ref) {
  document.frm_.TYPOVY_SPIS.value = ref.value;
  return false;
}


//-->
</script>
