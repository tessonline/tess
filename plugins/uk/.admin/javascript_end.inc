<script language="JavaScript" type="text/javascript">
<!--

function DruhAdresataWhoIS(val) {
  $( "input[name='WHOIS_NUMBER']" ).closest( "div[class='form-row']" ).css( "display", "none" );
  DruhAdresata(val);

  if (val == 'C') {
    DruhAdresata('O');
    $( "input[name='WHOIS_NUMBER']" ).closest( "div[class='form-row']" ).css( "display", "block" );
    $( "input[name='WHOIS_IDSTUDIA']" ).closest( "div[class='form-item']" ).css( "display", "block" );
  }
  if (val == 'G') {
    DruhAdresata('O');
    $( "input[name='WHOIS_NUMBER']" ).closest( "div[class='form-row']" ).css( "display", "block" );
    $( "input[name='WHOIS_IDSTUDIA']" ).closest( "div[class='form-item']" ).css( "display", "none" );
  }
	
  if (val=='S') {
	  	$( "select[name='VNITRNI_ADRESATI_SKUPINY']").closest( "div[class='form-row']" ).css( "display", "block" );
    	$( "select[name^='ORGANIZACNI_VYBOR']").closest( "div[class='form-row']" ).css( "display", "block" );
  		
  } else {
	  	$( "select[name='VNITRNI_ADRESATI_SKUPINY']").closest( "div[class='form-row']" ).css( "display", "none" );
    	$( "select[name^='ORGANIZACNI_VYBOR']").closest( "div[class='form-row']" ).css( "display", "none" );
	}

  $( "select[name='ODESL_PRAC2']").closest( "div[class='form-item']" ).css( "display", "none" );
	
	$( "#select2-ODESL_ODBOR-container").closest( "div[class='form-item']" ).css( "display", "none" );
  
}

//    $( "input[name='ODESL_PRIJMENI']" ).closest( "div[class='form-row']" ).css( "display", "none" );


function GuideWHOIS() {
  var f=document.forms[0];
  if ((f.ODESL_PRIJMENI.value && f.ODESL_JMENO.value) || f.WHOIS_NUMBER.value || f.WHOIS_IDSTUDIA.value){
    url = 'G_NAME=posta_plugins_uk_whois&Ident='+f.WHOIS_NUMBER.value+'&StudID='+f.WHOIS_IDSTUDIA.value+'&jmeno='+f.ODESL_JMENO.value+'&prijmeni='+f.ODESL_PRIJMENI.value+'&typ='+f.ODES_TYP.value;
    NewWindowGuide('/ost/posta/plugins/uk/guide.php?'+url);
  }else
    alert("Zadejte jméno a příjmení nebo WhoIS číslo nebo ID studia pro dohledání!");
}

function TypovySpisWHOIS() {
  var f=document.forms[0];
    url = 'G_NAME=posta_plugins_typovySpisWhoIS&Ident='+f.WHOIS_NUMBER.value+'&IDstudia='+f.WHOIS_IDSTUDIA.value+'&typ='+f.ODES_TYP.value+'&skartace='+f.SKARTACE.value;
    NewWindowGuide('/ost/posta/plugins/uk/guide.php?'+url);
}

$( "input[name='WHOIS_NUMBER']" ).closest( "div[class='form-row']" ).css( "display", "block" );



//-->
</script>