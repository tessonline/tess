<?php
  $fce_decin_znak = "
  if (document.forms[0].DATUM_VYRIZENI.value && (!document.forms[0].SKARTACE.value || !document.forms[0].VYRIZENO.value)) {
    alert('Při zadání datumu vyřízení je nutné vyplnit spisový znak a způsob vyřízení!');
    return(false);
  }
  ";

  $fce_zpracovatel_interni = "
  if (document.forms[0].ODESL_PRAC2.value) {
    document.forms[0].ODESL_PRAC2.value = '';
  }
  ";


  $FORM_CONFIG["schema"][] = array("elements"=>array(
     array("type"=>"valid_fce","name_fce"=>$fce_decin_znak)),
        "visible"=>$is_edit && ($GLOBALS['ODESLANA_POSTA']=='f'),
     );

  $FORM_CONFIG["schema"][] = array("elements"=>array(
     array("type"=>"valid_fce","name_fce"=>$fce_zpracovatel_interni)),
        "visible"=>($is_new || $is_insert) && ($GLOBALS['ODESLANA_POSTA']=='t'),
     );

