<?php
require_once(FileUpUrl('.admin/form_js_global.inc'));

$path = addslashes (FileUpUrl('duplicita.php'));

$validSkartacniRezim = "
    var url = '".$path."?&SKAR_ZNAK='+document.forms[0].SKAR_ZNAK.value+'&SKAR_LHUTA='+document.forms[0].SKAR_LHUTA.value;
    var ajx = getAjax(url, null, null, false);
    if (ajx.responseText == 'neni cislo') {
      alert('Skartační lhůta musí být celé číslo.');
      document.forms[0].SKAR_LHUTA.value='';
      return false;
    }
    if (ajx.responseText != '0') {
      alert('Záznam s tímto skartačním znakem a skartační lhůtou je již zadán. Nelze zadat znovu stejný záznam.');
      return false;
    }
        
    return(true);    ";

$isEdit = In_Array($form_params['formtype'], array($f_edit));
$isInfo = In_Array($form_params['formtype'], array($f_info));
$isInsert = In_Array($form_params['formtype'], array($f_insert));

$FORM_CONFIG["schema"][] = array( "elements"=>array(
  array( "type"=>"text", "name"=>"JID", "frozen" => true)),
  "visible" => $isEdit || $isInfo,
  "label" =>"JID:");

$FORM_CONFIG["schema"][] = array( "elements"=>array(
  array( "type"=>"text", "name"=>"SKAR_ZNAK")),
  "label"=>"Skartační znak:");

$FORM_CONFIG["schema"][] = array( "elements"=>array(
  array( "type"=>"text", "name"=>"SKAR_LHUTA")),
  "label"=>"Skartační lhůta:");

  $FORM_CONFIG["schema"][] = array("elements"=>array(
    array("type"=>"valid_fce","name_fce"=>$validSkartacniRezim)),
    "visible"=>$isInsert,
  );
                          
?>
