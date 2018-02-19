<?php

  $fce_ruk="
  if (document.forms[0].EXTERNI_CK.value) {

    var str=document.forms[0].EXTERNI_CK.value;
    var re1=/(\d+)\s(\w+)/;
    var re1=/UKRUK\d{10}/;
    var result1=re1.test(str); //vrací: true
    if (result1) return true;
    else {
      alert('PID není zadán korektně. Správný tvar je UKRUKNNNNNNNNNN (=UKRUK a 10 číslic)');
      return false;
    }
  }
  ";
  $fce_ruk_znak = "
  if (document.forms[0].DATUM_PODATELNA_PRIJETI.value && !document.forms[0].SKARTACE.value) {
    alert('Při zadání datumu odeslání je nutné vyplnit spisový znak!');
    return(false);
  }
  if (document.forms[0].ODESL_EMAIL.value) {
    var email = document.forms[0].ODESL_EMAIL;
    var filter = /^[a-zA-Z0-9.!#$%&'*+/=?^_`{|}~-]+@[a-zA-Z0-9](?:[a-zA-Z0-9-]{0,61}[a-zA-Z0-9])?(?:\.[a-zA-Z0-9](?:[a-zA-Z0-9-]{0,61}[a-zA-Z0-9])?)*$/;

    if (!filter.test(email.value)) {
      alert('Email není zadán ve správném tvaru!');
      document.forms[0].ODESL_PRIJMENI.focus();
      return(false);
    }
  }
  ";

  $fce_ruk_adresat = "
  var val = document.forms[0].ODES_TYP.value;
  if(val=='P' && !document.forms[0].ODESL_PRIJMENI_FIRMA.value)   {
    alert('Při zadání právnické osoby je nutné zadat název firmy!');
    document.forms[0].ODESL_PRIJMENI_FIRMA.focus();
    return(false);
  }
  if(val=='U' && !document.forms[0].ODESL_PRIJMENI_FIRMA.value)   {
    alert('Při zadání orgánu veřejné moci je nutné zadat její název!');
    document.forms[0].ODESL_PRIJMENI_FIRMA.focus();
    return(false);
  }

  if(val=='O' && (!document.forms[0].ODESL_PRIJMENI.value || !document.forms[0].ODESL_JMENO.value))   {
    alert('Při zadání fyzické osoby je nutné zadat její příjmení a jméno!');
    document.forms[0].ODESL_PRIJMENI.focus();
    return(false);
  }

  if(val=='F' && (!document.forms[0].ODESL_PRIJMENI.value || !document.forms[0].ODESL_JMENO.value))   {
    alert('Při zadání podnikající fyzické osoby je nutné zadat její příjmení a jméno!');
    document.forms[0].ODESL_PRIJMENI.focus();
    return(false);
  }

  if((val=='N' || val=='B' || val=='E' || val=='T' || val=='D') && (!document.forms[0].ODESL_PRIJMENI.value || !document.forms[0].ODESL_JMENO.value))   {
    alert('Je nutné zadat její příjmení a jméno osoby!');
    document.forms[0].ODESL_PRIJMENI.focus();
    return(false);
  }


  ";

  //varovani pro rejst. cislo
  $FORM_CONFIG["schema"][] = array("elements"=>array(
     array("type"=>"valid_fce","name_fce"=>$fce_ruk)),
        "visible"=>!$is_multiedit && ($GLOBALS['ODESLANA_POSTA']=='t' || $is_new || $is_insert),
     );


  $FORM_CONFIG["schema"][] = array("elements"=>array(
     array("type"=>"valid_fce","name_fce"=>$fce_ruk_znak)),
        "visible"=>!$is_multiedit && ($GLOBALS['ODESLANA_POSTA']=='t'),
     );

  $FORM_CONFIG["schema"][] = array("elements"=>array(
     array("type"=>"valid_fce","name_fce"=>$fce_ruk_adresat)),
        "visible"=>!$is_multiedit,
     );


