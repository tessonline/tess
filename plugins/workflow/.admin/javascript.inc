<iframe id="ifrm_get_value2" name="ifrm_get_value2" style="position:absolute;z-index:0;left:0;top:0;visibility:hidden"></iframe>
<script language="JavaScript" type="text/javascript">

function zmenaDat_visibility(v) {
 if (v=="hide") {
//	 $( "select[name='DOKUMENT']" ).closest( "div[class='form-row']" ).css( "display", "none" );
	 $( "select[name='PROMENNA']" ).closest( "div[class='form-row']" ).css( "display", "none" );
	 $( "input[name='HODNOTA']" ).closest( "div[class='form-row']" ).css( "display", "none" );
 }	else {
//	 $( "select[name='DOKUMENT']" ).closest( "div[class='form-row']" ).css( "display", "block" );
	 $( "select[name='PROMENNA']" ).closest( "div[class='form-row']" ).css( "display", "block" );
	 $( "input[name='HODNOTA']" ).closest( "div[class='form-row']" ).css( "display", "block" );
 }
}

function schvalovaciProces_visibility(v) {
	 if (v=="hide") {
		 $( "input[name='SCHVALUJICI_TEXT']" ).closest( "div[class='form-row']" ).css( "display", "none" );
		 $( "select[name='TYPSCHVALENI']" ).closest( "div[class='form-row']" ).css( "display", "none" );
		 $( "select[name='SCHVALUJICI_ID']" ).closest( "div[class='form-row']" ).css( "display", "none" );
	 }	else {
		 $( "input[name='SCHVALUJICI_TEXT']" ).closest( "div[class='form-row']" ).css( "display", "block" );
		 $( "select[name='TYPSCHVALENI']" ).closest( "div[class='form-row']" ).css( "display", "block" );
		 $( "select[name='SCHVALUJICI_ID']" ).closest( "div[class='form-row']" ).css( "display", "block" );
	 }	
}

function novaPolozka_visibility(v) {
	 if (v=="hide") {
		 $( "input[name='NOVA_POLOZKA']" ).closest( "div[class='form-row']" ).css( "display", "none" );
		 $( "select[name='DATOVY_TYP']" ).closest( "div[class='form-row']" ).css( "display", "none" );
	 }	else {
		 $( "input[name='NOVA_POLOZKA']" ).closest( "div[class='form-row']" ).css( "display", "block" );
		 $( "select[name='DATOVY_TYP']" ).closest( "div[class='form-row']" ).css( "display", "block" );
	 }	
	
}


function WorkflowChange(vysledek)
{
	var workflow = $("[name='ID_WORKFLOW']").val();

	//zmena dat
	if (workflow==1) {
		zmenaDat_visibility("show");
		schvalovaciProces_visibility("hide");
		novaPolozka_visibility("hide");	
		var dokument = $("[name='DOKUMENT']").val();
		newwindow = window.open('<?php echo GetAgendaPath('POSTA',false,true);?>/plugins/workflow/get_promenna.php?WORKFLOW='+workflow+'&DOKUMENT='+dokument+'&vysledek='+vysledek,'ifrm_get_value2','height=600px,width=600px,left=1,top=1,scrollbars,resizable');
  	newwindow.focus();
	}

	//založ schvalovací proces
	if (workflow==2) {
		zmenaDat_visibility("hide");
		schvalovaciProces_visibility("show");
		novaPolozka_visibility("hide");
	}

	//nová položka formuláře
	if (workflow==3) {
		zmenaDat_visibility("hide");
		schvalovaciProces_visibility("hide");
		novaPolozka_visibility("show");
	}
	
}

function promennaChange(promenna,select_array) {
	var value = select_array[promenna.value];
	newwindow = window.open('<?php echo GetAgendaPath('POSTA',false,true);?>/plugins/workflow/get_element_hodnota.php?ofselect='+value+'&select_array='+select_array,'ifrm_get_value2','height=600px,width=600px,left=1,top=1,scrollbars,resizable');
  newwindow.focus();	
}
</script>